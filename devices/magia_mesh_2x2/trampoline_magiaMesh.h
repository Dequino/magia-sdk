#ifndef _MESH_MAGIA_TRAMPOLINE_INCLUDE_GUARD_
#define _MESH_MAGIA_TRAMPOLINE_INCLUDE_GUARD_

#include <stdint.h>

/**
 * @brief Setup the core to a known state.
 *
 * This function will set up the global pointer and thread pointer for the core.
 */
 #define _SETUP_GP_TP() \
    asm volatile(".option push\n" \
                ".option norelax\n" \
                "la gp, __global_pointer$\n" \
                ".option pop\n" \
                "mv tp, zero\n" \
                : /* No outputs */ \
                : /* No inputs */ \
                : /* No clobbered registers */)

// Helper functions
void set_busy();
void clean_busy();
void mesh_return(uint32_t ret);


#endif