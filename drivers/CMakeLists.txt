# Define mappings for drivers
set(DRIVER_MAPPINGS
    magia:magia_mesh
)

# Call the macro
add_magia_subdirectories(${TARGET_PLATFORM} "Driver" "${DRIVER_MAPPINGS}")

target_include_directories(runtime_host PUBLIC ${CMAKE_CURRENT_LIST_DIR})