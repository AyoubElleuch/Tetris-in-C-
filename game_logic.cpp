#include "game_logic.h"

bool canPlacePiece(
    const bool boardGrid[BoardHeight][BoardWidth],
    const bool piece[PieceHeight][PieceWidth],
    int candidateRow,
    int candidateCol) {
    for (int pieceRowIndex = 0; pieceRowIndex < PieceHeight; pieceRowIndex++) {
        for (int pieceColumnIndex = 0; pieceColumnIndex < PieceWidth; pieceColumnIndex++) {
            if (!piece[pieceRowIndex][pieceColumnIndex]) {
                continue;
            }

            int boardRow = candidateRow + pieceRowIndex;
            int boardColumn = candidateCol + pieceColumnIndex;
            if (boardRow < 0 || boardRow >= BoardHeight ||
                boardColumn < 0 || boardColumn >= BoardWidth ||
                boardGrid[boardRow][boardColumn]) {
                return false;
            }
        }
    }
    return true;
}

void lockPiece(
    bool boardGrid[BoardHeight][BoardWidth],
    const bool piece[PieceHeight][PieceWidth],
    int& pieceRow,
    int& pieceCol) {
    for (int pieceRowIndex = 0; pieceRowIndex < PieceHeight; pieceRowIndex++) {
        for (int pieceColumnIndex = 0; pieceColumnIndex < PieceWidth; pieceColumnIndex++) {
            if (piece[pieceRowIndex][pieceColumnIndex]) {
                boardGrid[pieceRow + pieceRowIndex][pieceCol + pieceColumnIndex] = true;
            }
        }
    }
    pieceRow = 0;
    pieceCol = BoardWidth / 2 - 1;
}
