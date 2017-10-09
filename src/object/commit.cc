#include "commit.h"

#include <sstream>
#include <string>
#include <vector>
#include <experimental/string_view>
#include <iostream>

#include "../utils/strings.h"

namespace git {

Commit::Commit():
    hash_(),
    tree_(),
    parents_(),
    author_(),
    committer_(),
    msg_()
{}

void Commit::SetHash(git::Hash hash) {
    hash_ = std::move(hash);
}

Error Commit::ComputeHash() {
    auto str = String();
    std::string hash;
    if (auto e = Object::Sha1Hash(str, &hash); !e.Ok()) {
        return e;
    }
    hash_ = git::Hash{hash};
    return Error::Success();
}

void Commit::SetTree(git::Hash tree) {
    tree_ = std::move(tree);
}

void Commit::SetAuthor(Signature author) {
    author_ = std::move(author);
}

void Commit::SetCommitter(Signature committer) {
    committer_ = std::move(committer);
}

void Commit::SetMessage(std::string msg) {
    msg_ = std::move(msg);
}

void Commit::AddParent(git::Hash hash) {
    parents_.push_back(std::move(hash));
}

const git::Hash &Commit::Hash() const {
    return hash_;
}

const git::Hash &Commit::Tree() const {
    return tree_;
}

const Signature &Commit::Author() const {
    return author_;
}

const Signature &Commit::Committer() const {
    return committer_;
}

const std::string &Commit::Message() const {
    return msg_;
}

const std::vector<Hash> &Commit::Parents() const {
    return parents_;
}

Error Commit::Parse(const std::string &raw, Commit *commit) {
    std::stringstream ss(raw);
    std::string line;
    while (std::getline(ss, line)) {
        if (HasPrefix(line, "author")) {
            Signature s;
            if (auto err = Signature::Parse(line, &s); !err.Ok()) {
                return err;
            }
            commit->author_ = s;
        } else if (HasPrefix(line, "committer")) {
            Signature s;
            if (auto err = Signature::Parse(line, &s); !err.Ok()) {
                return err;
            }
            commit->committer_ = s;
        } else if (HasPrefix(line, "parent")) {
            commit->AddParent(git::Hash{line.substr(sizeof("parent"), 40)});
        } else if (HasPrefix(line, "tree")) {
            commit->SetTree(git::Hash{line.substr(sizeof("tree"), 40)});
        } else if (line == "") {
            break;
        } else {
            return Error{"Commit::Parse: unexpected content"};
        }
    }
    commit->SetMessage(ss.str());
    std::string hash;
    if (Error err = Object::Sha1Hash(raw, &hash); !err.Ok()) {
        return err;
    }
    commit->SetHash(git::Hash{hash});
    return  Error::Success();
}

std::string Commit::String() const {
    std::stringstream ss;

    ss << "tree " << tree_.Hex() << "\n";

    for (const auto& parent : parents_) {
        ss << "parent " << parent.Hex() << "\n";
    }

    ss << "author " << author_.Name();
    ss << " <" << author_.Email() << "> ";
    ss << author_.Time().Unix() << " +0800" <<"\n";

    ss << "committer " << committer_.Name();
    ss << " <" << committer_.Email() << "> ";
    ss << committer_.Time().Unix() << " +0800" <<"\n";

    ss << "\n";
    ss << msg_;

    return ss.str();
}

// `committer chunchun g <chfun@gmaillll.com> 1503980267
Error Signature::Parse(const std::string &raw, Signature *s) {
    assert(s != nullptr);
    StringView type;
    if (HasPrefix(raw, "author")) {
        type = SubView(raw, 0, sizeof("author")-1);
    } else if (HasPrefix(raw, "committer")) {
        type = SubView(raw, 0, sizeof("committer")-1);
    }
    std::size_t left = raw.find('<');
    if (left == std::string::npos) {
        return Error{"Signature::Parse: bad content"};
    }
    std::size_t right = raw.find('>', left);
    if (right == std::string::npos) {
        return Error{"Signature::Parse: bad content"};
    }
    s->email_ = raw.substr(left + 1, right - left - 1);
    s->name_ = raw.substr(type.length()+1, left - type.length() - 2);

    left = right + 2;
    right = raw.find(" ", left);
    if (right == std::string::npos) {
        return Error{"Signature::Parse: bad content"};
    }
    int64_t unix = std::stoll(raw.substr(left, right - left));
    s->time_ = git::Time{unix};
    return Error::Success();
}


} //namespace
