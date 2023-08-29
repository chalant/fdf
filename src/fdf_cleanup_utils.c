#include "fdf.h"

void	delete_all_matrix(t_matrix *matrix)
{
	if (!matrix)
		return ;
	delete_matrix(matrix, matrix->rows);
}
