#include <stdio.h>
#include <stdlib.h>
#include <list.h>

typedef struct my_struct {
    // needs to be the actual object itself and not a pointer
    // if it was a pointer, it would be malloc'd on heap elsewhere
    // so the memory location of the actual node would be random
    // and couldnt find it with list_container()
    list_node_t list_node;
    int num;
} my_struct_t;

int main() {
    list_t *my_list = init_list();
    my_struct_t *s1 = malloc(sizeof(my_struct_t));
    s1->num = 1;
    list_add_tail(my_list, &s1->list_node);
    my_struct_t *s2 = malloc(sizeof(my_struct_t));
    s2->num = 2;
    list_add_tail(my_list, &s2->list_node);
    my_struct_t *s3 = malloc(sizeof(my_struct_t));
    s3->num = 3;
    list_add_tail(my_list, &s3->list_node);

    list_node_t *iter;
    list_for_each(iter, my_list) {
        my_struct_t *curr_struct = list_container(iter, my_struct_t, list_node);
        printf("Struct contains %d\n", curr_struct->num);
    }

    return 0;
}