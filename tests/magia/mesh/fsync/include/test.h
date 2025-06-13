#ifndef _TEST_FSYNC_INCLUDE_GUARD_
#define _TEST_FSYNC_INCLUDE_GUARD_

int write_delayed(uint8_t lvl, uint32_t id, uint32_t x, uint32_t y, uint32_t addr);

int check_values(uint8_t lvl, uint32_t id, uint32_t x, uint32_t y, uint32_t addr);

#endif //_TEST_FSYNC_INCLUDE_GUARD_