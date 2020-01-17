#include <conio.h>
#include <chrono>
#include <thread>
#include "Game.h"
using std::thread;
using namespace std::chrono_literals;

namespace pacman
{

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



  Game::Game(GameUI* gameUI)
  {
    if (gameUI == nullptr) {
      exit(0);
    }
    gameUI_ = gameUI;
    gameState_ = new GameState();
    isPaused_ = true;
    pointsForDot_ = 10;
    pointsForEnergizer_ = 50;

    int width = gameState_->getMaze()->getColumns();
    int height = gameState_->getMaze()->getRows();

    gameUI_->setMazeWidthHeight(width, height);

    menuItems_ = { "Start game", "High scores", "Exit" };
    selectedMenuItem_ = main_menu_options::START_GAME;

    changedPacmanDirectionEvent_.subscribe(&gameState_->pacman_);
  }



  Game::~Game()
  {
    if (gameState_ != nullptr) {
      changedPacmanDirectionEvent_.unSubscribe(&gameState_->pacman_);
      delete gameState_;
      gameState_ = nullptr;
    }
  }



  void Game::run()
  {
    mainMenu();
  }



  key getPressedKey()
  {
    int pressedKey;
    key returnedKey;

    bool infiniteLoop = true;
    while (infiniteLoop) {
      pressedKey = _getch();

      if (pressedKey == key::ENTER) {
        returnedKey = key::ENTER;
        infiniteLoop = false;
      }
      else if (pressedKey == key::ESCAPE) {
        returnedKey = key::ESCAPE;
        infiniteLoop = false;
      }
      else if (pressedKey == key::SYMBOL_BEFORE_ARROWS) {
        key arrow = static_cast<key>(_getch());
        returnedKey = arrow;
        infiniteLoop = false;
      }
    }
    return returnedKey;
  }



  void Game::mainMenu()
  {
    gameUI_->displayMainMenu(menuItems_, selectedMenuItem_);

    if (menuItems_.size() <= main_menu_options::EXIT) {
      throw std::exception("wrong amount of menu items");
    }

    bool infiniteLoop = true;
    while (infiniteLoop)
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
          infiniteLoop = false;
          break;
      }
    }
  }



  void Game::handleSelectedMenuItem(const int menuItemIndex)
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

    gameUI_->draw(*gameState_);

    bool isGameContinuing = true;
    while(isGameContinuing) {
      if (!isPaused_) {
        gameState_->pacman_.move();
        eatFood();

        gameUI_->draw(*gameState_);
      }
      std::this_thread::sleep_for(200ms);
    }

    inputThread.detach();
  }



  void Game::eatFood()
  {
    Point pacmanPosition = gameState_->getPacmanPosition();
    Cell cell = gameState_->getMaze()->getCell(pacmanPosition);

    if (cell.food != food::EMPTY) {
      switch (cell.food)
      {
        case food::DOT:
          gameState_->score_ += pointsForDot_;
          break;

        case food::ENERGIZER:
          gameState_->score_ += pointsForEnergizer_;
          break;
      }
      gameState_->setFood(pacmanPosition, food::EMPTY);
    }
  }



  void Game::handlePacmanControl()
  {
    while (true) {
      char keypressed = _getch();
      switch (keypressed) {
        case 'w':
        case 'W':
          isPaused_ = false;
          changedPacmanDirectionEvent_.notify(direction::UP);
          break;

        case 's':
        case 'S':
          isPaused_ = false;
          changedPacmanDirectionEvent_.notify(direction::DOWN);
          break;

        case 'a':
        case 'A':
          isPaused_ = false;
          changedPacmanDirectionEvent_.notify(direction::LEFT);
          break;

        case 'd':
        case 'D':
          isPaused_ = false;
          changedPacmanDirectionEvent_.notify(direction::RIGHT);
          break;

        case 'p':
        case 'P':
          isPaused_ = !isPaused_;
          break;
      }
    }
  }


}