#include "foreach.h"
#include "iter.h"

void foreach(t_iter *iter, t_action action)
{
	t_elem elem;
	while ((elem = get_next_elem(iter)).iter_stat == ITER_OK) {
		action(elem.data);
		del_elem(iter, elem);
	}
	del_iter(iter);
}
