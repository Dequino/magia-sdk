#include "config_magiaMesh.h"

#include "addr_map.h"
#include "mesh.h"

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Configure Magia mesh before usage.
 * This function performs different configurations of the Magia tile before offloading a
 * workloads. Namely, it:
 * - resets the busy register
 * - resets the return register
 *
 * @param mesh_id ID of the mesh to wait for.
 */
 void config_magiaMesh(uint8_t mesh_id) {
    volatile uint32_t *busyRegAddr;
    volatile int32_t *returnRegAddr;

    busyRegAddr = (volatile uint32_t *)(MESH_CTRL_BASE + MAGIA_MESH_BUSY_REG_OFFSET);
    returnRegAddr = (volatile int32_t *)(MESH_CTRL_BASE + MAGIA_MESH_RETURN_REG_OFFSET);

    // Reset busy register
    *busyRegAddr = 0;

    // Reset return register
    *returnRegAddr = 0;

    return;
}