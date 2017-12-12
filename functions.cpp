#include "header.hpp"
#include "card.hpp"
#include "class_ship.hpp"
#include "specific_classes.hpp"
#include "functions.hpp"

bool unsigned_integer_from_file(std::ifstream &file, int &number){
  if(!file.eof()){
    std::string text;
    getline(file, text);
    if(text.size()){
      for(unsigned int i = 0; i != text.size(); i++){
        if(!isdigit(text[i])){
          std::cout << "Input isn't unsigned integer." << std::endl;
          return false;
        }
      }
      number = std::stoi(text);
      return true;
    }
    else{
      std::cout << "The line was empty." << std::endl;
      return false;
    }
  }
  else{
    std::cout << "There is nothing else to read." << std::endl;
    return false;
  }
}

bool read_card_size(std::ifstream &file, card &present_card){
  if(!file.eof()){
    std::string text;
    bool whitespace = false;
    getline(file, text);
    if(text.size()){
      for(unsigned int i = 0; i != text.size(); i++){
        if(text[i] == ' '){
          if(i == 0 || whitespace == true || i == text.size() - 1){
            std::cout << "The coordinates are incorrect." << std::endl;
            return false;
          }
          whitespace = true;
        }
        else{
          if(!isdigit(text[i])){
            std::cout << "There's incorrect character in the line." << std::endl;
            return false;
          }
        }
      }
      std::string temporary;
      temporary = text.substr(0, text.find(" "));
      present_card.height = stoi(temporary);
      temporary = text.substr(text.find(" "));
      present_card.width = stoi(temporary);
      return true;
    }
    else{
      std::cout << "The line was empty." << std::endl;
      return false;
    }
  }
  else{
    std::cout << "There is nothing else to read." << std::endl;
    return false;
  }
}

bool read_ships_quantity(std::ifstream &file, std::vector<ship*> &ships){
  ship * next;
  int number_of_type = 0;
  int types = 0;
  bool correct;
  while(!file.eof() && types != 4){
    correct = unsigned_integer_from_file(file, number_of_type);
    if(correct){
      types++;
      for(int i = 0; i < number_of_type; i++){
        switch(types){
          case 1:{
            next = new four_mast;
            ships.push_back(next);
            break;
          }
          case 2:{
            next = new three_mast;
            ships.push_back(next);
            break;
          }
          case 3:{
            next = new two_mast;
            ships.push_back(next);
            break;
          }
          case 4:{
            next = new one_mast;
            ships.push_back(next);
            break;
          }
        }
      }
    }
    else return false;
  }
  if(types == 4) return true;
  else return false;
}

bool fill_up_the_map(const card& present_card, char ** map, const std::vector<ship*> &ships){
  int x = 0, y = 0;
  bool correct = true;
  for(unsigned int i = 0 ; i != ships.size() && correct; i++){
    if(y == present_card.height) return false;
    std::cout << "size = " << ships[i]->get_size() << "    extant= " << ships[i]->get_extant() << std::endl;
    if(!ships[i]->get_status()) correct = ships[i]->set_on_map(x, y, present_card, map, ships, i);
  }
  return correct;
}

void show_map(const card& present_card, char ** map, const std::vector<ship*> &ships){
  std::cout << "       ";
  for(int j = 0; j < present_card.width; j++){
    if(j < 9) std::cout << " "<< j + 1 << ".  ";
    else std::cout << j + 1 << ".  ";
  }
  std::cout << std::endl;
  for(int i = 0; i < present_card.height; i++){
    std::cout << "\n";
    if(i < 9) std::cout << i + 1 << ".    ";
    else std::cout << i + 1 << ".   ";
    for(int j = 0; j < present_card.width; j++) std::cout << "  "<< map[i][j] << "  ";
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
