#pragma once

#include "RoyalGame.hpp"
#include "TetrisGame.hpp"

#include <iostream>
#include <memory>
#include <vector>

class GameEngine
{
  public:
    GameEngine() = default;
    virtual ~GameEngine() = default;

    [[nodiscard]] virtual bool handleAction(TetrisGame& game, Action action);

    [[nodiscard]] virtual bool handleBag(TetrisGame& game);
    virtual void handleEmptyBag(TetrisGame& game);
    virtual void handleSwap(TetrisGame& game);

    [[nodiscard]] virtual bool handleFallingPiece(TetrisGame& game);
    [[nodiscard]] virtual bool handlePlacingPiece(TetrisGame& game);

    virtual void handleSpawn(TetrisGame& game);
    virtual void handleSpawn(TetrisGame& game, Tetromino& piece);

    virtual void handleGameLogic(TetrisGame& game);
    virtual void handleGameOver(TetrisGame& game);
    virtual void handleScore(TetrisGame& game, int linesCleared);
    virtual void handlingRoutine(TetrisGame& game, Action action);

    // interface for bonus and malus (should raise an exception if not
    // implemented) and view

    [[nodiscard]] virtual bool viewPreviousOpponent(TetrisGame& game);
    [[nodiscard]] virtual bool viewNextOpponent(TetrisGame& game);

    virtual void handleBonus(TetrisGame& game);
    virtual void handleMalus(TetrisGame& game);

    static void sendToEnemy();
    static void handleEnergy();
};
