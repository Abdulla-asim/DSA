#include <iostream>
#include <string>
#include <iomanip>
#include <stack>

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

        TreeNode<T> *get_smallest(TreeNode<T> *p) {
            if (!p) { // if no tree exits
                return nullptr;
            }

            while(p->left) { // loop until next to the left node is null
                p = p->left; // go to left node
            }

            return p;
        }

        TreeNode<T> *get_largest(TreeNode<T> *p) {
            if (!p) { // if root is null
                return nullptr;
            }

            // keep going right until you fing the largest value
            while(p->right) {
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
            if (root == nullptr) {
                return;
            }

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

        TreeNode<T> *delete_node(TreeNode<T> *node, T value) {
            if (node == nullptr) return nullptr;

            // if value is less than node value, go to leeft subtree
            if (value < node->data) 
                node->left = delete_node(node->left, value);
            else if (value > node->data)
                node->right = delete_node(node->right, value);
            else {
                // THe case where node only has left or only right child
                // delete node and swap the node we want to remove with its left or right child
                if (node->left == nullptr) {
                    TreeNode<T> *right_child = node->right;
                    // delete the node
                    delete node;
                    return right_child;
                }
                else if (node->right == nullptr) {
                    TreeNode<T> *left_child = node->left;
                    // delete the node
                    delete node;
                    return left_child;
                }
                // in case there are both left and right childs, swap with predecessor or successor
                else {
                    // get the successor
                    TreeNode<T> *temp = get_smallest(node->right);

                    // swap the data
                    node->data = temp->data;

                    // Now remove the successor from the tree
                    node->right = delete_node(node->right, temp->data);
                }
            }
            return node;
        }

        void destroy_tree(TreeNode<T> *root) {
            if (root == nullptr) return;

            // delete using postorder traversal
            destroy_tree(root->left);
            destroy_tree(root->right);
            delete root;
        }

        void node_types(TreeNode<T> *root) {
            if (root == nullptr) return;

            int leaves, only_left, only_right, both;
            stack<TreeNode<T> *> stack;

            leaves = only_left = only_right = both = 0;
            // pushh root to stack
            stack.push(root);

            // Pre order Traversal
            while (!stack.empty()) {
                TreeNode<T> *ptr = stack.top();
                stack.pop();

                if (!(ptr->left) && !(ptr->right))
                    leaves++;
                else if (!(ptr->left) && (ptr->right))
                    only_right++;
                else if ((ptr->left) && !(ptr->right))
                    only_left++;
                else if ((ptr->left) && (ptr->right))
                    both++;

                if (ptr->right) stack.push(ptr->right);
                if (ptr->left) stack.push(ptr->left);
            }

            cout << "Leave Nodes: " << leaves; N;
            cout << "Nodes with Only Left Children: " << only_left; N;
            cout << "Nodes with Only right childres: " << only_right; N;
            cout << "Nodes with both children: " << both; N;
        }

        TreeNode<T> *delete_leaves(TreeNode<T> *root) {
            if (root == nullptr) return nullptr;

            // Pre ORder Traversal
            if (!(root->left) && !(root->right)) {// if no left and right child
                delete_node(root, root->data); // print leaf
                return nullptr;
            }

            root->left = delete_leaves(root->left);
            root->right = delete_leaves(root->right);

            return root;
        }

        TreeNode<T> *remove_node_with_left_subtree(TreeNode<T> *p) {
            if (p == nullptr) return nullptr;

            p->left = remove_node_with_left_subtree(p->left);
            p->right = remove_node_with_left_subtree(p->right);

            if ((p->left) && !(p->right)) {
                TreeNode<T> *temp = p->left;
                delete p;
                return temp;
            }

            return p;
        }

        bool is_leaf(TreeNode<T> *p) {
            if (!p) return false; // node not found
            return (p->left == nullptr && p->right == nullptr);
        }

        bool only_leftchilds(TreeNode<T> *p) {
            if (!p) return false; // node not found
            return (p->left != nullptr && p->right == nullptr);
        }

        bool only_rightchilds(TreeNode<T> *p) {
            if (!p) return false; // node not found
            return (p->left == nullptr && p->right != nullptr);
        }

        bool has_bothchilds(TreeNode<T> *p) {
            if (!p) return false; // node not found
            return (p->left != nullptr && p->right != nullptr);
        }

        void search_predecessor(TreeNode<T> *p) {
            T value = get_largest(p->left)->data;
            search(value);
        }
};

int main () {
    BinarySearchTree<int> *bst = new BinarySearchTree<int>();
    
    printf("Inserting...\n");
    bst->insert(9);
    bst->insert(6);
    bst->insert(11);
    bst->insert(10);
    bst->insert(15);
    bst->insert(7);
    bst->insert(5);
    bst->insert(18);
    bst->insert(16);
    bst->insert(17);
    bst->insert(14);

    bst->printTree(bst->root, 5, 6);


    // 1. Deleting a node
    bst->delete_node(bst->root, 11);
    cout << "\nDeleting 11" << endl; N;

    bst->printTree(bst->root);

    // 3. PRinting leaves
    printf("Leaves:\n");
    bst->print_leaves_recursive(bst->root); N;

    // 4. Count and print count of leaves, nodes with only left or only right and both child nodes.
    cout << "\nCounting types of nodes.."; N;
    bst->node_types(bst->root); N;

    // 5. delete all leaf nodes of a tree;
    cout << "Deleting the leaves"; N;
    bst->delete_leaves(bst->root);
    bst->printTree(bst->root); N;

    // 6. Delete nodes having left subtree
    cout << "Deleting nodes with left subtree"; N;
    bst->remove_node_with_left_subtree(bst->root);
    bst->printTree(bst->root);

    // 2. Destroying Tree
    cout << " destroy tree " << endl;
    bst->destroy_tree(bst->root);
    bst->root = nullptr; // set root to null

    bst->printTree(bst->root); N; // nothibng printex because no tree

    return 0;
}