#include "header.hpp"
#include "card.hpp"
#include "class_ship.hpp"
#include "specific_classes.hpp"
#include "functions.hpp"

// Funkcja sprawdzająca czy ze strumienia została poprawnie wczytana liczba całkowita
bool unsigned_integer_input_from_stream(std::istream &input_stream, int &number){
  // Sprawdzenie czy, gdy strumieniem jest plik, nie został osiągnięty jego koniec
  if(!input_stream.eof()){
    std::string text;
    // Wczytanie całej linijki tekstu do zmiennej text
    getline(input_stream, text);
    // Sprawdzenie czy wczytany ciąg znaków nie jest pusty
    if(text.size()){
      // Sprawdzenie czy wszystkie znaki w ciągu są liczbami całkowitymi
      for(unsigned int i = 0; i != text.size(); i++){
        if(!isdigit(text[i])){
          std::cout << "Input isn't unsigned integer." << std::endl;
          return false;
        }
      }
      // W przypadku, gdy wszystkie znaki są liczbami całkowitymi, ciąg znaków jest konwertowany na liczbę całkowitą
      number = std::stoi(text);
      if(number >= 25){
        std::cout << "You entered a very big number of ships, this may cause some trobules, please try again." << std::endl;
        return false;
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

// Funkcja wczytująca ze strumienia dwie liczby całkowite oddzielone spacją
// Liczby te określają wielkość mapy i są zapisywane w strkturze pomocniczej present_card
bool read_card_size(std::istream &input_stream, card &present_card){
  // Sprawdzenie analogiczne do funkcji powyżej
  if(!input_stream.eof()){
    std::string text;
    bool whitespace = false;
    getline(input_stream, text);
    // Sprawdzenie czy ciąg zawiera najmniejszą dozwoloną liczbę znaków
    if(text.size() >= 3){
      for(unsigned int i = 0; i != text.size(); i++){
        // Sprawdzenie czy wystąpiła spacja i czy spełnia niezbędne warunku
        if(text[i] == ' '){
          if(i == 0 || whitespace == true || i == text.size() - 1){
            std::cout << "The coordinates are incorrect." << std::endl;
            return false;
          }
          whitespace = true;
        }
        else{
          // Sprawdzenie czy znak będący czymś innym niż spacją nie jest liczbą
          if(!isdigit(text[i])){
            std::cout << "There's incorrect character in the line." << std::endl;
            return false;
          }
        }
      }
      // Stworzenie pomocniczej zmiennej typu string,
      // w której zapisujemy po kolei obydwa ciągi znaków reprezentujących liczby
      // i z której konwertujemy je na potrzebne nam dane
      std::string temporary;
      temporary = text.substr(0, text.find(" "));
      present_card.height = stoi(temporary);
      temporary = text.substr(text.find(" "));
      present_card.width = stoi(temporary);
      if(present_card.height >= 19 || present_card.width >= 28){
        std::cout << "You entered so big map max coordinates, that this may cause some troubles, please try again." << std::endl;
        return false;
      }
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

// Funkcja wczytująca ze strumienia kolejne liczby reprezentujące ilość poszczególnych statków,
// tworząca odpowiednie obiekty i dodająca je do kontenera ships
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

// Funkcja wypełniająca mapę map statkami z kontenera ships
bool fill_up_the_map(const card& present_card, char ** map, const std::vector<ship*> &ships){
  int x = 0, y = 0;
  bool correct = true;
  for(unsigned int i = 0 ; i != ships.size() && correct; i++){
    if(y == present_card.height) return false;
    correct = ships[i]->set_on_map(x, y, present_card, map, ships, i);
  }
  return correct;
}

// Funkcja testująca dane z pliku
void file_test(std::ifstream &file){
  card * present_card = new card;
  std::vector<ship*> ships;
  char ** map = NULL;
  // Warunek poprawności danych do dalszych działań
  if(read_card_size(file, *present_card) && read_ships_quantity(file, *present_card, ships)){
    // Funkcja template tworząca matrix danego typu o danych rozmiarach i wypełniająca go danym znakiem danego typu
    map = create_map(map, present_card->height, present_card->width, '-');
    // Funkcja zwracająca status poprawności wypełniania mapy
    if(!fill_up_the_map(*present_card, map, ships)){
      show_map(*present_card, map, ships);
      std::cout << LINE << "\nSomething went wrong so this is only the vision of the map,\nwith probably the best setting for the ships that can fit." << std::endl;
    }
    else show_map(*present_card, map, ships);
    // Usuwanie mapy
    for(int i = 0; i < present_card->height; i++) delete[] map[i];
    delete[] map;
  }
  else std::cout << LINE << "\nSomething went wrong with input.\n" << LINE << std::endl;
  // Usuwanie danych z kontenera i pomocniczej present_card
  for(ship * iterator: ships) delete iterator;
  delete present_card;
  // Zamknięcie pliku
  file.close();
}

// Test manualny działa analogicznie do testu z pliku
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
      show_map(*present_card, map, ships);
      std::cout << LINE << "\nSomething went wrong, so this is only the vision of the map,\nwith probably the best setting for the ships that can fit." << std::endl;
    }
    else show_map(*present_card, map, ships);
    for(int i = 0; i < present_card->height; i++) delete[] map[i];
    delete[] map;
  }
  else std::cout << LINE << "\nYou entered the wrong input.\n" << LINE << std::endl;
  for(ship * iterator: ships) delete iterator;
  delete present_card;
}

// Test automatyczny opiera się na losowaniu wysokości mapy z zakresu 18 i szerokości z zakresu 27
// Następnie w parciu o te dane losuje resztę danych, czyli ilość poszczególnych statków
void random_test(){
  std::string enter;
  int max;
  card * present_card = new card;
  srand(time(NULL));
  int number_of_tests = rand() % 10;
  std::cout << LINE << "\nStarting " << number_of_tests << " random tests." << std::endl;
  for(int i = 0; i < number_of_tests; i++){
    std::vector<ship*> ships;
    char ** map = NULL;
    ship * next = NULL;
    present_card->height = 1 + (present_card->height + rand()) % 17;
    present_card->width = 1 + (present_card->width + rand()) % 26;
    if(present_card->width > present_card->height) max = present_card->width;
    else max = present_card->height;
    present_card->number_of_four_mast =  rand() % max;
    present_card->number_of_three_mast = rand() % max;
    present_card->number_of_two_mast = rand() % max;
    present_card->number_of_one_mast = rand() % max;
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
    std::cout << LINE << "\nThis is test number: " << i + 1 << ".";
    std::cout << "\nSize of map: " << present_card->width << " x " << present_card->height << ".\n";
    std::cout << LINE << "\nShips:";
    std::cout << "\nOne-masted = " << present_card->number_of_one_mast << ".";
    std::cout << "\nTwo-masted = " << present_card->number_of_two_mast << ".";
    std::cout << "\nThree-masted = " << present_card->number_of_three_mast << ".";
    std::cout << "\nFour-masted = " << present_card->number_of_four_mast << "\n" << LINE << std::endl;
    map = create_map(map, present_card->height, present_card->width, '-');
    if(!fill_up_the_map(*present_card, map, ships)){
      std::cout << LINE << "\nI can't put these ships on the map of this size..\n"<< LINE << std::endl;
    }
    else show_map(*present_card, map, ships);
    for(int i = 0; i < present_card->height; i++) delete[] map[i];
    delete[] map;
    for(ship * iterator: ships) delete iterator;
    std::cout << "Enter something to go to the new test." << std::endl;
    getline(std::cin, enter);
  }
  delete present_card;
}

// Funkcja wyświetlająca dane i mapę
void show_map(const card& present_card, char ** map, const std::vector<ship*> &ships){
  int number_of = 1;
  std::cout << LINE << "\nMap is the size of " << present_card.width << " x " << present_card.height << ".\n" << LINE; 
  std::cout << "\nThere's is " << present_card.number_of_one_mast << " ships of size = " << number_of++ << ".";
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
