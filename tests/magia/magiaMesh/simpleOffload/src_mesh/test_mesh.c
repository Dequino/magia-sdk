#include "test_mesh.h"
#include "test_host.h"

#include "mesh.h"

#include "trampoline_magiaMesh.h"

/**
 * @brief Main function of the mesh test.
 *
 * @return int Return 0 if the test was successful, -1 otherwise.
 */
int32_t testReturn(void *args) {
    // Cast to the correct struct
    offloadArgs_t *argsStruct = (offloadArgs_t *)args;

    // Check if the value is correct
    if (argsStruct->value != 0xdeadbeef) {
        return -1;
    }

    return TESTVAL;
}