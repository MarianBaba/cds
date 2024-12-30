#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int data;
    struct node *parent;
    struct node *right;
    struct node *left;
};

struct bst {
    struct node *root;
};

struct node *min_bst(struct node *root) {
    struct node *current = root;
    struct node *parent = NULL;
    while (current != NULL) {
        parent = current;
        current = current->left;
    }
    return parent;
};

struct node *max_bst(struct node *root) {
    struct node *current = root;
    struct node *parent = NULL;
    while (current != NULL) {
        parent = current;
        current = current->right;
    }
    return parent;
};

struct node *successor(struct node *root) {
    if (root == NULL || root->right == NULL) {
        return NULL;
    }
    return min_bst(root->right);
}

struct node *predecessor(struct node *root) {
    if (root == NULL || root->left == NULL) {
        return NULL;
    }
    return max_bst(root->left);
}

struct node *search(struct node *root, int target) {
    if (root == NULL) {
        printf("%d not found\n", target);
        return NULL;
    }
    if (root->data == target) {
        printf("%d found!\n", target);
        return root;
    }
    if (root->data > target) {
        return search(root->left, target);
    } else {
        return search(root->right, target);
    }
}

void delete(struct bst *bst, int target) {
    if (bst->root == NULL) {
        return;
    } 
    struct node *node = search(bst->root, target);
    if (node == NULL) {
        return;
    }

    if (node->left == NULL && node->right == NULL) {
        struct node *parent = node->parent;
        if (parent->left != NULL && parent->left->data == node->data) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        free(node);
        return;
    } else if (node->left == NULL && node->right != NULL) {
        struct node *child = node->right;
        struct node *parent = node->parent;
        if (parent->left != NULL && parent->left->data == node->data) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        child->parent = parent;
        free(node);
    } else if (node->left != NULL && node->right == NULL) {
        struct node *child = node->left;
        struct node *parent = node->parent;
        if (parent->left != NULL && parent->left->data == node->data) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        child->parent = parent;
        free(node);
    } else {
        struct node *scr = successor(node);
        if (scr != NULL) {
            int data = scr->data;
            delete(bst, scr->data);
            node->data = data;
            return;
        }
        struct node *pcr = predecessor(node);
        if (pcr != NULL) {
            int data = pcr->data;
            delete(bst, pcr->data);
            node->data = data;
            return;
        }
    }
}

void preorder(struct node *root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(struct node *root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
};

void postorder(struct node *root) {
    if (root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
};

struct bst *create_bst() {
    struct bst *bst = malloc(sizeof(struct bst));
    if (bst == NULL) {
        printf("error allocating memory for new bst, exiting...\n");
        exit(1);
    }
    bst->root = NULL;
    return bst;
};

void insert_recursive(struct bst *bst, struct node *root, int data) {
    if (bst->root == NULL) {
        struct node *node = malloc(sizeof(struct node));
        node->data = data;
        node->parent = NULL;
        node->right = NULL;
        node->left = NULL;
        bst->root = node;
        return;
    }
    if (root->data > data) {
        if (root->left == NULL) {
            struct node *node = malloc(sizeof(struct node));
            node->data = data;
            node->left = NULL;
            node->right = NULL;
            root->left = node;
            node->parent = root;
            return;
        } else {
            insert_recursive(bst, root->left, data);
        }
    } else {
        if (root->right == NULL) {
            struct node *node = malloc(sizeof(struct node));
            node->data = data;
            node->left = NULL;
            node->right = NULL;
            root->right = node;
            node->parent = root;
            return;
        } else {
            insert_recursive(bst, root->right, data);
        }
    }
};

void insert_iterative(struct bst *bst, int data) {
    struct node *node = malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;

    if (bst->root == NULL) {
        bst->root = node;
        return;
    }

    struct node *parent = NULL;
    struct node *current = bst->root;

    while (current != NULL) {
        parent = current;
        if (current->data > node->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    node->parent = parent;
    if (parent->data > data) {
        parent->left = node;
    } else {
        parent->right = node;
    }
}

void print_edges(struct node *root) {
    if (root == NULL) {
        return;
    }
    printf("Node %d: ", root->data);
    if (root->left != NULL) {
        printf("Left -> %d, ", root->left->data);
    } else {
        printf("Left -> NULL, ");
    }
    if (root->right != NULL) {
        printf("Right -> %d, ", root->right->data);
    } else {
        printf("Right -> NULL, ");
    }
    if (root->parent != NULL) {
        printf("Parent -> %d", root->parent->data);
    } else {
        printf("Parent -> NULL");
    }
    printf("\n");
    print_edges(root->left);
    print_edges(root->right);
}

int main() {
    struct bst *bst = create_bst();
    insert_iterative(bst, 10);
    insert_iterative(bst, 2);
    insert_iterative(bst, 15);
    insert_iterative(bst, 5);
    insert_iterative(bst, 100);
    insert_iterative(bst, 13);
    return 0;
};