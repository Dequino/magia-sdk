file(GLOB_RECURSE C_SOURCES_MAGIA
  "trampoline_magiaMesh.c"
)

target_sources(runtime_mesh_magia PRIVATE ${C_SOURCES_MAGIA})
target_include_directories(runtime_mesh_magia PUBLIC ${CMAKE_CURRENT_LIST_DIR})