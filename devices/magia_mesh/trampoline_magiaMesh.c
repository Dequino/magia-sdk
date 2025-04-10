#include "trampoline_magiaMesh.h"

// Persistent trampoline function pointer for each tile
extern void (*_trampoline_function)(void *);

// Peristent argument storage for the trampoline function
extern void *_trampoline_args;

// Persistant stack pointer storage for each core
extern void *_trampoline_stack;

/**
 * @brief Trampoline function for the mesh tile.
 * This function will set up the stack pointer and call the function.
 */
void __attribute__((naked)) _trampoline() {
    return;
}

/**
 * @brief Set the busy flag of the mesh.
 */
 void set_busy() {
    return;
}

/**
 * @brief Clean the busy flag of the cluster.
 */
 void clean_busy() {
    return;
}

/**
 * @brief Captures the return value of the mesh.
 * @param ret Return value of the mesh tile.
 */
 void mesh_return(uint32_t ret) {
    return;
}