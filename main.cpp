#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Map_Reader.h"
#include "Game.h"
#include <iostream>
static bool run = true;
Log l;
Map_Reader& m=m.getReader();

int main(){
    Game g;
    g.run();
    return 0;
}