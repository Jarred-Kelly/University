# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\COS2614A1_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\COS2614A1_autogen.dir\\ParseCache.txt"
  "COS2614A1_autogen"
  )
endif()
