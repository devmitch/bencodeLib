/*  Generic doubly linked list implementation 
    Uses simplified container_of macro to get contents
    of list nodes */

typedef struct list_node {
    struct list_node *next, *prev;
} list_node_t;

typedef struct list {
    list_node_t *head, *tail;
} list_t;

list_t *init_list();
void list_add_tail(list_t *list, list_node_t *node);
list_node_t *list_del_tail(list_t *list);

// simplified version of the container_of() macro
#define list_container(ptr, type, member) \
    ((type *)((char *)ptr - (size_t)(&((type *)0)->member)))

#define list_for_each(iter, list)                                        \
    for ((iter) = (list)->head; (iter) != NULL; (iter) = (iter)->next)
