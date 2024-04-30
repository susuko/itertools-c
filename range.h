#ifndef RANGE_H
# define RANGE_H

# include "iter.h"

typedef struct s_range_iter {
	t_iter base;
	int end;
	int i;
} t_range_iter;

t_iter *range(int start, int end);

#endif
