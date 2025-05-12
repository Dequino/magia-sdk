#ifndef MAGIA_TILE_UTILS_H
#define MAGIA_TILE_UTILS_H

#include "tinyprintf.h"

#define mmio64(x) (*(volatile uint64_t *)(x))
#define mmio32(x) (*(volatile uint32_t *)(x))
#define mmio16(x) (*(volatile uint16_t *)(x))
#define mmio8(x)  (*(volatile uint8_t  *)(x))

#define addr64(x) (*(uint64_t *)(&x))
#define addr32(x) (*(uint32_t *)(&x))
#define addr16(x) (*(uint16_t *)(&x))
#define addr8(x)  (*(uint8_t  *)(&x))

void wait_print(unsigned int cycles){
    for(int i = 0; i <= cycles; i++){
        printf("Waiting: [");
        for(int j = 0; j < i; j++)
            printf("+");
        for(int j = 0; j < cycles - i; j++)
            printf("-");
        printf("]\n");
    }
}

inline void irq_en(volatile uint32_t index_oh){
    asm volatile("addi t0, %0, 0\n\t"
                 "csrrs zero, mie, t0"
                 ::"r"(index_oh));
}

inline uint32_t irq_st(){
    uint32_t irq_status;
    asm volatile("csrr %0, mip"
                 :"=r"(irq_status):);
    return irq_status;
}

inline void wait_nop(uint32_t nops){
    for (int i = 0; i < nops; i++) asm volatile("addi x0, x0, 0" ::);
}

inline void sentinel_instr_id(){
    asm volatile("addi x0, x0, 0x404" ::);
}

inline void sentinel_instr_ex(){
    asm volatile("addi x0, x0, 0x505" ::);
}

inline void ccount_en(){
    asm volatile("csrrci zero, 0x320, 0x1" ::);
}

inline void ccount_dis(){
    asm volatile("csrrsi zero, 0x320, 0x1" ::);
}

inline uint32_t get_cyclel(){
    uint32_t cyclel;
    asm volatile("csrr %0, cycle"
                 :"=r"(cyclel):);
    return cyclel;
}

inline uint32_t get_cycleh(){
    uint32_t cycleh;
    asm volatile("csrr %0, cycleh"
                 :"=r"(cycleh):);
    return cycleh;
}

uint32_t get_cycle(){
    uint32_t cyclel = get_cyclel();
    uint32_t cycleh = get_cycleh();
    if (cycleh) return 0;
    return cyclel;
}

inline uint32_t get_timel(){
    uint32_t timel;
    asm volatile("csrr %0, time"
                 :"=r"(timel):);
    return timel;
}

inline uint32_t get_timeh(){
    uint32_t timeh;
    asm volatile("csrr %0, timeh"
                 :"=r"(timeh):);
    return timeh;
}

uint32_t get_time(){
    uint32_t timel = get_timel();
    uint32_t timeh = get_timeh();
    if (timeh) return 0;
    return timel;
}

#endif /*MAGIA_TILE_UTILS_H*/