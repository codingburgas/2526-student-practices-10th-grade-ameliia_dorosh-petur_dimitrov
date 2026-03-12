# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\kino-plex_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\kino-plex_autogen.dir\\ParseCache.txt"
  "kino-plex_autogen"
  "pages\\CMakeFiles\\pages_autogen.dir\\AutogenUsed.txt"
  "pages\\CMakeFiles\\pages_autogen.dir\\ParseCache.txt"
  "pages\\pages_autogen"
  )
endif()
