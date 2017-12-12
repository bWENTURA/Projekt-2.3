#include "header.hpp"
#include "card.hpp"
#include "class_ship.hpp"

// Konstruktor klasy bazowe ship
ship::ship(int new_size, bool status) : size(new_size), status(status) {
  //std::cout << LINE << "\nConstructor of ship class.\n" << LINE << std::endl;
}

// Destruktor klasy bazowej ship
ship::~ship(){
  //std::cout << LINE << "\nDestructor of ship class.\n" << LINE << std::endl;
}

// Funkcja zwracająca wielkość danego obiektu typu ship
int ship::get_size(){
  return size;
}

// Funkcja zwracająca status obiektu typu ship
bool ship::get_status(){
  return status;
}

// Funkcja zmieniająca status danego obiektu na pozytywny
void ship::change_status_positive(){
  status = true;
}

//Funkcja sprawdzająca czy obiekt typu ship może zmieścić się w poziomie na mapie o podanej wielkości
bool ship::can_fit_in_width(int width, int height, const card& present_card, int ** map){
  // Sprawdzenie czy statek zmieści się w poziomie
  if(width + this->get_size() <= present_card.width){
    bool can = true;
    // Sprawdzenie czy pola do umieszczenia statku są wolne
    for(int i = width; i < width + this->get_size(); i++){
      if(map[height][i] != 0){
        can = false;
        break;
      }
    }
    if(can){
      if(height != 0){
        // Sprawdzenie czy pola nad statkiem są wolne
        for(int j = width; j < width + this->get_size(); j++){
          if(map[height-1][j] != 0) return false;
        }
        // Sprawdzenie czy pola w górnym lewym i prawym rogu wybranego obszaru są wolne
        if((width != 0 && map[height-1][width-1]) || (width + this->get_size() != present_card.width && map[height-1][width + this->get_size()])) return false;
      }
      // Sprawdzenie czy pojedyncze pola przed i za wybranym obszarem są wolne
      if((width != 0 && map[height][width-1]) || (width + this->get_size() != present_card.width && map[height][width + this->get_size()])) return false;
      // Sprawdzenie czy pojedyncze pola w dolym lewym i prawym rogu wybranego obszaru są wolne
      if(height + 1 != present_card.height && ((width != 0 && map[height + 1][width-1]) || (width + this->get_size() != present_card.width && map[height + 1][width + this->get_size()]))) return false;
      return true;
    }
    else return false;
  }
  else return false;
}

//Funkcja sprawdzająca czy statek może się zmieścić w pionie, działająca podobnie do funkcji wyżej
bool ship::can_fit_in_height(int width, int height, const card& present_card, int ** map){
  // Sprawdzenie czy statek mieści się w pionie
  if(height + this->get_size() <= present_card.height){
    // Sprawdzenie 
    for(int i = height; i < height + this->get_size(); i++){
      if(map[i][width] != 0) return false;
    }
    if(width != 0){
      for(int j = height; j < height + this->get_size(); j++){
        if(map[j][width-1] != 0) return false;
      }
      if((height != 0 && map[height-1][width-1]) || (height + this->get_size() != present_card.height && map[height + this->get_size()][width-1])) return false;
    }
    if((height != 0 && map[height-1][width]) || (height + this->get_size() != present_card.height && map[height + this->get_size()][width])) return false;
    if(width + 1 != present_card.width && ((height != 0 && map[height - 1][width + 1]) || (height + this->get_size() != present_card.height && map[height + this->get_size()][width + 1]))) return false;
    return true;
  }
  else return false;
}

bool ship::find_smaller(std::vector<ship*> ships, unsigned int &index, int size){
  unsigned int next_index = index;
  while(next_index != ships.size() && ships[next_index]->get_size() > size){
    std::cout << next_index << "    " << ships[next_index]->get_extant() << "     " << next_index + ships[next_index]->get_extant() << std::endl;
    if(ships[next_index]->get_status()){
      next_index++;
    }
    else{
      next_index = next_index + ships[next_index]->get_extant();
    }
    // if(next_index != ships.size() && next_index == next_index + ships[next_index]->get_extant()){
    //   std::cout << "inside!" << std::endl;
    //   if(ships[next_index]->get_status()){
    //     std::cout << "inside1!" << std::endl;
    //     next_index++;
    //   }
    // }
  }
  if(next_index != ships.size() && ships[next_index]->get_size() == size){
    while(ships[next_index]->get_status() && next_index + 1 != ships.size() && ships[next_index]->get_size() == size){
      std::cout << "inside2!" << std::endl;

      next_index++;
    }
    if(!ships[next_index]->get_status() && ships[next_index]->get_size() == size){
      std::cout << "inside3! siz = " << ships[next_index]->get_size() << std::endl;

      index = next_index;
      return true;
    }
  }
  return false;
}

