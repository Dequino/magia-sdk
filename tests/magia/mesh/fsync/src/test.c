#include <stdint.h>

#include "test.h"
#include "tile.h"
#include "fsync.h"

/**
 * Writes a value to the L1 memory address to be used to verify correct synchronization.
 * Delays the write by an increasing number of nops depending on the core id.
 */
int write_delayed(uint8_t lvl, uint32_t id, uint32_t x, uint32_t y, uint32_t addr){
    uint8_t val = (uint8_t)((x >> ((lvl + 2) / 2)) + ((y >> ((lvl + 1) / 2))*(MESH_X_TILES >> ((lvl + 2) / 2))));
    wait_nop(100 * id);
    mmio8(addr) = val;
    return 0;
}

/**
 * Compares the value written in L1 memory with the value written in L1 memory of the tile_0 of the same synched mesh area.
 */
int check_values(uint8_t lvl, uint32_t id, uint32_t x, uint32_t y, uint32_t addr){
    uint8_t val = *(volatile uint8_t*)(addr);
    uint8_t id_0 = (((val % (MESH_X_TILES >> ((lvl + 2) / 2))) << ((lvl + 2) / 2)) + (((val / (MESH_X_TILES >> ((lvl + 2) / 2))) << ((lvl + 1) / 2)) * MESH_X_TILES));
    uint8_t val_0 = *(volatile uint8_t*)(L1_BASE + (id_0 * L1_TILE_OFFSET));
    if(val_0 != val){
        printf("Error detected at sync level %d - val is: %d but val_0 (id_0:%d) is %d", lvl, val, id_0, val_0);
    }
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
        /**
        * 1_a. Synchronize before write (waits the read of the previous cycle).
        */
        fsync_sync(&fsync_ctrl, (uint32_t) i);

        /**
        * 1_b. Write value.
        */
        write_delayed(i, hartid, x_id, y_id, l1_tile_base);

        /**
        * 1_c. Synchronize on the current level.
        */
        fsync_sync(&fsync_ctrl, (uint32_t) i);

        /**
        * 1_d. Check if the other tiles have written the correct value.
        */
        check_values(i, hartid, x_id, y_id, l1_tile_base);    
    }

    magia_return(hartid, PASS_EXIT_CODE);
    
    return 0;
}