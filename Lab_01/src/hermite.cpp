#include "hermite.h"

void init_hermite_matrix_vectors_blocks(Matrix &matrix, int row_blocks, int data_count)
{
    int index = 0;
    for (int row_block = 0; row_block < row_blocks; row_block++)
    {
        for (int row_mem = 0; row_mem < data_count; row_mem++)
        {
            matrix[row_block * data_count + row_mem][X].block = row_block;
            matrix[row_block * data_count + row_mem][X].integers.push_back(index);
            matrix[row_block * data_count + row_mem][Y].block = row_block;
            matrix[row_block * data_count + row_mem][Y].integers.push_back(index);
            index++;
        }
    }
}
