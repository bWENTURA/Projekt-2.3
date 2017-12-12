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
bool ship::can_fit_in_width(int width, int height, const card& present_card, char ** map){
  // Sprawdzenie czy statek zmieści się w poziomie
  if(width + this->get_size() <= present_card.width){
    bool can = true;
    // Sprawdzenie czy pola do umieszczenia statku są wolne
    for(int i = width; i < width + this->get_size(); i++){
      if(map[height][i] != '-'){
        can = false;
        break;
      }
    }
    if(can){
      if(height != 0){
        // Sprawdzenie czy pola nad statkiem są wolne
        for(int j = width; j < width + this->get_size(); j++){
          if(map[height-1][j] != '-') return false;
        }
        // Sprawdzenie czy pojdyncze pola w górnym lewym i prawym rogu wybranego obszaru są wolne
        if((width != 0 && map[height-1][width-1] != '-') || (width + this->get_size() != present_card.width && map[height-1][width + this->get_size()] != '-')) return false;
      }
      // Sprawdzenie czy pojedyncze pola przed i za wybranym obszarem są wolne
      if((width != 0 && map[height][width-1] != '-') || (width + this->get_size() != present_card.width && map[height][width + this->get_size()] != '-')) return false;
      // Sprawdzenie czy pojedyncze pola w dolnym lewym i prawym rogu wybranego obszaru są wolne
      if(height + 1 != present_card.height && ((width != 0 && map[height + 1][width-1] != '-') || (width + this->get_size() != present_card.width && map[height + 1][width + this->get_size()] != '-'))) return false;
      return true;
    }
    else return false;
  }
  else return false;
}

//Funkcja sprawdzająca czy statek może się zmieścić w pionie, działająca podobnie do funkcji wyżej
bool ship::can_fit_in_height(int width, int height, const card& present_card, char ** map){
  // Sprawdzenie czy statek mieści się w pionie
  if(height + this->get_size() <= present_card.height){
    // Sprawdzenie czy pola do umieszczenia statku są wolne w pionie
    for(int i = height; i < height + this->get_size(); i++){
      if(map[i][width] != '-') return false;
    }
    if(width != 0){
      // Sprawdzenie czy pola po lewej stronie statku są wolne
      for(int j = height; j < height + this->get_size(); j++){
        if(map[j][width-1] != '-') return false;
      }
      // Sprawdzenie czy pola w górnym i dolnym rogu po lewej stronie wybranego obszaru są wolne
      if((height != 0 && map[height-1][width-1] != '-') || (height + this->get_size() != present_card.height && map[height + this->get_size()][width-1] != '-')) return false;
    }
    // Sprawdzenie czy pola nad i pod obszarem są wolne
    if((height != 0 && map[height-1][width] != '-') || (height + this->get_size() != present_card.height && map[height + this->get_size()][width] != '-')) return false;
    // Sprawdzenie czy pola w górnym i dolnym rogu po prawej stronie wybranego obszaru są wolne
    if(width + 1 != present_card.width && ((height != 0 && map[height - 1][width + 1] != '-') || (height + this->get_size() != present_card.height && map[height + this->get_size()][width + 1] != '-'))) return false;
    return true;
  }
  else return false;
}

// Funkcja sprawdzająca czy jest mniejszy statek, który można by umieścić w wolnej przestrzeni lub zastępczo
bool ship::find_smaller(std::vector<ship*> ships, unsigned int &index, int size){
  unsigned int next_index = index;
  // Pętla wyszukuje statek o rozmiarze podanym jako argument
  while(next_index != ships.size() && ships[next_index]->get_size() > size){
    if(ships[next_index]->get_status()){
      next_index++;
    }
    else{
      next_index = next_index + ships[next_index]->get_extant();
    }
  }
  // Warunek sprawdzający czy statek został znaleziony
  if(next_index != ships.size() && ships[next_index]->get_size() == size){
    // Pętla szukająca wsród statków o podanym rozmiarze takiego, który ma status false
    while(ships[next_index]->get_status() && next_index + 1 != ships.size() && ships[next_index]->get_size() == size){
      next_index++;
    }
    // Sprawdzenie czy statek został znaleziony
    if(!ships[next_index]->get_status() && ships[next_index]->get_size() == size){
      index = next_index;
      return true;
    }
  }
  return false;
}

