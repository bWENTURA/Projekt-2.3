#ifndef TEMPLATE_CLASSES_HPP
#define TEMPLATE_CLASSES_HPP

class one_mast: public ship{
  static int number_to_set;
  std::vector<int[2]> coordinates;
  public:
  one_mast();
  ~one_mast();
  int get_size();
  bool get_status();
  void change_extant();
  int get_extant();
  //void struck(int width, int height);
};

class two_mast: public ship{
  static int number_to_set;
  std::vector<int[2]> coordinates;
  public:
  two_mast();
  ~two_mast();
  int get_size();
  bool get_status();
  void change_extant();
  int get_extant();
  // void struck(int width, int height);
};

class three_mast: public ship{
  static int number_to_set;
  std::vector<int[2]> coordinates;
  public:
  three_mast();
  ~three_mast();
  int get_size();
  bool get_status();
  void change_extant();
  int get_extant();
  // void struck(int width, int height);
};

class four_mast: public ship{
  static int number_to_set;
  std::vector<int[2]> coordinates;
  public:
  four_mast();
  ~four_mast();
  int get_size();
  bool get_status();
  void change_extant();
  int get_extant();
  // void struck(int width, int height);
};

#endif
