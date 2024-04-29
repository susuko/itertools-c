#ifndef REDUCE_H
# define REDUCE_H

# include "iter.h"

typedef void * (*t_reducer)(void *sum, void *data);
typedef void (*t_del_sum)(void *sum);

void *reduce(t_base_iter *iter, t_reducer reducer, void *init, t_del_sum del_sum);

#endif
