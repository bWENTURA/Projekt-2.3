#ifndef CLASS_SHIP_HPP
#define CLASS_SHIP_HPP

// Klasa bazowa reprezentująca statek. Posiada jedną publiczną metodę, reszta jest typu protected,
// aby uniemożliwić dostęp, ale umożliwić dziedziczenie

class ship{
  protected:
  int size;
  bool status;
  int get_size();
  bool get_status();
  void change_status_positive();
  virtual int get_extant() = 0;
  virtual void change_extant() = 0;
  bool can_fit_in_width(int width, int height, const card &present_card, char **map);
  bool can_fit_in_height(int width, int height, const card &present_card, char **map);
  bool find_smaller(std::vector<ship*> ships, unsigned int &index, int size);
  bool place_between(int &width, int &height, int between, const card &present_card, char **map, std::vector<ship*> ships, unsigned int index);
  bool try_another_option(int &width, int &height, const card &present_card, char **map, std::vector<ship*> ships, unsigned int index);
  bool try_to_place_horizontal(int &width, int &height, const card& present_card, char ** map);
  bool try_to_place_vertical(int &width, int &height, const card& present_card, char ** map);
  public:
  ship(int new_size = 0, bool status = false);
  virtual ~ship();
  bool set_on_map(int &width, int &height, const card& present_card, char ** map, std::vector<ship*> ships, unsigned int index);
};

#endif
