#include "ChessInVS.h"

bool Checked(unsigned char K,char* B, char C){
    int d=1;
    char p;
    while((K>>3)>=d && (K&7)>=d){
        p=B[K-9*d];
        if(p){
            if(p*C==-9 || p*C==-4 || (d==1 && C==-1 && (p==1 || p==2)))return true;
            break;
        }
        d++;
    }
    d=1;
    while((K>>3)>=d && (K&7)<=7-d){
        p=B[K-7*d];
        if(p){
            if(p*C==-9 || p*C==-4 || (d==1 && C==-1 && (p==1 || p==2)))return true;
            break;
        }
        d++;
    }
    d=1;
    while((K>>3)<=7-d && (K&7)>=d){
        p=B[K+7*d];
        if(p){
            if(p*C==-9 || p*C==-4 || (d==1 && C==1 && (p==-1 || p==-2)))return true;
            break;
        }
        d++;
    }
    d=1;
    while((K>>3)<=7-d && (K&7)<=7-d){
        p=B[K+9*d];
        if(p){
            if(p*C==-9 || p*C==-4 || (d==1 && C==1 && (p==-1 || p==-2)))return true;
            break;
        }
        d++;
    }
    d=1;
    while((K>>3)>=d){
        p=B[K-8*d];
        if(p){
            if(p*C==-9 || p*C==-5 || p*C==-6)return true;
            break;
        }
        d++;
    }
    d=1;
    while((K>>3)<=7-d){
        p=B[K+8*d];
        if(p){
            if(p*C==-9 || p*C==-5 || p*C==-6)return true;
            break;
        }
        d++;
    }
    d=1;
    while((K&7)>=d){
        p=B[K-d];
        if(p){
            if(p*C==-9 || p*C==-5 || p*C==-6)return true;
            break;
        }
        d++;
    }
    d=1;
    while((K&7)<=7-d){
        p=B[K+d];
        if(p){
            if(p*C==-9 || p*C==-5 || p*C==-6)return true;
            break;
        }
        d++;
    }

    if((K&7)>0){
        if((K>>3)>1 && B[K-17]*C==-3)return true;
        if((K>>3)<6 && B[K+15]*C==-3)return true;
    }

    if((K&7)<7){
        if((K>>3)>1 && B[K-15]*C==-3)return true;
        if((K>>3)<6 && B[K+17]*C==-3)return true;
    }

    if((K>>3)>0){
        if((K&7)>1 && B[K-10]*C==-3)return true;
        if((K&7)<6 && B[K-6]*C==-3)return true;
    }

    if((K>>3)<7){
        if((K&7)>1 && B[K+6]*C==-3)return true;
        if((K&7)<6 && B[K+10]*C==-3)return true;
    }
    return false;
}

unsigned char CheckMove(unsigned char pi,unsigned char pf, char* B,char C,unsigned char K1,unsigned char K2){
    unsigned char cs=0;
    if(pi>=64){
        cs=1;
        if(pi==64){
            pi=0+28-28*C;
            pf=3+28-28*C;
            K1=2+28-28*C;
        }
        else{
            pi=7+28-28*C;
            pf=5+28-28*C;
            K1=6+28-28*C;
        }
        B[4+28-28*C]=0;
    }
    unsigned op=0;
    char ti=B[pi];
    char tf=B[pf&63];
    B[pi]=0;
    B[pf&63]=ti;
    if(ti==C && (((pf&63)>>3)==0 || ((pf&63)>>3)==7)){
        if (pf>=192)B[pf&63]=9*C;
        else if(pf>=128)B[pf&63]=5*C;
        else if(pf>=64)B[pf&63]=4*C;
        else B[pf&63]=3*C;
    }
    else if(ti==C && B[pf-8*C]*C==-2){
        op=pf-8*C;
        B[pf-8*C]=0;
    }
    unsigned char s=1;
    if(Checked(K2,B,-C))s=2;
    if(Checked(K1,B,C))s=0;

    B[pi]=ti;
    B[pf&63]=tf;
    if(op)B[op]=-2*C;
    if(cs)B[4+28-28*C]=8*C;

    return s;
}

