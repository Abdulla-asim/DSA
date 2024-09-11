/* 
    Abdullah
    program: "anagrams"
    DATE: 10/9/24
*/
#include <string>
#include <unordered_map>
#include <iostream>

using namespace::std;

unordered_map<char, int> charCount(string s);
bool anagrams(string a, string b);

int main() {
    // Test (True if the strings are anagrams)
    string s1 = "cat";
    string s2 = "tac";
    cout << s1 << " and " << s2 << " are aagrams: " << anagrams(s1, s2) << endl;

    return 0;
}

unordered_map<char, int> charCount(string s) {
    // Create a hash map for storing counts of characters
    unordered_map<char, int> count;

    // Store the count of each character(also key)
    for (char ch : s)
        count[ch]++;

    return count;
}

bool anagrams(string a, string b) {
    // return true if both hash maps are equal (same character counts)
    if (charCount(a) == charCount(b)) return true;

    return false;
}

