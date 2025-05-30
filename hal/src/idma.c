#include <stdint.h>
#include "idma.h"


/*-----------------------------------------------------------------*/
/* IDMA weak stubs (can be overridden by platform implementations) */
/*-----------------------------------------------------------------*/

__attribute__((weak)) int idma_init(idma_controller_t *ctrl){
    (void) ctrl;
    return 1;
}

__attribute__((weak)) int idma_memcpy_1d(idma_controller_t *ctrl, uint8_t dir, uint32_t axi_addr, uint32_t obi_addr, uint32_t len){
    (void) ctrl;
    (void) dir;
    (void) axi_addr;
    (void) obi_addr;
    (void) len;
    return 1;
}

__attribute__((weak)) int idma_memcpy_2d(idma_controller_t *ctrl, uint8_t dir, uint32_t axi_addr, uint32_t obi_addr, uint32_t len, uint32_t std, uint32_t reps){
    (void) ctrl;
    (void) dir;
    (void) axi_addr;
    (void) obi_addr;
    (void) len;
    (void) std;
    (void) reps;
    return 1;
}

/*----------------------------------------*/
/* Export the controller API for the IDMA */
/*----------------------------------------*/
__attribute__((weak)) idma_controller_api_t idma_api = {
    .init = idma_init,
    .memcpy_1d = idma_memcpy_1d,
    .memcpy_2d = idma_memcpy_2d,
};