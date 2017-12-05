#ifndef CLASS_SHIP_HPP
#define CLASS_SHIP_HPP

class ship{
  protected:
  int size;
  bool status;
  public:
  ship(int new_size = 0, bool status = false);
  virtual ~ship();
  virtual int get_size() = 0;
  virtual bool get_status() = 0;
  virtual bool can_fit_in_width(int width, int height, const card& present_card, int **map) = 0;
  virtual bool can_fit_in_height(int height, const card& present_card) = 0;
  virtual bool set_on_map(int &width, int &height, const card& present_card, int ** map, std::vector<ship*> ships) = 0;
  //virtual void struck() = 0;
};

class one_mast: public ship{
  static int number_to_set;
  std::vector<int[2]> coordinates;
  public:
  one_mast();
  ~one_mast();
  int get_size();
  bool get_status();
  bool can_fit_in_width(int width, int height, const card& present_card, int ** map);
  bool can_fit_in_height(int height, const card& present_card);
  bool set_on_map(int &width, int &height, const card& present_card, int ** map, std::vector<ship*> ships);
  //void struck(int width, int height);
};

// class two_mast: public ship{
//   std::vector<int[2]> coordinates;
//   public:
//   two_mast();
//   int get_size();
//   void show_on_map();
//   void struck(int width, int height);
// };
//
// class three_mast: public ship{
//   std::vector<int[2]> coordinates;
//   public:
//   three_mast();
//   int get_size();
//   void show_on_map();
//   void struck(int width, int height);
// };
//
// class four_mast: public ship{
//   std::vector<int[2]> coordinates;
//   public:
//   four_mast();
//   int get_size();
//   void show_on_map();
//   void struck(int width, int height);
// };

#endif
