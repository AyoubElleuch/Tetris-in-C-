#pragma once

constexpr int BoardWidth = 10;
constexpr int BoardHeight = 20;
constexpr int PieceWidth = 2;
constexpr int PieceHeight = 2;

bool canPlacePiece(
    const bool boardGrid[BoardHeight][BoardWidth],
    const bool piece[PieceHeight][PieceWidth],
    int candidateRow,
    int candidateCol);

void lockPiece(
    bool boardGrid[BoardHeight][BoardWidth],
    const bool piece[PieceHeight][PieceWidth],
    int& pieceRow,
    int& pieceCol);

void clearFullLines(bool boardGrid[BoardHeight][BoardWidth]);
