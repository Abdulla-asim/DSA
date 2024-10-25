#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Some helpful macros
#define visit(x)    printf("%d ", (x->data))
#define N           printf("\n")

// Class for Tree nodes
template <typename T>
class TreeNode {
    public:
        T data;
        TreeNode *left;
        TreeNode *right;

        TreeNode(T data) {
            this->data = data;
            this->left = nullptr;
            this->right = nullptr;
        }

        // Destructor
        ~TreeNode() {
            delete left;
            delete right;
        }
};

// Class for Binary search tree
template <typename T>
class BinarySearchTree {
    public:
        TreeNode<T> *root, *prev_location, *location;

        BinarySearchTree() {
            this->root = nullptr;
            this->prev_location = nullptr;
            this->location = nullptr;
        }

        ~BinarySearchTree() {
            delete root;
        }

        void insert(T value) {
            if (!root) { // if root is empty
                root = new TreeNode<T>(value);
                return;
            }
            else if (search(value)) { // search for value in the tree
                printf("Value alredy exists...\n");
                return;
            }

            if (value < prev_location->data) // if value is smaller than the current node
                prev_location->left = new TreeNode<T>(value); // insert in left node
            else
                prev_location->right = new TreeNode<T>(value); // insert in right node

            cout << "Inserted " << value << endl; 
            
            return;
        }

        // REMOVE LATER
        // Recursive Ordered Insertion without Search
        TreeNode<T> *my_insert(TreeNode<T> *node, T data) {
            if (node == nullptr) { // if emtpy root node
                return new TreeNode<T>(data);
            }
            else if (data < node->data) 
                node->left = insert(node->left, data);
            else
                node->right = insert(node->right, data);
            
            return node;
        }

        // Search Function
        bool search(T value) {
            // if root node is null pointer
            if (!root)
                return false; // location: null, prev_location: null

            location = root; // current location
            
            while(location) {
                if (value == location->data)
                    return true; // location: root, prev_location: null

                prev_location = location; // set previous location

                if (value < location->data) // if value is smaller than current location
                    location = location->left; // go to the left node
                else 
                    location = location->right; // else go to the right node
            }

            return false;
        }

        void delete_tree(TreeNode<T> *p) {
            delete_tree(p->left); // delete left subtree
            delete_tree(p->right); // delete right subtree
            delete p; // delete root
        }

        bool is_empty() {
            return root == nullptr; // check if root is null
        }

        void preorder(TreeNode<T> *node) {
            if (!node) {
                return;
            }
            // VLR
            visit(node);
            preorder(node->left); // go left node
            preorder(node->right); // go right node
        }

        void inorder(TreeNode<T> *node) {
            if (!node) { // if empty node
                return;
            }
            // LVR
            preorder(node->left);
            visit(node);
            preorder(node->right);
        }

        void postorder(TreeNode<T> *node) {
            if (!node) { // if empty node
                return;
            }
            // LRV
            preorder(node->left);
            preorder(node->right);
            visit(node);
        }

        TreeNode<T> *get_smallest() {
            if (!root) { // if no tree exits
                return nullptr;
            }

            TreeNode<T> *p = root; // point to the root
            while(p->left) { // loop until next to the left node is null
                /* Since this is a binary "search" tree, you do not need to check this condition but i included it
                for a more general code */
                if (p->left->data < p->data) // if data in left node is less than data in current node
                    p = p->left; // go to left node
            }

            return p;
        }

        TreeNode<T> *get_largest() {
            if (!root) { // if root is null
                return nullptr;
            }

            TreeNode<T> *p = root;
            // keep going right until you fing the largest value
            while(p->right) {
                if (p->right->data > p->data)
                    p = p->right;
            }

            return p;
        }

        void print_leaves_recursive(TreeNode<T> *p ) {
            if (!p) { // return if empty node
                return;
            }
            // LRV
            print_leaves_recursive(p->left);
            print_leaves_recursive(p->right);
            if (!(p->left) && !(p->right)) // if no left and right child
                visit(p); // print leaf
        }

        // Recursive
        int count_leaves_recursive(TreeNode<int> *p) {
            if (!p) // if null pointer
                return 0;

            if (p->left == nullptr && p->right == nullptr) // if not left and right childs
                return 1;
            
            // return sum of left and right leaves
            return count_leaves_recursive(p->left) + count_leaves_recursive(p->right); 
        }

        // Recursive
        int count_internal_nodes_recursive(TreeNode<int> *p) {
            if(!p || (p->left == nullptr && p->right == nullptr)) // return 0 if no childs
                return 0;

            // return sum of internal nodes + 1 for the root node
            return 1 + count_internal_nodes_recursive(p->left) + count_internal_nodes_recursive(p->right);
        }

        int height(TreeNode<int> *p) {
            if (!p) // for empty root
                return -1;

            int height_left = height(p->left); // traverse the left subtree
            int height_right = height(p->right); // traverse the right subtree
            
            // retunr the maximum length from the left and right subtrees + 1 for root
            return 1 + max(height_left, height_right);
        }

        int depth(TreeNode<int> *p, TreeNode<int> *target_node, int current_depth) {
            if (!p) // if empty tree
                return -1;

            if (p == target_node) { // if current node points to target
                return current_depth;
            }

            int depth_left = depth(p->left, target_node, current_depth+1); // traverse the left subtree
            if (depth_left != -1) { // if there was a left subtree
                return depth_left;
            }
           
            // in case there was no left subtree 
            return depth(p->right, target_node, current_depth+1);;
        }

        // Helper function to print the tree
        // generated and written by ChatGPT
        void printTree(TreeNode<T>* root, int space = 0, int indent = 6) {
            // Base case
            if (root == nullptr)
                return;

            // Increase distance between levels
            space += indent;

            // Process right child first
            printTree(root->right, space);

            // Print current node after space count
            cout << endl;
            cout << setw(space) << root->data << "\n";

            // Process left child
            printTree(root->left, space);
        }
};

int main () {
    int num;
    BinarySearchTree<int> *bst = new BinarySearchTree<int>();
    
    printf("Inserting...\n");
    bst->insert(9);
    bst->insert(6);
    bst->insert(11);
    bst->insert(10);
    bst->insert(15);
    bst->insert(7);
    bst->insert(5);

    bst->printTree(bst->root);

    printf("\nPreorder\n");
    bst->preorder(bst->root);
    N; // New Line

    printf("\nInorder\n");
    bst->inorder(bst->root);
    N;

    printf("\nPostorder\n");
    bst->postorder(bst->root);
    N;

    num = 12;
    printf("\nSearching for %d...\n", num);
    if(bst->search(num)) {
        printf("%d found.\n", bst->location->data);
    }
    
    printf("\nSmallest value in tree: %d\n", bst->get_smallest()->data);
    printf("\nLargest value in tree: %d\n", bst->get_largest()->data); N;

    printf("Leaves:\n");
    bst->print_leaves_recursive(bst->root); N;

    printf("%d leaves found.", bst->count_leaves_recursive(bst->root)); N;

    printf("\nInternal Nodes: %d\n", bst->count_internal_nodes_recursive(bst->root));
    
    printf("\nHeight of tree: %d\n", bst->height(bst->root));

    printf("\nDepth of 5: %d\n", bst->depth(bst->root, bst->root->left->left, 0));

    return 0;
}