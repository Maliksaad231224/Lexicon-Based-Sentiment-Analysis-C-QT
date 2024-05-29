# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\lex_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\lex_autogen.dir\\ParseCache.txt"
  "lex_autogen"
  )
endif()
