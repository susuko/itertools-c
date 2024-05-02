#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "iter.h"
#include "foreach.h"
#include "filter.h"
#include "map.h"
#include "reduce.h"
#include "range.h"
#include "lambda.h"

typedef struct s_digits {
	int n[3];
} t_digits;

typedef struct s_result {
	int eat;
	int bite;
} t_result;

typedef struct s_digits_and_result {
	t_digits digits;
	t_result result;
} t_digits_and_result;

void *memdup(const void *src, size_t size)
{ 
	void *buf = malloc(size);
	if (buf) {
		return memcpy(buf, src, size);
	}
	else {
		return NULL;
	}
}

t_digits num_to_digits(int num)
{
	return (t_digits) {
		.n[0] = num / 100 % 10,
		.n[1] = num / 10 % 10,
		.n[2] = num / 1 % 10
	};
}

bool is_unique_digits(t_digits digits)
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == j) {
				continue;
			}
			if (digits.n[i] == digits.n[j]) {
				return false;
			}
		}
	}
	return true;
}

bool result_eq(t_result a, t_result b)
{
	return a.eat == b.eat && a.bite == b.bite;
}

t_result check(t_digits a, t_digits b)
{
	t_result result = { 0, 0 };
	for (int i = 0; i < 3; i++) {
		if (a.n[i] == b.n[i]) {
			result.eat++;
		}
		else {
			for (int j = 0; j < 3; j++) {
				if (a.n[i] == b.n[j]) {
					result.bite++;
				}
			}
		}
	}
	return result;
}

// ./numer0n.out [<num>,<eat>,<bite>] ...
int main(int argc, char *argv[])
{
	foreach(({
		t_iter *it = range(0, 1000);
		it = map(it, MAPPER({
			__auto_type num = (int *)_x;
			t_digits digits = num_to_digits(*num);
			return memdup(&digits, sizeof(t_digits));
		}), free);
		it = filter(it, PRED({
			__auto_type digits = (t_digits *)_x;
			return is_unique_digits(*digits);
		}));
		it = filter(it, PRED({
			__auto_type digits = (t_digits *)_x;
			return *(bool *)reduce(({
				map(range(1, argc), MAPPER({
					__auto_type i = (int *)_x;
					int num, eat, bite;
					sscanf(argv[*i], "%d,%d,%d", &num, &eat, &bite);
					return memdup(&(t_digits_and_result) {
						.digits = num_to_digits(num),
						.result = { .eat = eat, .bite = bite }
					}, sizeof(t_digits_and_result));
				}), free);
			}), REDUCER({
				__auto_type ok = (bool *)_s;
				__auto_type input = (t_digits_and_result *)_e;
				*ok = *ok && result_eq(input->result, check(input->digits, *digits));
				return ok;
			}), &(bool){ true }, NULL);
		}));
	}), ACTION({
		__auto_type digits = (t_digits *)_x;
		printf("%d %d %d\n", digits->n[0], digits->n[1], digits->n[2]);
	}));

	return 0;
}
