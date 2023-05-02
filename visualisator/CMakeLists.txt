PROJECT(visualisation)
cmake_minimum_required(VERSION 3.22)

set (CMAKE_CXX_STANDARD 11)

set(EXAMPLES
  visualisation
)
  
foreach(EXAMPLE ${EXAMPLES})
    add_executable(${EXAMPLE} ${EXAMPLE}.cpp)
    if(UNIX)
      target_link_libraries(${EXAMPLE} -lm)
    endif()
endforeach()
