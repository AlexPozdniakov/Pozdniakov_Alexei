#include <conio.h>
#include <chrono>
#include <thread>
#include "Game.h"
using std::thread;
using namespace std::chrono_literals;


enum key : unsigned char
{
  ARROW_UP = 72,
  ARROW_DOWN = 80,
  ARROW_LEFT = 75,
  ARROW_RIGHT = 77,
  SYMBOL_BEFORE_ARROWS = 224,

  ENTER = 13,
  ESCAPE = 27
};



Game::Game()
{
  gameState_ = new GameState();
  gameUI_ = new ConsoleUI();
  isPaused_ = false;

  int width = gameState_->getMaze()->getColumns();
  int height = gameState_->getMaze()->getRows();

  gameUI_->setMazeWidthHeight(width, height);

  menuItems_ = { "Start game", "High scores", "Exit" };
  selectedMenuItem_ = main_menu_options::START_GAME;

  changedPacmanDirectionEvent.Attach(&gameState_->pacman_);
  changedPacmanDirectionEvent.Attach(&gameState_->pacman_);
}



Game::~Game()
{
  if (gameState_ != nullptr) {
    changedPacmanDirectionEvent.Detach(&gameState_->pacman_);
    delete gameState_;
    gameState_ = nullptr;
  }

  if (gameUI_ != nullptr) {
    delete gameUI_;
    gameUI_ = nullptr;
  }
}



void Game::run()
{
  mainMenu();
}



key getPressedKey()
{
  int pressedKey;
  while (true) {
    pressedKey = _getch();

    if (pressedKey == key::ENTER) {
      return key::ENTER;
    }
    else if (pressedKey == key::ESCAPE) {
      return key::ESCAPE;
    }
    else if (pressedKey == key::SYMBOL_BEFORE_ARROWS) {
      key arrow = static_cast<key>(_getch());
      return arrow;
    }
  }
}



void Game::mainMenu()
{
  gameUI_->displayMainMenu(menuItems_, selectedMenuItem_);

  if (menuItems_.size() <= main_menu_options::EXIT) {
    throw std::exception("wrong amount of menu items");
  }

  while (true)
  {
    key pressedKey = getPressedKey();
    switch (pressedKey) {
      case key::ARROW_UP:
        if (selectedMenuItem_ > main_menu_options::START_GAME)
          selectedMenuItem_--;
        else
          selectedMenuItem_ = main_menu_options::EXIT;

        gameUI_->displayMainMenu(menuItems_, selectedMenuItem_);
        break;

      case key::ARROW_DOWN:
        if (selectedMenuItem_ < main_menu_options::EXIT)
          selectedMenuItem_++;
        else
          selectedMenuItem_ = main_menu_options::START_GAME;

        gameUI_->displayMainMenu(menuItems_, selectedMenuItem_);
        break;

      case key::ENTER:
        handleSelectedMenuItem(selectedMenuItem_);
        break;

      case key::ESCAPE:
        return;
    }
  }
}



void Game::handleSelectedMenuItem(int menuItemIndex)
{
  main_menu_options selectedOption = static_cast<main_menu_options>(menuItemIndex);
  switch (selectedOption) {
    case START_GAME:
      startGame();
      break;

    case HIGH_SCORES:
      //
      break;

    case EXIT:
      exit(0);
      break;
  }
}



void Game::startGame()
{
  thread inputThread(&Game::handlePacmanControl, this);


  while(true) {
    gameState_->pacman_.Move();
    gameUI_->draw(*gameState_);
    std::this_thread::sleep_for(200ms);
  }

  inputThread.detach();
}



void Game::handlePacmanControl()
{
  while (true) {
    char keypressed = _getch();
    switch (keypressed) {
      case 'w':
      case 'W':
        changedPacmanDirectionEvent.Notify(direction::UP);
        break;

      case 's':
      case 'S':
        changedPacmanDirectionEvent.Notify(direction::DOWN);
        break;

      case 'a':
      case 'A':
        changedPacmanDirectionEvent.Notify(direction::LEFT);
        break;

      case 'd':
      case 'D':
        changedPacmanDirectionEvent.Notify(direction::RIGHT);
        break;

      case 'p':
      case 'P':

        break;
    }
  }
}