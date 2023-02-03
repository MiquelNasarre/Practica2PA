#include "ChessInVS.h"

void Pawn::Move(unsigned char m){
    SimpleMoveFunction(Mov[m][0],Mov[m][1]&63);
    if(B->WBoard[Pos-8*Color]==-2*Color){
        B->PBoard[Pos-8*Color]->Delete();
        B->PBoard[Pos-8*Color]=0;
        B->WBoard[Pos-8*Color]=0;
    }
    else if(((Mov[m][1]&63)-(Mov[m][0]&127))*Color==16){
        B->WBoard[Pos]=2*Color;
        Type=2;
    }
    else if((Pos>>3)==0 || (Pos>>3)==7){
        int i=0;
        if(Mov[m][1]>=192){
            while (B->P[(1-Color)/2].Q[i])i++;
            B->P[(1-Color)/2].Q[i]=(Queen*)calloc(1,sizeof(Queen));
            B->P[(1-Color)/2].Q[i]->B=B;
            B->P[(1-Color)/2].Q[i]->Pos=Pos;
            B->P[(1-Color)/2].Q[i]->Color=Color;
            B->P[(1-Color)/2].Q[i]->Type=9;
            B->WBoard[Pos]=9*Color;
            B->PBoard[Pos]=B->P[(1-Color)/2].Q[i];
        }
        else if(Mov[m][1]>=128){
            while (B->P[(1-Color)/2].R[i])i++;
            B->P[(1-Color)/2].R[i]=(Rook*)calloc(1,sizeof(Rook));
            B->P[(1-Color)/2].R[i]->B=B;
            B->P[(1-Color)/2].R[i]->Pos=Pos;
            B->P[(1-Color)/2].R[i]->Color=Color;
            B->P[(1-Color)/2].R[i]->Type=5;
            B->WBoard[Pos]=5*Color;
            B->PBoard[Pos]=B->P[(1-Color)/2].R[i];
        }
        else if(Mov[m][1]>=64){
            while (B->P[(1-Color)/2].B[i])i++;
            B->P[(1-Color)/2].B[i]=(Bishop*)calloc(1,sizeof(Bishop));
            B->P[(1-Color)/2].B[i]->B=B;
            B->P[(1-Color)/2].B[i]->Pos=Pos;
            B->P[(1-Color)/2].B[i]->Color=Color;
            B->P[(1-Color)/2].B[i]->Type=4;
            B->WBoard[Pos]=4*Color;
            B->PBoard[Pos]=B->P[(1-Color)/2].B[i];
        }
        else{
            while (B->P[(1-Color)/2].N[i])i++;
            B->P[(1-Color)/2].N[i]=(Knight*)calloc(1,sizeof(Knight));
            B->P[(1-Color)/2].N[i]->B=B;
            B->P[(1-Color)/2].N[i]->Pos=Pos;
            B->P[(1-Color)/2].N[i]->Color=Color;
            B->P[(1-Color)/2].N[i]->Type=3;
            B->WBoard[Pos]=3*Color;
            B->PBoard[Pos]=B->P[(1-Color)/2].N[i];
        }
        Delete();
    }
}

void Pawn::LegalMoves(){
    DeleteMoves();
    if(Type==2)B->WBoard[Pos]=Color;
    Type=1;
    if(B->WBoard[Pos-1]*Color==-2)AddMove(Pos,Pos-1+8*Color);
    if(B->WBoard[Pos+1]*Color==-2)AddMove(Pos,Pos+1+8*Color);
    if(((Pos>>3)*Color==1 || (Pos>>3)*Color==-6) && !B->WBoard[Pos+8*Color] && !B->WBoard[Pos+16*Color])AddMove(Pos,Pos+16*Color);
    if((Pos>>3)*Color!=-1 && (Pos>>3)*Color!=6){
        if(!B->WBoard[Pos+8*Color])AddMove(Pos,Pos+8*Color);
        if((Pos&7)>0 && B->WBoard[Pos-1+8*Color]*Color<0)AddMove(Pos,Pos-1+8*Color);
        if((Pos&7)<7 && B->WBoard[Pos+1+8*Color]*Color<0)AddMove(Pos,Pos+1+8*Color);
    }
    else {
        if(!B->WBoard[Pos+8*Color]){
            AddMove(Pos,Pos+Color*8);
            AddMove(Pos,Pos+Color*8+64);
            AddMove(Pos,Pos+Color*8+128);
            AddMove(Pos,Pos+Color*8+192);
        }
        if((Pos&7)>0 && B->WBoard[Pos-1+8*Color]*Color<0){
            AddMove(Pos,Pos-1+8*Color);
            AddMove(Pos,Pos-1+8*Color+64);
            AddMove(Pos,Pos-1+8*Color+128);
            AddMove(Pos,Pos-1+8*Color+192);
        }
        if((Pos&7)<7 && B->WBoard[Pos+1+8*Color]*Color<0){
            AddMove(Pos,Pos+1+8*Color);
            AddMove(Pos,Pos+1+8*Color+64);
            AddMove(Pos,Pos+1+8*Color+128);
            AddMove(Pos,Pos+1+8*Color+192);
        }
    }
}
