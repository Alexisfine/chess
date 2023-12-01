#ifndef CHESS_TWOPLAYERCHESSBOARD_H
#define CHESS_TWOPLAYERCHESSBOARD_H


#include "ChessBoard.h"

class TwoPlayerChessBoard : public ChessBoard {
    void setupBoard();
public:
    TwoPlayerChessBoard(int dimension);
    MoveResult makeMove(Move move, ChessColor color) override;
    MoveResult isMoveLegal(const Move& move, ChessColor color) override;
    bool isValidPos(const Position& pos) const override;
    ~TwoPlayerChessBoard() override;
    void refresh() override;
    bool isColorInCheck(ChessColor color) override;
    bool isColorInCheckMate(ChessColor color) override;
    void addTo(const Position& pos, ChessColor color, ChessType chessType) override;
    void remove(const Position& pos) override;
    bool verifySetup() override;
    bool simulateMove(Move move, ChessColor color) override;
    bool simulateEnPassant(Move move, ChessColor color) override;
    std::vector<ValidMove> getAllValidMoves(ChessColor color, bool check) override;

};


#endif //CHESS_TWOPLAYERCHESSBOARD_H
