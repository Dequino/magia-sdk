#ifndef HAL_REDMULE_H
#define HAL_REDMULE_H

/** Forward declaration of the Redmule controller instance and API structure. */
typedef struct redmule_controller redmule_controller_t;
typedef struct redmule_controller_api redmule_controller_api_t;

/**
 * WIP
 * Holds the API function pointers, base address and controller-specific configuration.
 */
struct redmule_controller {
    redmule_controller_api_t *api;
    uint32_t base;
    void *cfg;
};

/**
 * WIP
 * Redmule API
 */
struct redmule_controller_api {
    int (init*)(redmule_controller_t *ctrl);
};

/*
 * Generic implementation of the Redmule controller.
 */
extern redmule_controller_api_t redmule_api;

#endif //HAL_REDMULE_H