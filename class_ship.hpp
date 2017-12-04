#ifndef CLASS_SHIP_HPP
#define CLASS_SHIP_HPP

class ship{
  protected:
  int size;
  public:
  ship(int new_size = 0);
  virtual ~ship();
  virtual int get_size() = 0;
  //virtual void struck() = 0;
};

class one_mast: public ship{
  std::vector<int[2]> coordinates;
  public:
  one_mast();
  ~one_mast();
  int get_size();
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
