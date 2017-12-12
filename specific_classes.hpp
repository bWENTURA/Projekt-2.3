#ifndef SPECIFIC_CLASSES_HPP
#define SPECIFIC_CLASSES_HPP

class one_mast: public ship{
  static int number_to_set;
  public:
  one_mast();
  ~one_mast();
  void change_extant();
  int get_extant();
};

class two_mast: public ship{
  static int number_to_set;
  public:
  two_mast();
  ~two_mast();
  void change_extant();
  int get_extant();
};

class three_mast: public ship{
  static int number_to_set;
  public:
  three_mast();
  ~three_mast();
  void change_extant();
  int get_extant();
};

class four_mast: public ship{
  static int number_to_set;
  public:
  four_mast();
  ~four_mast();
  void change_extant();
  int get_extant();
};

#endif
