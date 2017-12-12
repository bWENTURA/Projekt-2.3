#include "header.hpp"
#include "card.hpp"
#include "class_ship.hpp"
#include "specific_classes.hpp"
#include "functions.hpp"

int main(int argc, char * argv[]){
  if(argc == 2){
    std::ifstream file;
    file.open(argv[1]);
    if(file){
      card * present_card = new card;
      std::vector<ship*> ships;
      if(read_card_size(file, *present_card) && read_ships_quantity(file, ships)){
        int ** map = new int*[present_card->height];
        for(int i = 0; i < present_card->height; i++){
          map[i] = new int[present_card->width];
          for(int j = 0; j < present_card->width; j++) map[i][j] = 0;
        }
        if(!fill_up_the_map(*present_card, map, ships)){
          std::cout << LINE << "\nSomething went wrong with setting ships on the map.\n" << LINE << std::endl;
        }
        show_map(*present_card, map, ships);
        for(int i = 0; i < present_card->height; i++) delete[] map[i];
        delete[] map;
      }
      for(ship * iterator: ships) delete iterator;
      delete present_card;
      file.close();
    }
    else{
      std::cout << "Program have not opened file correctly." << std::endl;
    }
  }
  else std::cout << "Number of parameters is wrong." << std::endl;
  return 0;
}
