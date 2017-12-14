#include "header.hpp"
#include "card.hpp"
#include "class_ship.hpp"
#include "specific_classes.hpp"

// Dla każdej klasy znajduje się definicja konstruktora, destruktora, i funkcji operujących na polu statycznym


int one_mast::number_to_set = 0;

one_mast::one_mast(): ship(1) {
  number_to_set++;
  //std::cout << LINE << "\nConstructor of one_mast class.\n" << LINE << std::endl;
}

one_mast::~one_mast(){
  number_to_set = 0;
  //std::cout << LINE << "\nDestructor of one_mast class.\n" << LINE << std::endl;
}

void one_mast::change_extant(){
  number_to_set--;
}

int one_mast::get_extant(){
    return number_to_set;
}

int two_mast::number_to_set = 0;

two_mast::two_mast(): ship(2) {
  number_to_set++;
  //std::cout << LINE << "\nConstructor of two_mast class.\n" << LINE << std::endl;
}

two_mast::~two_mast(){
  number_to_set = 0;
  //std::cout << LINE << "\nDestructor of two_mast class.\n" << LINE << std::endl;
}

void two_mast::change_extant(){
  number_to_set--;
}
int two_mast::get_extant(){
    return number_to_set;
}

int three_mast::number_to_set = 0;

three_mast::three_mast(): ship(3) {
  number_to_set++;
  //std::cout << LINE << "\nConstructor of three_mast class.\n" << LINE << std::endl;
}

three_mast::~three_mast(){
  number_to_set = 0;
  //std::cout << LINE << "\nDestructor of three_mast class.\n" << LINE << std::endl;
}

void three_mast::change_extant(){
  number_to_set--;
}

int three_mast::get_extant(){
    return number_to_set;
}

int four_mast::number_to_set = 0;

four_mast::four_mast(): ship(4) {
  number_to_set++;
  //std::cout << LINE << "\nConstructor of four_mast class.\n" << LINE << std::endl;
}

four_mast::~four_mast(){
  number_to_set = 0;
  //std::cout << LINE << "\nDestructor of four_mast class.\n" << LINE << std::endl;
}

void four_mast::change_extant(){
  number_to_set--;
}

int four_mast::get_extant(){
    return number_to_set;
}
