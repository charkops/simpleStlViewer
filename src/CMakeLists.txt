
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

set (SOURCE_FILES 
  main.cpp
  geometry.cpp
  StlReader.cpp
)

add_executable(simpleStlViewer ${SOURCE_FILES})
target_include_directories(simpleStlViewer PRIVATE ${PROJECT_SOURCE_DIR}/include)

