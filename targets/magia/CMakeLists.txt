################################################################################
# Host Runtime Library                                                         #
################################################################################
add_library(runtime_host STATIC)

file(GLOB_RECURSE ASM_SOURCES
  "src/crt0.S"
)

file(GLOB_RECURSE C_SOURCES
  "src/*.c"
)

set_property(SOURCE ${ASM_SOURCES} PROPERTY LANGUAGE ASM)

target_sources(runtime_host
  PRIVATE
  ${ASM_SOURCES}
  ${C_SOURCES}
)

# WIESEP: Export the target specific include directory
target_include_directories(runtime_host
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include
)

target_compile_options(runtime_host
  PRIVATE
  -O2
)

target_compile_options(runtime_host
  PUBLIC
  -march=${ISA_HOST}
  -mabi=${ABI}
)

target_link_options(runtime_host
  PUBLIC
  -L${CMAKE_CURRENT_LIST_DIR}
  -Tlink.ld
  -march=${ISA_HOST}
  -mabi=${ABI}
  -nostartfiles
  -ffreestanding
)

################################################################################
# Magia mesh Runtime Library                                                 #
################################################################################
add_library(runtime_mesh_magia STATIC)

# WIESEP: Export the headers also to the cluster runtime
target_include_directories(runtime_mesh_magia
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include
)

# WIESEP: Do not export optimization flags
target_compile_options(runtime_mesh_magia
  PRIVATE
  -O2
)

target_compile_options(runtime_mesh_magia
  PUBLIC
  -march=${ISA_CLUSTER_PULP}
  -mabi=${ABI}
)

# WIESEP: Expose common link option
target_link_options(runtime_mesh_magia
  PUBLIC
  -march=${ISA_CLUSTER_PULP}
  -mabi=${ABI}
  -nostartfiles
  -ffreestanding
)