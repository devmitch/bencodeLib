// c standard libraries
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
// external libraries
#include <bencode.h>

bc_node_t *bcl_decode(char *bc_buf) {
    size_t n_parsed = 0;
    bc_node_t *ret = bcl_decode_inner(bc_buf, &n_parsed);
    return ret;
}

/* Main recursive function */
bc_node_t *bcl_decode_inner(char *bc_buf, size_t *n_parsed) {
    // current node to be returned at this state of recursion
    bc_node_t *curr = malloc(sizeof(bc_node_t));
    // number of characters parsed in helper functions (used to progress buffer)

    switch (bc_buf[0]) {
        case 'i': // number
            curr->type = NUM;
            bc_buf++; // we will only give bcl_decode_int buffer starting from the numbers themselves, not i, so we can reuse elsewhere
            curr->data.num = bcl_decode_int(bc_buf, n_parsed);
            // dont know if we actually need to progress buffer in this case but whatever
            bc_buf += *n_parsed;
            assert(*bc_buf == 'e');
            *n_parsed += 2; //includes the i and e. this is so janky lol 
            break;
        
        case '0' ... '9': // string
            curr->type = STR;
            curr->data.str = bcl_decode_string(bc_buf, n_parsed);
            bc_buf += *n_parsed;
            break;

        case 'l': // list
            curr->type = LIST;
            // init list here, just in case its empty list
            curr->data.list = init_list();
            bc_buf++;
            *n_parsed += 1;
            size_t list_progress = 0;
            while (*bc_buf != 'e') {
                list_add_tail(curr->data.list, &bcl_decode_inner(bc_buf, &list_progress)->list_node);
                bc_buf += list_progress;
                *n_parsed += list_progress;
                list_progress = 0;
            }
            *n_parsed += 1;
            break;

        case 'd': //dict
            curr->type = DICT;
            curr->data.list = init_list();
            bc_buf++;
            *n_parsed += 1;
            size_t dict_progress = 0;
            while (*bc_buf != 'e') {
                bc_dict_pair_t *pair = malloc(sizeof(bc_dict_pair_t));

                pair->key = bcl_decode_inner(bc_buf, &dict_progress);
                assert(pair->key->type == STR); //part of spec
                bc_buf += dict_progress;
                *n_parsed += dict_progress;
                dict_progress = 0;

                pair->value = bcl_decode_inner(bc_buf, &dict_progress);
                bc_buf += dict_progress;
                *n_parsed += dict_progress;
                dict_progress = 0;
                
                list_add_tail(curr->data.list, &pair->list_node);
            }
            *n_parsed += 1;
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