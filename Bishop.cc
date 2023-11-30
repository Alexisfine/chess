#include "Bishop.h"

Bishop::Bishop(ChessColor color):
    ChessPiece(ChessType::BISHOP, color) {}

bool Bishop::isMovePossiblyValid(ChessBoard& board, const Move& move) {
    std::vector<ValidMove> possibleValidMoves = getAvailableMoves(board, move.getStart(), false);
    for (auto validMove : possibleValidMoves) {
        if (move.getStart() == validMove.getStart() && move.getEnd() == validMove.getEnd()) return true;
    }
    return false;
}

std::vector<ValidMove> Bishop::addPossibleMoveByDirection(ChessBoard& board,
                                        const Position& curPosition, int dy, int dx, int maxMoves, bool check) {
    vector<ValidMove> newMoves;
    int curRow = curPosition.getRow();
    int curCol = curPosition.getCol();
    for (int x = 0; x < maxMoves; x++) {
        Position newPosition {curRow + dy, curCol + dx};
        if (!board.isValidPos(newPosition)) return newMoves; // check if position is valid
        const Cell& cell = board.getCellAtPos(newPosition);
        bool canCapture = false;
        bool canCheck = false;
        if (cell.isOccupied()) {
            canCapture = true;
            if (!cell.isOccupiedByColor(color)) {
                ValidMove possibleMove {curPosition, newPosition, this, canCapture, canCheck};
                if (check) {
                    bool willCheck = board.simulateMove(possibleMove, color);
                    if (!willCheck) {
                        newMoves.emplace_back(possibleMove);
                    }
                } else {
                    newMoves.emplace_back(possibleMove);
                }
            }
            break; //cannot move pass another chesspiece
        }
        //if the cell is not occupied
        ValidMove possibleMove {curPosition, newPosition, this, canCapture, canCheck};
        if (check) {
            bool willCheck = board.simulateMove(possibleMove, color);
            if (!willCheck) newMoves.emplace_back(possibleMove);
        } else newMoves.emplace_back(possibleMove);


        // update curRow and curCol
        curRow += dy;
        curCol += dx;
    }
    return newMoves;
}


std::vector<ValidMove> Bishop::getAvailableMoves(ChessBoard& board, const Position& curPosition, bool check)  {
    std::vector<ValidMove> moves;
    int curRow = curPosition.getRow();
    int curCol = curPosition.getCol();
    //maximum number of moves, without considering blocks
    int dimension = board.getDimension();
    int RX = dimension - curCol;
    int LX = curCol - 1;
    int upY = dimension - curRow;
    int downY = curRow - 1;
    //diagonal moves
    int UR = std::min(RX, upY); //up-right direction
    int UL = std::min(LX, upY); //up-left direction
    int DR = std::min(RX, downY); //down-right direction
    int DL = std::min(LX, downY); //down-left direction
    //1. Up-right diagonal moves
    auto upRight = addPossibleMoveByDirection(board, curPosition, 1, 1, UR, check);
    for (auto move : upRight) moves.emplace_back(move);

    //2. Up-left diagonal moves
    auto upLeft = addPossibleMoveByDirection(board, curPosition, 1, -1, UL, check);
    for (auto move : upLeft) moves.emplace_back(move);

    //3. Down-right diagonal moves
    auto downRight = addPossibleMoveByDirection(board, curPosition, -1, 1, DR, check);
    for (auto move : downRight) moves.emplace_back(move);

    //4. Down-left diagonal moves
    auto downLeft = addPossibleMoveByDirection(board, curPosition, -1, -1, DL, check);
    for (auto move : downLeft) moves.emplace_back(move);

    return moves;
}



