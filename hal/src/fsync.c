#include <stdint.h>
#include "fsync.h"
#include "utils/tinyprintf.h"


/*-----------------------------------------------------------------*/
/* Fsync weak stubs (can be overridden by platform implementations) */
/*-----------------------------------------------------------------*/

/*
__attribute__((weak)) int fsync_init(fsync_controller_t *ctrl){
    (void) ctrl;
    return 1;
}
*/

/*
__attribute__((weak)) int fsync_sync(fsync_controller_t *ctrl, uint32_t level){
    (void) ctrl;
    (void) level;
    return 1;
}*/

/*----------------------------------------*/
/* Export the controller API for the Fsync */
/*----------------------------------------*/
__attribute__((weak)) fsync_controller_api_t fsync_api = {
    .init = fsync_init,
    .sync = fsync_sync,
};