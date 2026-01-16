# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/appWeStudy_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/appWeStudy_autogen.dir/ParseCache.txt"
  "appWeStudy_autogen"
  )
endif()
