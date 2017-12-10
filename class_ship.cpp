#include "header.hpp"
#include "card.hpp"
#include "class_ship.hpp"

ship::ship(int new_size, bool status) : size(new_size), status(status) {
  //std::cout << LINE << "\nConstructor of ship class.\n" << LINE << std::endl;
}

ship::~ship(){
  //std::cout << LINE << "\nDestructor of ship class.\n" << LINE << std::endl;
}

bool ship::can_fit_in_width(int width, int height, const card& present_card, int ** map){
  std::cout << width << "    " << height << std::endl;
  if(width + this->get_size() <= present_card.width){
    bool can = true;
    bool check_for_smaller = false;
    int i;
    for(i = width; i < width + this->get_size(); i++){
      if(map[height][i] != 0) can = false;
      else check_for_smaller = true;
    }
    if(!can){
      if(check_for_smaller){
        std::cout << "Check for smaller." << std::endl;
        return true;
      }
      else return false;
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
  else return false;
}

bool ship::can_fit_in_height(int width, int height, const card& present_card, int ** map){
  if(height + this->get_size() <= present_card.height){
    // bool can = true;
    // bool check_for_smaller = false;
    int i;
    for(i = height; i < height + this->get_size(); i++){
      if(map[i][width] != 0) return false;
      // else check_for_smaller = true;
    }
    if(width != 0){
      for(int j = height; j < height + this->get_size(); j++){
        if(map[j][width-1] != 0) return false;
      }
      if((height != 0 && map[height-1][width-1]) || (height + this->get_size() != present_card.height && map[height + this->get_size()][width-1])) return false;
    }
    if((height != 0 && map[height-1][width]) || (height + this->get_size() != present_card.width && map[height + this->get_size()][width])) return false;
    if(width + 1 != present_card.width && ((height != 0 && map[height - 1][width + 1]) || (height + this->get_size() != present_card.width && map[height + this->get_size()][width + 1]))) return false;
    return true;
  }
  else return false;
}

bool ship::set_on_map(int &width, int &height, const card& present_card, int **map, std::vector<ship*> ships){
  if((present_card.width - width < this->get_size()) && (present_card.height - height < this->get_size())){
    std::cout << "There's not enough space to fit ship." << std::endl;
    return false;
  }
  else{
    bool can_fit = false;
    for(int i = width; i <= present_card.width - this->get_size(); i++){
      if(map[height][i] == 0){
        if(can_fit_in_width(width, height, present_card, map)){
          width = i;
          can_fit = true;
          break;
        }
      }
    }
    if(can_fit){
      for(int i = width; i < width + this->get_size(); i++) map[height][i] = this->get_size();
      this->status = true;
      std::cout << this->get_size() << " = rozmiar, ile jeszcze = " << this->get_extant() << std::endl;
      this->change_extant();
      std::cout << this->get_size() << " = rozmiar, ile jeszcze = " << this->get_extant() << std::endl;
      if(width + this->get_size() + 1 >= present_card.width){
        height++;
        width = 0;
      }
      else width = width + this->get_size() + 1;
      std::cout << "Everything is ok in width." << std::endl;
      return true;
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
        std::cout << this->get_size() << " = rozmiar, ile jeszcze = " << this->get_extant() << std::endl;
        this->change_extant();
        std::cout << this->get_size() << " = rozmiar, ile jeszcze = " << this->get_extant() << std::endl;
        height++;
        width = 0;
        std::cout << "Everything is ok in height." << std::endl;
        return true;
      }
      if(height + 1 == present_card.height) return false;
      height++;
      width = 0;
    }
    return this->set_on_map(width, height, present_card, map, ships);
  }
}
