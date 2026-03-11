#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
class Item {
 private:
    std::string _name;
 public:
    Item(std::string name);
    ~Item();
    std::string getName();
};

class Material : public Item {}
class Food : public Item {
 private:
    int _hungerValue;
 public:
    Food(int value);
    ~Food();
    int getHunger();
    void setHunger(int value);
}
#endif
