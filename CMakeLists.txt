cmake_minimum_required(VERSION 3.1)

project(projectName)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)


# if(EXISTS ${PROJECT_SOURCE_DIR}/testing)
# 	message(STATUS "Including /testing directory")
# 	add_subdirectory(${PROJECT_SOURCE_DIR}/testing)
# endif(EXISTS ${PROJECT_SOURCE_DIR}/testing)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)