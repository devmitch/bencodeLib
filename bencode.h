#include <stdlib.h>

typedef enum bc_type {
    NUM,
    STR,
    LIST,
    DICT
} bc_type_t;

typedef struct bc_node {
    bc_type_t type;
    union {
        int num;
        char *str;
        // list
        // dict
    } data;
} bc_node_t;

bc_node_t *bcl_decode(char *bc_buf);
long long int bcl_decode_int(char *bc_buf, size_t *n_parsed);
