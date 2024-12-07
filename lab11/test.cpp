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

    int size() {
        return heap.size() - 1;
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

HuffmanNode* build_huffman_tree(MinHeap& min_heap) {
    while (min_heap.size() > 2) {
        auto left = min_heap.top();
        min_heap.pop();
        auto right = min_heap.top();
        min_heap.pop();

        // Merge two smallest nodes
        HuffmanNode* left_node = new HuffmanNode(left.second, left.first);
        HuffmanNode* right_node = new HuffmanNode(right.second, right.first);

        HuffmanNode* merged = new HuffmanNode('\0', left.first + right.first);
        merged->left = left_node;
        merged->right = right_node;

        min_heap.push({merged->frequency, '\0'});
    }

    // Final root node
    return new HuffmanNode('\0', min_heap.top().first);
}

int main() {
    string input;
    cout << "Enter a string: ";
    getline(cin, input);

    // Step 2: Frequency table
    unordered_map<char, int> frequency_table;
    for (char c : input) {
        frequency_table[c]++; // {character, frequency}
    }

    // Step 3: Use custom MinHeap to build Huffman Tree
    MinHeap min_heap;
    for (const auto& pair : frequency_table) {
        min_heap.push({pair.second, pair.first}); // {frequency, character}
    }

    unordered_map<char, HuffmanNode*> nodes;
    for (const auto& pair : frequency_table) {
        nodes[pair.first] = new HuffmanNode(pair.first, pair.second); // nodes[char] = {character, frequency}
    }

    while (min_heap.size() > 1) { // Fix: Stop when only one node is left in the heap
        auto left = min_heap.top();
        min_heap.pop();
        auto right = min_heap.top();
        min_heap.pop();

        HuffmanNode* left_node = nodes[left.second];
        HuffmanNode* right_node = nodes[right.second];

        // Merge nodes
        HuffmanNode* merged = new HuffmanNode('\0', left.first + right.first);
        merged->left = left_node;
        merged->right = right_node;

        // Push merged node back into the heap
        min_heap.push({merged->frequency, '\0'});

        // Store the merged node separately
        nodes['\0'] = merged; // Avoid overwriting other nodes
    }

    // Final root of the Huffman Tree
    HuffmanNode* root = nodes['\0']; // Fix: Root is guaranteed to be the last merged node

    // Step 4: Generate Huffman Codes
    unordered_map<char, string> huffman_codes;
    generate_codes(root, "", huffman_codes);

    // Output the table
    cout << "\nCharacter | Frequency | Huffman Code\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    for (const auto& pair : huffman_codes) {
        cout << "    " << pair.first << "        " << frequency_table[pair.first] << "          " << pair.second << "\n";
    }

    return 0;
}

int main_1() {
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
    for (const auto& pair : frequency_table) {
        min_heap.push({pair.second, pair.first});
    }

    unordered_map<char, HuffmanNode*> nodes;
    for (const auto& pair : frequency_table) {
        nodes[pair.first] = new HuffmanNode(pair.first, pair.second);
    }

    HuffmanNode* root = nullptr; // Correct root node tracking
    while (min_heap.size() > 1) { // Fix: Stop at a single root node
        auto left = min_heap.top();
        min_heap.pop();
        auto right = min_heap.top();
        min_heap.pop();

        HuffmanNode* left_node = nodes[left.second];
        HuffmanNode* right_node = nodes[right.second];

        HuffmanNode* merged = new HuffmanNode('\0', left.first + right.first);
        merged->left = left_node;
        merged->right = right_node;

        root = merged; // Update root
        min_heap.push({merged->frequency, '\0'});
    }

    // Step 4: Generate Huffman Codes
    unordered_map<char, string> huffman_codes;
    generate_codes(root, "", huffman_codes);

    // Output the table
    cout << "\nCharacter | Frequency | Huffman Code\n";
    cout << "---------------------------------\n";
    for (const auto& pair : frequency_table) {
        cout << "    " << pair.first << "        " << pair.second << "          " << huffman_codes[pair.first] << "\n";
    }

    return 0;
}

