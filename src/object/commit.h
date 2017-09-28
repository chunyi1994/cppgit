#ifndef COMMIT_H
#define COMMIT_H
#include <string>
#include <vector>
#include <sstream>
#include <experimental/optional>


#include "../errors/errors.h"
#include "../utils/times.h"
#include "hash.h"
#include "object.h"

namespace git {


class Signature {
public:
    Signature():
        name_(), email_(), time_(){}

    Signature(std::string name, std::string email, git::Time time) :
        name_(std::move(name)),
        email_(std::move(email)),
        time_(std::move(time)) {}

    const std::string& Name() const {return name_;}
    const std::string& Email() const {return email_;}
    const git::Time Time() const {return time_;}
private:
    std::string name_;
    std::string email_;
    git::Time time_;
};

class Commit {
public:
    using Opt = std::experimental::optional<Commit>;

public:
    Commit();

public:
    std::string String() const;

    void SetTree(git::Hash tree);
    void SetAuthor(Signature author);
    void SetCommitter(Signature committer);
    void SetMessage(std::string msg);
    void AddParent(Hash hash);

    void SetHash(git::Hash hash);
    Error ComputeHash();


    const git::Hash& Hash() const;
    const git::Hash& Tree() const;
    const Signature& Author() const;
    const Signature& Committer() const;
    const std::string& Message() const;

public:
    static std::pair<Commit::Opt, Error>
    New(const char *content, std::size_t len);

    static std::pair<Commit::Opt, Error>
    New(const std::string& content);

private:
    git::Hash hash_;
    git::Hash tree_;
    std::vector<git::Hash> parents_;
    Signature author_;
    Signature committer_;
    std::string msg_;
};

inline Commit::Commit():
    hash_(),
    tree_(),
    parents_(),
    author_(),
    committer_(),
    msg_()
{}

inline void Commit::SetHash(git::Hash hash) {
    hash_ = std::move(hash);
}

inline Error Commit::ComputeHash() {
    auto str = String();
    std::string hash;
    if (auto e = Object::Sha1Hash(str, &hash); !e.Ok()) {
        return e;
    }
    hash_ = git::Hash{hash};
    return Error::Success();
}

inline void Commit::SetTree(git::Hash tree) {
    tree_ = std::move(tree);
}

inline void Commit::SetAuthor(Signature author) {
    author_ = std::move(author);
}

inline void Commit::SetCommitter(Signature committer) {
    committer_ = std::move(committer);
}

inline void Commit::SetMessage(std::string msg) {
    msg_ = std::move(msg);
}

inline void Commit::AddParent(git::Hash hash) {
    parents_.push_back(std::move(hash));
}

inline const git::Hash &Commit::Hash() const {
    return hash_;
}

inline const git::Hash &Commit::Tree() const {
    return tree_;
}

inline const Signature &Commit::Author() const {
    return author_;
}

inline const Signature &Commit::Committer() const {
    return committer_;
}

const std::string &Commit::Message() const {
    return msg_;
}



inline std::string Commit::String() const {
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




} // namespace

#endif // COMMIT_H
