#include <iostream>

#include "stl_reader/stl_reader.h"

using std::cout;
using std::endl;  

int main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << "\tfile.stl" << endl;
    return EXIT_FAILURE;
  }

  std::string stlFile (argv[1]);
  cout << stlFile << endl;


  return EXIT_SUCCESS;
}