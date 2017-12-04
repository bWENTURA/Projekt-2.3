#ifndef CLASS_SHIP_HPP
#define CLASS_SHIP_HPP

class ship{
  int size;
  public:

  virtual int get_size();
  virtual void show_on_map();
  virtual void struck(int width, int height);
};

class one_mast: public ship{
  int size;
  std::vector<int[2]> coordinates;
};


#endif
