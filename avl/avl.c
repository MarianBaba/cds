#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    int balance; // Balance factor of the node
    struct node *parent;
    struct node *left;
    struct node *right;
};

struct avl {
    struct node *root;
};

// Function Prototypes
struct avl *create_avl();
struct node *search(struct node *node, int target);
struct node *min_avl(struct node *node);
struct node *max_avl(struct node *node);
struct node *successor(struct node *node);
struct node *predecessor(struct node *node);
void insert(struct avl *avl, int data);
void delete(struct avl *avl, int target);
void left_rotation(struct avl *avl, struct node *node);
void right_rotation(struct avl *avl, struct node *node);
void print_edges(struct node *node);

// AVL Tree Creation
struct avl *create_avl() {
    struct avl *avl = malloc(sizeof(struct avl));
    avl->root = NULL;
    return avl;
}

// Search Function
struct node *search(struct node *node, int target) {
    if (node == NULL || node->data == target) {
        return node;
    }
    if (target < node->data) {
        return search(node->left, target);
    } else {
        return search(node->right, target);
    }
}

// Find the Node with Minimum Value
struct node *min_avl(struct node *node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Find the Node with Maximum Value
struct node *max_avl(struct node *node) {
    while (node->right != NULL) {
        node = node->right;
    }
    return node;
}

// Find Successor
struct node *successor(struct node *node) {
    if (node->right != NULL) {
        return min_avl(node->right);
    }
    struct node *parent = node->parent;
    while (parent != NULL && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

// Find Predecessor
struct node *predecessor(struct node *node) {
    if (node->left != NULL) {
        return max_avl(node->left);
    }
    struct node *parent = node->parent;
    while (parent != NULL && node == parent->left) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

// Left Rotation
void left_rotation(struct avl *avl, struct node *node) {
    struct node *right = node->right;
    node->right = right->left;
    if (right->left != NULL) {
        right->left->parent = node;
    }
    right->parent = node->parent;
    if (node->parent == NULL) {
        avl->root = right;
    } else if (node == node->parent->left) {
        node->parent->left = right;
    } else {
        node->parent->right = right;
    }
    right->left = node;
    node->parent = right;
}

// Right Rotation
void right_rotation(struct avl *avl, struct node *node) {
    struct node *left = node->left;
    node->left = left->right;
    if (left->right != NULL) {
        left->right->parent = node;
    }
    left->parent = node->parent;
    if (node->parent == NULL) {
        avl->root = left;
    } else if (node == node->parent->left) {
        node->parent->left = left;
    } else {
        node->parent->right = left;
    }
    left->right = node;
    node->parent = left;
}

// Insert Function
void insert(struct avl *avl, int data) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->data = data;
    new_node->balance = 0;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;

    if (avl->root == NULL) {
        avl->root = new_node;
        return;
    }

    struct node *current = avl->root;
    struct node *parent = NULL;

    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    new_node->parent = parent;
    if (data < parent->data) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }

    // Rebalance
    struct node *n = new_node;
    while (parent != NULL) {
        if (n == parent->left) {
            parent->balance--;
        } else {
            parent->balance++;
        }

        if (parent->balance == 0) {
            break;
        } else if (parent->balance == -2) {
            if (n->balance == -1) {
                right_rotation(avl, parent); // LL case
            } else {
                left_rotation(avl, n);
                right_rotation(avl, parent); // LR case
            }
            break;
        } else if (parent->balance == 2) {
            if (n->balance == 1) {
                left_rotation(avl, parent); // RR case
            } else {
                right_rotation(avl, n);
                left_rotation(avl, parent); // RL case
            }
            break;
        }

        n = parent;
        parent = parent->parent;
    }
}

// Delete Function
void delete(struct avl *avl, int target) {
    struct node *node = search(avl->root, target);
    if (node == NULL) {
        printf("Node %d not found.\n", target);
        return;
    }

    // Helper function to rebalance after deletion
    void rebalance_after_deletion(struct avl *avl, struct node *node) {
        while (node != NULL) {
            int old_balance = node->balance;

            // Update the balance factor
            if (node->left == NULL && node->right == NULL) {
                node->balance = 0;
            } else if (node->left == NULL) {
                node->balance = 1;
            } else if (node->right == NULL) {
                node->balance = -1;
            } else {
                int left_height = node->left->balance == 0 ? 1 : abs(node->left->balance) + 1;
                int right_height = node->right->balance == 0 ? 1 : abs(node->right->balance) + 1;
                node->balance = right_height - left_height;
            }

            // Rebalancing cases
            if (node->balance == 2) { // Right-heavy
                if (node->right->balance >= 0) { // Right-Right Case
                    left_rotation(avl, node);
                } else { // Right-Left Case
                    right_rotation(avl, node->right);
                    left_rotation(avl, node);
                }
            } else if (node->balance == -2) { // Left-heavy
                if (node->left->balance <= 0) { // Left-Left Case
                    right_rotation(avl, node);
                } else { // Left-Right Case
                    left_rotation(avl, node->left);
                    right_rotation(avl, node);
                }
            }

            // If the balance factor hasn't changed, stop rebalancing
            if (node->balance == old_balance) {
                break;
            }

            node = node->parent; // Move up to the parent
        }
    }

    // Case 1: Node to delete has no children
    if (node->left == NULL && node->right == NULL) {
        if (node->parent == NULL) { // Node is the root
            avl->root = NULL;
        } else if (node == node->parent->left) {
            node->parent->left = NULL;
        } else {
            node->parent->right = NULL;
        }
        rebalance_after_deletion(avl, node->parent);
        free(node);
        return;
    }

    // Case 2: Node to delete has one child
    if (node->left == NULL || node->right == NULL) {
        struct node *child = (node->left != NULL) ? node->left : node->right;
        if (node->parent == NULL) { // Node is the root
            avl->root = child;
        } else if (node == node->parent->left) {
            node->parent->left = child;
        } else {
            node->parent->right = child;
        }
        child->parent = node->parent;
        rebalance_after_deletion(avl, child->parent);
        free(node);
        return;
    }

    // Case 3: Node to delete has two children
    struct node *succ = successor(node); // Find the successor
    node->data = succ->data;            // Copy successor's data to the current node
    delete(avl, succ->data);            // Recursively delete the successor
}

// Print Tree Structure
void print_edges(struct node *node) {
    if (node == NULL) {
        return;
    }
    printf("Node %d: ", node->data);
    if (node->left != NULL) {
        printf("Left -> %d, ", node->left->data);
    } else {
        printf("Left -> NULL, ");
    }
    if (node->right != NULL) {
        printf("Right -> %d, ", node->right->data);
    } else {
        printf("Right -> NULL, ");
    }
    if (node->parent != NULL) {
        printf("Parent -> %d", node->parent->data);
    } else {
        printf("Parent -> NULL");
    }
    printf(", Balance -> %d\n", node->balance);
    print_edges(node->left);
    print_edges(node->right);
}

// Main Function
int main() {
    struct avl *avl = create_avl();

    insert(avl, 10);
    insert(avl, 20);
    insert(avl, 5);
    insert(avl, 30);
    insert(avl, 15);
    insert(avl, 25);

    printf("Tree Structure After Insertions:\n");
    print_edges(avl->root);

    printf("\nDeleting Node 20...\n");
    delete(avl, 20);
    print_edges(avl->root);

    return 0;
}