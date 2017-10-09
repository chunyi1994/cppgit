#ifndef TREE_TEST_H
#define TREE_TEST_H

#include <iostream>
#include "tree.h"
using namespace git;
using namespace std;
namespace test {


int test_tree_get(void) {
    Tree t;
    t.Set("eihei", Hash{"faa"}, Mode{Mode::folder});
    auto entry = t.Get("eihei");
    if (!entry) {
        cout <<"failed";
    } else {
        cout <<"ok";
    }
    cout<<endl;


    auto entry2 = t.Get("notfound");
    if (!entry2) {
        cout <<"ok";
    } else {
        cout <<"failed";
    }
    cout<<endl;
    return 0;
}

void test_tree_string() {
    Tree t;
    t.Set(".mmmmm.txt", Hash{"0a433596d18ea5fea25fefd29ac4ef00d41f9fd6"}, Mode{100644});
    t.Set("rahaha.txt", Hash{"0a433596d18ea5fea25fefd29ac4ef00d41f9fd6"}, Mode{100777});
    cout << t.String() << endl;
}

void test_tree_parse(void) {
    Tree t;
    char raw[] = "40000 hello.txt\00001234567890123456789100644 hhh.txt\00001234567890123456789";
    std::string content(raw, sizeof(raw) - 1);
    auto err = Tree::Parse(content, &t);
    if (!err.Ok()) {
        cout << err.String() << endl;
    }
    auto entry = t.Get("hello.txt");
    if (entry) {
        std::cout << entry->Filename()<<" " << entry->Hash().Hex()<<" " << entry->Mode().String()<<std::endl;
    }

    entry = t.Get("hhh.txt");
    if (entry) {
        std::cout << entry->Filename()<<" " << entry->Hash().Hex()<<" " << entry->Mode().String();
    }
}


}


#endif // TREE_TEST_H
