#include <stddef.h>

#include "dump.h"


static bool same_16_chars(uint8_t* block, uint8_t chr)
/*
 * Check if 16 bytes of the block are equal to chr.
 */
{
    for (unsigned i = 0; i < 16; i++ ) {
        if (block[i] != chr) {
            return false;
        }
    }
    return true;
}

void dump_hex(FILE* fp, uint8_t* data, unsigned size)
{
    bool prev_row_same_char = false;
    uint8_t prev_row_char = 0;
    bool skipping = false;
    unsigned column = 0;
    for (unsigned i = 0; i < size;) {
        if (column == 0) {
            if (prev_row_same_char && size - i > 16
                && same_16_chars(data + i, prev_row_char)) {
                i += 16;
                if (!skipping) {
                    skipping = true;
                    fputs("...\n",  fp);
                }
                continue;
            }
            prev_row_same_char = true;
            prev_row_char = data[i];
            skipping = false;
            fprintf(fp, "%p: ", (void*) (((ptrdiff_t) data) + i));
        }
        if (prev_row_char != data[i]) {
            prev_row_same_char = false;
        }
        fprintf(fp, "%02x", data[i++]);
        column++;
        if (column == 8) {
            fprintf(fp, " - ");
        } else if (column == 16) {
            fputc('\n', fp);
            column = 0;
        } else {
            fputc(' ', fp);
        }
    }
    if (column < 16) {
        fputc('\n', fp);
    }
}
