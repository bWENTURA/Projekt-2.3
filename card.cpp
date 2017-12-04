#include "header.hpp"
#include "card.hpp"

card::card(){
  width = 0;
  height = 0;
}

card::~card(){
  std::cout << LINE << "\nCard object deleted\n" << LINE << std::endl;
}
