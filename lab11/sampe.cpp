#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <climits>
#include <math.h>

using namespace std;

class MinHeap {
    vector<pair<int, char>> heap;

    int left_child(int i) {
        return 2 * i;
    }

    int right_child(int i) {
        return 2 * i + 1;
    }

    int parent(int i) {
        return i / 2;
    }

    void sift_up(int i) {
        while (i > 1 && heap[parent(i)].first > heap[i].first) {
            swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
    }

    void sift_down(int i) {
        int smallest = i;
        int l = left_child(i);
        int r = right_child(i);
        if (l < heap.size() && heap[l].first < heap[smallest].first) {
            smallest = l;
        }
        if (r < heap.size() && heap[r].first < heap[smallest].first) {
            smallest = r;
        }
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            sift_down(smallest);
        }
    }

public:
    MinHeap() {
        heap.push_back({INT_MIN, '\0'}); // Dummy element at index 0
    }

    void push(pair<int, char> x) {
        heap.push_back(x);
        sift_up(heap.size() - 1);
    }

    pair<int, char> top() {
        return heap.size() > 1 ? heap[1] : make_pair(INT_MAX, '\0');
    }

    void pop() {
        if (heap.size() <= 1) return;
        heap[1] = heap.back();
        heap.pop_back();
        sift_down(1);
    }

    bool is_empty() {
        return heap.size() <= 1;
    }
};

// Huffman Node structure
struct HuffmanNode {
    char character;
    int frequency;
    HuffmanNode *left, *right;

    HuffmanNode(char c, int freq) : character(c), frequency(freq), left(nullptr), right(nullptr) {}
};

// Function to generate the Huffman Codes
void generate_codes(HuffmanNode* root, const string& code, unordered_map<char, string>& huffman_codes) {
    if (!root) return;

    // Leaf node
    if (!root->left && !root->right) {
        huffman_codes[root->character] = code;
    }

    generate_codes(root->left, code + "0", huffman_codes);
    generate_codes(root->right, code + "1", huffman_codes);
}

// Function to decode the encoded string back to original string
string decode_string(HuffmanNode* root, const string& encoded_string) {
    string decoded_string;
    HuffmanNode* current = root;
    for (char bit : encoded_string) {
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        }

        // If a leaf node is reached
        if (!current->left && !current->right) {
            decoded_string += current->character;
            current = root; // Reset back to root for the next sequence
        }
    }
    return decoded_string;
}

// Function to encode the string
string encode_string(const string& input, const unordered_map<char, string>& huffman_codes) {
    string encoded_string;
    for (char c : input) {
        encoded_string += huffman_codes.at(c);
    }
    return encoded_string;
}

int main() {
    string input;
    cout << "Enter a string: ";
    getline(cin, input);

    // Step 2: Frequency table
    unordered_map<char, int> frequency_table;
    for (char c : input) {
        frequency_table[c]++;
    }

    // Step 3: Use custom MinHeap to build Huffman Tree
    MinHeap min_heap;
    unordered_map<char, HuffmanNode*> nodes;
    for (const auto& pair : frequency_table) {
        nodes[pair.first] = new HuffmanNode(pair.first, pair.second);
        min_heap.push({pair.second, pair.first});
    }

    while (min_heap.size() > 1) {
        auto left = min_heap.top();
        min_heap.pop();
        auto right = min_heap.top();
        min_heap.pop();

        HuffmanNode* left_node = nodes[left.second];
        HuffmanNode* right_node = nodes[right.second];

        HuffmanNode* merged = new HuffmanNode('\0', left.first + right.first);
        merged->left = left_node;
        merged->right = right_node;

        nodes['\0'] = merged;
        min_heap.push({merged->frequency, '\0'});
    }

    // Root of the Huffman Tree
    HuffmanNode* root = nodes['\0'];

    // Step 4: Generate Huffman Codes
    unordered_map<char, string> huffman_codes;
    generate_codes(root, "", huffman_codes);

    // Encode the input string
    string encoded_string = encode_string(input, huffman_codes);

    // Decode the string
    string decoded_string = decode_string(root, encoded_string);

    // Output
    cout << "\nCharacter | Frequency | Huffman Code\n";
    cout << "---------------------------------\n";
    for (const auto& pair : huffman_codes) {
        cout << "    " << pair.first << "        " << frequency_table[pair.first] << "          " << pair.second << "\n";
    }

    cout << "\nOriginal String: " << input << "\n";
    cout << "Encoded String: " << encoded_string << "\n";
    cout << "Decoded String: " << decoded_string << "\n";

    return 0;
}
