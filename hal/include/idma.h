// Copyright 2024 ETH Zurich and University of Bologna.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Viviane Potocnik <vivianep@iis.ee.ethz.ch>
// Alberto Dequino <alberto.dequino@unibo.it>


#ifndef HAL_IDMA_H
#define HAL_IDMA_H

/** Forward declaration of the idma controller instance and API structure. */
typedef struct idma_controller idma_controller_t;
typedef struct idma_controller_api idma_controller_api_t;


/**
 * WIP
 * Holds the API function pointers, base address and controller-specific configuration.
 */
struct idma_controller {
    idma_controller_api_t *api;
    uint32_t base;
    void *cfg;
};

/**
 * WIP
 * IDMA API
 */
struct idma_controller_api {
    int (init*)(idma_controller_t *ctrl);
    int (memcpy_1d*)(uint8_t dir, uint32_t axi_addr, uint32_t obi_addr, volatile uint32_t len);
    int (memcpy_2d*)(uint8_t dir, uint32_t axi_addr, uint32_t obi_addr, uint32_t len, uint32_t std, uint32_t reps);
};

/*
 * Generic implementation of the IDMA controller.
 */
extern idma_controller_api_t idma_api;

#endif //HAL_IDMA_H