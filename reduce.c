#include <stdlib.h>
#include "reduce.h"
#include "iter.h"

void *reduce(t_base_iter *iter, t_reducer reducer, void *init, t_del_sum del_sum)
{
	void *sum = init;
	t_elem elem;
	while ((elem = get_next_elem(iter)).iter_stat == ITER_OK) {
		void *new_sum = reducer(sum, elem.data);
		if (del_sum)
			del_sum(sum);
		del_elem(elem);
		sum = new_sum;
	}
	del_iter(iter);
	return sum;
}
