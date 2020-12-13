#include <stdio.h>
#include <stdlib.h>
#include <list.h>

typedef struct my_struct {
    list_node_t *list_node;
    int num;
} my_struct_t;

int main() {
    list_t *my_list = malloc(sizeof(list_t));
    my_struct_t *s1 = malloc(sizeof(my_struct_t));
    s1->num = 1;
    s1->list_node = init_list_node();
    list_add_tail(my_list, s1->list_node);
    my_struct_t *s2 = malloc(sizeof(my_struct_t));
    s2->num = 2;
    s2->list_node = init_list_node();
    list_add_tail(my_list, s2->list_node);
    my_struct_t *s3 = malloc(sizeof(my_struct_t));
    s3->num = 3;
    s3->list_node = init_list_node();
    list_add_tail(my_list, s3->list_node);

    list_node_t *curr = init_list_node();
    list_for_each(curr, my_list) {
        printf("%d\n", list_container(curr, my_struct_t, list_node)->num);
    }

    return 0;
}