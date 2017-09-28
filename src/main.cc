
#include <zlib.h>
#include <iostream>
#include "object/zlibs.h"
using namespace std;
using namespace git;
int main()

{
    if (int a = 0; a > -1) {
        cout <<"aaa";
    }
    ZlibCompressor z{"fdafa"};
    int a = compressBound(2);
    cout << a<< endl;

    return 0;

}




