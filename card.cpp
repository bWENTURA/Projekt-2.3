#include "header.hpp"
#include "card.hpp"

// Konstruktor i destruktor struktury card

card::card(){
  width = 0;
  height = 0;
  number_of_one_mast = 0;
  number_of_two_mast = 0;
  number_of_three_mast = 0;
  number_of_four_mast = 0;
  //std::cout << LINE << "\nCard object created.\n" << LINE << std::endl;
}

card::~card(){
  //std::cout << LINE << "\nCard object deleted.\n" << LINE << std::endl;
}
