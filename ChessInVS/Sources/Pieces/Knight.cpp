#include "ChessInVS.h"

void Knight::Move(unsigned char m){
    SimpleMoveFunction(Mov[m][0],Mov[m][1]);
}

void Knight::LegalMoves(){
    DeleteMoves();
    if((Pos&7)>0){
        if((Pos>>3)>1 && B->WBoard[Pos-17]*Color<=0)AddMove(Pos,Pos-17);
        if((Pos>>3)<6 && B->WBoard[Pos+15]*Color<=0)AddMove(Pos,Pos+15);
    }
    if((Pos&7)<7){
        if((Pos>>3)>1 && B->WBoard[Pos-15]*Color<=0)AddMove(Pos,Pos-15);
        if((Pos>>3)<6 && B->WBoard[Pos+17]*Color<=0)AddMove(Pos,Pos+17);
    }
    if((Pos>>3)>0){
        if((Pos&7)>1 && B->WBoard[Pos-10]*Color<=0)AddMove(Pos,Pos-10);
        if((Pos&7)<6 && B->WBoard[Pos-6]*Color<=0)AddMove(Pos,Pos-6);
    }
    if((Pos>>3)<7){
        if((Pos&7)>1 && B->WBoard[Pos+6]*Color<=0)AddMove(Pos,Pos+6);
        if((Pos&7)<6 && B->WBoard[Pos+10]*Color<=0)AddMove(Pos,Pos+10);
    }
}
