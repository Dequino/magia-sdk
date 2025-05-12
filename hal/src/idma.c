#include "idma.h"

/*-----------------------------------------------------------------*/
/* IDMA weak stubs (can be overridden by platform implementations) */
/*-----------------------------------------------------------------*/

__attribute__((weak)) int idma_init(idma_controller_t *ctrl){
    (void)ctrl;
    return 0;
}

/*----------------------------------------*/
/* Export the controller API for the IDMA */
/*----------------------------------------*/
__attribute__((weak)) idma_controller_api_t idma_api = {
    .init = idma_init,
};