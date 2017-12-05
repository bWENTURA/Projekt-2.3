#include "header.hpp"
#include "card.hpp"
#include "class_ship.hpp"

ship::ship(int new_size, bool status) : size(new_size), status(status) {
  //std::cout << LINE << "\nConstructor of ship class.\n" << LINE << std::endl;
}

ship::~ship(){
  //std::cout << LINE << "\nDestructor of ship class.\n" << LINE << std::endl;
}

int one_mast::number_to_set = 0;

one_mast::one_mast(): ship(1) {
  number_to_set++;
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

bool one_mast::can_fit_in_width(int width, int height, const card& present_card, int ** map){
  if(width + this->get_size() <= present_card.width){
    std::cout << "it's ok" << std::endl;
    int i;
    for(i = width; i < width + this->get_size(); i++){
      if(map[height][i] != 0) return false;
    }
    std::cout << "it's second ok" << std::endl;
    if(width + this->get_size() < present_card.width){
      std::cout << "it's third ok" << std::endl;
      if(height - 1 >= 0){
        if(map[height-1][width + this->get_size()] != 0) return false;
        else return true;
      }
      else{
        if(map[height][width + this->get_size()] != 0) return false;
      }
      return true;
    }
    else return true;
  }
  else return false;
}

bool one_mast::can_fit_in_height(int height, const card& present_card){
  if(height + this->get_size() <= present_card.height) return true;
  else return false;
}

bool one_mast::set_on_map(int &width, int &height, const card& present_card, int **map, std::vector<ship*> ships){
  if((present_card.width - width < this->get_size()) && (present_card.height - height < this->get_size())){
    std::cout << "There's not enough space to fit ship." << std::endl;
    return false;
  }
  else{
    if(this->can_fit_in_width(width, height, present_card, map)){
      this->status = true;
      for(int i = width; i < width + this->get_size(); i++) map[height][i] = this->get_size();
      if(width + this->get_size() + 1 >= present_card.width){
        height++;
        width = 0;
      }
      else width = width + 2;
      return true;
    }
    else return false;
  }
}

//one_mast::one_mast(): ship() {};
