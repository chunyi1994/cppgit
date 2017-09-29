#include "commit.h"

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


} //namespace
