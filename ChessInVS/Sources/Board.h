#pragma once

class GAME_API Board{
    public:
        PieceSet P[2];
        char WBoard[64];
        Piece* PBoard[64];
        bool Check;
        unsigned int Turn: 1;

        void AllLegalMoves();
        void DeleteAllMoves();
        void Check_ifLegal();
        void DestroyBoard();
        void MakeMove(unsigned char m);
        bool LegalMoves();
        bool SufficientMaterial();
        bool CanCastleQSD();
        bool CanCastleKSD();
};
