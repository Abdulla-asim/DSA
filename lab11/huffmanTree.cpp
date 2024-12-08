#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <climits>
#include <math.h>

using namespace std;

unordered_map<char, int> frequency_table;
unordered_map<char, string> huffman_codes;

// Huffman Node structure
struct HuffmanNode {
    char character;
    int frequency;
    HuffmanNode *left, *right;

    HuffmanNode(char c, int freq) : character(c), frequency(freq), left(nullptr), right(nullptr) {}
};

class MinHeap {
    vector<pair<int, HuffmanNode*>> heap;

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
        heap.push_back({INT_MIN, nullptr}); // Dummy element at index 0
    }

    void push(pair<int, HuffmanNode*> x) {
        heap.push_back(x);
        sift_up(heap.size() - 1);
    }

    pair<int, HuffmanNode*> top() {
        return heap.size() > 1 ? heap[1] : make_pair(INT_MAX, nullptr);
    }

    void pop() {
        if (heap.size() <= 1) return;
        heap[1] = heap.back();
        heap.pop_back();
        sift_down(1);
    }

    int size() {
        return heap.size() - 1; // Exclude dummy element
    }

    bool is_empty() {
        return size() <= 1;
    }
};

// Function to generate the Huffman Codes
void generate_codes(HuffmanNode* root, const string& code, unordered_map<char, string>& huffman_codes) {
    if (!root) return;

    // Leaf node
    if (!root->left && !root->right) {
        huffman_codes[root->character] = code;
        return;
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

// Generated huffman codes for the input string
HuffmanNode* task_1(string input) {

    // Step 2: Frequency table
    for (char c : input) {
        frequency_table[c]++;
    }

    // Step 3: Use custom MinHeap to build Huffman Tree
    MinHeap min_heap;
    for (const auto& pair : frequency_table) {
        HuffmanNode* node = new HuffmanNode(pair.first, pair.second);
        min_heap.push({pair.second, node});
    }

    // Build Huffman Tree
    while (min_heap.size() > 1) {
        auto left = min_heap.top();
        min_heap.pop();
        auto right = min_heap.top();
        min_heap.pop();

        HuffmanNode* merged = new HuffmanNode('\0', left.first + right.first);
        merged->left = left.second;
        merged->right = right.second;

        min_heap.push({merged->frequency, merged});
    }

    // Root of the Huffman Tree
    HuffmanNode* root = min_heap.top().second;

    // Step 4: Generate Huffman Codes
    generate_codes(root, "", huffman_codes);

    // Output the table
    cout << "\nCharacter | Frequency | Huffman Code\n";
    cout << "---------------------------------\n";
    for (const auto& pair : frequency_table) {
        cout << "    " << pair.first << "        " << pair.second << "          " << huffman_codes[pair.first] << "\n";
    }

    return root;
}

// Encodes and then decodes the input string
void task_2(string input) {

    HuffmanNode *root = task_1(input);

    // Encode the input string
    string encoded_string = encode_string(input, huffman_codes);

    // Decode the string
    string decoded_string = decode_string(root, encoded_string);

    cout << "\nOriginal String: " << input << "\n";
    cout << "Encoded String: " << encoded_string << "\n";
    cout << "Decoded String: " << decoded_string << "\n";

}

void task_3(string input) {

    // Generate huffman codes
    task_1(input);

    // Calculate original and compressed sizes
    int original_size_bits = input.size() * 8; // ASCII encoding (8 bits per char)
    int compressed_size_bits = 0;

    for (const auto& pair : frequency_table) {
        compressed_size_bits += frequency_table[pair.first] * huffman_codes[pair.first].length();
    }

    double compression_ratio = (double)original_size_bits / compressed_size_bits;

    // Print results
    cout << "\nOriginal Size (bits): " << original_size_bits;
    cout << "\nCompressed Size (bits): " << compressed_size_bits;
    cout << "\nCompression Ratio: " << compression_ratio << "\n";

}

int main() {

    cout << "LAB 11 TASKS:\n";
    cout << "~~~~~~~~~~~~~\n";
    cout << "Task 1: Huffman Tree Constructino\n";
    cout << "Task 2: Huffman Encoding and Decoding\n";
    cout << "Task 3: Compression Analysis\n";
    cout << "Enter the task number: ";
    int task;
    cin >> task;
    cin.ignore();
    cout << "~~~~~~~~~~~~~\n";

    string input;
    cout << "Enter a string: ";
    getline(cin, input);

    if (task == 1) task_1(input);
    else if (task == 2) task_2(input);
    else if (task == 3) {
        cout << "Task 3: Compression Analysis and Extensions\n";
        cout << "Select input type:\n";
        cout << "1. Custom Input\n";
        cout << "2. Uniform Distribution (e.g., 'abcdef')\n";
        cout << "3. Realistic Paragraph\n";

        int input_type;
        cin >> input_type;
        cin.ignore();

        if (input_type == 2) input = "aaaaaa";
        else if (input_type == 3) input = "abcdef";
        else if (input_type == 4) input = "Huffman coding is a data compression algorithm.";
        else if (input_type != 1) {
            cout << "Invalid input type\n";
            return 0;
        }

        if (input_type == 1) {
            cout << "Enter your string: ";
            getline(cin, input);
        }

        task_3(input);
    }
    else cout << "Invalid task number\n";

    return 0;
}