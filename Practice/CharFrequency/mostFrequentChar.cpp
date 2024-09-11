/* 
    Abdullah
    Description:    "Write a function, mostFrequentChar, that takes in a string as an argument.
                    The function should return the most frequent character of the string. 
                    If there are ties, return the character that appears earlier in the string.
                    You can assume that the input string is non-empty."
    DATE: 10/9/24
*/
#include <iostream>
#include <string>
#include <unordered_map>

using namespace::std;

char most_frequent_char(string s) {
    // Create a hash map saving the counts of characters
    unordered_map<char, int> count;
    for (char c : s)
        count[c]++;

    // Iterate through the hash map and find the highest frequency lowest index character
    char best = '\0';
    for (char c : s)
        if (count[c] > count[best]) best = c; // use "<=" sign if you want the greatest index one

    // Return the lowest index maximum frequency character
    return best;
}

int main() {
    // Testing
    string s1 = "accellerate";

    cout << "Most Frequent lowest index Character: " << most_frequent_char(s1) << endl;
}
