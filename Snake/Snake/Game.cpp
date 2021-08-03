#include "Game.h"

void Game::initWindow()
{
    std::ifstream file("Config/window.ini");

    this->viedoModes = sf::VideoMode::getFullscreenModes();

    std::string title = "None";
    sf::VideoMode window_bound = sf::VideoMode::getDesktopMode();
    bool fullscreen = false;
    unsigned framerate_limit = 120;
    bool vertical_sync_enable = false;
    unsigned antialazing_lvl = 0;

    if (file.is_open())
    {
        std::getline(file, title);
        file >> window_bound.width >> window_bound.height;
        file >> fullscreen;
        file >> framerate_limit;
        file >> vertical_sync_enable;
        file >> antialazing_lvl;
    }

    file.close();

    this->fullscreen = fullscreen;
    this->windowSettings.antialiasingLevel = antialazing_lvl;
    if (this->fullscreen)
    {
        this->window = new sf::RenderWindow(window_bound, title, sf::Style::Fullscreen, windowSettings);
    }
    else
    {
        this->window = new sf::RenderWindow(window_bound, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
    }
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enable);
}

void Game::initKeys()
{
    std::fstream file_keys("Config/supported_keys.ini");

    if (file_keys.is_open())
    {
        std::string key = "";
        int key_value = 0;

        while (file_keys >> key >> key_value)
        {
            this->supportedKeys[key] = key_value;
        }
    }

    file_keys.close();
}

void Game::initStates()
{
    this->states.push(new GameState(this->window, &this->supportedKeys, &this->states));
}


Game::Game()
{
    this->initWindow();
    this->initKeys();
    this->initStates();
}

Game::~Game()
{
    delete this->window;

    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }

}

void Game::endApplication()
{
    std::cout << "End application\n";
}

void Game::updateDT()
{
    this->dt = this->dt_clock.restart().asSeconds();
}

void Game::updateEvents()
{
    while (this->window->pollEvent(this->sf_event))
    {
        if (this->sf_event.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::update()
{
    this->updateEvents();
    if (this->states.top()->newDelay())
        delay = 0.2;

    if (!this->states.empty())
    {
        this->states.top()->update(this->chrono, this->delay);
        if (this->states.top()->getFlag())
        {
            if(delay > 0.03)
                delay -= (delay * 0.005);
        }

        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();

            delete this->states.top();
            this->states.pop();
        }
    }
    //Application end
    else
    {
        this->endApplication();
        this->window->close();
    }
}

void Game::render()
{
    this->window->clear();

    if (!this->states.empty())
    {
        this->states.top()->render(*this->window);
    }

    this->window->display();
}

void Game::run()
{
    srand(time(NULL));
	while (this->window->isOpen())
	{
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        chrono += time;
        this->update();

        if (chrono > delay)
        {
            chrono = 0;
        }
        this->render();
	}
}
