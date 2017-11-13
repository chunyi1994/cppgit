#include <iostream>
#include <ctime>
#include <vector>
#include "utils/buffer.h"
#include "object/zlibs.h"
#include "object/tree.h"
#include "object/tree_test.h"
#include "object/commit_test.h"
#include "utils/strings.h"
#include <memory>
using namespace std;
using namespace git;
int main(void)
{
    test::test_tree_string();
    string str;
    vector<char> vec;
    shared_ptr<string> ptr = make_shared<string>("f");
    cout << "str:" << sizeof(str)<<endl;
    cout << "vec:" << sizeof(vec)<<endl;
    cout << "ptr:" << sizeof(ptr)<<endl;
    return 0;
}
