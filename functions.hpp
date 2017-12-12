#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

bool unsigned_integer_input_from_file(std::ifstream &file, int &number);

bool read_card_size(std::ifstream& file, card& present_card);

bool read_ships_quantity(std::ifstream& file, std::vector<ship*> &ships);

bool fill_up_the_map(const card& present_card, char ** map, const std::vector<ship*> &ships);

void show_map(const card& present_card, char ** map, const std::vector<ship*> &ships);

#endif
