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
    vector<Player*> players;
    vector<int> score;
    map<Player*, bool> isChecked;
    int currentTurn = 0;
    bool inGame = false;
    GameResult gameResult;
    bool makeMove(const Position& from, const Position& to);
    void switchTurn();

public:
    ChessGame(int dimension);
    ~ChessGame();
    void start();
    void resign();
    bool hasStarted();
    void addChess(const Position& pos, ChessColor color, ChessType chessType);
    bool move(const Position& from, const Position& to);
    ChessColor getCurrentColor();
    map<Player*, bool> getIsChecked();
    void removeChess(const Position& pos);
    void setCurrentTurn(ChessColor color);

    friend std::ostream &operator<<(std::ostream &out, const ChessGame& game);

    bool verifySetup();
    void displayScore();
    GameResult getResult();
};


#endif //CHESS_CHESSGAME_H
