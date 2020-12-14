#include <stdio.h>
#include <string.h>

#include <bencode.h>

void print_bencode_inner(bc_node_t *bc) {
    //printf("starting inner run\n");
    //printf("current node type = %d\n", bc->type);
    switch (bc->type) {
        case NUM:
            printf("%d", bc->data.num);
            break;
        case STR:
            printf("%s", bc->data.str);
            break;
        case LIST:
            //printf("found a list..?\n");
            printf("[");
            list_node_t *iter;
            int list_count = 1;
            list_for_each(iter, bc->data.list) {
                if (list_count != 1) {
                    printf(",");
                }
                print_bencode_inner(list_container(iter, bc_node_t, list_node));
                list_count++;
            }
            printf("]");
            break;
        default:
            printf("WHAT IN THE FUCK\n");
            break;
    }
}

void print_bencode(char *bc_buf) {
    printf("|%s| is decoded as: \n", bc_buf);
    char *buf = strdup(bc_buf);
    bc_node_t *decoded_struct = bcl_decode(buf);
    print_bencode_inner(decoded_struct);
    printf("\n\n");
}

int main() {
    print_bencode("i69e");
    print_bencode("i-60e");
    print_bencode("4:spam");
    print_bencode("0:");
    print_bencode("l4:spam4:eggse");
    print_bencode("le");
    print_bencode("ll4:testee");
    print_bencode("li6eli7eee");
    print_bencode("li420elllli5ei6e3:lolei9elel3:yepe2:okeei8eee");
    return 0;
}