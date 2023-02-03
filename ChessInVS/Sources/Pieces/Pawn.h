#pragma once

class GAME_API Pawn:public Piece{
    public:
        void Move(unsigned char m);
        void LegalMoves();
};
