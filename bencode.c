// c standard libraries
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
// external libraries
#include <bencode.h>


bc_node_t *bcl_decode(char *bc_buf) {
    // current node to be returned at this state of recursion
    bc_node_t *curr = malloc(sizeof(bc_node_t));
    // number of characters parsed in helper functions (used to progress buffer)
    size_t n_parsed;

    switch (bc_buf[0]) {
        case 'i':
            curr->type = NUM;
            curr->data.num = bcl_decode_int(bc_buf, &n_parsed);
            bc_buf += n_parsed; // dont know if we actually need to progress this buffer but whatever
            break;

        default:
            //uhh
            printf("wat");
    }

    return curr;
}

// doesnt handle underflow or overflow cases
// need to handle case where ret == 0 and sign = -1
long long int bcl_decode_int(char *bc_buf, size_t *n_parsed) {
    assert(bc_buf[0] == 'i'); // just in case :)
    *n_parsed += 1;
    bc_buf++;
    int sign = 1;
    if (*bc_buf == '-') {
        sign = -1;
        bc_buf++;
        *n_parsed += 1;
    }
    long long int ret = 0;

    // essentially convert string to long long int
    while (isdigit(*bc_buf)) {
        ret = ret * 10;
        ret += *bc_buf - '0';
        *n_parsed += 1;
        bc_buf++;
    }

    assert(*bc_buf == 'e');
    *n_parsed += 1;

    return ret;
}