// Funkcja sprawdzająca czy w obszarze za małym dla statku wywołującego może zmieścić się mniejszy. W razie możliwości wstawia mniejsze statki
bool ship::place_between(int &width, int &height, int space_between, const card &present_card, char **map, std::vector<ship*> ships, unsigned int index){
  std::cout << height << "   " << width << std::endl;
  unsigned int next_index = index;
  switch(space_between){
    case 1:{
      // Próba znalezienia statku o wielkości 1 i umieszczenia go na mapie
      if(find_smaller(ships, next_index, 1)){
        if(ships[next_index]->try_to_place_horizontal(width, height, present_card, map)){
          return true;
        }
      }
      else{
        // Próba wpasowania obiektu wywołującego pionowo
        if(this->try_to_place_vertical(width, height, present_card, map)){
          return true;
        }
        else{
          next_index = index;
          // Próba wpasowania statku o rozmiarze 3 pionowo
          if(this->get_size() != 3){
            if(find_smaller(ships, next_index, 3)){
              if(ships[next_index]->try_to_place_vertical(width, height, present_card, map)){
                return true;
              }
            }
          }
          // Próba wpasowania statku o rozmiarze 2 pionowo
          if(height + 2 == present_card.height){
            next_index = index;
            if(find_smaller(ships, next_index, 2)){
              if(ships[next_index]->try_to_place_vertical(width, height, present_card, map)){
                return true;
              }
            }
          }
        }
      }
      break;
    }
    case 2:{
      // Próba znalezienia statku o rozmiarze 2
      if(find_smaller(ships, next_index, 2)){
        if(ships[next_index]->try_to_place_horizontal(width, height, present_card, map)){
          return true;
        }
      }
      else{
        // Próba wpasowania statku wywołującego pionowo
        if(this->try_to_place_vertical(width, height, present_card, map)){
          return true;
        }
      }
      break;
    }
    case 3:{
      // Próba wpasowania statku o rozmiarze 3
      if(find_smaller(ships, next_index, 3)){
        if(ships[next_index]->try_to_place_horizontal(width, height, present_card, map)){
          return true;
        }
      }
      else{
        // Próba wpasowania statku o rozmiarze 1
        if(find_smaller(ships, next_index, 1)){
          if(ships[next_index]->try_to_place_horizontal(width, height, present_card, map)){
            if(!this->try_to_place_vertical(width, height, present_card, map)){
              if(find_smaller(ships, next_index, 1)){
                ships[next_index]->try_to_place_horizontal(width, height, present_card, map);
              }
              else{
                // Próba wpasowania statku o rozmiarze 2
                next_index = index;
                if(find_smaller(ships, next_index, 2)){
                  ships[next_index]->try_to_place_vertical(width, height, present_card, map);
                }
              }
            }
            return true;
          }
        }
        // Próba wpasowania statku wywołującego pionowo
        // if(this->try_to_place_vertical(width, height, present_card, map)){
        //   return true;
        // }
        // else{
        //   // Próba wpasowania statku o rozmiarze 1
        //   if(find_smaller(ships, next_index, 1)){
        //     if(ships[next_index]->try_to_place_horizontal(width, height, present_card, map)){
        //       return true;
        //     }
        //   }
        //   else{
        //     // Próba wpasowania statku o rozmiarze 2
        //     if(find_smaller(ships, next_index, 2)){
        //       if(ships[next_index]->try_to_place_vertical(width, height, present_card, map)){
        //         return true;
        //       }
        //     }
        //   }
        // }
      }
      break;
    }
  }
  return false;
}

