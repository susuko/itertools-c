#ifndef FILTER_H
# define FILTER_H

# include <stdbool.h>
# include "iter.h"

typedef bool (*t_pred)(void *data);

typedef struct s_filter_iter {
	t_iter base;
	t_iter *src_iter;
	t_pred pred;
} t_filter_iter;

t_iter *filter(t_iter *iter, t_pred pred);

#endif
