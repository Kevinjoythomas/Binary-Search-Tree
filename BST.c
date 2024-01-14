#include<stdio.h>
#include<stdlib.h>

// Definition of a binary search tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to perform an in-order traversal of the binary search tree
void inorder(struct Node* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d\t", root->data);
    inorder(root->right);
}

// Function to insert a new node with a given data value into the binary search tree
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        new_node->data = data;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }

    return root;
}

// Function to find the lowest common ancestor (LCA) of two nodes with values a and b
struct Node* lca(struct Node* root, int a, int b) {
    if (root->data < a && root->data < b) {
        return lca(root->right, a, b);
    } else if (root->data > a && root->data > b) {
        return lca(root->left, a, b);
    } else {
        return root;
    }
}

// Function to find the in-order successor of a given node
struct Node* inordersuccessor(struct Node* root, struct Node* check) {
    struct Node* successor = NULL;
    while (root != NULL) {
        if (root->data > check->data) {
            successor = root;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return successor;
}

// Function to find the successor of a given node
struct Node* successor(struct Node* root) {
    root = root->right;
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to delete a node with a given value from the binary search tree
struct Node* delete(struct Node* root, int val) {
    if (root == NULL) {
        printf("Invalid value");
        return root;
    }

    if (val < root->data) {
        root->left = delete(root->left, val);
    } else if (val > root->data) {
        root->right = delete(root->right, val);
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        } else {
            struct Node* temp = successor(root);
            root->data = temp->data;
            root->right = delete(root->right, temp->data);
        }
    }
    return root;
}

// Main function
int main() {
    struct Node* root = NULL;
    int arr[10] = {200, 100, 400, 50, 150, 250, 180, 120, 135};

    // Insert elements into the binary search tree
    for (int i = 0; i < 10; i++) {
        root = insert(root, arr[i]);
    }

    // Display the original binary search tree
    printf("Original BST:\n");
    inorder(root);

    // Delete a node with value 120 from the binary search tree
    root = delete(root, 120);
    printf("\n");

    // Display the modified binary search tree after deletion
    inorder(root);

    return 0;
}
