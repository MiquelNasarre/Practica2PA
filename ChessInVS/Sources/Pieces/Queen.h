#pragma once

class GAME_API Queen:public Piece{
    public:
        void Move(unsigned char m);
        void LegalMoves();
};
