# Define mappings for drivers
set(DRIVER_MAPPINGS
    magia-2x2:
)

# Call the macro
add_magia_subdirectories(${TARGET_PLATFORM} "Driver" "${DRIVER_MAPPINGS}")

target_include_directories(runtime PUBLIC ${CMAKE_CURRENT_LIST_DIR})