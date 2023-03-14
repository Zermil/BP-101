#ifndef UTILS_H
#define UTILS_H

#define ERROR_EXIT(msg, ...)                    \
    do {                                        \
        fprintf(stderr, (msg), __VA_ARGS__);    \
        exit(1);                                \
    } while (0)

#define ERROR_RETURN(r, msg, ...)               \
    do {                                        \
        fprintf(stderr, (msg), __VA_ARGS__);    \
        return(r);                              \
    } while (0)      

#define CLAMP_TOP(x, y) ((x) > (y) ? (x) : (y))
#define CLAMP_BOT(x, y) ((x) < (y) ? (x) : (y))

#define UNUSED(x) ((void)(x))

#endif // UTILS_H
