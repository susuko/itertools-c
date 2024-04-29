#ifndef LIST_H
# define LIST_H

# include "iter.h"

typedef struct s_list {
	void *data;
	struct s_list *next;
	t_del_elem del_elem;
} t_list;

typedef struct s_list_iter {
	t_base_iter base;
	t_list *list;
} t_list_iter;

t_base_iter *list_to_iter(t_list *list);
t_list *iter_to_list(t_base_iter *iter);

#endif
