#ifndef SETTINGSTATE_H
#define SETTINGSTATE_H

#include "State.h"
#include "Gui.h"

class SettingState :
    public State
{
private:
    //Variables
    sf::Texture bgTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, gui::Button*>  buttons;
    std::map<std::string, gui::DropDownList*>  dropDownLists;

    //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initGui();

public:
    SettingState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~SettingState();

    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
    void renderGui(sf::RenderTarget& target);
};

#endif