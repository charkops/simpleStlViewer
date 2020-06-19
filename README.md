
# SimpleStlViewer: a minimal stl viewer made with OpenGL (GLFW + glad)

* Tested on Linux (ubuntu 18.04)

# Dependencies: GLFW 
* sudo apt install libglfw3 libglfw3-dev

* Simple Cmake Project structure, in order to build simply:
``` c++
  git clone --recursive https://github.com/charkops/simpleStlViewer
  cd ${PROJECT_SOURCE_DIR}
  mkdir build && cd build
  cmake ..
  make
  ./simpleStlViewer path_to_stl_file.stl

```