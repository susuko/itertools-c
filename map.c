#include <stdlib.h>
#include "map.h"
#include "iter.h"

static t_elem get_next_elem_for_map(t_base_iter *iter)
{
	t_map_iter *map_iter = (t_map_iter *)iter;
	t_elem elem = get_next_elem(map_iter->src_iter);
	if (elem.iter_stat == ITER_OK) {
		void *data = map_iter->mapper(elem.data);
		del_elem(map_iter->src_iter, elem);
		return (t_elem) {
			.data = data,
			.iter_stat = ITER_OK
		};
	}
	return elem;
}

static void del_iter_for_map(t_base_iter *iter)
{
	del_iter(((t_map_iter *)iter)->src_iter);
	free(iter);
}

t_base_iter *map(t_base_iter *iter, t_mapper mapper, t_del_elem del_elem)
{
	t_map_iter *map_iter = malloc(sizeof(t_map_iter));
	map_iter->base.get_next_elem = get_next_elem_for_map;
	map_iter->base.del_iter = del_iter_for_map;
	map_iter->base.del_elem = del_elem;
	map_iter->src_iter = iter;
	map_iter->mapper = mapper;
	return (t_base_iter *)map_iter;
}
