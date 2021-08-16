#include "bst.h"
#include "ostream.h"

#include <stdio.h>
#include <stddef.h>

#define asizeof(x) (sizeof(x) / sizeof(x[0]))

void print_bst_op(bst_node_t * item, void * acc)
{
    ostream_write((ostream_t *) acc, "%d, ", item->value);
}

void sum_bst_op(bst_node_t * item, void * acc)
{
    *((int *)acc) += item->value;
}

int main(void)
{
    bst_node_t * root = NULL;
    ostream_t * ostream = ostream_create(256);
    int expectedSum, observedSum;

    // Create a binary search tree through repeated-insertion 

    int values[] = {5, 2, 7, 1, 3, 4, 6, 8, 9};
    for (unsigned int i = 0; i < asizeof(values); i++)
    {
        root = bst_insert(root, values[i]);
    }

    // Print the binary search tree with depth-first traversal

    ostream_write(ostream, "Depth-first: ");
    bst_depth_first_traversal(root, print_bst_op, (void *)ostream);
    ostream_write(ostream, "\r\n");
    ostream_flush(ostream);

    // Compute the sum of the values

    expectedSum = 0;
    for (unsigned int i = 0; i < asizeof(values); i++)
    {
        expectedSum += values[i];
    }
    ostream_write(ostream, "Expected sum: %d\r\n", expectedSum);

    observedSum = 0;
    bst_depth_first_traversal(root, sum_bst_op, (void *)&observedSum);
    ostream_write(ostream, "Observed sum: %d\r\n", observedSum);
    ostream_flush(ostream);

    // Clean up allocated memory

    ostream_delete(&ostream);   
    bst_free(&root);

    return 0;
}