set(TEST_NAME test_helloworld)

file(GLOB_RECURSE TEST_SRCS
  "src/*.c"
)

add_executable(${TEST_NAME} ${TEST_SRCS})
target_include_directories(${TEST_NAME} PUBLIC include)

target_compile_options(${TEST_NAME}
  PRIVATE
  -O2
)
target_link_libraries(${TEST_NAME} PUBLIC runtime)

add_custom_command(
        TARGET ${TEST_NAME}
        POST_BUILD
        COMMAND ${CMAKE_OBJDUMP} -dhS $<TARGET_FILE:${TEST_NAME}> > $<TARGET_FILE:${TEST_NAME}>.s)