void Board::AllLegalMoves(){
    P[1-Turn].K->DeleteMoves();
    int i=0;
    while(P[1-Turn].P[i] && i<8)P[1-Turn].P[i++]->DeleteMoves();
    i=0;
    while(P[1-Turn].N[i] && i<10)P[1-Turn].N[i++]->DeleteMoves();
    i=0;
    while(P[1-Turn].B[i] && i<10)P[1-Turn].B[i++]->DeleteMoves();
    i=0;
    while(P[1-Turn].R[i] && i<10)P[1-Turn].R[i++]->DeleteMoves();
    i=0;
    while(P[1-Turn].Q[i] && i<9)P[1-Turn].Q[i++]->DeleteMoves();

    P[Turn].K->LegalMoves();
    i=0;
    while(P[Turn].P[i] && i<8)P[Turn].P[i++]->LegalMoves();
    i=0;
    while(P[Turn].N[i] && i<10)P[Turn].N[i++]->LegalMoves();
    i=0;
    while(P[Turn].B[i] && i<10)P[Turn].B[i++]->LegalMoves();
    i=0;
    while(P[Turn].R[i] && i<10)P[Turn].R[i++]->LegalMoves();
    i=0;
    while(P[Turn].Q[i] && i<9)P[Turn].Q[i++]->LegalMoves();
}

void Board::DeleteAllMoves() {
    P[0].K->DeleteMoves();
    int i = 0;
    while (P[0].P[i] && i < 8)P[0].P[i++]->DeleteMoves();
    i = 0;
    while (P[0].N[i] && i < 10)P[0].N[i++]->DeleteMoves();
    i = 0;
    while (P[0].B[i] && i < 10)P[0].B[i++]->DeleteMoves();
    i = 0;
    while (P[0].R[i] && i < 10)P[0].R[i++]->DeleteMoves();
    i = 0;
    while (P[0].Q[i] && i < 9)P[0].Q[i++]->DeleteMoves();

    P[1].K->DeleteMoves();
    i = 0;
    while (P[1].P[i] && i < 8)P[1].P[i++]->DeleteMoves();
    i = 0;
    while (P[1].N[i] && i < 10)P[1].N[i++]->DeleteMoves();
    i = 0;
    while (P[1].B[i] && i < 10)P[1].B[i++]->DeleteMoves();
    i = 0;
    while (P[1].R[i] && i < 10)P[1].R[i++]->DeleteMoves();
    i = 0;
    while (P[1].Q[i] && i < 9)P[1].Q[i++]->DeleteMoves();
}

void Board::Check_ifLegal(){
    unsigned char L;
    char* Iboard=(char*)memcpy(malloc(64),WBoard,64);
    int j=0;
    while(P[Turn].K->Mov[j] && j<27){
        L=CheckMove(P[Turn].K->Mov[j][0],P[Turn].K->Mov[j][1],Iboard,1-2*Turn,P[Turn].K->Mov[j][1],P[1-Turn].K->Pos);
        if(!L){P[Turn].K->DeleteMove(j);continue;}
        if(L==2)P[Turn].K->Mov[j][0]+=128;
        j++;
    }
    int i=0;
    while(P[Turn].P[i] && i<8){
        j=0;
        while(P[Turn].P[i]->Mov[j] && j<27){
            L=CheckMove(P[Turn].P[i]->Mov[j][0],P[Turn].P[i]->Mov[j][1],Iboard,1-2*Turn,P[Turn].K->Pos,P[1-Turn].K->Pos);
            if(!L){P[Turn].P[i]->DeleteMove(j);continue;}
            if(L==2)P[Turn].P[i]->Mov[j][0]+=128;
            j++;
        }
        i++;
    }
    i=0;
    while(P[Turn].N[i] && i<10){
        j=0;
        while(P[Turn].N[i]->Mov[j] && j<27){
            L=CheckMove(P[Turn].N[i]->Mov[j][0],P[Turn].N[i]->Mov[j][1],Iboard,1-2*Turn,P[Turn].K->Pos,P[1-Turn].K->Pos);
            if(!L){P[Turn].N[i]->DeleteMove(j);continue;}
            if(L==2)P[Turn].N[i]->Mov[j][0]+=128;
            j++;
        }
        i++;
    }
    i=0;
    while(P[Turn].B[i] && i<10){
        j=0;
        while(P[Turn].B[i]->Mov[j] && j<27){
            L=CheckMove(P[Turn].B[i]->Mov[j][0],P[Turn].B[i]->Mov[j][1],Iboard,1-2*Turn,P[Turn].K->Pos,P[1-Turn].K->Pos);
            if(!L){P[Turn].B[i]->DeleteMove(j);continue;}
            if(L==2)P[Turn].B[i]->Mov[j][0]+=128;
            j++;
        }
        i++;
    }
    i=0;
    while(P[Turn].R[i] && i<10){
        j=0;
        while(P[Turn].R[i]->Mov[j] && j<27){
            L=CheckMove(P[Turn].R[i]->Mov[j][0],P[Turn].R[i]->Mov[j][1],Iboard,1-2*Turn,P[Turn].K->Pos,P[1-Turn].K->Pos);
            if(!L){P[Turn].R[i]->DeleteMove(j);continue;}
            if(L==2)P[Turn].R[i]->Mov[j][0]+=128;
            j++;
        }
        i++;
    }
    i=0;
    while(P[Turn].Q[i] && i<9){
        j=0;
        while(P[Turn].Q[i]->Mov[j] && j<27){
            L=CheckMove(P[Turn].Q[i]->Mov[j][0],P[Turn].Q[i]->Mov[j][1],Iboard,1-2*Turn,P[Turn].K->Pos,P[1-Turn].K->Pos);
            if(!L){P[Turn].Q[i]->DeleteMove(j);continue;}
            if(L==2)P[Turn].Q[i]->Mov[j][0]+=128;
            j++;
        }
        i++;
    }
}

