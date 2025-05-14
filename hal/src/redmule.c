#include "redmule.h"

/*--------------------------------------------------------------------*/
/* Redmule weak stubs (can be overridden by platform implementations) */
/*--------------------------------------------------------------------*/

__attribute__((weak)) int redmule_init(redmule_controller_t *ctrl){
    (void)ctrl;
    return 0;
}

__attribute__((weak)) int redmule_gemm(uint32_t x, uint32_t w, uint32_t y, uint16_t m, uint16_t n, uint16_t k){
    (void)x;
    (void)w;
    (void)y;
    (void)m;
    (void)n;
    (void)k;
    return 0;
}

/*-------------------------------------------*/
/* Export the controller API for the Redmule */
/*-------------------------------------------*/
__attribute__((weak)) redmule_controller_api_t redmule_api = {
    .init = redmule_init,
    .gemm = redmule_gemm,
};