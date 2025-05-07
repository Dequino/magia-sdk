# Define mappings for devices
set(DEVICE_MAPPINGS
    magia-2x2:
)

# Call the macro
add_magia_subdirectories(${TARGET_PLATFORM} "Device" "${DEVICE_MAPPINGS}")