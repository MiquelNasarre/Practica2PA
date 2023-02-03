#include "ChessInVS.h"

void King::Move(unsigned char m) {
    Type=7;
    if(!(Mov[m][1]&64))return SimpleMoveFunction(Mov[m][0],Mov[m][1]);
    else{
        if (Mov[m][0] & 128)B->Check = true;
        if(Mov[m][1]==64){
            Rook* R = B->P[B->Turn].R[0];
            B->WBoard[Pos] = 0;
            B->PBoard[Pos] = 0;
            B->WBoard[R->Pos] = 0;
            B->PBoard[R->Pos] = 0;

            Pos = 2 + 28 - 28 * Color;
            R->Pos = 3 + 28 - 28 * Color;

            B->WBoard[Pos] = 7 * Color;
            B->PBoard[Pos] = this;
            B->WBoard[R->Pos] = 6 * Color;
            B->PBoard[R->Pos] = R;
            B->Turn = 1 - B->Turn;
            return;
        }
        if(Mov[m][1]==65){
            Rook* R = B->P[B->Turn].R[1];
            if (!R)R = B->P[B->Turn].R[0];
            B->WBoard[Pos] = 0;
            B->PBoard[Pos] = 0;
            B->WBoard[R->Pos] = 0;
            B->PBoard[R->Pos] = 0;

            Pos = 6 + 28 - 28 * Color;
            R->Pos = 5 + 28 - 28 * Color;

            B->WBoard[Pos] = 7 * Color;
            B->PBoard[Pos] = this;
            B->WBoard[R->Pos] = 6 * Color;
            B->PBoard[R->Pos] = R;
            B->Turn = 1 - B->Turn;
            return;

        }
    }
}

void King::LegalMoves(){
    DeleteMoves();
    if(!B->Check){
        if(B->CanCastleQSD())AddMove(64,64);
        if(B->CanCastleKSD())AddMove(65,65);
    }
    if((Pos&7)>0){
        if((Pos>>3)>0 && B->WBoard[Pos-9]*Color<=0)AddMove(Pos,Pos-9);
        if((Pos>>3)<7 && B->WBoard[Pos+7]*Color<=0)AddMove(Pos,Pos+7);
        if(B->WBoard[Pos-1]*Color<=0)AddMove(Pos,Pos-1);
    }
    if((Pos&7)<7){
        if((Pos>>3)>0 && B->WBoard[Pos-7]*Color<=0)AddMove(Pos,Pos-7);
        if((Pos>>3)<7 && B->WBoard[Pos+9]*Color<=0)AddMove(Pos,Pos+9);
        if(B->WBoard[Pos+1]*Color<=0)AddMove(Pos,Pos+1);
    }
    if((Pos>>3)<7 && B->WBoard[Pos+8]*Color<=0)AddMove(Pos,Pos+8);
    if((Pos>>3)>0 && B->WBoard[Pos-8]*Color<=0)AddMove(Pos,Pos-8);
}
