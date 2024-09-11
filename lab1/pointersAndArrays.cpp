#include <iostream>

using namespace::std;

int main () {

    int list[5] = {3,6,9,12,15};
    int *pArr = list;

    cout << "The elements of list are: ";

    // Iterate over the list using pArr and print the elements.
    for (int i = 0; i <= sizeof(list)/5; i++)
        cout << *(pArr + i) << " ";

    // New line
    cout << endl;
    return 0;
}