void Board::DestroyBoard() {

    P[0].K->Delete();
    while (P[0].P[0])P[0].P[0]->Delete();
    while (P[0].N[0])P[0].N[0]->Delete();
    while (P[0].B[0])P[0].B[0]->Delete();
    while (P[0].R[0])P[0].R[0]->Delete();
    while (P[0].Q[0])P[0].Q[0]->Delete();
    P[1].K->Delete();
    while (P[1].P[0])P[1].P[0]->Delete();
    while (P[1].N[0])P[1].N[0]->Delete();
    while (P[1].B[0])P[1].B[0]->Delete();
    while (P[1].R[0])P[1].R[0]->Delete();
    while (P[1].Q[0])P[1].Q[0]->Delete();

    free(this);
}

void Board::MakeMove(unsigned char m){
    unsigned char i=0,j=0,n=0;
    while(P[Turn].K->Mov[j]){
        if(n==m)return P[Turn].K->Move(j);
        n++;
        j++;
    }
    while(i<8 && P[Turn].P[i]){
        j=0;
        while(P[Turn].P[i]->Mov[j]){
            if(n==m)return P[Turn].P[i]->Move(j);
            n++;
            j++;
        }
        i++;
    }
    i=0;
    while(i<8 && P[Turn].N[i]){
        j=0;
        while(P[Turn].N[i]->Mov[j]){
            if(n==m)return P[Turn].N[i]->Move(j);
            n++;
            j++;
        }
        i++;
    }
    i=0;
    while(i<8 && P[Turn].B[i]){
        j=0;
        while(P[Turn].B[i]->Mov[j]){
            if(n==m)return P[Turn].B[i]->Move(j);
            n++;
            j++;
        }
        i++;
    }
    i=0;
    while(i<8 && P[Turn].R[i]){
        j=0;
        while(P[Turn].R[i]->Mov[j]){
            if(n==m)return P[Turn].R[i]->Move(j);
            n++;
            j++;
        }
        i++;
    }
    i=0;
    while(i<8 && P[Turn].Q[i]){
        j=0;
        while(P[Turn].Q[i]->Mov[j]){
            if(n==m)return P[Turn].Q[i]->Move(j);
            n++;
            j++;
        }
        i++;
    }
}

bool Board::LegalMoves() {
    if (P[Turn].K->Mov[0])return true;
    int i = 0;
    while (P[Turn].P[i] && i < 8) {
        if (P[Turn].P[i++]->Mov[0])return true;
    }
    i = 0;
    while (P[Turn].N[i] && i < 10) {
        if (P[Turn].N[i++]->Mov[0])return true;
    }
    i = 0;
    while (P[Turn].B[i] && i < 10) {
        if (P[Turn].B[i++]->Mov[0])return true;
    }
    i = 0;
    while (P[Turn].R[i] && i < 10) {
        if (P[Turn].R[i++]->Mov[0])return true;
    }
    i = 0;
    while (P[Turn].Q[i] && i < 9) {
        if (P[Turn].Q[i++]->Mov[0])return true;
    }
    return false;
}

bool Board::SufficientMaterial() {

    if (P[0].R[0] || P[0].P[0] || P[0].Q[0])return true;
    if (P[0].N[0] && P[0].B[0]) return true;
    if (P[0].B[0] && P[0].B[1]) return true;
    if (P[0].N[0] && P[0].N[1] && P[1].N[2]) return true;

    if (P[1].R[0] || P[1].P[0] || P[1].Q[0])return true;
    if (P[1].N[0] && P[1].B[0]) return true;
    if (P[1].B[0] && P[1].B[1]) return true;
    if (P[1].N[0] && P[1].N[1] && P[1].N[2]) return true;

    return false;
}

