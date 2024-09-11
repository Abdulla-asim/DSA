#include<iostream>

using namespace::std;

int main() {
    int a, *pa;

    pa = &a;

    // Multiplying a pointer is not supported.
    // Does not compile.
    cout << " pa = " << pa << ", pa * 2 = " << (pa*2) << endl;
}