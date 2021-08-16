#include "bst.h"

#include <stddef.h>
#include <stdlib.h>

static void _bst_free(bst_node_t * root)
{
    if (root == NULL)
    {
        return;
    }

    if (root->left != NULL)
    {
        _bst_free(root->left);
    }

    if (root->right != NULL)
    {
        _bst_free(root->right);
    }

    free(root);
}

void bst_free(bst_node_t** root)
{
    _bst_free(*root);
    *root = NULL;
}

bst_node_t * bst_insert(bst_node_t * root, int value)
{
    if (root == NULL)
    {
        bst_node_t * item = malloc(sizeof(bst_node_t));
        item->value = value;
        item->left = NULL;
        item->right = NULL;
        return item;
    }

    else if (root->value > value)
    {
        root->left = bst_insert(root->left, value);
    }

    else
    {
        root->right = bst_insert(root->right, value);
    }

    return root;
}

void bst_depth_first_traversal(bst_node_t * root, bst_op_t op, void * acc)
{
    // depth-first traversal order is left subtree, root, right-subtree

    if (root == NULL)
    {
        return;
    }

    if (root->left != NULL)
    {
        bst_depth_first_traversal(root->left, op, acc);
    }

    if (op != NULL)
    {
        op(root, acc);
    }

    if (root->right != NULL)
    {
        bst_depth_first_traversal(root->right, op, acc);
    }
}

