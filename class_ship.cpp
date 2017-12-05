#include "header.hpp"
#include "class_ship.hpp"

ship::ship(int new_size, bool status) : size(new_size), status(status) {
  //std::cout << LINE << "\nConstructor of ship class.\n" << LINE << std::endl;
}

ship::~ship(){
  //std::cout << LINE << "\nDestructor of ship class.\n" << LINE << std::endl;
}

one_mast::one_mast(): ship(1) {
  //std::cout << LINE << "\nConstructor of one_mast class.\n" << LINE << std::endl;
}

one_mast::~one_mast(){
  //std::cout << LINE << "\nDestructor of one_mast class.\n" << LINE << std::endl;
}

int one_mast::get_size(){
    return size;
}

bool one_mast::get_status(){
  return status;
}

//one_mast::one_mast(): ship() {};
