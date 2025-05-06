add_library(runtime STATIC)

file(GLOB_RECURSE ASM_SOURCES
  "src/crt0.S"
)

file(GLOB_RECURSE C_SOURCES
  "src/*.c"
)

set_property(SOURCE ${ASM_SOURCES} PROPERTY LANGUAGE ASM)

target_sources(runtime
  PRIVATE
  ${ASM_SOURCES}
  ${C_SOURCES}
)

# WIESEP: Export the target specific include directory
target_include_directories(runtime
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include
)

target_compile_options(runtime
  PRIVATE
  -O2
)

target_compile_options(runtime
  PUBLIC
  -march=${ISA}
  -mabi=${ABI}
)

target_link_options(runtime
  PUBLIC
  -L${CMAKE_CURRENT_LIST_DIR}
  -Tlink.ld
  -march=${ISA}
  -mabi=${ABI}
  -nostartfiles
  -ffreestanding
)