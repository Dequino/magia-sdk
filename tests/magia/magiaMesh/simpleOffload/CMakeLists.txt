set(TEST_NAME test_magiaMesh_simpleOffload)

######## HOST Code #############################################################
file(GLOB_RECURSE TEST_HOST_SRCS
  "src_host/*.c"
)

add_library(${TEST_NAME}_host OBJECT ${TEST_HOST_SRCS})
target_include_directories(${TEST_NAME}_host PUBLIC include)

# WIESEP: Set the correct ISA and ABI for the host
target_compile_options(${TEST_NAME}_host
  PRIVATE
  -O2
)
target_link_libraries(${TEST_NAME}_host PUBLIC runtime_host hal_host)

######## MESH Code ##########################################################
file(GLOB_RECURSE TEST_PULP_SRCS
  "src_mesh/*.c"
)

add_library(${TEST_NAME}_mesh OBJECT ${TEST_PULP_SRCS})
target_include_directories(${TEST_NAME}_mesh PUBLIC include)

# WIESEP: Set the correct ISA and ABI for the mesh
target_compile_options(${TEST_NAME}_mesh
  PRIVATE
  -O2
)
target_link_libraries(${TEST_NAME}_mesh PUBLIC runtime_mesh_magia)

######## TEST Executable #######################################################
add_magia_test(
  ${TEST_NAME}
)

# WIESEP: Link the host and mesh code to the test executable
target_link_libraries(${TEST_NAME} PUBLIC ${TEST_NAME}_host)
target_link_libraries(${TEST_NAME} PUBLIC ${TEST_NAME}_mesh)