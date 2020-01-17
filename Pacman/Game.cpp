#include <conio.h>
#include <chrono>
#include <thread>
#include "Game.h"
#include "ConsoleKey.h"
using std::thread;
using namespace std::chrono_literals;

namespace pacman
{

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
    int pressedKey = _getch();
    if (pressedKey == key::SYMBOL_BEFORE_ARROWS) {
      key arrow = static_cast<key>(_getch());
      return arrow;
    }
    return static_cast<key>(pressedKey);
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
        case key::ENG_W_CAPITAL:
        case key::ENG_W_LOWERCASE:
        case key::RUS_W_CAPITAL:
        case key::RUS_W_LOWERCASE:
          if (selectedMenuItem_ > main_menu_options::START_GAME)
            selectedMenuItem_--;
          else
            selectedMenuItem_ = main_menu_options::EXIT;

          gameUI_->displayMainMenu(menuItems_, selectedMenuItem_);
          break;

        case key::ARROW_DOWN:
        case key::ENG_S_CAPITAL:
        case key::ENG_S_LOWERCASE:
        case key::RUS_S_CAPITAL:
        case key::RUS_S_LOWERCASE:
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

        if (gameState_->isLevelComplete()) {
          isPaused_ = true;
          if (gameState_->getLevel() > 255) {
            // game over. save score
          }
          else {
            gameState_->setPacmanStartPosition();
            gameState_->resetFood();
          }
        }

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
      unsigned char keypressed = _getch();
      switch (keypressed) {
        case ENG_W_CAPITAL:
        case ENG_W_LOWERCASE:
        case RUS_W_CAPITAL:
        case RUS_W_LOWERCASE:
          isPaused_ = false;
          changedPacmanDirectionEvent_.notify(direction::UP);
          break;

        case ENG_S_CAPITAL:
        case ENG_S_LOWERCASE:
        case RUS_S_CAPITAL:
        case RUS_S_LOWERCASE:
          isPaused_ = false;
          changedPacmanDirectionEvent_.notify(direction::DOWN);
          break;

        case ENG_A_CAPITAL:
        case ENG_A_LOWERCASE:
        case RUS_A_CAPITAL:
        case RUS_A_LOWERCASE:
          isPaused_ = false;
          changedPacmanDirectionEvent_.notify(direction::LEFT);
          break;

        case ENG_D_CAPITAL:
        case ENG_D_LOWERCASE:
        case RUS_D_CAPITAL:
        case RUS_D_LOWERCASE:
          isPaused_ = false;
          changedPacmanDirectionEvent_.notify(direction::RIGHT);
          break;

        case ENG_P_CAPITAL:
        case ENG_P_LOWERCASE:
        case RUS_P_CAPITAL:
        case RUS_P_LOWERCASE:
          isPaused_ = !isPaused_;
          break;
      }
    }
  }


}