#include "ChessInVS.h"

void fancySmanschyPrintBoard(Board * B) {
    char* P = B->WBoard;
    int H = 5, W = 10;
    system("color");
    printf("\n   ");
    for(int i=0;i<8;i++){
        for(int h=0;h<H;h++){
            for(int j=0;j<8;j++){
                if((j+i)%2)printf("\033[%s;%sm",BGblack,TXwhite);
                else printf("\033[%s;%sm",BGwhite,TXblack);
                if(!P[(7-i)*8+j]){
                    if(!h && !j)printf("%i",8-i);
                    else printf(" ");
                    for(int w=0;w<W-2;w++)printf(" ");
                    if(h==4 && i==7)printf("%c",97+j);
                    else printf(" ");
                }
                else {
                    if(!h && !j)printf("%i",8-i);
                    else printf(" ");
                    if(P[(7 - i) * 8 + j] >0 && (j+i)%2)printf("\033[%s;%sm",BGblack,PCwhite);
                    else if(P[(7 - i) * 8 + j] >0 && !((j+i)%2))printf("\033[%s;%sm",BGwhite,PCwhite);
                    else if(P[(7 - i) * 8 + j] <0 && (j+i)%2)printf("\033[%s;%sm",BGblack,PCblack);
                    else printf("\033[%s;%sm",BGwhite,PCblack);

                    if(abs(P[(7 - i) * 8 + j])==8 || abs(P[(7 - i) * 8 + j])==7){
                        if(h==0)printf("%c%c%c%c%c%c%c%c",32,32,32,220,220,32,32,32);
                        if(h==1)printf("%c%c%c%c%c%c%c%c",32,32,223,219,219,223,32,32);
                        if(h==2)printf("%c%c%c%c%c%c%c%c",32,220,219,219,219,219,220,32);
                        if(h==3)printf("%c%c%c%c%c%c%c%c",32,220,219,219,219,219,220,32);
                        if(B->Check && (P[(7 - i) * 8 + j] *(1-2*B->Turn)==8 || P[(7 - i) * 8 + j] *(1-2*B->Turn)==7) && (j+i)%2)printf("\033[%s;%sm",BGblack,KGcheck);
                        if(B->Check && (P[(7 - i) * 8 + j] *(1-2*B->Turn)==8 || P[(7 - i) * 8 + j] *(1-2*B->Turn)==7) && !((j+i)%2))printf("\033[%s;%sm",BGwhite,KGcheck);
                        if(h==4)printf("%c%c%c%c%c%c%c%c",32,223,223,223,223,223,223,32);
                        if(P[(7 - i) * 8 + j] >0 && (j+i)%2)printf("\033[%s;%sm",BGblack,PCwhite);
                        else if(P[(7 - i) * 8 + j] >0 && !((j+i)%2))printf("\033[%s;%sm",BGwhite,PCwhite);
                        else if(P[(7 - i) * 8 + j] <0 && (j+i)%2)printf("\033[%s;%sm",BGblack,PCblack);
                        else printf("\033[%s;%sm",BGwhite,PCblack);
                    }
                    if(abs(P[(7 - i) * 8 + j])==9){
                        if(h==0)printf("%c%c%c%c%c%c%c%c",32,32,220,32,32,220,32,32);
                        if(h==1)printf("%c%c%c%c%c%c%c%c",32,220,220,219,219,220,220,32);
                        if(h==2)printf("%c%c%c%c%c%c%c%c",32,32,220,219,219,220,32,32);
                        if(h==3)printf("%c%c%c%c%c%c%c%c",32,220,219,219,219,219,220,32);
                        if(h==4)printf("%c%c%c%c%c%c%c%c",32,223,223,223,223,223,223,32);
                    }
                    if(abs(P[(7 - i) * 8 + j])==5 || abs(P[(7 - i) * 8 + j])==6){
                        if(h==0)printf("%c%c%c%c%c%c%c%c",32,32,220,32,32,220,32,32);
                        if(h==1)printf("%c%c%c%c%c%c%c%c",32,32,219,219,219,219,32,32);
                        if(h==2)printf("%c%c%c%c%c%c%c%c",32,32,223,219,219,223,32,32);
                        if(h==3)printf("%c%c%c%c%c%c%c%c",32,32,220,219,219,220,32,32);
                        if(h==4)printf("%c%c%c%c%c%c%c%c",32,223,223,223,223,223,223,32);
                    }
                    if(abs(P[(7 - i) * 8 + j])==3){
                        if(h==0)printf("%c%c%c%c%c%c%c%c",32,32,32,220,220,220,32,32);
                        if(h==1)printf("%c%c%c%c%c%c%c%c",32,32,219,219,220,219,220,32);
                        if(h==2)printf("%c%c%c%c%c%c%c%c",32,32,219,219,219,223,223,32);
                        if(h==3)printf("%c%c%c%c%c%c%c%c",32,32,220,219,219,220,32,32);
                        if(h==4)printf("%c%c%c%c%c%c%c%c",32,223,223,223,223,223,223,32);
                    }
                    if(abs(P[(7 - i) * 8 + j])==4){
                        if(h==0)printf("%c%c%c%c%c%c%c%c",32,32,32,220,220,32,32,32);
                        if(h==1)printf("%c%c%c%c%c%c%c%c",32,32,219,219,219,219,32,32);
                        if(h==2)printf("%c%c%c%c%c%c%c%c",32,32,32,219,219,32,32,32);
                        if(h==3)printf("%c%c%c%c%c%c%c%c",32,32,220,219,219,220,32,32);
                        if(h==4)printf("%c%c%c%c%c%c%c%c",32,223,223,223,223,223,223,32);
                    }
                    if(abs(P[(7 - i) * 8 + j])==1 || abs(P[(7 - i) * 8 + j])==2){
                        if(h==0)printf("%c%c%c%c%c%c%c%c",32,32,32,32,32,32,32,32);
                        if(h==1)printf("%c%c%c%c%c%c%c%c",32,32,220,219,219,220,32,32);
                        if(h==2)printf("%c%c%c%c%c%c%c%c",32,32,223,219,219,223,32,32);
                        if(h==3)printf("%c%c%c%c%c%c%c%c",32,32,219,219,219,219,32,32);
                        if(h==4)printf("%c%c%c%c%c%c%c%c",32,32,32,32,32,32,32,32);
                    }

                    if((j+i)%2)printf("\033[%s;%sm",BGblack,TXwhite);
                    else printf("\033[%s;%sm",BGwhite,TXblack);
                    if(h==4 && i==7)printf("%c",97+j);
                    else printf(" ");
                }

            }
            printf("\033[0m\n   ");
        }

    }
    printf("\033[0m");
}

void PrintLegalMoves(char** m){
    int i=-1;
    printf(" LEGAL MOVES:");
    while(m[++i]){
        if(!(i%8))printf("\n\n  ");
        printf("%s",m[i]);
        int c=0;
        while(m[i][c++]);
        for(int j=c;j<9;j++)printf(" ");
    }
    printf("\n");
}

void PrintCurrentLines(Game* G) {
    if (!G->Lines || !G->Lines[0])return;
    printf("\n   L1(ML):  %s\n", G->S[G->Lines[0]->PreM]);
    int i = 0;
    while (G->Lines[++i]) {
        printf("   L%i:      %s\n", i + 1, G->S[G->Lines[i]->PreM]);
    }
}