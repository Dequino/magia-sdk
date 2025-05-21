set(TEST_NAME test_magiaMesh)

file(GLOB_RECURSE TEST_SRCS
  "src/*.c"
)

add_library(${TEST_NAME}_lib OBJECT ${TEST_SRCS})
target_include_directories(${TEST_NAME}_lib PUBLIC include)

target_compile_options(${TEST_NAME}_lib
  PRIVATE
  -O2
)
target_link_libraries(${TEST_NAME}_lib PUBLIC runtime hal)

add_magia_test(
  ${TEST_NAME}
)

target_link_libraries(${TEST_NAME} PUBLIC ${TEST_NAME}_lib)