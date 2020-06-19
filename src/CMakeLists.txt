
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

set (SOURCE_FILES 
  main.cpp
  glad.c
  Camera.cpp
  Shader.cpp
  StlReader.cpp
  Geometry.cpp
)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

add_executable(simpleStlViewer ${SOURCE_FILES})
target_include_directories(simpleStlViewer PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(simpleStlViewer PRIVATE ${GLFW_STATIC_LIBRARIES})
