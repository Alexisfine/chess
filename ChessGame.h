#ifndef CHESS_CHESSGAME_H
#define CHESS_CHESSGAME_H

#include "ChessBoard.h"
#include <map>
using namespace std;

enum class GameResult {
    IN_PROGRESS,
    WHITE_WON,
    BLACK_WON,
    DRAW
};



class ChessGame {
    ChessBoard* chessBoard;
    Player* players[2] = {nullptr, nullptr};
    int score[2] = {0, 0};
    bool isChecked[2] = {false, false};
    int currentTurn = 0;
    bool inGame = false;
    GameResult gameResult;
    MoveResult makeMove(const Position& from, const Position& to);
    void switchTurn();

public:
    ChessGame(int dimension);
    ~ChessGame();
    void start(PlayerType pt1, PlayerType pt2);
    void resign();
    bool hasStarted();
    void addChess(const Position& pos, ChessColor color, ChessType chessType);
    MoveResult move(const Position& from, const Position& to);
    ChessColor getCurrentColor();
    bool* getIsChecked();
    void removeChess(const Position& pos);
    void setCurrentTurn(ChessColor color);
    void init();
    bool autoMove(ChessColor color);
    void erase();
    void promotePawn(ChessType chessType, const Position& pos);
    void completeSetup();

    friend std::ostream &operator<<(std::ostream &out, const ChessGame& game);

    bool verifySetup();
    void displayScore();
    GameResult getResult();
};


#endif //CHESS_CHESSGAME_H
