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
    int i;
    for(i = width; i < width + this->get_size(); i++){
      if(map[height][i] != 0){
        can = false;
        break;
      }
    }
    if(can){
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
    else return false;
  }
  else return false;
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
  if(!this->get_status()){
    bool coordinates_changed = false;
    if(!this->try_to_place(width, height, present_card, map)){
      int between = 0;
      unsigned int next_index = index;
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
        switch(between){
          case 1:{
            std::cout << "In first" << std::endl;
            while(next_index != ships.size() && ships[next_index]->get_size() != 1){
              if(ships[next_index]->get_status()) next_index++;
              else next_index = next_index + ships[next_index]->get_extant();
            }
            if(next_index != ships.size()){
              while(ships[next_index]->get_status() && next_index + 1 != ships.size()){
                next_index++;
              }
              if(!ships[next_index]->get_status()){
                if(ships[next_index]->try_to_place(width, height, present_card, map)){
                  coordinates_changed = true;;
                }
              }
            }
            else{
              // height
            }
            break;
          }
          case 2:{
            std::cout << "In second" << std::endl;
            while(next_index != ships.size() && ships[next_index]->get_size() != 2){
                if(ships[next_index]->get_status()) next_index++;
                else next_index = next_index + ships[next_index]->get_extant();
            }
            if(next_index != ships.size()){
              while(ships[next_index]->get_status() && next_index + 1 != ships.size()){
                next_index++;
              }
              if(!ships[next_index]->get_status()){
                if(ships[next_index]->try_to_place(width, height, present_card, map)){
                  coordinates_changed = true;;
                }
              }
            }
            else{
              // height
            }
            break;
          }
          case 3:{
            std::cout << "In third" << std::endl;
            while(next_index != ships.size() && ships[next_index]->get_size() != 3){
                next_index = next_index + ships[next_index]->get_extant();
            }
            if(next_index != ships.size()){
              while(ships[next_index]->get_status() && next_index + 1 != ships.size()){
                next_index++;
              }
              if(!ships[next_index]->get_status()){
                if(ships[next_index]->try_to_place(width, height, present_card, map)){
                  coordinates_changed = true;;
                }
              }
            }
            else{

              // height
            }
            break;
          }
        }
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
    // else{
    //   bool can_fit = false;
    //   for(int i = width; i < present_card.width; i++){
    //     if(map[height][i] == 0){
    //       if(can_fit_in_height(i, height, present_card, map)){
    //         width = i;
    //         can_fit = true;
    //       }
    //     }
    //   }
    //   if(can_fit){
    //     for(int i = height; i < height + this->get_size(); i++) map[i][width] = this->get_size();
    //     this->status = true;
    //     this->change_extant();
    //     height++;
    //     width = 0;
    //     std::cout << "Everything is ok in height." << std::endl;
    //     return true;
    //   }
    //   else{
    //     if(width + 1 == present_card.width){
    //       if(height + 1 == present_card.height) return false;
    //       height++;
    //       width = 0;
    //     }
    //     else width = width + 1;
    //     return this->set_on_map(width, height, present_card, map, ships, index);
    //   }
    // }
    // if(smaller_fitted) return this->set_on_map(width, height, present_card, map, ships, index);
    // else{
    //   if(width + 1 == present_card.width){
    //     if(height + 1 == present_card.height) return false;
    //     height++;
    //     width = 0;
    //   }
    //   else width = width + 1;
    //   return this->set_on_map(width, height, present_card, map, ships, index);
    // }
  }
  else return true;
}

bool ship::try_to_place(int &width, int &height, const card &present_card, int **map){
  if(this->can_fit_in_width(width, height, present_card, map)){
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
  else return false;
}
