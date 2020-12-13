#include <stdlib.h>
#include <list.h>

typedef enum bc_type {
    NUM,
    STR,
    LIST,
    DICT
} bc_type_t;

typedef struct bc_node {
    list_node_t list_node;
    bc_type_t type;
    union {
        int num;
        char *str;
        list_t *list;
        // dict
    } data;
} bc_node_t;

bc_node_t *bcl_decode(char *bc_buf);
bc_node_t *bcl_decode_inner(char *bc_buf, size_t *n_parsed);
long long int bcl_decode_int(char *bc_buf, size_t *n_parsed);
char *bcl_decode_string(char *bc_buf, size_t *n_parsed);
