#include "ChessInVS.h"

void Rook::Move(unsigned char m){
    Type=5;
    SimpleMoveFunction(Mov[m][0],Mov[m][1]);
}

void Rook::LegalMoves(){
    DeleteMoves();
    int d=1;
    while((Pos>>3)>=d && B->WBoard[Pos-8*d]*Color<=0){
        AddMove(Pos,Pos-8*d);
        if(B->WBoard[Pos-8*d++]*Color<0)break;
    }
    d=1;
    while((Pos>>3)<=7-d && B->WBoard[Pos+8*d]*Color<=0){
        AddMove(Pos,Pos+8*d);
        if(B->WBoard[Pos+8*d++]*Color<0)break;
    }
    d=1;
    while((Pos&7)>=d && B->WBoard[Pos-d]*Color<=0){
        AddMove(Pos,Pos-d);
        if(B->WBoard[Pos-d++]*Color<0)break;
    }
    d=1;
    while((Pos&7)<=7-d && B->WBoard[Pos+d]*Color<=0){
        AddMove(Pos,Pos+d);
        if(B->WBoard[Pos+d++]*Color<0)break;
    }
}
