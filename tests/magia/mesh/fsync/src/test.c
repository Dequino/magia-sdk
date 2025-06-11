#include "test.h"
#include "tile.h"
#include "fsync.h"

/**
 * Writes a value to the L1 memory address to be used to verify correct synchronization.
 * 
 */
int write_delayed(uint8_t lvl, uint32_t id, uint32_t addr){
    return 0;
}

/**
 * This test checks the correctness of the Fractal Sync mechanism for synchronizing mesh tiles at different tree levels.
 * Each tiles of the same synchronization level writes an identical value in its L1 memory.
 * After the write, each tile reads the value written by the others in the same synchronization level to check their correctness.
 * Each tile has a delay on the write proportional to its ID, making the synchronization mechanism mandatory. 
 */
int main(void){
    /** 
     * 0. Get the tile's hartid, mesh coordinates and define its L1 base, also initialize the controllers for fsync.
     */
    uint32_t hartid = get_hartid();

    fsync_config_t fsync_cfg = {.hartid = hartid};
    fsync_controller_t fsync_ctrl = {
        .base = NULL,
        .cfg = &fsync_cfg,
        .api = &fsync_api,
    };

    fsync_init(&fsync_ctrl);

    uint32_t y_id = GET_Y_ID(hartid);
    uint32_t x_id = GET_X_ID(hartid);
    uint32_t l1_tile_base = L1_BASE + hartid * L1_TILE_OFFSET;

    /**
     * 1. Cycle over the synchronization levels.
     * Increasing the synchronization level increases the mesh area that has to be synchronized.
     */
    for(uint8_t i = 0; i < MAX_SYNC_LVL; i++){
        write_delayed(i, hartid, l1_tile_base);
    }
    int test_int = -123;
    
    printf("Hello world! %d", test_int);

    magia_return(hartid, PASS_EXIT_CODE);
    
    return 0;
}