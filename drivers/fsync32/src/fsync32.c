#include <stdint.h>
#include "fsync32.h"
#include "regs/tile_ctrl.h"
#include "addr_map/tile_addr_map.h"
#include "utils/fsync_isa_utils.h"
#include "utils/tinyprintf.h"
#include "utils/magia_utils.h"

int fsync32_init(fsync_controller_t *ctrl) {
    irq_en(1<<IRQ_FSYNC_DONE);
    return 0;
}

/**
 * Synchronize the tile with the others of the selected level synchronization tree level.
 * Level 0 will synchronize with the neighbor tile.
 * Increasing the level will synchronize with more neighborhoods.
 * At maximum level (log_2(N_tiles)) the entire mesh is synchronized.
 *
 * @param level Tree level over which synchronize.
 */
int fsync32_sync(fsync_controller_t *ctrl, uint32_t level){
    if(level >= MAX_SYNC_LVL){
        printf("Error: synchronization level is too high! Maximum level is: %d", MAX_SYNC_LVL);
        return 1;
    }
    //printf("Calling sync level %d", level);
    fsync((uint8_t) (1 << (level)));
    //asm volatile("wfi" ::: "memory");
    return 0;
}

extern int fsync_init(fsync_controller_t *ctrl)
    __attribute__((alias("fsync32_init"), used, visibility("default")));
extern int fsync_sync(fsync_controller_t *ctrl, uint32_t level)
    __attribute__((alias("fsync32_sync"), used, visibility("default")));

/* Export the FSYNC-specific controller API */
fsync_controller_api_t fsync_api = {
    .init = fsync32_init,
    .sync = fsync32_sync,
};

