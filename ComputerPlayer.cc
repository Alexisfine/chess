#include "ComputerPlayer.h"
#include "ValidMove.h"
#include <random>
#include <vector>

ComputerPlayer::ComputerPlayer(int playerNo, ChessBoard *board, const ChessColor &color) :
    Player{playerNo, PlayerType::COMPUTER, board, color} {}

void ComputerPlayer::setLevel(int newLevel) {
    level = newLevel;
}    

const ChessColor ComputerPlayer::getColor() const {
    return color;
}

int ComputerPlayer::randomint(int size) {
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, size);
    int randomIndex = distr(eng);
    return randomIndex;
}

ValidMove ComputerPlayer::getMove() {
    // if (level == 1) {
    //     vector<ValidMove> moves = board->getAllValidMoves(color, true);
    //     int randomIndex = randomint(moves.size() - 1); //generate a random integer
    //     return moves[randomIndex];
    // }
    vector<ValidMove> moves = board->getAllValidMoves(color, true);
    vector<ValidMove> priorityMoves;
    if (level >= 2) {
        for (const auto& move : moves) {
            if (move.getCanCapture() || move.getCanCheck()) {
                priorityMoves.push_back(move);
            }
        }
    }

    // For Level 2, choose randomly among capturing or checking moves, if available
    if (level == 2 && !priorityMoves.empty()) {
        return priorityMoves[randomint(priorityMoves.size() - 1)];
    }

    // For Level 3, add moves that reduce potential captures by the opponent
    if (level == 3) {
        for (const auto& move : moves) {
            if (!board->simulateCapture(move, color)) {
                priorityMoves.push_back(move);
            }
        }
        if (!priorityMoves.empty()) {
            return priorityMoves[randomint(priorityMoves.size() - 1)];
        }
    }

    // If no priority moves are available, or if level is 1, make a random move
    return moves[randomint(moves.size() - 1)];
}
    //select a random cell from AllChessPiece
//    while (true) {
//        if (allChessPiece.empty()) return false; //if there are no movable chesspieces, return false
//        int randomIndex = randomint(allChessPiece.size() - 1); //generate a random integer
//        Cell randomCell = allChessPiece[randomIndex];
//        //select a random move
//        Position pos = randomCell.getPosition();
//        std::vector<ValidMove> allRandomMove = randomCell.getChessPiece()->getAvailableMoves(*board, pos, true);
//        if (allRandomMove.empty()) {
//            allChessPiece.erase(allChessPiece.begin() + randomIndex); //remove this chesspiece that has no valid moves
//            continue; //reselect a cell
//        }
//        Move randomMove = allRandomMove[randomint(allRandomMove.size() - 1)];
//        board->makeMove(randomMove, color);
//        return true;
//    }

