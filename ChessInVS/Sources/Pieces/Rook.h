#pragma once

class GAME_API Rook:public Piece{
    public:
        void Move(unsigned char m);
        void LegalMoves();
};
