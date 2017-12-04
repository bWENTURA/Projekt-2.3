#include "header.hpp"
#include "card.hpp"
#include "class_ship.hpp"
#include "functions.hpp"

bool integer_input(std::ifstream &file, int &number){
  if(!file.eof()){
    std::string text;
    getline(file, text);
    if(text.size()){
      for(unsigned int i = 0; i != text.size(); i++){
        if(!isdigit(text[i])){
          std::cout << "Input isn't integer." << std::endl;
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

bool read_size(std::ifstream &file, card &present_card){
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
    correct = integer_input(file, number_of_type);
    std::cout << number_of_type << std::endl;
    if(correct){
      types++;
      for(int i = 0; i < number_of_type; i++){
        switch(types){
          case 1:{
            next = new one_mast;
            ships.push_back(next);
            break;
          }
          // case 2:{
          //   next = new two_mast;
          //   ships.push_back(next);
          //   break;
          // }
          // case 3:{
          //   next = new three_mast;
          //   ships.push_back(next);
          //   break;
          // }
          // case 4:{
          //   next = new four_mast;
          //   ships.push_back(next);
          //   break;
          // }
        }
      }
    }
    else return false;
  }
  if(types == 4) return true;
  else return false;
}

void fill_up_the_map(const card& present_card, const std::vector<ship*> &ships){

}


void show_map(const std::vector<ship*> &ships){

}
