#pragma once

class GAME_API Piece{
    public:
        int Color: 2;
        unsigned int Type: 4;
        unsigned char Pos;
        unsigned char* Mov[28];
        Board* B;

        //virtual void Move(unsigned char m) = 0;
        //virtual void LegalMoves() = 0;

        void Delete();
        void DeleteMoves();
        void DeleteMove(int j);
        void AddMove(unsigned char pi, unsigned char pf);
        void SimpleMoveFunction(unsigned char pi,unsigned char pf);
};