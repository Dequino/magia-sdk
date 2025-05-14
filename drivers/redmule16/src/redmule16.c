// Copyright 2025 ETH Zurich and University of Bologna.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Viviane Potocnik <vivianep@iis.ee.ethz.ch>
// Alberto Dequino <alberto.dequino@unibo.it>
//
// This file provides the strong (driver-specific) implementations for the
// Redmule functions on FP16 vector data.
// These functions override the weak HAL symbols.
// This is a WIP and might be redundant, as the moment of writing there is only one Redmule configuration tested on MAGIA.


#include "redmule16.h"
#include "regs/tile_ctrl.h"
#include "utils/redmule_isa_utils.h"
#include "utils/magia_utils.h"

static int redmule16_init(redmule_controller_t *ctrl) {
    (void)ctrl;
    return 0;
}


/* Export the Redmule-specific controller API */
redmule_controller_api_t redmule_api = {
    .init = redmule16_init,
};