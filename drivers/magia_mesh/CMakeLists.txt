################################################################################
# Host Runtime Library                                                         #
################################################################################
file(GLOB_RECURSE C_SOURCES
  "*.c"
)

target_sources(runtime_host PRIVATE ${C_SOURCES})
target_compile_definitions(runtime_host INTERFACE MAGIA_DRIVER_MAGIA_MESH)

target_include_directories(runtime_host PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)