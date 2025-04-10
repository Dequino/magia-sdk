#include "config_magiaMesh.h"

#include "addr_map.h"

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
    return;
}