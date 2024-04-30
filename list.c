#include <stdlib.h>
#include "list.h"
#include "iter.h"

static t_elem get_next_elem_for_list(t_iter *iter)
{
	t_list_iter *list_iter = (t_list_iter *)iter;
	if (list_iter->list) {
		void *data = list_iter->list->data;
		list_iter->list = list_iter->list->next;
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

static void del_iter_for_list(t_iter *iter)
{
	free(iter);
}

static t_list *new_list(t_elem elem)
{
	t_list *list = malloc(sizeof(t_list));
	list->data = elem.data;
	list->next = NULL;
	return list;
}

static t_list *add_list(t_list *a, t_list *b)
{
	a->next = b;
	return b;
}

t_iter *list_to_iter(t_list *list)
{
	t_list_iter *list_iter = malloc(sizeof(t_list_iter));
	list_iter->base.get_next_elem = get_next_elem_for_list;
	list_iter->base.del_iter = del_iter_for_list;
	list_iter->base.del_elem = NULL;
	list_iter->list = list;
	return (t_iter *)list_iter;
}

t_list *iter_to_list(t_iter *iter)
{
	t_list head = { .next = NULL };
	t_list *tail = &head;
	t_elem elem;
	while ((elem = get_next_elem(iter)).iter_stat == ITER_OK) {
		tail = add_list(tail, new_list(elem));
	}
	del_iter(iter);
	return head.next;
}