bool Board::CanCastleQSD() {
    King* K = P[Turn].K;
    Rook* R = P[Turn].R[0];

    if (Check || K->Type == 7)return false;
    if (!R || R->Type == 5 || R->Pos > K->Pos)return false;

    unsigned char p = K->Pos - 1;
    while (p >= 2 + 56 * Turn) {
        if (R->Pos != p && WBoard[p])return false;
        p--;
    }

    p = R->Pos + 1;
    while (p <= 3 + 56 * Turn) {
        if (K->Pos != p && WBoard[p])return false;
        p++;
    }

    p = K->Pos - 1;
    while (p > 2 + 56 * Turn) {
        if (Checked(p--, WBoard, (1 - 2 * Turn)))return false;
    }
    if (Checked(2 + 56 * Turn, WBoard, (1 - 2 * Turn)))return false;

    return true;
}

bool Board::CanCastleKSD() {
    King* K = P[Turn].K;
    if (Check || K->Type == 7)return false;

    Rook* R = P[Turn].R[0];
    if (!R)return false;
    if (R->Pos < K->Pos)R = P[Turn].R[1];
    if (!R || R->Type==5)return false;

    unsigned char p = K->Pos + 1;
    while (p <= 6 + 56 * Turn) {
        if (R->Pos != p && WBoard[p])return false;
        p++;
    }

    p = R->Pos - 1;
    while (p >= 5 + 56 * Turn) {
        if (K->Pos != p && WBoard[p])return false;
        p--;
    }

    p = K->Pos + 1;
    while (p <= 6 + 56 * Turn) {
        if (Checked(p++, WBoard, (1 - 2 * Turn)))return false;
    }
    
    return true;
}

Board* initialBoard(){
    Board* B=(Board*)calloc(1,sizeof(Board));

    //WHITE PIECES

    B->P[0].K=(King*)NewPiece(B,1,4,8);
    B->P[0].Q[0]=(Queen*)NewPiece(B,1,3,9);
    B->P[0].R[0]=(Rook*)NewPiece(B,1,0,6);
    B->P[0].R[1]=(Rook*)NewPiece(B,1,7,6);
    B->P[0].N[0]=(Knight*)NewPiece(B,1,1,3);
    B->P[0].N[1]=(Knight*)NewPiece(B,1,6,3);
    B->P[0].B[0]=(Bishop*)NewPiece(B,1,2,4);
    B->P[0].B[1]=(Bishop*)NewPiece(B,1,5,4);
    for(int i=0;i<8;i++)B->P[0].P[i]=(Pawn*)NewPiece(B,1,8+i,1);

    //BLACK PIECES

    B->P[1].K=(King*)NewPiece(B,-1,4+56,8);
    B->P[1].Q[0]=(Queen*)NewPiece(B,-1,3+56,9);
    B->P[1].R[0]=(Rook*)NewPiece(B,-1,0+56,6);
    B->P[1].R[1]=(Rook*)NewPiece(B,-1,7+56,6);
    B->P[1].N[0]=(Knight*)NewPiece(B,-1,1+56,3);
    B->P[1].N[1]=(Knight*)NewPiece(B,-1,6+56,3);
    B->P[1].B[0]=(Bishop*)NewPiece(B,-1,2+56,4);
    B->P[1].B[1]=(Bishop*)NewPiece(B,-1,5+56,4);
    for(int i=0;i<8;i++)B->P[1].P[i]=(Pawn*)NewPiece(B,-1,48+i,1);

    return B;
}

