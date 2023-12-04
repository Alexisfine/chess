#include "ComputerPlayer.h"
#include "ValidMove.h"
#include <random>
#include <vector>
#include <algorithm>

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
     if (level == 1) {
         vector<ValidMove> moves = board->getAllValidMoves(color, true);
         int randomIndex = randomint(moves.size() - 1); //generate a random integer
         return moves[randomIndex];
     }

     vector<ValidMove> moves = board->getAllValidMoves(color, true);
    if (level == 2) {
     std::sort(moves.begin(), moves.end(), [](const ValidMove& a, const ValidMove& b) {
         if (a.getCanCheck() != b.getCanCheck()) {
             // Moves where 'canCheck' is true come first
             return a.getCanCheck() > b.getCanCheck();
         } else {
             // Among moves with the same 'canCheck' status, sort by 'canCapture'
             return a.getCanCapture() > b.getCanCapture();
         }
     });
     return moves[0];
    }

    if (level == 3) {
        std::sort(moves.begin(), moves.end(), [](const ValidMove& a, const ValidMove& b) {
            if (a.getBeCapturedScore() != b.getBeCapturedScore()) {
                return a.getBeCapturedScore() > b.getBeCapturedScore();
            }
            else if (a.getCanCheck() != b.getCanCheck()) {
                // Moves where 'canCheck' is true come first
                return a.getCanCheck() > b.getCanCheck();
            } else {
                // Among moves with the same 'canCheck' status, sort by 'canCapture'
                return a.getCanCapture() > b.getCanCapture();
            }
        });
        return moves[0];
    }

    if (level == 4) {
        std::sort(moves.begin(), moves.end(), [](const ValidMove& a, const ValidMove& b) {
            int aScore = 0;
            int bScore = 0;
            if (a.getCanCheck()) aScore += 10;
            if (b.getCanCheck()) bScore += 10;
            aScore = aScore + a.getCapturedScore() + 2*a.getBeCapturedScore();
            bScore = bScore + b.getBeCapturedScore() + 2*b.getBeCapturedScore();
            return aScore > bScore;
        }
        );
    }
    return moves[0];
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

