#include "ComputerPlayer.h"
#include <random>
#include <vector>

ComputerPlayer::ComputerPlayer(int playerNo, ChessBoard *board, const ChessColor &color) :
    Player{playerNo, true, board, color} {}

ChessColor ComputerPlayer::getColor() {
    return color;
}

int randomint(int size) {
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, size);
    int randomIndex = distr(eng);
    return randomIndex;
}

bool ComputerPlayer::oneMove() {
    //LEVEL1: random legal moves
    if (level == 1) {
    std::vector<Cell> cp; //a vector of all possible movable chesspieces
    for (int i = 1; i <=8; i++) {
        for (int j = 1; j <= 8; j++) {
            const Position p {i,j};
            if (board->getCellAtPos(p).getState() == CellState::EMPTY) continue; //if the cell is empty
            if (board->getCellAtPos(p).getChessPiece()->getOwner().getColor() == color) {
                cp.emplace_back(board->getCellAtPos(p));
            }
        }
    }
    //select a random cell from cp
    while (true) {
        if (cp.empty()) return false; //if there are no movable chesspieces, return false
        int randomindex = randomint(cp.size() - 1); //generate a random integer
        Cell randomcell = cp[randomindex];
        //select a random move
        Position pos = randomcell.getPosition();
        std::vector<ValidMove> allrandommove = randomcell.getChessPiece()->getAvailableMoves(pos); 
        if (allrandommove.empty()) {
            cp.erase(cp.begin() + randomindex); //remove this chesspiece that has no valid moves
            continue; //reselect a cell
        }
        Move randommove = allrandommove[randomint(allrandommove.size() - 1)];
        board->makeMove(randommove, *this);
        return true;
    }
}
}