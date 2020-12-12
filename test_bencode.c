#include <stdio.h>
#include <string.h>

#include <bencode.h>

int main() {
    char *test = strdup("i69e");
    bc_node_t *decoded_struct = bcl_decode(test);
    printf("%s decoded becomes %d\n", test, decoded_struct->data.num);

    char *test2 = strdup("i-60e");
    bc_node_t *decoded_struct2 = bcl_decode(test2);
    printf("%s decoded becomes %d\n", test2, decoded_struct2->data.num);

    char *test3 = strdup("4:spam");
    bc_node_t *decoded_struct3 = bcl_decode(test3);
    printf("%s decoded becomes %s.\n", test3, decoded_struct3->data.str);
    
    char *test4 = strdup("0:");
    bc_node_t *decoded_struct4 = bcl_decode(test4);
    printf("%s decoded becomes %s.\n", test4, decoded_struct4->data.str);

    return 0;
}