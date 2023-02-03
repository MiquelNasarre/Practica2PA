#pragma once

class GAME_API Knight:public Piece{
    public:
        void Move(unsigned char m);
        void LegalMoves();
};
