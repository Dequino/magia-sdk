# Define mappings for tests
set(TEST_MAPPINGS
    magia:magia
)

# Call the macro
add_magia_subdirectories(${TARGET_PLATFORM} "Test" "${TEST_MAPPINGS}")