#ifndef BST_H
#define BST_H

#include <stdbool.h>

struct _bst_node_t;

struct _bst_node_t {
    int value;
    struct _bst_node_t * left;
    struct _bst_node_t * right;
};

typedef struct _bst_node_t bst_node_t;

typedef void(*bst_op_t)(bst_node_t * item, void * acc);

#ifdef __cplusplus
extern "C" {
#endif

bst_node_t * bst_insert(bst_node_t * root, int value);

bool bst_contains(bst_node_t * root, int value);

void bst_free(bst_node_t** root);

void bst_depth_first_traversal(bst_node_t * root, bst_op_t op, void * acc);

#ifdef __cplusplus
}
#endif

#endif