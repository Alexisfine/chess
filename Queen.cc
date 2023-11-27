#include "Queen.h"

Queen::Queen(ChessBoard& board, Player& owner):
    ChessPiece(ChessType::QUEEN, board, owner) {}

bool Queen::isMovePossiblyValid(const Move& move)  {
    std::vector<ValidMove> possibleValidMoves = getAvailableMoves(move.getStart());
    for (auto validMove : possibleValidMoves) {
        if (move.getStart() == validMove.getStart() && move.getEnd() == validMove.getEnd()) return true;
    }
    return false;
}

void Queen::addPossibleMoveByDirection(std::vector<ValidMove> possibleMoves,
                                const Position& curPosition, int dy, int dx, int maxMoves) {
    int curRow = curPosition.getRow();
    int curCol = curPosition.getCol();
    for (int x = 0; x < maxMoves; x++) {
        Position newPosition {curRow + dy, curCol + dx};
        if (!board.isValidPos(newPosition)) return; // check if position is valid
        const Cell& cell = board.getCellAtPos(newPosition);
        bool canCapture = false;
        bool canCheck = false;
        if (cell.isOccupied()) {
            canCapture = true;
            if (!cell.isOccupiedByMe(owner)) {
                ValidMove possibleMove {curPosition, newPosition, this, canCapture, canCheck};
                possibleMoves.emplace_back(possibleMove);
            }
            break; //cannot move pass another chesspiece
        }
        //if the cell is not occupied
        ValidMove possibleMove {curPosition, newPosition, this, canCapture, canCheck};
        possibleMoves.emplace_back(possibleMove);

        // update curRow, curCol
        curRow += dy;
        curCol += dx;
    }

}
std::vector<ValidMove> Queen::getAvailableMoves(const Position& curPosition)  {
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
    addPossibleMoveByDirection(moves, curPosition, 0, 1, RX);

    //move left
    addPossibleMoveByDirection(moves, curPosition, 0, -1, LX);

    //move up
    addPossibleMoveByDirection(moves, curPosition, 1, 0, upY);

    //move down
    addPossibleMoveByDirection(moves, curPosition, -1, 0, downY);

    //diagonal moves
    int UR = std::min(RX, upY); //up-right direction
    int UL = std::min(LX, upY); //up-left direction
    int DR = std::min(RX, downY); //down-right direction
    int DL = std::min(LX, downY); //down-left direction
    //1. Up-right diagonal moves
    addPossibleMoveByDirection(moves, curPosition, 1, 1, UR);
    //2. Up-left diagonal moves
    addPossibleMoveByDirection(moves, curPosition, 1, -1, UL);
    //3. Down-right diagonal moves
    addPossibleMoveByDirection(moves, curPosition, -1, 1, DR);
    //4. Down-left diagonal moves
    addPossibleMoveByDirection(moves, curPosition, -1, -1, DL);

    return moves;
}
