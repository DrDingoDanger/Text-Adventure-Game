#ifndef GAME_HPP
#define GAME_HPP

#include <string>

#include "Player.hpp"
#include "WorldMap.hpp"
#include "UserInput.hpp"
#include "ScreenDisplay.hpp"

class Game {
 private:
    WorldMap _map;
    Player _player;
    std::string _winItem;
    bool _isOver = false;
    UserInput _ui;
    ScreenDisplay _display;

 public:
    Game();

    bool isOver() const;

    void start();
    void update();
    bool checkWin();
    bool checkLose() const;
    void endGame();
};
#endif
