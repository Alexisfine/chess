#include "ChessGame.h"
#include "TwoPlayerChessBoard.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include <iostream>

ChessGame::ChessGame(int dimension) : chessBoard{new TwoPlayerChessBoard{dimension}} {}

ChessGame::~ChessGame() {
    for (auto player : players) delete player;
    delete chessBoard;
}

void ChessGame::start(PlayerType pt1, PlayerType pt2) {
    delete players[0];
    delete players[1];

    if (pt1 == PlayerType::HUMAN) {
        players[0] = new HumanPlayer{1, chessBoard, ChessColor::WHITE};
    } else {
        players[0] = new ComputerPlayer{1, chessBoard, ChessColor::WHITE};
    }

    if (pt2 == PlayerType::HUMAN) {
        players[1] = new HumanPlayer{1, chessBoard, ChessColor::BLACK};
    } else {
        players[1] = new ComputerPlayer{1, chessBoard, ChessColor::BLACK};
    }

    inGame = true;
    gameResult = GameResult::IN_PROGRESS;
    isChecked[0] = false;
    isChecked[1] = false;
}

bool ChessGame::makeMove(const Position& from, const Position& to) {
    Move move {from, to, chessBoard->getCellAtPos(from).getChessPiece()};
    bool flag = chessBoard->makeMove(move, players[currentTurn]->getColor());
    if (flag) {
        switchTurn();
        // Pawn promotion
        ChessPiece* cp = chessBoard->getCellAtPos(to).getChessPiece();
        if (cp->getType() == ChessType::PAWN) {
            if (cp->getColor() == ChessColor::WHITE && to.getRow() == 8) {
                chessBoard->remove(to);
                addChess(to, ChessColor::WHITE, ChessType::ROOK);
            } else if (cp->getColor() == ChessColor::BLACK && to.getRow() == 1) {
                chessBoard->remove(to);
                addChess(to, ChessColor::BLACK, ChessType::ROOK);
            }
        }

    }
    for (int i = 0; i < 2; i++) {
        if (chessBoard->isColorInCheck(players[i]->getColor())) {
            isChecked[i] = true;
        } else {
            isChecked[i] = false;
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
    if (currentTurn < 1) currentTurn++;
    else currentTurn = 0;
}

bool* ChessGame::getIsChecked() {
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

void ChessGame::init() {
    chessBoard->refresh();
    for (auto player : players) delete player;
    players[0] = nullptr;
    players[1] = nullptr;
}

bool ChessGame::autoMove(ChessColor color) {
    bool res = true;
    if (color == ChessColor::WHITE) {
        if (players[0]->getPlayerType() != PlayerType::COMPUTER) return false;
        ComputerPlayer* player = dynamic_cast<ComputerPlayer*>(players[0]);
        ValidMove move = player->getMove();
        res = chessBoard->makeMove(move, color);
    } else {
        if (players[1]->getPlayerType() != PlayerType::COMPUTER) return false;
        ComputerPlayer* player = dynamic_cast<ComputerPlayer*>(players[1]);
        ValidMove move = player->getMove();
        res = chessBoard->makeMove(move, color);
    }
    if (res) switchTurn();
    return res;
}










