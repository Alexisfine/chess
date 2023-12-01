#include "Rook.h"

Rook::Rook(ChessColor color) :
        ChessPiece{ChessType::ROOK, color} {}

MoveResult Rook::isMovePossiblyValid(ChessBoard& board, const Move& move)  {
    std::vector<ValidMove> possibleValidMoves = getAvailableMoves(board, move.getStart(), true);
    for (auto validMove : possibleValidMoves) {
        if (move.getStart() == validMove.getStart() && move.getEnd() == validMove.getEnd()) return {true, false};
    }
    return {false, false};
}

vector<ValidMove> Rook::addPossibleMoveByDirection(ChessBoard& board,
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
                } else newMoves.emplace_back(possibleMove);
            }
            break; //cannot move pass another chesspiece
        }
        //if the cell is not occupied
        ValidMove possibleMove {curPosition, newPosition, this, canCapture, canCheck};
        if (check) {
            bool willCheck = board.simulateMove(possibleMove, color);
            if (!willCheck) {
                newMoves.emplace_back(possibleMove);
            }
        } else newMoves.emplace_back(possibleMove);

        // update curRow and curCol
        curRow += dy;
        curCol += dx;
    }
    return newMoves;
}



std::vector<ValidMove> Rook::getAvailableMoves(ChessBoard& board, const Position& curPosition, bool check) {
    std::vector<ValidMove> moves;
    const int dimension = board.getDimension();
    int curRow = curPosition.getRow();
    int curCol = curPosition.getCol();
    //maximum number of moves, without considering blocks
    int RX = dimension - curCol;
    int LX = curCol - 1;
    int upY = dimension - curRow;
    int downY = curRow - 1;
    //move right
    auto right = addPossibleMoveByDirection(board, curPosition, 0, 1, RX, check);
    for (auto move : right) moves.emplace_back(move);

    //move left
    auto left = addPossibleMoveByDirection(board, curPosition, 0, -1, LX, check);
    for (auto move : left) moves.emplace_back(move);

    //move up
    auto up = addPossibleMoveByDirection(board, curPosition, 1, 0, upY, check);
    for (auto move : up) moves.emplace_back(move);

    //move down
    auto down = addPossibleMoveByDirection(board, curPosition, -1, 0, downY, check);
    for (auto move : down) moves.emplace_back(move);


    return moves;
}
