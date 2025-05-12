// Copyright 2025 ETH Zurich and University of Bologna.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Viviane Potocnik <vivianep@iis.ee.ethz.ch>
// Alberto Dequino <alberto.dequino@unibo.it>
//
// These functions override the weak HAL symbols.


#include "idma32.h"
#include "regs/tile_ctrl.h"
#include "utils/idma_isa_utils.h"
#include "utils/magia_utils.h"

static int idma32_init(idma_controller_t *ctrl) {
    (void)ctrl;
    return 0;
}


/* Export the CLINT-specific interrupt API */
idma_controller_api_t idma_api = {
    .init = idma32_init,
};