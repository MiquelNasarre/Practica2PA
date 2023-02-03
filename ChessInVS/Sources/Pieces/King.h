#pragma once

class GAME_API King:public Piece{
    public:
       void Move(unsigned char m);
       void LegalMoves();
};