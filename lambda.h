#ifndef LAMBDA_H
# define LAMBDA_H

# define PRED(body) ({ bool _pred(void *_x) body _pred; })
# define MAPPER(body) ({ void *_mapper(void *_x) body _mapper; })
# define REDUCER(body) ({ void *_reducer(void *_s, void *_e) body _reducer; })
# define ACTION(body) ({ void _action(void *_x) body _action; })

#endif
