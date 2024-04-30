#ifndef FOREACH_H
# define FOREACH_H

# include "iter.h"

typedef void (*t_action)(void *data);

void foreach(t_iter *iter, t_action action);

#endif
