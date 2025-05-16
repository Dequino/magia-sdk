#ifndef _TILE_ADDR_MAP_INCLUDE_GUARD_
#define _TILE_ADDR_MAP_INCLUDE_GUARD_


#define NUM_L1_BANKS (32)
#define WORDS_BANK   (8192)
#define BITS_WORD    (32)
#define BITS_BYTE    (8)

#define RESERVED_START (0x00000000)
#define RESERVED_END   (0x0000FFFF)
#define STACK_START    (0x00010000)
#define STACK_END      (0x0001FFFF)
#define L1_BASE        (0x00020000)
#define L1_SIZE        (0x000E0000)
#define L1_TILE_OFFSET (0x00100000)
#define MHARTID_OFFSET (0x00100000)
#define L2_BASE        (0xCC000000)
#define TEST_END_ADDR  (0xCC030000)

#define MESH_X_TILES (2)
#define MESH_Y_TILES (2)
#define NUM_HARTS    (MESH_X_TILES*MESH_Y_TILES)

#define STR_OFFSET  (0x00000000)
#define STR_BASE    (RESERVED_START + STR_OFFSET)
#define SYNC_OFFSET (0x0000F000)
#define SYNC_BASE   (RESERVED_START + SYNC_OFFSET)
#define SYNC_EN     (SYNC_BASE + 0x4)

#define GET_X_ID(mhartid)  (mhartid%MESH_Y_TILES)
#define GET_Y_ID(mhartid)  (mhartid/MESH_Y_TILES)
#define GET_ID(y_id, x_id) ((y_id*MESH_Y_TILES)+x_id)

#endif // _TILE_ADDR_MAP_INCLUDE_GUARD_