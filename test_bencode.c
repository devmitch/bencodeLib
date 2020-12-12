#include <stdio.h>
#include <string.h>

#include <bencode.h>

int main() {
    char *test = strdup("i69e");
    bc_node_t *decoded_struct = bcl_decode(test);
    printf("The output integer is %d\n", decoded_struct->data.num);
    return 0;
}