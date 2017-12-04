#include "header.hpp"
#include "card.hpp"
#include "class_ship.hpp"
#include "functions.hpp"

int main(){
  card * present_card = new card;
  std::vector<ship*> ships;
  std::ifstream file;
  file.open("test.txt");
  if(read_size(file, *present_card) && read_ships_quantity(file, ships)){
    std::cout << "Bangla" << std::endl;
  }
  else{
    std::cout << LINE << "\nSomething went wrong.\n" << LINE << std::endl;
  }
  file.close();
  for(ship * iterator: ships) delete iterator;
  delete present_card;
  return 0;
}
