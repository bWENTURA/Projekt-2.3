#include "header.hpp"
#include "card.hpp"
#include "class_ship.hpp"
#include "functions.hpp"

int main(int argc, char * argv[]){
  if(argc == 2){
    card * present_card = new card;
    std::vector<ship*> ships;
    std::ifstream file;
    file.open(argv[1]);
    if(read_size(file, *present_card) && read_ships_quantity(file, ships)){
      std::cout << "Bangla" << std::endl;
      int ** map = new int*[present_card->height];
      for(int i = 0; i < present_card->height; i++){
        map[i] = new int[present_card->width];
        for(int j = 0; j < present_card->width; j++) map[i][j] = 0;
      }
      if(!fill_up_the_map(*present_card, map, ships)){
        std::cout << LINE << "\nSomething went wrong with setting ships on the map.\n" << LINE << std::endl;
      }
      std::cout << present_card->width << "    " << present_card->height << std::endl;
      show_map(*present_card, map, ships);
      for(ship * iterator: ships) delete iterator;
      for(int i = 0; i < present_card->height; i++) delete[] map[i];
      delete[] map;
    }
    file.close();
    delete present_card;
  }
  else std::cout << "Number of parameters is wrong." << std::endl;
  return 0;
}
