#ifndef MAGIA_UTILS_H
#define MAGIA_UTILS_H

#include "magia_tile_utils.h"
#include "addr_map/tile_addr_map.h"

#define h_pprintf(x) (h_psprint(get_hartid(), x))
#define n_pprintf(x) (n_psprint(get_hartid(), x))
#define   pprintf(x) (  psprint(get_hartid(), x))
#define   pprintln   (  pprintf("\n"))

inline uint32_t get_hartid(){
    uint32_t hartid;
    asm volatile("csrr %0, mhartid"
                 :"=r"(hartid):);
    return hartid;
}

inline void amo_increment(volatile uint32_t addr){
    asm volatile("addi t0, %0, 0" ::"r"(addr));
    asm volatile("li t1, 1" ::);
    asm volatile("amoadd.w t2, t1, (t0)" ::);
}

char* utoa(unsigned int value, unsigned int base, char* result) {
    if (base < 2 || base > 16){
        *result = '\0'; 
        return result; 
    }

    char *ptr0 = result;
    char *ptr1 = result;
    char tmp_char;
    unsigned int tmp_value;

    do {
        tmp_value = value;
        value    /= base;
        *ptr0++   = "0123456789ABCDEF"[tmp_value - value * base];
    } while (value);

    *ptr0-- = '\0';
  
    // Reverse the string
    while(ptr1 < ptr0) {
        tmp_char = *ptr0;
        *ptr0--  = *ptr1;
        *ptr1++  = tmp_char;
    }
    return result;
}

char* bs(uint32_t x) {
    uint32_t hartid = get_hartid();
    char *address = STR_BASE + L1_TILE_OFFSET*hartid;

    return utoa(x, 2, address);
}

char* ds(uint32_t x) {
    uint32_t hartid = get_hartid();
    char *address = STR_BASE + L1_TILE_OFFSET*hartid;

    return utoa(x, 10, address);
}

char* hs(uint32_t x) {
    uint32_t hartid = get_hartid();
    char *address = STR_BASE + L1_TILE_OFFSET*hartid;

    return utoa(x, 16, address);
}

void h_psprint(uint32_t hartid, const char* string){
    mmio8(0xFFFF0004 + (hartid*4)) = '[';
    mmio8(0xFFFF0004 + (hartid*4)) = 'm';
    mmio8(0xFFFF0004 + (hartid*4)) = 'h';
    mmio8(0xFFFF0004 + (hartid*4)) = 'a';
    mmio8(0xFFFF0004 + (hartid*4)) = 'r';
    mmio8(0xFFFF0004 + (hartid*4)) = 't';
    mmio8(0xFFFF0004 + (hartid*4)) = 'i';
    mmio8(0xFFFF0004 + (hartid*4)) = 'd';
    mmio8(0xFFFF0004 + (hartid*4)) = ' ';
    char*   mhardid_str = ds(hartid);
    uint8_t mhartid_idx = 0;
    while (mhardid_str[mhartid_idx] != '\0')
        mmio8(0xFFFF0004 + (hartid*4)) = mhardid_str[mhartid_idx++];
    mmio8(0xFFFF0004 + (hartid*4)) = ']';
    mmio8(0xFFFF0004 + (hartid*4)) = ' ';

    uint8_t index = 0;
    while (string[index] != '\0')
        mmio8(0xFFFF0004 + (hartid*4)) = string[index++];
}

void n_psprint(uint32_t hartid, const char* string){
    uint8_t index = 0;
    while (string[index] != '\0')
        mmio8(0xFFFF0004 + (hartid*4)) = string[index++];
    mmio8(0xFFFF0004 + (hartid*4)) = '\n';
}

void psprint(uint32_t hartid, const char* string){
    uint8_t index = 0;
    while (string[index] != '\0')
        mmio8(0xFFFF0004 + (hartid*4)) = string[index++];
}

#endif /*MAGIA_UTILS_H*/