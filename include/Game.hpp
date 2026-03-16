#ifndef GAME_HPP
#define GAME_HPP

#include <string>

#include "Player.hpp"
#include "WorldMap.hpp"
#include "UserInput.hpp"
#include "ScreenDisplay.hpp"

class Game {
 private:
    Player _player;
    WorldMap _map;
    std::string _winItem;
    bool _isOver = false;
    UserInput _ui;
    ScreenDisplay _display;

 public:
    Game();

    bool isOver() const;

    void start();
    void update();
    bool checkWin() const;
    bool checkLose() const;
    void endGame();
};
#endif
