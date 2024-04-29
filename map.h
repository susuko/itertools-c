#ifndef MAP_H
# define MAP_H

# include "iter.h"

typedef void * (*t_mapper)(void *data);

typedef struct s_map_iter {
	t_base_iter base;
	t_base_iter *src_iter;
	t_mapper mapper;
	t_del_elem del_elem;
} t_map_iter;

t_base_iter *map(t_base_iter *iter, t_mapper mapper, t_del_elem del_elem);

#endif
