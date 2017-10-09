#ifndef TREE_H
#define TREE_H

#include <map>
#include <string>
#include <experimental/optional>
#include "hash.h"
#include "../errors/errors.h"

namespace git {

class Mode {
public:
    Mode() : mode_(0) {}
    explicit Mode(uint32_t mode): mode_(mode) {}
    explicit Mode(const std::string& m): mode_(std::stoi(m)){}

    bool IsZero() const { return mode_ == 0;}

    std::string String() const { return std::to_string(mode_); }

    friend bool operator==(uint32_t m, const Mode& mode);

    friend bool operator==(const Mode& mode, uint32_t m);

    Mode& operator=(uint32_t m);

    static constexpr uint32_t folder = 40000;
    static constexpr uint32_t normal_file = 100644;

private:
    uint32_t mode_;
};

class TreeEntry {
public:
    TreeEntry(): filename_(), hash_(), mode_(){}
    TreeEntry(std::string filename, Hash hash, Mode mode);

    git::Mode Mode() const { return mode_; }
    git::Hash Hash() const { return hash_; }
    std::string Filename() const { return filename_; }
    // static Error Parse(const std::string &,TreeEntry* tree);
private:
    std::string filename_;
    git::Hash hash_;
    git::Mode mode_;
};

class Tree {
public:
    using Iterator = std::map<std::string, TreeEntry>::iterator;
    using ConstIterator = std::map<std::string, TreeEntry>::const_iterator;
public:
    Tree();

    Iterator end();
    Iterator begin();

    ConstIterator end() const;
    ConstIterator begin() const;

    ConstIterator cend() const;
    ConstIterator cbegin() const;

    void Set(std::string filename, Hash hash, Mode mode);
    bool Contains(const std::string& filename) const;

    std::experimental::optional<TreeEntry>
    Get(const std::string& filename);

    std::string String() const;

    static Error Parse(const std::string &,Tree* tree);

private:
    std::map<std::string, TreeEntry> entries_;
};

} // namespace

#endif // TREE_H
