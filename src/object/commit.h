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

    static Error Parse(const std::string& raw, Signature *s);
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
    void AddParent(git::Hash hash);

    void SetHash(git::Hash hash);
    Error ComputeHash();

    const git::Hash& Hash() const;
    const git::Hash& Tree() const;
    const Signature& Author() const;
    const Signature& Committer() const;
    const std::string& Message() const;
    const std::vector<git::Hash>& Parents() const;

    static Error Parse(const std::string& raw, Commit* commit);

public:

private:
    git::Hash hash_;
    git::Hash tree_;
    std::vector<git::Hash> parents_;
    Signature author_;
    Signature committer_;
    std::string msg_;
};


} // namespace

#endif // COMMIT_H
