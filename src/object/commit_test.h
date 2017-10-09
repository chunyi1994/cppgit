#ifndef COMMIT_TEST_H
#define COMMIT_TEST_H
#include "commit.h"
#include <iostream>
using namespace git;

namespace test {

void test_commit () {
    Commit commit{};
    commit.SetMessage("update readme.md");
    commit.AddParent(Hash{"f4a0a3c982fe9accc2423a631359a4cb8f67efcb"});
    auto now = Time::Now();
    commit.SetAuthor(Signature{"chunyi", "704613309@qq.com", now});
    commit.SetCommitter(Signature{"chunyi", "704613309@qq.com", now});
    commit.SetTree(Hash{"2ba1c1f3d023c01ee60abad056c1f72ec905235a"});
    commit.ComputeHash();
    cout << commit.String() << endl;
    cout << commit.Hash().Hex() << endl;
}

void test_commit_parse () {
    Commit commit{};
    const char raw[]= "tree f4a0a3c982fe9accc2423a631359a4cb8f67efcb\nparent 2ba1c1f3d023c01ee60abad056c1f72ec905235a\nauthor chun chun <sunfish.gao@email.com> 1502263703 +0800\ncommitter chun chun <sunfish.gao@email.com> 1502263703 +0800\n\nUpdate readme.md";
    std::string content{raw, sizeof(raw) - 1};
    auto err = Commit::Parse(content, &commit);
    if (!err.Ok()) {
        cout << err.String() << endl;
    }
    cout << "author: " << commit.Author().Email() << endl;
    cout << "author name: " << commit.Author().Name() << endl;
    cout << "author time: " << commit.Author().Time().IsZero() << endl;
    cout << "author time: " << commit.Author().Time().Unix() << endl;

    cout << "committer: " << commit.Committer().Email() << endl;
    cout << "hash: " << commit.Hash().Hex() << endl;
    cout << "tree: " << commit.Tree().Hex() << endl;
    cout << "parent: " << commit.Parents().at(0).Hex() << endl;
}

} // namespae
#endif // COMMIT_TEST_H
