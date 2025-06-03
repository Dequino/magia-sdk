# Magia-sdk
This repository contains the WIP development platform for the mesh-based architecture [Magia](https://github.com/pulp-platform/MAGIA/tree/main).
It provides useful tools for programming and running software applications on simulated MAGIA architectures for benchmarking, debugging and profiling.

Magia and Magia-SDK are developed as part of the [PULP project](https://pulp-platform.org/index.html), a joint effort between ETH Zurich and the University of Bologna.

## Getting started and Usage
Follow the instructions in the [Magia](https://github.com/pulp-platform/MAGIA/tree/main) repository to properly set up your own environment to use this SDK. In particular, you need to:

1. Set your **bash** (*very important*) environment correctly by running **in the MAGIA directory**: 
    
    `source setup_env.sh`

2. Build the Magia architecture following [the repository instructions](https://github.com/pulp-platform/MAGIA/tree/main). **Be very careful to set the desired number of tiles in the mesh**. Currently, FlooNoC supports 2x2, 4x4, 8x8, 16x16 and 32x32 architecture designs. The MAGIA files to be modified to change the number of tiles **before building the hardware** are:

    - *Makefile* (change `num_cores` to the total number of tiles: 4, 16, 64, 256, 1024)
    - *hw/mesh/magia_pkg.sv* (change the `N_TILES_X` and `N_TILES_Y` parameters to the dimensions desired supported by FlooNoC)

3. Make sure that all the tools are visible by shell with:

    `which cmake bender vsim python`

    In case your Python installation is not findable with `python` (for example, you only have `python3`), please make a symbolic link with your own Python binary to `python` or change the MAGIA *Makefile* calls to `python` to your own binary.

    You can make sure that bender is findable by running:

    `export PATH=<absolute path to MAGIA root directory>:$PATH`

4. Make sure the RISC-V GCC compiler is installed and visible in the `$PATH` environment variable. You can check if and where the compiler is installed by running the following command on your root (`/`) directory:

    `find . ! -readable -prune -o -name "riscv32-unknown-elf-gcc" -print`

    Then add the compiler to the `$PATH` environment variable with:

    `export PATH=<absolute path to directory containing the compiler binary>:$PATH`

5. You can now work with **magia-sdk**. `cd magia-sdk` and to compile and build the test binaries for a desired architecture run:

    `make clean build target-platform=<target_architecture_name (i.e. magia-2x2)> compiler=<GCC/LLVM>`

    To run one of the tests:

    `make run test=<name_of_test_binary_in_build/bin> platform=<rtl/gvsoc> num_cores=<total_number_of_tiles> gui=<0:terminal, 1:vsim graphic interface>`

## Adding your own test
This SDK uses a nested CMakeList mechanism to build and check for dependencies.
To add your own test, you have to integrate a new test folder inside the **tests** directory.

1. Change directory to the desired architecture test folder

    `cd tests/<architecture_name>/mesh`

2. Create a new test directory

    `mkdir <test_name>`

3. Modify the *CMakeList.txt* file in the current mesh directory, adding the following line:

    `add_subdirectory(<test_name>)`

    You can also *exclude* the generation of other tests binaries by commenting/deleting the lines for those tests.

4. Add to the *\<test_name\>* directory:

    1. A new CMakeList.txt file following this template:
    
            set(TEST_NAME <test_name>)

            file(GLOB_RECURSE TEST_SRCS
            "src/*.c"
            )

            add_executable(${TEST_NAME} ${TEST_SRCS})
            target_include_directories(${TEST_NAME} PUBLIC include)

            target_compile_options(${TEST_NAME}
            PRIVATE
            -O2
            )
            target_link_libraries(${TEST_NAME} PUBLIC runtime hal)

            add_custom_command(
                    TARGET ${TEST_NAME}
                    POST_BUILD
                    COMMAND ${CMAKE_OBJDUMP} -dhS $<TARGET_FILE:${TEST_NAME}> > $<TARGET_FILE:${TEST_NAME}>.s)
    
    2. An **src** directory containing your test's source (.c) files

    3. An **include** directory containing your test's header (.h) files

## Folder Structure

### targets
This directory contains the *startup routine*, *linker script*, *address map*, *register definitions*, *custom ISA instructions*, *MAGIA mesh and tile util instructions* for each specific architecture.

### scripts
Contains scripts to automatize the test building and running.

### hal
Contains the weak definitions of this SDK APIs. These are the API instruction that should be used by the programmer when developing applications to be run on MAGIA. These instructions are then overloaded by the corresponding driver implementation specific for the chosen architecture. The APIs currently available are for controlling and using the *idma*, *redmule* and *fractalsyn* modules.

### drivers
Contains the architecture-specific implementation and source code for the HAL APIs. Despite each implementation having different names, thanks to an aliasing system the programmer can use the same name for the same API instruction on different architectures.

### devices
Nothing there. 

If MAGIA ever evolves to have a host-offload mechanism, this folder will contain the trampoline functions.

### cmake
Contains utility files for *cmake* automatic compilation.

