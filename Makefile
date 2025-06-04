# Copyright (C) 2023-2024 ETH Zurich and University of Bologna
#
# Licensed under the Solderpad Hardware License, Version 0.51 
# (the "License"); you may not use this file except in compliance 
# with the License. You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# SPDX-License-Identifier: SHL-0.51
#
# Authors: Victor Isachi <victor.isachi@unibo.it>
# Alberto Dequino <alberto.dequino@unibo.it>
# 
# Magia-sdk Makefile

SHELL 			:= /bin/bash

BUILD_DIR 		:= ../MAGIA/work/sw/tests/$(test).c
MAGIA_DIR 		:= ../MAGIA
BIN 			:= $(BUILD_DIR)/verif

target-platform := magia-2x2
compiler 		:= GCC
gui 			:= 0


clean:
	rm -rf build/

build:
ifeq ($(compiler), LLVM)
	$(error COMING SOON!)
endif
	cmake -DTARGET_PLATFORM=$(target-platform) -DCOMPILER=$(compiler) -B build --trace-expand
	cmake --build build --verbose

run: 
	@echo 'Magia is available at https://github.com/pulp-platform/MAGIA.git'
	@echo 'please run "source setup_env.sh" in the magia folder before running this script'
	@echo 'and make sure the risc-v objdump binary is visible on path using "which riscv32-unknown-elf-objdump".'
ifndef test
	$(error Proper formatting is: make run test=<test_name> platform=rtl|gvsoc <num_cores=x>)
endif
ifeq (,$(wildcard ./build/bin/$(test)))
	$(error No test found with name: $(test))
endif
ifndef platform
	$(error Proper formatting is: make run test=<test_name> platform=rtl|gvsoc)
endif
ifeq ($(platform), gvsoc)
	$(error COMING SOON!)
else ifeq ($(platform), rtl)
	mkdir -p $(BUILD_DIR)
	cp ./build/bin/$(test) $(BUILD_DIR)/verif
	objcopy --srec-len 1 --output-target=srec $(BIN) $(BIN).s19
	scripts/parse_s19.pl $(BIN).s19 > $(BIN).txt
	python3 scripts/s19tomem.py $(BIN).txt $(BUILD_DIR)/stim_instr.txt $(BUILD_DIR)/stim_data.txt
	cd $(BUILD_DIR)													&& \
	cp -sf ../../../../modelsim.ini modelsim.ini    				&& \
	ln -sfn ../../../../work work         			
	riscv32-unknown-elf-objdump -d -S $(BIN) > $(BIN).dump
	riscv32-unknown-elf-objdump -d -l -s $(BIN) > $(BIN).objdump
	python3 scripts/objdump2itb.py $(BIN).objdump > $(BIN).itb
	cd ../MAGIA 													&& \
	make run test=$(test) gui=$(gui)
else
	$(error Only rtl and gvsoc are supported as platforms.)
endif

MAGIA:
ifeq ($(target-platform), magia-2x2)
	sed -i -E 's/^(num_cores[[:space:]]*\?=[[:space:]]*)[0-9]+/\14/' $(MAGIA_DIR)/Makefile
	sed -i -E 's/^( *localparam int unsigned N_TILES_[XY][[:space:]]*=[[:space:]]*)[0-9]+;/\12;/' $(MAGIA_DIR)/hw/mesh/magia_pkg.sv
else ifeq ($(target-platform), magia-4x4)
	sed -i -E 's/^(num_cores[[:space:]]*\?=[[:space:]]*)[0-9]+/\116/' $(MAGIA_DIR)/Makefile
	sed -i -E 's/^( *localparam int unsigned N_TILES_[XY][[:space:]]*=[[:space:]]*)[0-9]+;/\14;/' $(MAGIA_DIR)/hw/mesh/magia_pkg.sv
else ifeq ($(target-platform), magia-8x8)
	sed -i -E 's/^(num_cores[[:space:]]*\?=[[:space:]]*)[0-9]+/\164/' $(MAGIA_DIR)/Makefile
	sed -i -E 's/^( *localparam int unsigned N_TILES_[XY][[:space:]]*=[[:space:]]*)[0-9]+;/\18;/' $(MAGIA_DIR)/hw/mesh/magia_pkg.sv
else ifeq ($(target-platform), magia-16x16)
	sed -i -E 's/^(num_cores[[:space:]]*\?=[[:space:]]*)[0-9]+/\1256/' $(MAGIA_DIR)/Makefile
	sed -i -E 's/^( *localparam int unsigned N_TILES_[XY][[:space:]]*=[[:space:]]*)[0-9]+;/\116;/' $(MAGIA_DIR)/hw/mesh/magia_pkg.sv
else
	$(error unrecognized platform (acceptable platform: magia-2x2|4x4|8x8|16x16).)
endif
	cd $(MAGIA_DIR)									&& \
	make python_venv || true						&& \
	source setup_env.sh 							&& \
	make python_deps || true						&& \
	make bender										&& \
	make update-ips > update-ips.log mesh_dv=1		&& \
	make floonoc-patch || true						&& \
	make build-hw > build-hw.log mesh_dv=1 			