bool ship::set_on_map(int &width, int &height, const card &present_card, int **map, std::vector<ship*> ships, unsigned int index){
  std::cout << "index = " << index << std::endl;
  if(!this->get_status()){
    bool coordinates_changed = false;
    if(!this->can_fit_in_width(width, height, present_card, map)){
      int between = 0;
      for(int i = width; i < width + this->get_size() && i != present_card.width; i++){
        if(map[height][i] == 0){
          between++;
        }
        else{
          between--;
          break;
        }
      }
      if(this->get_size() != between){
        std::cout << "In between" << std::endl;
        unsigned int next_index = index;
        switch(between){
          case 1:{
            std::cout << "In first" << std::endl;
            if(find_smaller(ships, next_index, 1)){
              std::cout << "founded!" << std::endl;
              if(ships[next_index]->try_to_place_horizontal(width, height, present_card, map)){
                coordinates_changed = true;;
              }
            }
            else{
              if(this->try_to_place_vertical(width, height, present_card, map)){
                return true;
              }
              else{
                std::cout << "brum!" << std::endl;
                next_index = index;
                if(this->get_size() != 3){
                  std::cout << "brum1!" << std::endl;

                  if(find_smaller(ships, next_index, 3)){
                    std::cout << "brum3!" << std::endl;

                    if(ships[next_index]->try_to_place_horizontal(width, height, present_card, map)){
                      coordinates_changed = true;
                    }
                  }
                }
                if(!coordinates_changed && height + 2 == present_card.height){
                  std::cout << "brum4!" << std::endl;

                  next_index = index;
                  if(find_smaller(ships, next_index, 2)){
                    std::cout << "brum5!" << std::endl;

                    if(ships[next_index]->try_to_place_vertical(width, height, present_card, map)){
                      coordinates_changed = true;
                    }
                  }
                }
              }
            }
            break;
          }
          case 2:{
            std::cout << "In second" << std::endl;
            if(find_smaller(ships, next_index, 2)){
              std::cout << "founded!" << std::endl;
              if(ships[next_index]->try_to_place_horizontal(width, height, present_card, map)){
                coordinates_changed = true;;
              }
            }
            else{
              if(this->try_to_place_vertical(width, height, present_card, map)){
                return true;
              }
            }
            break;
          }
          case 3:{
            std::cout << "In third" << std::endl;
            if(find_smaller(ships, next_index, 3)){
              std::cout << "founded! " << next_index << std::endl;
              if(ships[next_index]->try_to_place_horizontal(width, height, present_card, map)){
                coordinates_changed = true;;
              }
            }
            else{
              if(find_smaller(ships, next_index, 1)){
                std::cout << "founded!" << std::endl;
                if(ships[next_index]->try_to_place_horizontal(width, height, present_card, map)){
                  coordinates_changed = true;;
                }
              }
              if(coordinates_changed){
                if(this->try_to_place_vertical(width, height, present_card, map)){
                  return true;
                }
                else{
                  if(find_smaller(ships, next_index, 1)){
                    std::cout << "founded!" << std::endl;
                    if(ships[next_index]->try_to_place_horizontal(width, height, present_card, map)){
                      coordinates_changed = true;;
                    }
                  }
                  else{
                    if(find_smaller(ships, next_index, 2)){
                      std::cout << "founded!" << std::endl;
                      if(ships[next_index]->try_to_place_vertical(width, height, present_card, map)){
                        coordinates_changed = true;;
                      }
                    }
                  }
                }
              }
            }
            break;
          }
        }
      }
    }
    else{
      bool another_one = false;
      if(width + this->get_size() + 1 == present_card.width){
        unsigned next_index_1 = index, next_index_2 = index, next_index_3 = index;
        switch(this->get_size()){
          case 4:{
            std::cout << "In case 4" << std::endl;

            if(find_smaller(ships, next_index_1, 3) && find_smaller(ships, next_index_2, 1)){
              std::cout << "In case 41" << std::endl;

              if(ships[next_index_1]->try_to_place_horizontal(width, height, present_card, map) && ships[next_index_2]->try_to_place_horizontal(width, height, present_card, map)){
                another_one = true;
              }
            }
            if(!another_one){
              std::cout << "In case 42" << std::endl;

              next_index_1 = index;
              if(find_smaller(ships, next_index_1, 2)){
                std::cout << "In case 421" << std::endl;
                std::cout << "next_index_1 = " << next_index_1 << std::endl;
                next_index_2 = next_index_1 + 1;
                std::cout << "next_index_2 = " << next_index_2 << std::endl;
                if(find_smaller(ships, next_index_2, 2)){
                  std::cout << "In case 422" << std::endl;

                  if(ships[next_index_1]->try_to_place_horizontal(width, height, present_card, map) && ships[next_index_2]->try_to_place_horizontal(width, height, present_card, map)){
                    another_one = true;
                  }
                }
              }
            }
            if(!another_one){
              std::cout << "In case 43" << std::endl;

              next_index_1 = index;
              if(find_smaller(ships, next_index_1, 1)){
                next_index_2 = next_index_1 + 1;
                if(find_smaller(ships, next_index_2, 1)){
                  next_index_3 = next_index_2 + 1;
                  if(find_smaller(ships, next_index_3, 1)){
                    if(ships[next_index_1]->try_to_place_horizontal(width, height, present_card, map) && ships[next_index_2]->try_to_place_horizontal(width, height, present_card, map) && ships[next_index_3]->try_to_place_horizontal(width, height, present_card, map)){
                      another_one = true;
                    }
                  }
                }
              }
            }
            break;
          }
          case 3:{
            if(find_smaller(ships, next_index_1, 2) && find_smaller(ships, next_index_2, 1)){
              if(ships[next_index_1]->try_to_place_horizontal(width, height, present_card, map) && ships[next_index_2]->try_to_place_horizontal(width, height, present_card, map)){
                another_one = true;
              }
            }
            break;
          }
          case 2:{
            if(find_smaller(ships, next_index_1, 1) && find_smaller(ships, next_index_2, 1)){
              if(ships[next_index_1]->try_to_place_horizontal(width, height, present_card, map) && ships[next_index_2]->try_to_place_horizontal(width, height, present_card, map)){
                another_one = true;
              }
            }
            break;
          }
        }
      }
      if(!another_one) return this->try_to_place_horizontal(width, height, present_card, map);
    }
    if(!coordinates_changed){
      if(width + 1 == present_card.width){
        if(height + 1 == present_card.height) return false;
        height++;
        width = 0;
      }
      else width = width + 1;
    }
    return this->set_on_map(width, height, present_card, map, ships, index);
  }
  else return true;
}

bool ship::try_to_place_horizontal(int &width, int &height, const card &present_card, int **map){
  if(this->can_fit_in_width(width, height, present_card, map)){
    for(int i = width; i < width + this->get_size(); i++) map[height][i] = this->get_size();
    this->change_status_positive();
    this->change_extant();
    if(width + this->get_size() + 1 >= present_card.width){
      height++;
      width = 0;
    }
    else width = width + this->get_size() + 1;
    std::cout << "Everything is ok in width ~~ try to place." << std::endl;
    return true;
  }
  else return false;
}

bool ship::try_to_place_vertical(int &width, int &height, const card &present_card, int **map){
  bool can_fit = false;
  for(int i = width; i < present_card.width; i++){
    if(map[height][i] == 0){
      if(can_fit_in_height(i, height, present_card, map)){
        width = i;
        can_fit = true;
      }
    }
  }
  if(can_fit){
    for(int i = height; i < height + this->get_size(); i++) map[i][width] = this->get_size();
    this->change_status_positive();
    this->change_extant();
    height++;
    width = 0;
    std::cout << "Everything is ok in height." << std::endl;
    return true;
  }
  else return false;
}
