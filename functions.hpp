#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

template<typename T>
T ** create_map(T ** map, int height, int width, T sign){
  map = new T*[height];
  for(int i = 0; i < height; i++){
    map[i] = new T[width];
    for(int j = 0; j < width; j++) map[i][j] = sign;
  }
  return map;
}

bool unsigned_integer_input_from_stream(std::istream &input_stream, int &number);

bool read_card_size(std::istream& input_stream, card& present_card);

bool read_ships_quantity(std::istream& input_stream, card& present_card, std::vector<ship*> &ships);

bool fill_up_the_map(const card& present_card, char ** map, const std::vector<ship*> &ships);

void file_test(std::ifstream &file);

void manual_test();

void random_test();

void show_map(const card& present_card, char ** map, const std::vector<ship*> &ships);

#endif
