#pragma once
#include <ncurses.h>
#include <iostream>
#include <cstring>
#include "../constants.hpp"

class Menu
{
private:
    void visualizza_grafica();

public:
    Menu();

    void visualizza_menu();
};