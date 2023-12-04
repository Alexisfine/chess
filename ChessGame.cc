#include "ChessGame.h"
#include "TwoPlayerChessBoard.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include <iostream>

ChessGame::ChessGame(int dimension, XWindow& xw) : chessBoard{new TwoPlayerChessBoard{dimension}} {
    chessBoard->addGraphicsDisplay(xw);
}

ChessGame::~ChessGame() {
    for (auto player : players) delete player;
    delete chessBoard;
}

void ChessGame::start(PlayerType pt1, PlayerType pt2, int level1, int level2) {
    delete players[0];
    delete players[1];

    if (pt1 == PlayerType::HUMAN) {
        players[0] = new HumanPlayer{1, chessBoard, ChessColor::WHITE};
    } else {
        players[0] = new ComputerPlayer{1, chessBoard, ChessColor::WHITE};
        auto compPlayer = dynamic_cast<ComputerPlayer*>(players[0]);
        if (compPlayer) compPlayer->setLevel(level1);
    }

    if (pt2 == PlayerType::HUMAN) {
        players[1] = new HumanPlayer{2, chessBoard, ChessColor::BLACK};
    } else {
        players[1] = new ComputerPlayer{2, chessBoard, ChessColor::BLACK};
        auto compPlayer = dynamic_cast<ComputerPlayer*>(players[1]);
        if (compPlayer) compPlayer->setLevel(level2);

    }

    inGame = true;
    gameResult = GameResult::IN_PROGRESS;
    isChecked[0] = false;
    isChecked[1] = false;

    chessBoard->getTextDisplay().printMessage("Game begins");
    chessBoard->getTextDisplay().printContent();

    int possibleMoves = 0;
    if (currentTurn == 0) {
        possibleMoves = chessBoard->getAllValidMoves(ChessColor::WHITE, true).size();

    } else {
        possibleMoves = chessBoard->getAllValidMoves(ChessColor::BLACK, true).size();
    }
    if (possibleMoves == 0) {
        inGame = false;
        gameResult = GameResult::DRAW;
        score[0] += 0.5;
        score[1] += 0.5;
    }

    // stalemate setup
    if (getResult() == GameResult::DRAW) {
        chessBoard->getTextDisplay().printMessage("Stalemate");
        init();
    }
}

MoveResult ChessGame::makeMove(const Position& from, const Position& to) {
    Move move {from, to, chessBoard->getCellAtPos(from).getChessPiece()};
    MoveResult moveResult = chessBoard->makeMove(move, players[currentTurn]->getColor());

    if (!moveResult.success) return moveResult;
    switchTurn();

    if (chessBoard->isColorInCheck(ChessColor::BLACK)) {
        isChecked[1] = true;
    } else isChecked[1] = false;

    if (chessBoard->isColorInCheck(ChessColor::WHITE)) {
        isChecked[0] = true;
    } else isChecked[0] = false;

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
    return moveResult;
}

MoveResult ChessGame::move(const Position& from, const Position& to) {
    MoveResult res = makeMove(from, to);
    if (inGame && res.success) {
        int possibleMoves = 0;
        if (chessBoard->getCellAtPos(to).isOccupiedByColor(ChessColor::WHITE)) {
            possibleMoves = chessBoard->getAllValidMoves(ChessColor::BLACK, true).size();

        } else {
            possibleMoves = chessBoard->getAllValidMoves(ChessColor::WHITE, true).size();
        }
        if (possibleMoves == 0) {
            inGame = false;
            gameResult = GameResult::DRAW;
            score[0] += 0.5;
            score[1] += 0.5;
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
        chessBoard->getTextDisplay().printMessage("Black wins!");
    } else {
        score[0]++;
        gameResult = GameResult::WHITE_WON;
        chessBoard->getTextDisplay().printMessage("White wins!");
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
    setCurrentTurn(ChessColor::WHITE);
    for (auto player : players) delete player;
    players[0] = nullptr;
    players[1] = nullptr;
}

bool ChessGame::autoMove(ChessColor color) {
    MoveResult res;
    if (color == ChessColor::WHITE) {
        if (players[0]->getPlayerType() != PlayerType::COMPUTER) return false;
        ComputerPlayer* player = dynamic_cast<ComputerPlayer*>(players[0]);
        ValidMove move = player->getMove();
        res = chessBoard->makeMove(move, color);
        if (res.success && res.pawnPromotion) {
            removeChess(move.getEnd());
            addChess(move.getEnd(), ChessColor::WHITE, ChessType::QUEEN);
        }
    } else {
        if (players[1]->getPlayerType() != PlayerType::COMPUTER) return false;
        ComputerPlayer* player = dynamic_cast<ComputerPlayer*>(players[1]);
        ValidMove move = player->getMove();
        res = chessBoard->makeMove(move, color);
        if (res.success && res.pawnPromotion) {
            removeChess(move.getEnd());
            addChess(move.getEnd(), ChessColor::BLACK, ChessType::QUEEN);
        }
    }
    if (res.success) {
        if (chessBoard->isColorInCheck(ChessColor::BLACK)) {
            isChecked[1] = true;
        } else isChecked[1] = false;
        if (chessBoard->isColorInCheck(ChessColor::WHITE)) {
            isChecked[0] = true;
        } else isChecked[0] = false;
        switchTurn();

    }
    return res.success;
}

void ChessGame::erase() {
    for (int row = 1; row <= 8; row++) {
        for (int col = 1; col <= 8; col++) {
            removeChess({row, col});
        }
    }
}

void ChessGame::promotePawn(ChessType chessType, const Position& pos) {
    removeChess(pos);
    if (currentTurn == 0) {
        addChess(pos, ChessColor::BLACK, chessType);
    } else {
        addChess(pos, ChessColor::WHITE, chessType);
    }
    if (chessBoard->isColorInCheck(ChessColor::BLACK)) {
        isChecked[1] = true;
    } else isChecked[1] = false;

    if (chessBoard->isColorInCheck(ChessColor::WHITE)) {
        isChecked[0] = true;
    } else isChecked[0] = false;


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
}

void ChessGame::completeSetup() {
    chessBoard->completeSetup();
}

void ChessGame::postMove() {
    chessBoard->getTextDisplay().printContent();
    auto isCheckMate = getIsChecked();
    for (int i = 0; i < 2; i++) {
        if (*(isCheckMate + i)) {
            if (i == 0) {
                chessBoard->getTextDisplay().printMessage("White is in check.");
            } else {
                chessBoard->getTextDisplay().printMessage("Black is in check.");
            }
        }
    }

    // game has ended
    if (!hasStarted()) {
        if (getResult() == GameResult::WHITE_WON) {
            chessBoard->getTextDisplay().printMessage("Checkmate! White wins!");
        } else if (getResult() == GameResult::BLACK_WON) {
            chessBoard->getTextDisplay().printMessage("Checkmate! Black wins!");
        } else {
            chessBoard->getTextDisplay().printMessage("Stalemate");
        }
        init(); // reinitialized next game
    }
}