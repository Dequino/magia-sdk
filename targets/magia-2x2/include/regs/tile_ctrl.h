#ifndef _TILE_REG_DEFS_
#define _TILE_REG_DEFS_

#define DEFAULT_EXIT_CODE (0xDEFC)
#define PASS_EXIT_CODE    (0xAAAA)
#define FAIL_EXIT_CODE    (0xFFFF)

#define IRQ_REDMULE_EVT_0 (31)
#define IRQ_REDMULE_EVT_1 (30)
#define IRQ_A2O_ERROR     (29)
#define IRQ_O2A_ERROR     (28)
#define IRQ_A2O_DONE      (27)
#define IRQ_O2A_DONE      (26)
#define IRQ_A2O_START     (25)
#define IRQ_O2A_START     (24)
#define IRQ_A2O_BUSY      (23)
#define IRQ_O2A_BUSY      (22)
#define IRQ_REDMULE_BUSY  (21)
#define IRQ_FSYNC_DONE    (20)
#define IRQ_FSYNC_ERROR   (19)



#endif  // _TILE_REG_DEFS_