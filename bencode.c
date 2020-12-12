// c standard libraries
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
// external libraries
#include <bencode.h>

/* Main recursive function */
bc_node_t *bcl_decode(char *bc_buf) {
    // current node to be returned at this state of recursion
    bc_node_t *curr = malloc(sizeof(bc_node_t));
    // number of characters parsed in helper functions (used to progress buffer)
    size_t n_parsed = 0;

    switch (bc_buf[0]) {
        case 'i': // number
            curr->type = NUM;
            bc_buf++; // we will only give bcl_decode_int buffer starting from the numbers themselves, not i, so we can reuse elsewhere
            curr->data.num = bcl_decode_int(bc_buf, &n_parsed);
            // dont know if we actually need to progress buffer in this case but whatever
            bc_buf += n_parsed;
            assert(*bc_buf == 'e');
            break;
        
        case '0' ... '9': // string
            curr->type = STR;
            curr->data.str = bcl_decode_string(bc_buf, &n_parsed);
            bc_buf += n_parsed;
            break;

        case 'l': // list
            curr->type = LIST;
            // init list here, just in case its empty list

            bc_buf++;
            while (*bc_buf != 'e') {
                
            }
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
        ret += sign*(*bc_buf - '0');
        *n_parsed += 1;
        bc_buf++;
    }

    return ret;
}

char *bcl_decode_string(char *bc_buf, size_t *n_parsed) {
    assert(*bc_buf >= '0' && *bc_buf <= '9');
    size_t digits_parsed;
    long long int str_size = bcl_decode_int(bc_buf, &digits_parsed);
    *n_parsed += digits_parsed;
    bc_buf += digits_parsed;
    assert(*bc_buf == ':');
    *n_parsed += 1;
    bc_buf += 1;

    char *ret = malloc(str_size + 1);
    strncpy(ret, bc_buf, str_size);
    *n_parsed += str_size;
    ret[str_size] = '\0';

    return ret;
}