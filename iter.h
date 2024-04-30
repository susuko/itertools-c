#ifndef ITER_H
# define ITER_H

typedef struct s_elem t_elem;
typedef struct s_base_iter t_base_iter;
typedef enum e_iter_stat t_iter_stat;

typedef void (*t_del_elem)(void *data);
typedef void (*t_del_iter)(t_base_iter *iter);
typedef t_elem (*t_get_next_elem)(t_base_iter *iter);

enum e_iter_stat {
	ITER_OK,
	ITER_END
};

struct s_elem {
	void *data;
	t_iter_stat iter_stat;
};

struct s_base_iter {
	t_get_next_elem get_next_elem;
	t_del_iter del_iter;
	t_del_elem del_elem;
};

void del_elem(t_base_iter *iter, t_elem elem);
void del_iter(t_base_iter *iter);
t_elem get_next_elem(t_base_iter *iter);

#endif
