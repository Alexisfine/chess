#include "ChessGame.h"
#include "TwoPlayerChessBoard.h"
#include "HumanPlayer.h"
#include <iostream>

ChessGame::ChessGame(int dimension) : chessBoard{new TwoPlayerChessBoard{dimension}}, score(2, 0){
    Player* p1 = new HumanPlayer{1, chessBoard, ChessColor::WHITE};
    players.emplace_back(p1);
    Player* p2 = new HumanPlayer{2, chessBoard, ChessColor::BLACK};
    players.emplace_back(p2);
    isChecked[players[0]] = false;
    isChecked[players[1]] = false;
}

ChessGame::~ChessGame() {
    for (auto player : players) delete player;
    delete chessBoard;
}

void ChessGame::start() {
    inGame = true;
    gameResult = GameResult::IN_PROGRESS;
    isChecked[players[0]] = false;
    isChecked[players[1]] = false;
}

bool ChessGame::makeMove(const Position& from, const Position& to) {
    Move move {from, to, chessBoard->getCellAtPos(from).getChessPiece()};
    bool flag = chessBoard->makeMove(move, players[currentTurn]->getColor());
    if (flag) switchTurn();
    for (auto player : players) {
        if (chessBoard->isColorInCheck(player->getColor())) {
            isChecked[player] = true;
        } else {
            isChecked[player] = false;
        }
    }
    for (auto player : players) {
        if (chessBoard->isColorInCheckMate(player->getColor())) {
            inGame = false;
            if (currentTurn == 0) {
                score[1]++;
                gameResult = GameResult::BLACK_WON;
            } else {
                score[0]++;
                gameResult = GameResult::WHITE_WON;
            }
        }
    }
    return flag;
}

bool ChessGame::move(const Position& from, const Position& to) {
    bool res = makeMove(from, to);
    if (inGame) {
        int possibleMovesWhite = chessBoard->getAllValidMoves(ChessColor::WHITE, true).size();
        int possibleMovesBlack = chessBoard->getAllValidMoves(ChessColor::BLACK, true).size();
        if (possibleMovesWhite == 0 || possibleMovesBlack == 0) {
            inGame = false;
            gameResult = GameResult::DRAW;
        }
    }
    return res;
}


bool ChessGame::hasStarted() {
    return inGame;
}

void ChessGame::resign() {
    inGame = false;
    if (currentTurn == 0) {
        score[1]++;
        gameResult = GameResult::BLACK_WON;
    } else {
        score[0]++;
        gameResult = GameResult::WHITE_WON;
    }
}

std::ostream &operator<<(std::ostream &out, const ChessGame& game) {
    out << *game.chessBoard;
    return out;
}

void ChessGame::switchTurn() {
    if (currentTurn < players.size() - 1) currentTurn++;
    else currentTurn = 0;
}

map<Player*, bool> ChessGame::getIsChecked() {
    return isChecked;
}

ChessColor ChessGame::getCurrentColor() {
    return players[currentTurn]->getColor();
}

void ChessGame::addChess(const Position& pos, ChessColor color, ChessType chessType) {
    return chessBoard->addTo(pos, color, chessType);
}
void ChessGame::removeChess(const Position& pos) {
    return chessBoard->remove(pos);
}

void ChessGame::setCurrentTurn(ChessColor color) {
    if (color == ChessColor::WHITE) {
        currentTurn = 0;
    } else {
        currentTurn = 1;
    }
}

bool ChessGame::verifySetup() {
    return chessBoard->verifySetup();
}

void ChessGame::displayScore() {
    cout << "Final Score:" << endl;
    cout << "White: " << score[0] << endl;
    cout << "Black: " << score[1] << endl;
}

GameResult ChessGame::getResult() {
    return gameResult;
}










