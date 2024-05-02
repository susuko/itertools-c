#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "iter.h"
#include "foreach.h"
#include "filter.h"
#include "map.h"
#include "reduce.h"
#include "range.h"
#include "list.h"
#include "lambda.h"

bool test(void)
{
	bool result = true;

	// python3 -c "for z in [sum(range(y)) for y in [x * 2 for x in range(0, 100) if x % 2 == 0] if y < 50]: print(z)"
	int expect[] = { 0, 6, 28, 66, 120, 190, 276, 378, 496, 630, 780, 946, 1128 };
	int expect_size = sizeof(expect) / sizeof(expect[0]);

	t_list *list = iter_to_list(({
		t_iter *it = range(0, 100);
		it = filter(it, PRED({
			return *(int *)_x % 2 == 0;
		}));
		it = map(it, MAPPER({
			int *n = malloc(sizeof(int));
			*n = *(int *)_x * 2;
			return n;
		}), free);
		it = filter(it, PRED({
			return *(int *)_x < 50;
		}));
		it = map(it, MAPPER({
			return reduce(range(0, *(int *)_x), REDUCER({
				int *n = malloc(sizeof(int));
				*n = *(int *)_s + *(int *)_e;
				return n;
			}), calloc(1, sizeof(int)), free);
		}), free);
	}));

	int i = 0;
	foreach(list_to_iter(list), ACTION({
		int n = *(int *)_x;
		if (n != expect[i])
			result = false;
		i++;
	}));

	if (i != expect_size)
		result = false;

	for (t_list *l = list, *next; l; l = next) {
		next = l->next;
		free(l->data);
		free(l);
	}

	return result;
}

int main(void)
{
	bool result = test();

	if (result)
		printf("OK\n");
	else
		printf("ERROR\n");

	return !result;
}
