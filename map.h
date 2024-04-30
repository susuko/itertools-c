#ifndef MAP_H
# define MAP_H

# include "iter.h"

typedef void * (*t_mapper)(void *data);

typedef struct s_map_iter {
	t_iter base;
	t_iter *src_iter;
	t_mapper mapper;
} t_map_iter;

t_iter *map(t_iter *iter, t_mapper mapper, t_del_elem del_elem);

#endif
