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
  virtual void change_extant() = 0;
  virtual int get_extant() = 0;
  virtual bool can_fit_in_width(int width, int height, const card &present_card, int **map);
  virtual bool can_fit_in_height(int width, int height, const card &present_card, int **map);
  virtual bool find_smaller(std::vector<ship*> ships, unsigned int &index, int size);
  virtual bool set_on_map(int &width, int &height, const card& present_card, int ** map, std::vector<ship*> ships, unsigned int index);
  virtual bool try_to_place_horizontal(int &width, int &height, const card& present_card, int ** map);
  virtual bool try_to_place_vertical(int &width, int &height, const card& present_card, int ** map);
  //virtual void struck() = 0;
};

#endif
