#include "ChessInVS.h"

void Piece::DeleteMoves(){
    int i=0;
    while(Mov[i]){
        free(Mov[i]);
        Mov[i]=0;
        i++;
    }
}

void Piece::DeleteMove(int j){
    free(Mov[j]);
    while(j<26 && Mov[j]){Mov[j]=Mov[j+1];j++;}
}

void Piece::Delete(){
    DeleteMoves();
    int i=0;
    if(Type<=2){
        while(B->P[(1-Color)/2].P[i]!=this)i++;
        while(i<7){B->P[(1-Color)/2].P[i]=B->P[(1-Color)/2].P[i+1];i++;}
        B->P[(1-Color)/2].P[7]=0;
    }
    else if(Type==3){
        while(B->P[(1-Color)/2].N[i]!=this)i++;
        while(i<9){B->P[(1-Color)/2].N[i]=B->P[(1-Color)/2].N[i+1];i++;}
        B->P[(1-Color)/2].N[9]=0;
    }
    else if(Type==4){
        while(B->P[(1-Color)/2].B[i]!=this)i++;
        while(i<9){B->P[(1-Color)/2].B[i]=B->P[(1-Color)/2].B[i+1];i++;}
        B->P[(1-Color)/2].B[9]=0;
    }
    else if(Type<=6){
        while(B->P[(1-Color)/2].R[i]!=this)i++;
        while(i<9){B->P[(1-Color)/2].R[i]=B->P[(1-Color)/2].R[i+1];i++;}
        B->P[(1-Color)/2].R[9]=0;
    }
    else {
        while(B->P[(1-Color)/2].Q[i]!=this)i++;
        while(i<8){B->P[(1-Color)/2].Q[i]=B->P[(1-Color)/2].Q[i+1];i++;}
        B->P[(1-Color)/2].Q[8]=0;
    }
    free(this);
}

void Piece::AddMove(unsigned char pi, unsigned char pf){
    int i=0;
    while(Mov[i])i++;
    Mov[i]=(unsigned char*)malloc(2);
    Mov[i][0]=pi;
    Mov[i][1]=pf;
}

void Piece::SimpleMoveFunction(unsigned char pi, unsigned char pf) {
    B->Turn = 1 - B->Turn;
    B->Check = false;
    if (pi & 128)B->Check = true;
    pi = pi & 127;
    if (B->PBoard[pf])B->PBoard[pf]->Delete();
    B->WBoard[pi] = 0;
    B->PBoard[pi] = 0;
    B->WBoard[pf] = Type * Color;
    B->PBoard[pf] = this;
    Pos = pf;
}

Piece* CopyPiece(Piece* P0, Board* B){
    Piece* P=(Piece*)calloc(1,sizeof(Piece));
    P->B=B;
    P->Type=P0->Type;
    P->Color=P0->Color;
    P->Pos=P0->Pos;
    B->PBoard[P->Pos]=P;
    return P;
}

Piece* NewPiece(Board* B,char C,unsigned char Pos, unsigned char T){
    Piece* P=(Piece*)calloc(1,sizeof(Piece));
    P->B=B;
    P->Type=T;
    P->Color=C;
    P->Pos=Pos;
    B->PBoard[Pos]=P;
    B->WBoard[Pos]=T*C;
    return P;
}
