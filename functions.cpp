#include "header.hpp"
#include "card.hpp"
#include "class_ship.hpp"
#include "specific_classes.hpp"
#include "functions.hpp"

bool unsigned_integer_input_from_stream(std::istream &input_stream, int &number){
  if(!input_stream.eof()){
    std::string text;
    getline(input_stream, text);
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

bool read_card_size(std::istream &input_stream, card &present_card){
  if(!input_stream.eof()){
    std::string text;
    bool whitespace = false;
    getline(input_stream, text);
    if(text.size() >= 3){
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
      std::cout << "The line was empty or too short." << std::endl;
      return false;
    }
  }
  else{
    std::cout << "There is nothing else to read." << std::endl;
    return false;
  }
}

bool read_ships_quantity(std::istream &input_stream, card& present_card, std::vector<ship*> &ships){
  ship * next;
  int number_of_type = 0;
  int types = 0;
  bool correct;
  while(!input_stream.eof() && types != 4){
    correct = unsigned_integer_input_from_stream(input_stream, number_of_type);
    if(correct){
      types++;
      for(int i = 0; i < number_of_type; i++){
        switch(types){
          case 1:{
            next = new four_mast;
            ships.push_back(next);
            present_card.number_of_four_mast++;
            break;
          }
          case 2:{
            next = new three_mast;
            ships.push_back(next);
            present_card.number_of_three_mast++;
            break;
          }
          case 3:{
            next = new two_mast;
            ships.push_back(next);
            present_card.number_of_two_mast++;
            break;
          }
          case 4:{
            next = new one_mast;
            ships.push_back(next);
            present_card.number_of_one_mast++;
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
    //std::cout << "size = " << ships[i]->get_size() << "    extant= " << ships[i]->get_extant() << std::endl;
    if(!ships[i]->get_status()) correct = ships[i]->set_on_map(x, y, present_card, map, ships, i);
  }
  return correct;
}

void file_test(std::ifstream &file){
  card * present_card = new card;
  std::vector<ship*> ships;
  char ** map = NULL;
  if(read_card_size(file, *present_card) && read_ships_quantity(file, *present_card, ships)){
    map = create_map(map, present_card->height, present_card->width, '-');
    if(!fill_up_the_map(*present_card, map, ships)){
      std::cout << LINE << "\nSomething went wrong with setting ships on the map.\n" << LINE << std::endl;
    }
    else{
      if(present_card->height <= 18 &&  present_card->width <= 27){
        show_map(*present_card, map, ships);
      }
      else std::cout << LINE << "\nMap is too big to show in terminal.\n" << LINE << std::endl;
    }
    for(int i = 0; i < present_card->height; i++) delete[] map[i];
    delete[] map;
    for(ship * iterator: ships) delete iterator;
  }
  else std::cout << LINE << "\nSomething went wrong with input.\n" << LINE << std::endl;
  delete present_card;
  file.close();
}

void manual_test(){
  card * present_card = new card;
  std::vector<ship*> ships;
  char ** map = NULL;
  std::cout << LINE << "\nFirst enter two integers. Be sure that they are in the same line, separated only by one whitespace.\n";
  std::cout << "Then enter four integers, each in the separate line.\n";
  std::cout << "First will refer to the number of four-masted ship, second to the size of three-masted ship and so on.\n";
  std::cout << "Please, be sure that in the line is only one integer and nothing else.\n" << LINE << std::endl;
  if(read_card_size(std::cin, *present_card) && read_ships_quantity(std::cin, *present_card, ships)){
    map = create_map(map, present_card->height, present_card->width, '-');
    if(!fill_up_the_map(*present_card, map, ships)){
      std::cout << LINE << "\nSomething went wrong with setting ships on the map.\n" << LINE << std::endl;
    }
    else{
      if(present_card->height <= 18 &&  present_card->width <= 27){
        show_map(*present_card, map, ships);
      }
      else std::cout << LINE << "\nMap is too big to show in terminal.\n" << LINE << std::endl;
    }
    for(int i = 0; i < present_card->height; i++) delete[] map[i];
    delete[] map;
    for(ship * iterator: ships) delete iterator;
  }
  else std::cout << LINE << "\nYou entered the wrong input.\n" << LINE << std::endl;
  delete present_card;
}

void random_test(){
  card * present_card = new card;
  srand(time(NULL));
  int number_of_tests = rand() % 10;
  std::cout << LINE << "\nStarting " << number_of_tests << " random tests.\n" << LINE << std::endl;
  for(int i = 0; i < number_of_tests; i++){
    std::vector<ship*> ships;
    char ** map = NULL;
    ship * next = NULL;
    present_card->height = 1 + rand() % 17;
    present_card->width = 1 + rand() % 26;
    present_card->number_of_four_mast = rand() % present_card->height;
    present_card->number_of_three_mast = rand() % present_card->height;
    present_card->number_of_two_mast = rand() % present_card->width;
    present_card->number_of_one_mast = rand() % present_card->width;
    for(int j = 0; j < present_card->number_of_four_mast; j++){
      next = new four_mast;
      ships.push_back(next);
    }
    for(int j = 0; j < present_card->number_of_three_mast; j++){
      next = new three_mast;
      ships.push_back(next);
    }
    for(int j = 0; j < present_card->number_of_two_mast; j++){
      next = new two_mast;
      ships.push_back(next);
    }
    for(int j = 0; j < present_card->number_of_one_mast; j++){
      next = new one_mast;
      ships.push_back(next);
    }
    std::cout << LINE << "\nSize of map: " << present_card->height << " x " << present_card->width << std::endl;
    std::cout << LINE << "\nShips:";
    std::cout << "\nOne-masted = " << present_card->number_of_one_mast << ".";
    std::cout << "\nTwo-masted = " << present_card->number_of_two_mast << ".";
    std::cout << "\nThree-masted = " << present_card->number_of_three_mast << ".";
    std::cout << "\nFour-masted = " << present_card->number_of_four_mast << "\n" << LINE << std::endl;
    map = create_map(map, present_card->height, present_card->width, '-');
    if(!fill_up_the_map(*present_card, map, ships)){
      std::cout << LINE << "\nSomething went wrong with setting ships on the map.\n" << LINE << std::endl;
    }
    else{
      if(present_card->height <= 18 &&  present_card->width <= 27){
        show_map(*present_card, map, ships);
      }
      else std::cout << LINE << "\nMap is too big to show in terminal.\n" << LINE << std::endl;
    }
    for(int i = 0; i < present_card->height; i++) delete[] map[i];
    delete[] map;
    for(ship * iterator: ships) delete iterator;
    present_card->clear_card();
  }
  delete present_card;
}


void show_map(const card& present_card, char ** map, const std::vector<ship*> &ships){
  int number_of = 1;
  std::cout << LINE << "\nThere's is " << present_card.number_of_one_mast << " ships of size = " << number_of++ << ".";
  std::cout << "\nThere's is " << present_card.number_of_two_mast << " ships of size = " << number_of++ << ".";
  std::cout << "\nThere's is " << present_card.number_of_three_mast << " ships of size = " << number_of++ << ".";
  std::cout << "\nThere's is " << present_card.number_of_four_mast << " ships of size = " << number_of++ << ".\n" << LINE << std::endl;
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
