#include "iter.h"

void del_elem(t_elem elem)
{
	if (elem.del_elem)
		elem.del_elem(elem.data);
}

void del_iter(t_base_iter *iter)
{
	if (iter->del_iter)
		iter->del_iter(iter);
}

t_elem get_next_elem(t_base_iter *iter)
{
	return iter->get_next_elem(iter);
}
