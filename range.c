#include <stdlib.h>
#include <stdbool.h>
#include "range.h"
#include "iter.h"

static t_elem get_next_elem_for_range(t_iter *iter)
{
	t_range_iter *range_iter = (t_range_iter *)iter;
	if (range_iter->i < range_iter->end) {
		int *data = malloc(sizeof(int));
		*data = range_iter->i++;
		return (t_elem) {
			.data = data,
			.iter_stat = ITER_OK
		};
	}
	else {
		return (t_elem) {
			.iter_stat = ITER_END
		};
	}
}

static void del_iter_for_range(t_iter *iter)
{
	free(iter);
}

t_iter *range(int start, int end)
{
	t_range_iter *range_iter = malloc(sizeof(t_range_iter));
	range_iter->base.get_next_elem = get_next_elem_for_range;
	range_iter->base.del_iter = del_iter_for_range;
	range_iter->base.del_elem = free;
	range_iter->end = end;
	range_iter->i = start;
	return (t_iter *)range_iter;
}