Board* copyBoard(Board* B0){
    Board* B=(Board*)memcpy(malloc(sizeof(Board)),B0,sizeof(Board));

    B->P[0].K=(King*)CopyPiece(B0->P[0].K,B);
    B->P[1].K=(King*)CopyPiece(B0->P[1].K,B);
    int i=0;
    while(B0->P[0].N[i]){B->P[0].N[i]=(Knight*)CopyPiece(B0->P[0].N[i],B);i++;}i=0;
    while(B0->P[1].N[i]){B->P[1].N[i]=(Knight*)CopyPiece(B0->P[1].N[i],B);i++;}i=0;
    while(B0->P[0].B[i]){B->P[0].B[i]=(Bishop*)CopyPiece(B0->P[0].B[i],B);i++;}i=0;
    while(B0->P[1].B[i]){B->P[1].B[i]=(Bishop*)CopyPiece(B0->P[1].B[i],B);i++;}i=0;
    while(B0->P[0].R[i]){B->P[0].R[i]=(Rook*)CopyPiece(B0->P[0].R[i],B);i++;}i=0;
    while(B0->P[1].R[i]){B->P[1].R[i]=(Rook*)CopyPiece(B0->P[1].R[i],B);i++;}i=0;
    while(B0->P[0].Q[i]){B->P[0].Q[i]=(Queen*)CopyPiece(B0->P[0].Q[i],B);i++;}i=0;
    while(B0->P[1].Q[i]){B->P[1].Q[i]=(Queen*)CopyPiece(B0->P[1].Q[i],B);i++;}i=0;
    while(B0->P[0].P[i]){B->P[0].P[i]=(Pawn*)CopyPiece(B0->P[0].P[i],B);i++;}i=0;
    while(B0->P[1].P[i]){B->P[1].P[i]=(Pawn*)CopyPiece(B0->P[1].P[i],B);i++;}
    return B;
}

Board* FisherRandomBoard() {
    Board* B=(Board*)calloc(1,sizeof(Board));

    //RANDOM POSITION GENERATOR

    int p[8] = { 0,0,0,0,0,0,0,0 }, P[8] = { 0,0,0,0,0,0,0,0 }, h, i;

    srand(clock());

    //BISHOPS

    p[0] = 2 * (rand() % 4);
    p[1] = 2 * (rand() % 4) + 1;
    P[p[0]] = 1;
    P[p[1]] = 1;

    //QUEEN AND KINGHTS

    i = -1;
    h = rand() % 6 + 1;
    while (h) {
        i++;
        if (!P[i])h--;
    }
    p[2] = i;
    P[i] = 1;

    i = -1;
    h = rand() % 5 + 1;
    while (h) {
        i++;
        if (!P[i])h--;
    }
    p[3] = i;
    P[i] = 1;

    i = -1;
    h = rand() % 4 + 1;
    while (h) {
        i++;
        if (!P[i])h--;
    }
    p[4] = i;
    P[i] = 1;

    //ROOKS AND KING

    i = 0;
    while (P[i])i++;
    p[5] = i;
    P[i] = 1;
    i = 0;
    while (P[i])i++;
    p[6] = i;
    P[i] = 1;
    i = 0;
    while (P[i])i++;
    p[7] = i;
    P[i] = 1;

    //WHITE PIECES

    B->P[0].K = (King*)NewPiece(B, 1, p[6], 8);
    B->P[0].Q[0] = (Queen*)NewPiece(B, 1, p[2], 9);
    B->P[0].R[0] = (Rook*)NewPiece(B, 1, p[5], 6);
    B->P[0].R[1] = (Rook*)NewPiece(B, 1, p[7], 6);
    B->P[0].N[0] = (Knight*)NewPiece(B, 1, p[3], 3);
    B->P[0].N[1] = (Knight*)NewPiece(B, 1, p[4], 3);
    B->P[0].B[0] = (Bishop*)NewPiece(B, 1, p[0], 4);
    B->P[0].B[1] = (Bishop*)NewPiece(B, 1, p[1], 4);
    for (int i = 0; i < 8; i++)B->P[0].P[i] = (Pawn*)NewPiece(B, 1, 8 + i, 1);

    //BLACK PIECES

    B->P[1].K = (King*)NewPiece(B, -1, p[6] + 56, 8);
    B->P[1].Q[0] = (Queen*)NewPiece(B, -1, p[2] + 56, 9);
    B->P[1].R[0] = (Rook*)NewPiece(B, -1, p[5] + 56, 6);
    B->P[1].R[1] = (Rook*)NewPiece(B, -1, p[7] + 56, 6);
    B->P[1].N[0] = (Knight*)NewPiece(B, -1, p[3] + 56, 3);
    B->P[1].N[1] = (Knight*)NewPiece(B, -1, p[4] + 56, 3);
    B->P[1].B[0] = (Bishop*)NewPiece(B, -1, p[0] + 56, 4);
    B->P[1].B[1] = (Bishop*)NewPiece(B, -1, p[1] + 56, 4);
    for (int i = 0; i < 8; i++)B->P[1].P[i] = (Pawn*)NewPiece(B, -1, 48 + i, 1);

    return B;
}

bool CompareBoards(Board* B1, Board* B2) {
    if (B1->Turn != B2->Turn)return false;
    for (int i = 0; i < 64; i++) {
        if (B1->WBoard[i] != B2->WBoard[i])return false;
    }
    return true;
}
