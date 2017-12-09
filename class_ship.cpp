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
  // if(width + this->get_size() <= present_card.width){
  //   std::cout << "it's ok" << std::endl;
  //   int i;
  //   for(i = width; i < width + this->get_size(); i++){
  //     if(map[height][i] != 0) return false;
  //   }
  //   std::cout << "it's second ok" << std::endl;
  //   if(width + this->get_size() < present_card.width){
  //     std::cout << "it's third ok" << std::endl;
  //     if(height - 1 >= 0){
  //       std::cout << "it's fourth ok" << std::endl;
  //       if(map[height-1][width + this->get_size()] != 0) return false;
  //       else{
  //         std::cout << "It's fifth ok" << std::endl;
  //         return true;
  //       }
  //     }
  //     else{
  //       if(map[height][width + this->get_size()] != 0) return false;
  //     }
  //     return true;
  //   }
  //   else return true;
  // }
  // else return false;
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
      }
      else return false;
    }
    else{
      if(height != 0){
          if(width != 0){
            if(map[height-1][width] != 0 || map[height][width]) return false;
            if(height + 1 != present_card.height()){
              if(map[height + 1][width] != 0) return false;
            }
          }
          for(int j = width; j < width + this->get_size(); j++){
            if(map[height-1][j] != 0) return false;
          }
          if(j != present_card.width()){
            if(map[height-1][j] != 0 || map[height][j]) return false;
            if(height + 1 != present_card.height()){
              if(map[height + 1][j] != 0) return false;
            }
          }
        }
      }
    }
  }
  else return false;
}

bool ship::can_fit_in_height(int height, const card& present_card){
  if(height + this->get_size() <= present_card.height) return true;
  else return false;
}

bool ship::set_on_map(int &width, int &height, const card& present_card, int **map, std::vector<ship*> ships){
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
      else width = width + this->get_size() + 1;
      std::cout << "Everything is ok." << std::endl;
      return true;
    }
    // else{
    //   std::cout << "Ship can't fit in width" << std::endl;
    //   if(height + 1 == present_card.height){
    //     std::cout << "There's no space to fit ship." << std::endl;
    //     return false;
    //   }
    //   else{
    //     height++;
    //     width = 0;
    //     return this->set_on_map(width, height, present_card, map, ships);
    //   }
    // }
    else return false;
  }
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

// bool one_mast::can_fit_in_width(int width, int height, const card& present_card, int ** map){
//   if(width + this->get_size() <= present_card.width){
//     std::cout << "it's ok" << std::endl;
//     int i;
//     for(i = width; i < width + this->get_size(); i++){
//       if(map[height][i] != 0) return false;
//     }
//     std::cout << "it's second ok" << std::endl;
//     if(width + this->get_size() < present_card.width){
//       std::cout << "it's third ok" << std::endl;
//       if(height - 1 >= 0){
//         if(map[height-1][width + this->get_size()] != 0) return false;
//         else return true;
//       }
//       else{
//         if(map[height][width + this->get_size()] != 0) return false;
//       }
//       return true;
//     }
//     else return true;
//   }
//   else return false;
// }
//
// bool one_mast::can_fit_in_height(int height, const card& present_card){
//   if(height + this->get_size() <= present_card.height) return true;
//   else return false;
// }

// bool one_mast::set_on_map(int &width, int &height, const card& present_card, int **map, std::vector<ship*> ships){
//   if((present_card.width - width < this->get_size()) && (present_card.height - height < this->get_size())){
//     std::cout << "There's not enough space to fit ship." << std::endl;
//     return false;
//   }
//   else{
//     if(this->can_fit_in_width(width, height, present_card, map)){
//       this->status = true;
//       for(int i = width; i < width + this->get_size(); i++) map[height][i] = this->get_size();
//       if(width + this->get_size() + 1 >= present_card.width){
//         height++;
//         width = 0;
//       }
//       else width = width + 2;
//       return true;
//     }
//     else return false;
//   }
// }

int two_mast::number_to_set = 0;

two_mast::two_mast(): ship(2) {
  number_to_set++;
  //std::cout << LINE << "\nConstructor of two_mast class.\n" << LINE << std::endl;
}

two_mast::~two_mast(){
  //std::cout << LINE << "\nDestructor of two_mast class.\n" << LINE << std::endl;
}

int two_mast::get_size(){
    return size;
}

bool two_mast::get_status(){
  return status;
}
//
// three_mast::three_mast(): ship(3) {
//   number_to_set++;
//   //std::cout << LINE << "\nConstructor of three_mast class.\n" << LINE << std::endl;
// }
//
// three_mast::~three_mast(){
//   //std::cout << LINE << "\nDestructor of three_mast class.\n" << LINE << std::endl;
// }
//
// int three_mast::get_size(){
//     return size;
// }
//
// four_mast::four_mast(): ship(4) {
//   number_to_set++;
//   //std::cout << LINE << "\nConstructor of four_mast class.\n" << LINE << std::endl;
// }
//
// four_mast::~four_mast(){
//   //std::cout << LINE << "\nDestructor of four_mast class.\n" << LINE << std::endl;
// }
//
// int four_mast::get_size(){
//     return size;
// }
