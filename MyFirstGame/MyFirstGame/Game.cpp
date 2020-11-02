#include "Game.h"

//Static function

//Init function

void Game::initWindow()
{
    std::ifstream file("Config/window.ini");

    std::string title = "None";
    sf::VideoMode window_bound(800, 600);
    unsigned framerate_limit = 120;
    bool vertical_sync_enable = false;

    if (file.is_open())
    {
        std::getline(file, title);
        file >> window_bound.width >> window_bound.height;
        file >> framerate_limit;
        file >> vertical_sync_enable; 
    }

    file.close();

	this->window = new sf::RenderWindow(window_bound, title);
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
    this->states.push(new MainMenuState(this->window, &this->supportedKeys));
}

//Construction/destruction

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

//Fuction 

void Game::endApplication()
{
    std::cout << "End application\n";
}

void Game::updateDT()
{
    this->dt = this->dt_clock.restart().asSeconds();

   /* system("cls");
    std::cout << this->dt << "\n";*/

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

    if (!this->states.empty())
    {
        this->states.top()->update(this->dt);

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

    //Render items
    if (!this->states.empty())
    {
        this->states.top()->render(this->window);
    }

    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDT();
        this->update();
        this->render();
    }
}