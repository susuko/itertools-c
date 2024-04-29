#include <stdlib.h>
#include "list.h"
#include "iter.h"

static t_elem get_next_elem_for_list(t_base_iter *iter)
{
	t_list_iter *list_iter = (t_list_iter *)iter;
	if (list_iter->list) {
		t_list *now = list_iter->list;
		list_iter->list = list_iter->list->next;
		return (t_elem) {
			.data = now->data,
			.iter_stat = ITER_OK,
			.del_elem = now->del_elem
		};
	}
	else {
		return (t_elem) {
			.iter_stat = ITER_END
		};
	}
}

static void del_iter_for_list(t_base_iter *iter)
{
	free(iter);
}

static t_list *new_list(t_elem elem)
{
	t_list *list = malloc(sizeof(t_list));
	list->data = elem.data;
	list->next = NULL;
	list->del_elem = elem.del_elem;
	return list;
}

static t_list *add_list(t_list *a, t_list *b)
{
	a->next = b;
	return b;
}

t_base_iter *list_to_iter(t_list *list)
{
	t_list_iter *list_iter = malloc(sizeof(t_list_iter));
	list_iter->base.get_next_elem = get_next_elem_for_list;
	list_iter->base.del_iter = del_iter_for_list;
	list_iter->list = list;
	return (t_base_iter *)list_iter;
}

t_list *iter_to_list(t_base_iter *iter)
{
	t_list head = { .next = NULL };
	t_list *collected = &head;
	t_elem elem;
	while ((elem = get_next_elem(iter)).iter_stat == ITER_OK) {
		collected = add_list(collected, new_list(elem));
	}
	del_iter(iter);
	return head.next;
}
