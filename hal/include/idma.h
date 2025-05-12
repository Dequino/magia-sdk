#ifndef HAL_IDMA_H
#define HAL_IDMA_H

typedef struct idma_controller idma_controller_t;
typedef struct idma_controller_api idma_controller_api_t;

struct idma_controller {
    idma_controller_api_t *api;
    uint32_t base;
    void *cfg;
};

struct idma_controller_api {
    int (init*)(idma_controller_t *ctrl);
};

extern idma_controller_api_t idma_api;

#endif