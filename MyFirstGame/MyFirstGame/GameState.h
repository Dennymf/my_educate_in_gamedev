#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
class GameState :
    public State
{
private:
    PauseMenu* pmenu;
    sf::Font font;

    Player* player;

    //Functions
    void initKeybinds();
    void initTextures();
    void initPlayers();
    void initPauseMenu();
    void initFonts();

public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~GameState();

    //Function
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePauseMenuButton();
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);

};

#endif