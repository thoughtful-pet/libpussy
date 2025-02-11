#pragma once

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

void dump_bitmap(FILE* fp, uint8_t* data, unsigned size);
void dump_hex(FILE* fp, uint8_t* data, unsigned size);

#ifdef __cplusplus
}
#endif
