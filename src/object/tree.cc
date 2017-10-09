#include "tree.h"

#include <iostream>
#include <vector>
#include <sstream>

#include "../utils/strings.h"

namespace git {

Tree::Tree():
    entries_()
{

}

Tree::Iterator Tree::end() {
    return entries_.end();
}

Tree::Iterator Tree::begin() {
    return entries_.begin();
}

Tree::ConstIterator Tree::end() const {
    return entries_.end();
}

Tree::ConstIterator Tree::begin() const {
    return entries_.begin();
}

Tree::ConstIterator Tree::cend() const {
    return entries_.cend();
}

Tree::ConstIterator Tree::cbegin() const {
    return entries_.cbegin();
}

void Tree::Set(std::string filename, Hash hash, Mode mode) {
    entries_[filename] = TreeEntry{
            std::move(filename),
            std::move(hash),
            std::move(mode)};
}

bool Tree::Contains(const std::string &filename) const {
    auto iter = entries_.find(filename);
    return iter != entries_.end();
}

std::experimental::optional<TreeEntry>
Tree::Get(const std::string &filename) {
    Iterator iter = entries_.find(filename);
    if (iter == entries_.end()) {
        return std::experimental::optional<TreeEntry>{};
    }
    return std::experimental::optional<TreeEntry>{iter->second};
}

std::string Tree::String() const {
    std::stringstream ss;
    std::vector<std::string> filenames;
    filenames.reserve(entries_.size());
    for (const auto& pair : entries_) {
        filenames.push_back(pair.first);
    }
    std::sort(filenames.begin(), filenames.end());
    for (const auto& filename : filenames) {
        auto iter = entries_.find(filename);
        const TreeEntry& entry = iter->second;
        ss << entry.Mode().String();
        ss << " ";
        ss << entry.Filename() << "\000";
        ss << entry.Hash().Digit();
    }
    return ss.str();
}

//40000 filename.txt\000XXXXXXXXXXXXXXXXXXXX
Error Tree::Parse(const std::string& raw, Tree *tree) {
    assert(tree != nullptr);
    if (raw.empty()) {
        return Error{"Tree::Parse: empty content"};
    }
    StringView view{raw};
    bool quit = false;
    while (!quit) {
        std::size_t pos = view.find('\0');
        if (pos == std::string::npos) {
            return Error{"Tree::Parse: bad content"};
        }
        auto left = view.substr(0, pos);
        std::size_t pos2 = left.find(' ');
        if (pos2 == std::string::npos) {
            return Error{"Tree::Parse: bad content"};
        }
        std::string mode_str;
        std::copy(left.begin(), left.begin()+pos2, std::back_inserter(mode_str));
        Mode mode{mode_str};
        if (mode.IsZero()) {
            return Error{"Tree::Parse: bad content"};
        }
        std::string filename;
        std::copy(left.begin()+pos2+1, left.end(), std::back_inserter(filename));

        std::string hash;
        auto start = view.begin()+pos+1;
        auto end = start;
        if (view.size() > 21 + pos) {
            end = view.begin() + pos + 21;
        } else {
            end = view.end();
            quit = true;
        }
        std::copy(start, end, std::back_inserter(hash));
        if (hash.length() != 20) {
            return Error{"Tree::Parse: bad content"};
        }
        tree->Set(filename, Hash{hash}, std::move(mode));
        if (!quit) {
            view = view.substr(pos + 21, view.length() - (pos + 21));
        }

    }
    return Error::Success();
}

bool operator==(uint32_t m, const Mode &mode) {
    return m == mode.mode_;
}

bool operator==(const Mode &mode, uint32_t m) {
    return m == mode.mode_;
}

Mode &Mode::operator=(uint32_t m) {
    mode_ = m;
    return *this;
}

TreeEntry::TreeEntry(std::string filename, git::Hash hash, git::Mode mode):
    filename_(std::move(filename)),
    hash_(std::move(hash)),
    mode_(std::move(mode))
{}


} // namespace
