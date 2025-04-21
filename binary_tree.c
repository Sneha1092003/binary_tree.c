#include <stdio.h>
#include <stdlib.h>

// Node structure for the tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Create a new node with given value
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Insert a new value into the tree
struct Node* insertNode(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insertNode(root->left, value);
    } else if (value > root->data) {
        root->right = insertNode(root->right, value);
    } else {
        printf("Value %d is already in the tree.\n", value);
    }
    return root;
}

// Search for a value in the tree
struct Node* searchNode(struct Node* root, int value) {
    if (root == NULL || root->data == value) {
        return root;
    }

    if (value < root->data) {
        return searchNode(root->left, value);
    } else {
        return searchNode(root->right, value);
    }
}

// Find the minimum node in a subtree
struct Node* findMin(struct Node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Delete a node from the tree
struct Node* deleteNode(struct Node* root, int value) {
    if (root == NULL) {
        printf("Value %d not found in the tree.\n", value);
        return NULL;
    }

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        // Node found
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

// Free memory of entire tree
void destroyTree(struct Node* root) {
    if (root == NULL) return;
    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
}

int main() {
    struct Node* root = NULL;
    int choice, value;
    int rootCreated = 0;

    printf("Welcome to Binary Search Tree Program\n");
    printf("1. Create Root Node\n");
    printf("2. Insert Value\n");
    printf("3. Search Value\n");
    printf("4. Delete Value\n");
    printf("5. Destroy Tree\n");
    

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (rootCreated) {
                    printf("Root node already created.\n");
                } else {
                    printf("Enter value for root node: ");
                    scanf("%d", &value);
                    root = createNode(value);
                    rootCreated = 1;
                    printf("Root node created with value %d.\n", value);
                }
                break;

            case 2:
                if (!rootCreated) {
                    printf("Please create the root node first.\n");
                } else {
                    printf("Enter value to insert: ");
                    scanf("%d", &value);
                    root = insertNode(root, value);
                }
                break;

            case 3:
                if (!rootCreated) {
                    printf("Tree is empty. Create root first.\n");
                } else {
                    printf("Enter value to search: ");
                    scanf("%d", &value);
                    if (searchNode(root, value)) {
                        printf("Value %d found in the tree.\n", value);
                    } else {
                        printf("Value %d not found.\n", value);
                    }
                }
                break;

            case 4:
                if (!rootCreated) {
                    printf("Tree is empty. Create root first.\n");
                } else {
                    printf("Enter value to delete: ");
                    scanf("%d", &value);
                    root = deleteNode(root, value);
                }
                break;

            case 5:
                destroyTree(root);
                root = NULL;
                rootCreated = 0;
                printf("Tree destroyed successfully.\n");
                break;
                
            default:
                printf("Invalid choice. Enter 1 to 5.\n");
        }
    }

    return 0;
}
