# Define mappings for devices
set(DEVICE_MAPPINGS
    magia:magia_mesh
)

# Call the macro
add_magia_subdirectories(${TARGET_PLATFORM} "Device" "${DEVICE_MAPPINGS}")