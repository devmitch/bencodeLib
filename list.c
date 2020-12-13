#include <stdlib.h>
#include <list.h>

list_t *init_list() {
    list_t *ret = malloc(sizeof(list_t));
    return ret;
}

list_node_t *init_list_node() {
    list_node_t *ret = malloc(sizeof(list_node_t));
    return ret;
}

void list_add_tail(list_t *list, list_node_t *node) {
    if (list->tail != NULL) {
        list->tail->next = node;
    }
    if (list->head == NULL) {
        list->head = node;
    }
    node->prev = list->tail;
    list->tail = node;
    node->next = NULL; // dont know if neccessary 
}

list_node_t *list_del_tail(list_t *list) {
    list_node_t *ret = list->tail;
    if (list->tail != NULL) {
        list->tail = list->tail->prev;
        if (list->tail != NULL) {
            list->tail->next = NULL;
        }
    }
    if (list->head == ret) {
        list->head = NULL;
    }
    return ret;
}
