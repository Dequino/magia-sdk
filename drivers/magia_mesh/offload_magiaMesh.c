#include "offload_magiaMesh.h"

#include "addr_map.h"

#include <stdint.h>
#include <stddef.h>

// Persistent trampoline function pointer for each tile
void (*_trampoline_function[NUM_MESH_TILES])(void *) = {NULL};

// Peristent argument storage for the trampoline function
void *_trampoline_args[NUM_MESH_TILES] = {NULL};

// Persistant stack pointer storage for each core
void *_trampoline_stack[NUM_MESH_TILES] = {NULL};

/**
 * @brief Trampoline function for the mesh tile.
 * This function will set up the stack pointer and call the function.
 */
 extern void _trampoline();

/**
 * @brief Generate a trampoline function for the mesh tile.
 * The trampoline function will set up the stack pointer and call the function.
 *
 * @param tile_id ID of the tile to offload to
 * @param function Function pointer to offload
 * @param args Arguments to pass to the function
 * @param stack Stack pointer for core
 * @return A pointer to the persistent trampoline function
 */
 static void *_generate_trampoline(uint32_t tile_id, void (*function)(void *), void *args,
 void *stack) {
    // Assign trampoline with captured arguments to the persistent function pointer
    _trampoline_function[tile_id] = function;
    _trampoline_args[tile_id] = args;
    _trampoline_stack[tile_id] = stack;

    // Store captured arguments in a persistent context if needed
    return _trampoline;
}

/**
 * @brief Offload a void function pointer to a mesh's tile.
 * The function will be executed on the specified tile of the mesh.
 *
 * @param function Function pointer to offload
 * @param args Arguments to pass to the function
 * @param stack_ptr Stack pointer for the tile
 * @param mesh_id ID of the mesh to offload to
 * @param tile_id ID of the tile to offload to
 */
 void offload_magiaMesh_tile(void *function, void *args, void *stack_ptr, uint8_t mesh_id, uint32_t tile_id) {
    return;
}

/**
 * @brief Offload a void function pointer to a mesh.
 * The function will be executed on all tiles of the mesh.
 *
 * @param function Function pointer to offload
 * @param args Arguments to pass to the function
 * @param stack_ptr Stack pointer for the tile
 * @param mesh_id ID of the mesh to offload to
 */
 void offload_magiaMesh(void *function, void *args, void *stack_ptr, uint8_t mesh_id) {
    return;
}

/**
 * @brief Blocking wait for the mesh to become idle.
 * The function busy waits until the mesh is ready.
 *
 * @param mesh_id ID of the mesh to wait for.
 */
 void wait_magiaMesh_busy(uint8_t mesh_id) {
    return;
}

/**
 * @brief Wait for the mesh to return a value.
 * The function busy waits until the mesh returns a non-zero value.
 *
 * @warning The return values must be non-zero, otherwise the function will busy wait forever!
 *
 * @param mesh_id ID of the cluster to wait for.
 * @return uint32_t Return value of the mesh.
 */
 uint32_t wait_magiaMesh_return(uint8_t mesh_id) {
    uint32_t retVal;
    return retVal;
}