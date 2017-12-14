#ifndef CARD_HPP
#define CARD_HPP

// Struktura zawierająca wszelkie istotne informacje co do postaci mapy
// i ilości statków danego typu na niej się znajdujących

struct card{
  int width;
  int height;
  int number_of_one_mast;
  int number_of_two_mast;
  int number_of_three_mast;
  int number_of_four_mast;
  card();
  ~card();
};

#endif
