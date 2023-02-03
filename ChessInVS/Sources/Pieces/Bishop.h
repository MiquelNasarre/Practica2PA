#pragma once

class GAME_API Bishop:public Piece{
    public:
        void Move(unsigned char m);
        void LegalMoves();
};