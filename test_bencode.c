#include <stdio.h>
#include <string.h>

#include <bencode.h>



void print_bencode(char *bc_buf) {
    printf("|%s| is decoded as: \n", bc_buf);
    char *buf = strdup(bc_buf);
    bc_node_t *decoded_struct = bcl_decode(buf);
    bcl_dump(decoded_struct);
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
    print_bencode("d3:cow3:moo4:spam4:eggse");
    print_bencode("d4:spaml1:a1:bee");
    print_bencode("d6:eg_keyd9:inner_keyi69eee");
    return 0;
}