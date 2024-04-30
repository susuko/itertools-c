#ifndef LIST_H
# define LIST_H

# include "iter.h"

typedef struct s_list {
	void *data;
	struct s_list *next;
} t_list;

typedef struct s_list_iter {
	t_iter base;
	t_list *list;
} t_list_iter;

t_iter *list_to_iter(t_list *list);
t_list *iter_to_list(t_iter *iter);

#endif
