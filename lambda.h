#ifndef LAMBDA_H
# define LAMBDA_H

# define PRED(...) ({ bool _pred(void *_x) __VA_ARGS__ _pred; })
# define MAPPER(...) ({ void *_mapper(void *_x) __VA_ARGS__ _mapper; })
# define REDUCER(...) ({ void *_reducer(void *_s, void *_e) __VA_ARGS__ _reducer; })
# define ACTION(...) ({ void _action(void *_x) __VA_ARGS__ _action; })

#endif
