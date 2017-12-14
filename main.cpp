#include "header.hpp"
#include "card.hpp"
#include "class_ship.hpp"
#include "specific_classes.hpp"
#include "functions.hpp"

int main(int argc, char * argv[]){
  bool exit = false;
  while(!exit){
    int input;
    bool correct = false;
    std::cout << LINE <<  "\n1. Load input from file, which name you putted as a parametr.\n";
    std::cout << "2. Run manual test.\n";
    std::cout << "3. Run auto test.\n";
    std::cout << "0. Exit.\n" << LINE << std::endl;
    correct = unsigned_integer_input_from_stream(std::cin, input);
    while(!correct || (input != 1 && input != 2 && input != 3 && input != 0)){
      std::cout << "You did something wrong, try again." << std::endl;
      correct = unsigned_integer_input_from_stream(std::cin, input);
    }
    switch(input){
      case 1:{
        if(argc == 2){
          std::ifstream file;
          file.open(argv[1]);
          if(file){
            file_test(file);
          }
          else{
            std::cout << "Program have not opened file correctly." << std::endl;
          }
        }
        else std::cout << "Number of parameters for program is wrong." << std::endl;
        break;
      }
      case 2:{
        manual_test();
        break;
      }
      case 3:{
        random_test();
        break;
      }
      case 0:{
        std::cout << "Exit!" << std::endl;
        exit = true;
      }
    }
  }
  return 0;
}
