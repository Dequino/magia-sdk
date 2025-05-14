#include "redmule.h"

/*--------------------------------------------------------------------*/
/* Redmule weak stubs (can be overridden by platform implementations) */
/*--------------------------------------------------------------------*/

__attribute__((weak)) int redmule_init(redmule_controller_t *ctrl){
    (void)ctrl;
    return 0;
}

/*-------------------------------------------*/
/* Export the controller API for the Redmule */
/*-------------------------------------------*/
__attribute__((weak)) redmule_controller_api_t redmule_api = {
    .init = redmule_init,
};