set(TEST_NAME test_magiaMesh)

file(GLOB_RECURSE TEST_SRCS
  "src/*.c"
)

add_library(${TEST_NAME} OBJECT ${TEST_SRCS})
target_include_directories(${TEST_NAME} PUBLIC include)

target_compile_options(${TEST_NAME}
  PRIVATE
  -O2
)
target_link_libraries(${TEST_NAME} PUBLIC runtime hal)

add_magia_test(
  ${TEST_NAME}
)

target_link_libraries(${TEST_NAME} PUBLIC ${TEST_NAME})