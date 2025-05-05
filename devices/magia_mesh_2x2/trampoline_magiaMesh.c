#include "mesh.h"
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
    _SETUP_GP_TP();

    asm volatile(
        // Make sure to properly initialize latch based RF
        "lui x1, 0\n"
        "lui x2, 0\n"
        "lui x3, 0\n"
        "lui x4, 0\n"
        "lui x5, 0\n"
        "lui x6, 0\n"
        "lui x7, 0\n"
        "lui x8, 0\n"
        "lui x9, 0\n"
        "lui x10, 0\n"
        "lui x11, 0\n"
        "lui x12, 0\n"
        "lui x13, 0\n"
        "lui x14, 0\n"
        "lui x15, 0\n"
        "lui x16, 0\n"
        "lui x17, 0\n"
        "lui x18, 0\n"
        "lui x19, 0\n"
        "lui x20, 0\n"
        "lui x21, 0\n"
        "lui x22, 0\n"
        "lui x23, 0\n"
        "lui x24, 0\n"
        "lui x25, 0\n"
        "lui x26, 0\n"
        "lui x27, 0\n"
        "lui x28, 0\n"
        "lui x29, 0\n"
        "lui x30, 0\n"
        "lui x31, 0\n"

        // Get hart ID (hardware thread ID)
        "csrr t1, mhartid\n" // Load mhartid into a0

        // Set up stack pointer
        "la a0, _trampoline_stack\n" // Load address of _trampoline_stack
        "slli t1, t1, 2\n"           // Multiply hart ID by 4 (size of pointer)
        "add a0, a0, t1\n"           // Compute the address of _trampoline_stack[hart_id]
        "lw sp, 0(a0)\n"             // Load stack pointer from the computed address

        // Load function pointer and arguments
        "la a0, _trampoline_function\n" // Load address of _trampoline_function
        "add a0, a0, t1\n"              // Compute address of _trampoline_function[hart_id]
        "lw a1, 0(a0)\n"                // Load function pointer into a1

        "la a0, _trampoline_args\n" // Load address of _trampoline_args
        "add a0, a0, t1\n"          // Compute address of _trampoline_args[hart_id]
        "lw a0, 0(a0)\n"            // Load argument pointer into a0
        
        "call set_busy\n"

        // Call the offloaded function
        "jr a1\n" // Jump and link to the function pointer in a1
        
        "call clean_busy\n"
        // By calling immediately after return, register contents in a0 are passed as the first argument
        "call cluster_return\n"
    );
}

/**
 * @brief Set the busy flag of the mesh.
 */
 void set_busy() {
    *((volatile uint32_t *)(MESH_CTRL_BASE + MAGIA_MESH_BUSY_REG_OFFSET)) = 1;
    return;
}

/**
 * @brief Clean the busy flag of the cluster.
 */
 void clean_busy() {
    *((volatile uint32_t *)(MESH_CTRL_BASE + MAGIA_MESH_BUSY_REG_OFFSET)) = 0;
    return;
}

/**
 * @brief Captures the return value of the mesh.
 * @param ret Return value of the mesh tile.
 */
 void mesh_return(uint32_t ret) {
    uint32_t retVal = ret | 0x000000001;

    *((volatile uint32_t *)(SOC_CTRL_BASE + MAGIA_MESH_RETURN_REG_OFFSET)) = retVal;

    return;
}