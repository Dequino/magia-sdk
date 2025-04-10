set(CMAKE_EXECUTABLE_SUFFIX ".elf")

set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_C_COMPILER ${TOOLCHAIN_DIR}/riscv32-unknown-elf-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}/riscv32-unknown-elf-g++)
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_OBJCOPY ${TOOLCHAIN_DIR}/riscv32-unknown-elf-objcopy)
set(CMAKE_OBJDUMP ${TOOLCHAIN_DIR}/riscv32-unknown-elf-objdump)
set(CMAKE_AR ${TOOLCHAIN_DIR}/riscv32-unknown-elf-ar)