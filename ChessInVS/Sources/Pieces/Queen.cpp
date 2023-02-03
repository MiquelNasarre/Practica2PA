#include "ChessInVS.h"

void Queen::Move(unsigned char m){
    SimpleMoveFunction(Mov[m][0],Mov[m][1]);
}

void Queen::LegalMoves(){
    DeleteMoves();
    int d=1;
    while((Pos>>3)>=d && (Pos&7)>=d && B->WBoard[Pos-9*d]*Color<=0){
        AddMove(Pos,Pos-9*d);
        if(B->WBoard[Pos-9*d++]*Color<0)break;
    }
    d=1;
    while((Pos>>3)>=d && (Pos&7)<=7-d && B->WBoard[Pos-7*d]*Color<=0){
        AddMove(Pos,Pos-7*d);
        if(B->WBoard[Pos-7*d++]*Color<0)break;
    }
    d=1;
    while((Pos>>3)<=7-d && (Pos&7)>=d && B->WBoard[Pos+7*d]*Color<=0){
        AddMove(Pos,Pos+7*d);
        if(B->WBoard[Pos+7*d++]*Color<0)break;
    }
    d=1;
    while((Pos>>3)<=7-d && (Pos&7)<=7-d && B->WBoard[Pos+9*d]*Color<=0){
        AddMove(Pos,Pos+9*d);
        if(B->WBoard[Pos+9*d++]*Color<0)break;
    }
    d=1;
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
