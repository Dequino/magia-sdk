file(GLOB_RECURSE SOURCES
  "src/*"
)

add_library(hal_host STATIC ${SOURCES})

target_include_directories(hal_host
  PUBLIC
  "include"
)
