#include "header.hpp"
#include "card.hpp"
#include "class_ship.hpp"

ship::ship(int new_size, bool status) : size(new_size), status(status) {
  //std::cout << LINE << "\nConstructor of ship class.\n" << LINE << std::endl;
}

ship::~ship(){
  //std::cout << LINE << "\nDestructor of ship class.\n" << LINE << std::endl;
}

bool ship::can_fit_in_width(int width, int height, const card& present_card, int ** map, bool &check_for_smaller){
  std::cout << width << "    " << height << std::endl;
  if(width + this->get_size() <= present_card.width){
    bool can = true;
    int i;
    for(i = width; i < width + this->get_size(); i++){
      if(map[height][i] != 0){
        can = false;
        break;
      }
    }
    if(i != width && i != width + this->get_size()) check_for_smaller = true;
    if(i == width + this->get_size()) check_for_smaller = false;
    if(!can){
      return false;
    }
    else{
      if(height != 0){
        for(int j = width; j < width + this->get_size(); j++){
          if(map[height-1][j] != 0) return false;
        }
        if((width != 0 && map[height-1][width-1]) || (width + this->get_size() != present_card.width && map[height-1][width + this->get_size()])) return false;
      }
      if((width != 0 && map[height][width-1]) || (width + this->get_size() != present_card.width && map[height][width + this->get_size()])) return false;
      if(height + 1 != present_card.height && ((width != 0 && map[height + 1][width-1]) || (width + this->get_size() != present_card.width && map[height + 1][width + this->get_size()]))) return false;
      return true;
    }
  }
  else{
    check_for_smaller = true;
    return false;
  }
}

bool ship::can_fit_in_height(int width, int height, const card& present_card, int ** map){
  std::cout << width << "    " << height << std::endl;
  if(height + this->get_size() <= present_card.height){
    int i;
    for(i = height; i < height + this->get_size(); i++){
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

bool ship::set_on_map(int &width, int &height, const card &present_card, int **map, std::vector<ship*> ships, unsigned int index){
  bool check_for_smaller = false;
  if(!this->get_status()){
    bool can_fit = false;
    bool smaller_fitted = false;
    if(can_fit_in_width(width, height, present_card, map, check_for_smaller)){
      can_fit = true;
    }
    else{
      if(check_for_smaller && (index + this->get_extant() != ships.size())){
        std::cout << "IN DA HAUS index = " << index + this->get_extant() << " rozmiar = " << ships[index + this->get_extant()]->get_size() << std::endl;
        smaller_fitted = ships[index + this->get_extant()]->try_to_place(width, height, present_card, map, ships, index + this->get_extant());
      }
    }
    if(can_fit){
      if(this->get_size() == 2 && (width + this->get_size() != present_card.width) && (index + this->get_extant() != ships.size())){
        smaller_fitted = ships[index + this->get_extant()]->try_to_place(width, height, present_card, map, ships, index + this->get_extant());
      }
      else{
        for(int i = width; i < width + this->get_size(); i++) map[height][i] = this->get_size();
        this->status = true;
        this->change_extant();
        if(width + this->get_size() + 1 >= present_card.width){
          height++;
          width = 0;
        }
        else width = width + this->get_size() + 1;
        std::cout << "Everything is ok in width." << std::endl;
        return true;
      }
    }
    else{
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
        this->status = true;
        this->change_extant();
        height++;
        width = 0;
        std::cout << "Everything is ok in height." << std::endl;
        return true;
      }
    }
    if(smaller_fitted) return this->set_on_map(width, height, present_card, map, ships, index);
    else{
      if(width + 1 == present_card.width){
        if(height + 1 == present_card.height) return false;
        height++;
        width = 0;
      }
      else width = width + 1;
      return this->set_on_map(width, height, present_card, map, ships, index);
    }
  }
  else return true;
}

bool ship::try_to_place(int &width, int &height, const card &present_card, int **map, std::vector<ship*> ships, unsigned int index){
  if(!this->status){
    bool check_for_smaller = false;
    if(this->can_fit_in_width(width, height, present_card, map, check_for_smaller)){
      if(this->get_size() == 2 && (width + this->get_size() != present_card.width) && index + this->get_extant() != ships.size()){
        return ships[index + this->get_extant()]->try_to_place(width, height, present_card, map, ships, index + this->get_extant());
      }
      else{
        for(int i = width; i < width + this->get_size(); i++) map[height][i] = this->get_size();
        this->status = true;
        this->change_extant();
        if(width + this->get_size() + 1 >= present_card.width){
          height++;
          width = 0;
        }
        else width = width + this->get_size() + 1;
        std::cout << "Everything is ok in width ~~ try to place." << std::endl;
        return true;
      }
    }
    else{
      if(check_for_smaller && (index + this->get_extant() != ships.size())){
        std::cout << "Da fuck" << std::endl;
        return ships[index + this->get_extant()]->try_to_place(width, height, present_card, map, ships, index + this->get_extant());
      }
      return false;
    }
  }
  else{
    if(index + 1 != ships.size()){
      return ships[index + 1]->try_to_place(width, height, present_card, map, ships, index + 1);
    }
    else return false;
  }
}
