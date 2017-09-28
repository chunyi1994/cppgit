#ifndef OBJECT_TEST_H
#define OBJECT_TEST_H
#include <iostream>
#include "object.h"
using namespace git;
using namespace std;
namespace test {

void test_object() {
    Object obj{Object::BLOB, "bobobobobo"};
    if (obj.Hash() != "e901062a030351d73218662f01366464d24fe344") {
        cout << "false" << endl;
        return;
    }
    cout << "true" << endl;
}



}

#endif // OBJECT_TEST_H
