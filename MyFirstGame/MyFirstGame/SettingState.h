#ifndef SETTINGSTATE_H
#define SETTINGSTATE_H

#include "State.h"
#include "Button.h"

class SettingState :
    public State
{
private:
    //Variables
    sf::Texture bgTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, Button*>  buttons;

    //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();

public:
    SettingState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~SettingState();

    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
    void renderButtons(sf::RenderTarget& target);
};

#endif