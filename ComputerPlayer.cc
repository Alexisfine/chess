#include "ComputerPlayer.h"
#include <random>
#include <vector>

ComputerPlayer::ComputerPlayer(int playerNo, ChessBoard *board, const ChessColor &color) :
    Player{playerNo, true, board, color} {}

ChessColor ComputerPlayer::getColor() {
    return color;
}

int ComputerPlayer::randomint(int size) {
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, size);
    int randomIndex = distr(eng);
    return randomIndex;
}

bool ComputerPlayer::oneMove() {
    //LEVEL1: Random legal moves
    if (level == 1) {
    std::vector<Cell> allChessPiece; //a vector of all possible movable chesspieces
    for (int i = 1; i <= board->getDimension(); i++) {
        for (int j = 1; j <= board->getDimension(); j++) {
            const Position p {i,j};
            if (board->getCellAtPos(p).getState() == CellState::EMPTY) continue; //if the cell is empty
            if (board->getCellAtPos(p).getChessPiece()->getColor() == color) {
                allChessPiece.emplace_back(board->getCellAtPos(p));
            }
        }
    }
    //select a random cell from AllChessPiece
    while (true) {
        if (allChessPiece.empty()) return false; //if there are no movable chesspieces, return false
        int randomIndex = randomint(allChessPiece.size() - 1); //generate a random integer
        Cell randomCell = allChessPiece[randomIndex];
        //select a random move
        Position pos = randomCell.getPosition();
        std::vector<ValidMove> allRandomMove = randomCell.getChessPiece()->getAvailableMoves(*board, pos, true);
        if (allRandomMove.empty()) {
            allChessPiece.erase(allChessPiece.begin() + randomIndex); //remove this chesspiece that has no valid moves
            continue; //reselect a cell
        }
        Move randomMove = allRandomMove[randomint(allRandomMove.size() - 1)];
        board->makeMove(randomMove, color);
        return true;
    }
}
}