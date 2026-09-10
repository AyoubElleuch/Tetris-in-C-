#include "game_logic.h"
#include "pieces.h"
#include <stdlib.h>

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

void clearFullLines(bool boardGrid[BoardHeight][BoardWidth]) {
    for (int row = BoardHeight - 1; row >= 0;) {
        bool isFull = true;
        for (int col = 0; col < BoardWidth; col++) {
            if (!boardGrid[row][col]) {
                isFull = false;
                break;
            }
        }

        if (isFull) {
            for (int tempRow = row; tempRow > 0; tempRow--) {
                for (int col = 0; col < BoardWidth; col++) {
                    boardGrid[tempRow][col] = boardGrid[tempRow - 1][col];
                }
            }
            for (int col = 0; col < BoardWidth; col++) {
                boardGrid[0][col] = false;
            }
        } else {
            row--;
        }
    }
}

bool isGameOver(
    const bool boardGrid[BoardHeight][BoardWidth],
    const bool piece[PieceHeight][PieceWidth]) {
        return !canPlacePiece(boardGrid, piece, 0, BoardWidth / 2 - 1);
}
    
void restartGame(
    bool boardGrid[BoardHeight][BoardWidth],
    int& pieceRow,
    int& pieceCol) {
    for (int row = 0; row < BoardHeight; row++) {
        for (int col = 0; col < BoardWidth; col++) {
            boardGrid[row][col] = false;
        }
    }
    pieceRow = 0;
    pieceCol = BoardWidth / 2 - 1;
}

void chooseRandomPiece(bool piece[PieceHeight][PieceWidth]) {
    int pieceIndex = rand() % 7;
    for (int row = 0; row < PieceHeight; row++) {
        for (int col = 0; col < PieceWidth; col++) {
            piece[row][col] = pieces[pieceIndex][row][col];
        }
    }
}

bool validRotatePiece(
    const bool boardGrid[BoardHeight][BoardWidth],
    const bool piece[PieceHeight][PieceWidth],
    int pieceRow,
    int pieceCol) {
    bool temp[PieceHeight][PieceWidth];
    for (int row = 0; row < PieceHeight; row++) {
        for (int col = 0; col < PieceWidth; col++) {
            temp[row][col] = piece[row][col];
        }
    }
    for (int row = 0; row < PieceHeight; row++) {
        for (int col = 0; col < PieceWidth; col++) {
            temp[row][col] = piece[PieceHeight - col - 1][row];
        }
    }
    return canPlacePiece(boardGrid, temp, pieceRow, pieceCol);
}

void rotatePiece(bool piece[PieceHeight][PieceWidth]) {
    bool temp[PieceHeight][PieceWidth];
    for (int row = 0; row < PieceHeight; row++) {
        for (int col = 0; col < PieceWidth; col++) {
            temp[row][col] = piece[row][col];
        }
    }
    for (int row = 0; row < PieceHeight; row++) {
        for (int col = 0; col < PieceWidth; col++) {
            piece[row][col] = temp[PieceHeight - col - 1][row];
        }
    }
}

void copyPiece(
    const bool source[PieceHeight][PieceWidth],
    bool destination[PieceHeight][PieceWidth]) {
    for (int row = 0; row < PieceHeight; row++) {
        for (int col = 0; col < PieceWidth; col++) {
            destination[row][col] = source[row][col];
        }
    }
}