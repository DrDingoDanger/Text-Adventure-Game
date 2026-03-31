#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

class Item {
 private:
    std::string _name;
    std::string _type;
 public:
    Item(std::string name, std::string type);
    virtual ~Item();
    std::string getName();
    std::string getType();
};

class Material : public Item {
 public:
    Material(std::string name);
    ~Material();
};

class Food : public Item {
 private:
    int _hungerValue;

 public:
    Food(std::string name, int value);
    ~Food();
    int getHunger();
    void setHunger(int value);
};

class Weapon : public Item {
 private:
   int _power;
 public:
    Weapon(std::string name, int power);
    ~Weapon();
    int getPower();
};

#endif
