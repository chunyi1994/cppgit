#include <iostream>
#include <ctime>
#include <vector>
#include "utils/buffer.h"
#include "object/zlibs.h"
using namespace std;
using namespace git;
int main(void)
{

    const unsigned char data[5] = {'h','e','l','l','o'};
    ZlibCompressor z{data, 5};

    std::vector<unsigned char> buffer(100, 'a');
    int n;
    n = z.Read(buffer.data(), 100);
    cout << n << endl;




    for (int i = 0; i < 30; i++) {
        cout <<(int) (unsigned char)buffer[i] << " " ;
    }

    return 0;
}


