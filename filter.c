#include <stdlib.h>
#include "filter.h"
#include "iter.h"

static t_elem get_next_elem_for_filter(t_base_iter *iter)
{
	t_filter_iter *filter_iter = (t_filter_iter *)iter;
	t_elem elem;
	while ((elem = get_next_elem(filter_iter->src_iter)).iter_stat == ITER_OK) {
		if (filter_iter->pred(elem.data))
			break;
		del_elem(elem);
	}
	return elem;
}

static void del_iter_for_filter(t_base_iter *iter)
{
	del_iter(((t_filter_iter *)iter)->src_iter);
	free(iter);
}

t_base_iter *filter(t_base_iter *iter, t_pred pred)
{
	t_filter_iter *filter_iter = malloc(sizeof(t_filter_iter));
	filter_iter->base.get_next_elem = get_next_elem_for_filter;
	filter_iter->base.del_iter = del_iter_for_filter;
	filter_iter->src_iter = iter;
	filter_iter->pred = pred;
	return (t_base_iter *)filter_iter;
}
