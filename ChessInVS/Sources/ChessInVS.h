#pragma once

#include <iostream>

#ifdef EXPORT_DLL
    #define GAME_API __declspec(dllexport)
#else
    #define GAME_API __declspec(dllimport)
#endif

#define GAME_FILES_FOLDER "..\\ChessInVS\\Resources\\GameFiles\\"

#pragma region Console Board Colors

#define BGblack "100"
#define TXblack  "90"
#define PCblack  "30"
#define BGwhite "103"
#define TXwhite  "93"
#define PCwhite  "33"
#define KGcheck  "31"

#pragma endregion

#pragma region Class & Functions

class Board;
class Piece;
class Pawn;
class Knight;
class Bishop;
class Rook;
class Queen;
class King;
class Game;

typedef struct pieceSet{
    Pawn* P[8];
    Knight* N[10];
    Bishop* B[10];
    Rook* R[10];
    Queen* Q[9];
    King* K;
}PieceSet;

Board* initialBoard();
Board* FisherRandomBoard();
Board* copyBoard(Board* B0);
Piece* CopyPiece(Piece* P0,Board* B);
Piece* NewPiece(Board* B,char C,unsigned char Pos, unsigned char T);
bool CompareBoards(Board* B1, Board* B2);

extern GAME_API void fancySmanschyPrintBoard(Board * B);
extern GAME_API void PrintLegalMoves(char** m);
extern GAME_API void PrintCurrentLines(Game* G);

#pragma endregion

#include "Board.h"
#include "Piece.h"
#include "King.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "Pawn.h"
#include "Game.h"