// Funkcja sprawdzająca czy da się optymalniej ustawić statki na mapie
bool ship::try_another_option(int &width, int &height, const card &present_card, char **map, std::vector<ship*> ships, unsigned int index){
  unsigned next_index_1 = index, next_index_2 = index, next_index_3;
  switch(this->get_size()){
    case 4:{
      std::cout << "In case 4" << std::endl;
      if(find_smaller(ships, next_index_1, 3) && find_smaller(ships, next_index_2, 1)){
        std::cout << "In case 41" << std::endl;
        if(ships[next_index_1]->try_to_place_horizontal(width, height, present_card, map) && ships[next_index_2]->try_to_place_horizontal(width, height, present_card, map)){
          return true;
        }
      }
      next_index_1 = index;
      if(find_smaller(ships, next_index_1, 2)){
        next_index_2 = next_index_1 + 1;
        if(find_smaller(ships, next_index_2, 2)){
          if(ships[next_index_1]->try_to_place_horizontal(width, height, present_card, map) && ships[next_index_2]->try_to_place_horizontal(width, height, present_card, map)){
            return true;
          }
        }
      }
      next_index_1 = index;
      if(find_smaller(ships, next_index_1, 1)){
        next_index_2 = next_index_1 + 1;
        if(find_smaller(ships, next_index_2, 1)){
          next_index_3 = next_index_2 + 1;
          if(find_smaller(ships, next_index_3, 1)){
            if(ships[next_index_1]->try_to_place_horizontal(width, height, present_card, map) && ships[next_index_2]->try_to_place_horizontal(width, height, present_card, map) && ships[next_index_3]->try_to_place_horizontal(width, height, present_card, map)){
              return true;
            }
          }
        }
      }
      break;
    }
    case 3:{
      if(find_smaller(ships, next_index_1, 2) && find_smaller(ships, next_index_2, 1)){
        if(ships[next_index_1]->try_to_place_horizontal(width, height, present_card, map) && ships[next_index_2]->try_to_place_horizontal(width, height, present_card, map)){
          return true;
        }
      }
      break;
    }
    case 2:{
      if(find_smaller(ships, next_index_1, 1)){
        next_index_2 = next_index_1 + 1;
        if(find_smaller(ships, next_index_2, 1)){
          if(ships[next_index_1]->try_to_place_horizontal(width, height, present_card, map) && ships[next_index_2]->try_to_place_horizontal(width, height, present_card, map)){
            return true;
          }
        }
      }
      break;
    }
  }
  return false;
}

// Funkcja ustawiająca statek na mapie
bool ship::set_on_map(int &width, int &height, const card &present_card, char **map, std::vector<ship*> ships, unsigned int index){
  // Sprawdzenie czy statek nie został już ustawiony
  if(!this->get_status()){
    bool coordinates_changed = false;
    if(!this->can_fit_in_width(width, height, present_card, map)){
      int space_between = 0;
      for(int i = width; i < width + this->get_size() + 1 && i != present_card.width; i++){
        // std::cout << height << "   " << width << std::endl;
        // std::cout << space_between << "    ble" << std::endl;
        if(map[height][i] == '-'){
          if(height != 0 && map[height - 1][i] != '-'){
            space_between--;
            break;
          }
          space_between++;
        }
        else{
          space_between--;
          // std::cout << "tak!" << space_between << std::endl;
          break;
        }
      }
      std::cout << space_between << std::endl;
      if(space_between > 0 && this->get_size() != space_between){
        coordinates_changed = this->place_between(width, height, space_between, present_card, map, ships, index);
      }
      if(!coordinates_changed){
        if(width + 1 == present_card.width){
          if(height + 1 == present_card.height) return false;
          height++;
          width = 0;
        }
        else width = width + 1;
      }
    }
    else{
      bool another_one = false;
      if(width + this->get_size() + 1 == present_card.width){
        another_one = this->try_another_option(width, height, present_card, map, ships, index);
      }
      if(!another_one) return this->try_to_place_horizontal(width, height, present_card, map);
    }
    return this->set_on_map(width, height, present_card, map, ships, index);
  }
  else return true;
}

bool ship::try_to_place_horizontal(int &width, int &height, const card &present_card, char **map){
  if(this->can_fit_in_width(width, height, present_card, map)){
    for(int i = width; i < width + this->get_size(); i++) map[height][i] = char(this->get_size() + 48);
    this->change_status_positive();
    this->change_extant();
    if(width + this->get_size() + 1 >= present_card.width){
      if(!(height + 1 == present_card.height)){
        height++;
        width = 0;
      }
    }
    else width = width + this->get_size() + 1;
    std::cout << "Everything is ok in width ~~ try to place." << std::endl;
    return true;
  }
  else return false;
}

bool ship::try_to_place_vertical(int &width, int &height, const card &present_card, char **map){
  bool can_fit = false;
  for(int i = width; i < present_card.width; i++){
    if(map[height][i] == '-'){
      if(can_fit_in_height(i, height, present_card, map)){
        width = i;
        can_fit = true;
      }
    }
  }
  if(can_fit){
    for(int i = height; i < height + this->get_size(); i++) map[i][width] = char(this->get_size() + 48);
    this->change_status_positive();
    this->change_extant();
    height++;
    width = 0;
    std::cout << "Everything is ok in height." << std::endl;
    return true;
  }
  else return false;
}
