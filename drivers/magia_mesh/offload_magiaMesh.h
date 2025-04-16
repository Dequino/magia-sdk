#ifndef _MESH_MAGIA_OFFLOAD_INCLUDE_GUARD_
#define _MESH_MAGIA_OFFLOAD_INCLUDE_GUARD_

#include <stdint.h>


// Function Offloading
void offload_magiaMesh(void *function, void *args, void *stack_ptr, uint8_t mesh_id);
void offload_magiaMesh_tile(void *function, void *args, void *stack_ptr, uint8_t mesh_id,
                              uint32_t tile_id);

// Synchronization
void wait_magiaMesh_busy(uint8_t mesh_id);
uint32_t wait_magiaMesh_return(uint8_t mesh_id);

#endif //_MESH_MAGIA_OFFLOAD_INCLUDE_GUARD_