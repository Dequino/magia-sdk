set(AVAILABLE_TARGETS
  "magia"
  CACHE STRING "Available Targets"
)

get_property(OPT_STRINGS CACHE OPT PROPERTY STRINGS)

if(NOT TARGET_PLATFORM IN_LIST AVAILABLE_TARGETS)
  message(FATAL_ERROR "Wrong value for TARGET_PLATFORM: Got ${TARGET_PLATFORM}. Available targets are: ${AVAILABLE_TARGETS}")
endif()

message(STATUS "[MAGIA-SDK] TARGET_PLATFORM       : ${TARGET_PLATFORM}")

if (TARGET_PLATFORM STREQUAL "magia")
  add_subdirectory(magia)
endif()