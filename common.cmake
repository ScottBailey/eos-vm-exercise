

# Safety and sanity check.
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "Prevented in-tree built. This is bad practice.")
endif()


set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility-inlines-hidden" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror" )
#set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunreachable-code" )  At this time, -Wunreachable-code is probably unstable.
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfloat-equal")
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow")
#  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wzero-as-null-pointer-constant")
