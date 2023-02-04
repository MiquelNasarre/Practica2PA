#include "ChessInVS.h"

void FilePrinterRecursive(Game* G, FILE* file) {
    if(G->Pre)fprintf(file, "%u ", G->PreM + 1);
    if (G->Lines) {
        int i = 0;
        while (G->Lines[i]) FilePrinterRecursive(G->Lines[i++], file);
    }
    if (G->Pre)fprintf(file, "0 ");
}

void Game::ExchangeWith(Game* G) {
    Game* p = G->Pre;
    Game** l = G->Lines;
    Board* b = G->B;
    unsigned char m = G->PreM;
    char** s = G->S;
    G->Pre = Pre;
    G->Lines = Lines;
    G->B = B;
    G->PreM = PreM;
    G->S = S;
    Pre = p;
    Lines = l;
    B = b;
    PreM = m;
    S = s;
}

void Game::GoBack(){
    if(Pre)ExchangeWith(Pre);
}

void Game::GoToLine(unsigned char i){
    int j=0;
    while(j<=i){
        if(Lines[j])j++;
        else return;
    }
    ExchangeWith(Lines[i]);
}

void Game::NewMove(unsigned char m){
    int i=0;
    while(Lines[i]){
        if(Lines[i]->PreM==m)return ExchangeWith(Lines[i]);
        i++;
    }
    Game** L=Lines;
    Lines=(Game**)memcpy(calloc(i+2,sizeof(void*)),Lines,sizeof(void*)*i);
    free(L);
    Lines[i]=(Game*)calloc(1,sizeof(Game));
    Lines[i]->Pre=Lines[i];
    Lines[i]->Lines=(Game**)calloc(1,sizeof(void*));
    Lines[i]->B=copyBoard(B);
    Lines[i]->B->AllLegalMoves();
    Lines[i]->B->Check_ifLegal();
    Lines[i]->B->MakeMove(m);
    Lines[i]->PreM=m;
    ExchangeWith(Lines[i]);
}

bool Game::DrawByRepetition() {
    int i = 0;
    Game* G = this;
    while (G) {
        if (CompareBoards(B, G->B))i++;
        G = G->Pre;
    }
    if (i >= 3)return true;
    return false;
}

void Game::StringMoveList(){
    B->AllLegalMoves();
    B->Check_ifLegal();
    unsigned char** M=(unsigned char**)calloc(250,sizeof(void*));
    unsigned char j=0,n=0,Turn=B->Turn;
    int i=0;
    PieceSet* P=B->P;

    while(B->P[Turn].K->Mov[j]){
        M[n]=(unsigned char*)malloc(2);
        M[n][0]=P[Turn].K->Mov[j][0];
        M[n++][1]=P[Turn].K->Mov[j++][1];
    }
    while(i<8 && P[Turn].P[i]){
        j=0;
        while(B->P[Turn].P[i]->Mov[j]){
            M[n]=(unsigned char*)malloc(2);
            M[n][0]=P[Turn].P[i]->Mov[j][0];
            M[n++][1]=P[Turn].P[i]->Mov[j++][1];
        }
        i++;
    }
    i=0;
    while(i<8 && P[Turn].N[i]){
        j=0;
        while(B->P[Turn].N[i]->Mov[j]){
            M[n]=(unsigned char*)malloc(2);
            M[n][0]=P[Turn].N[i]->Mov[j][0];
            M[n++][1]=P[Turn].N[i]->Mov[j++][1];
        }
        i++;
    }
    i=0;
    while(i<8 && P[Turn].B[i]){
        j=0;
        while(B->P[Turn].B[i]->Mov[j]){
            M[n]=(unsigned char*)malloc(2);
            M[n][0]=P[Turn].B[i]->Mov[j][0];
            M[n++][1]=P[Turn].B[i]->Mov[j++][1];
        }
        i++;
    }
    i=0;
    while(i<8 && P[Turn].R[i]){
        j=0;
        while(B->P[Turn].R[i]->Mov[j]){
            M[n]=(unsigned char*)malloc(2);
            M[n][0]=P[Turn].R[i]->Mov[j][0];
            M[n++][1]=P[Turn].R[i]->Mov[j++][1];
        }
        i++;
    }
    i=0;
    while(i<8 && P[Turn].Q[i]){
        j=0;
        while(B->P[Turn].Q[i]->Mov[j]){
            M[n]=(unsigned char*)malloc(2);
            M[n][0]=P[Turn].Q[i]->Mov[j][0];
            M[n++][1]=P[Turn].Q[i]->Mov[j++][1];
        }
        i++;
    }

    S=(char**)calloc(250,sizeof(void*));
    i=-1;
    while(M[++i]){
        S[i]=(char*)calloc(8,sizeof(char));
        if((M[i][0]&127)==M[i][1] && M[i][1]==64){
            S[i]=(char*)"O-O-O";
            if(M[i][0]&128)S[i]=(char*)"O-O-O+";
            continue;
        }
        if((M[i][0]&127)==M[i][1] && M[i][1]==65){
            S[i]=(char*)"O-O";
            if(M[i][0]&128)S[i]=(char*)"O-O+";
            continue;
        }
        int c=0;
        int p=abs(B->WBoard[(M[i][0]&127)]);
        if(p<3){
            if((M[i][1]-M[i][0])&7){
                S[i][c++]=(M[i][0]&7)+97;
                S[i][c++]='x';
            }
            S[i][c++]=(M[i][1]&7)+97;
            S[i][c++]=((M[i][1]&63)>>3)+49;
            if(M[i][1]>=192){S[i][c++]='=';S[i][c++]='Q';}
            else if(M[i][1]>=128){S[i][c++]='=';S[i][c++]='R';}
            else if(M[i][1]>=64){S[i][c++]='=';S[i][c++]='B';}
            else if(M[i][1]>55 || M[i][1]<8){S[i][c++]='=';S[i][c++]='N';}
            if(M[i][0]&128)S[i][c++]='+';
            continue;
        }
        if(p==5 || p==6)S[i][c++]='R';
        else if(p==3)S[i][c++]='N';
        else if(p==4)S[i][c++]='B';
        else if(p==9)S[i][c++]='Q';
        else if(p==7 || p==8)S[i][c++]='K';

        int j=-1;
        while(M[++j]){
            if(i!=j && M[i][1]==M[j][1]){
                if((p==5 || p==6) && (abs(B->WBoard[(M[j][0]&127)])==5 || abs(B->WBoard[(M[j][0]&127)])==6)){
                    if((M[i][0]&7)!=(M[j][0]&7))S[i][c++]=(M[i][0]&7)+97;
                    else S[i][c++]=((M[i][0]&127)>>3)+49;
                }
                if(p==3 && abs(B->WBoard[(M[j][0]&127)])==3){
                    if((M[i][0]&7)!=(M[j][0]&7))S[i][c++]=(M[i][0]&7)+97;
                    else S[i][c++]=((M[i][0]&127)>>3)+49;
                }
                if(p==4 && abs(B->WBoard[(M[j][0]&127)])==4){
                    if((M[i][0]&7)!=(M[j][0]&7))S[i][c++]=(M[i][0]&7)+97;
                    else S[i][c++]=((M[i][0]&127)>>3)+49;
                }
                if(p==9 && abs(B->WBoard[(M[j][0]&127)])==9){
                    if((M[i][0]&7)!=(M[j][0]&7))S[i][c++]=(M[i][0]&7)+97;
                    else S[i][c++]=((M[i][0]&127)>>3)+49;
                }
            }
        }

        if(B->WBoard[M[i][1]])S[i][c++]='x';
        S[i][c++]=(M[i][1]&7)+97;
        S[i][c++]=(M[i][1]>>3)+49;
        if(M[i][0]&128)S[i][c++]='+';
    }
}

void Game::DeleteGameTree() {
    if (B) {
        B->DestroyBoard();
        B = 0;
    }
    /*
    int i = 0;
    if (S) {
        while (S[i]) {
            free(S[i]);
            i++;
        }
        free(S);
        S = 0;
        i = 0;
    }
    */
    if (Lines) {
        int i = 0;
        while (Lines[i]) {
            Lines[i]->DeleteGameTree();
            free(Lines[i++]);
        }
        free(Lines);
        Lines = 0;
    }
    S = 0;
}

void Game::DeleteLine(unsigned char l) {
    int j = 0;
    while (j <= l) {
        if (Lines[j])j++;
        else return;
    }
    Lines[l]->DeleteGameTree();
    free(Lines[l]);
    while (Lines[l]) {
        Lines[l] = Lines[l + 1];
        l++;
    }
}

bool Game::GenerateTxtGameFile(char* name) {
    char FullName[100] = GAME_FILES_FOLDER;
    int i = 0;
    while (FullName[i])i++;
    int j = 0;
    while (name[j]) FullName[i++] = name[j++];
    FullName[i++] = '.';
    FullName[i++] = 't';
    FullName[i++] = 'x';
    FullName[i++] = 't';

    FILE* file = fopen(FullName, "w");
    if (!file)return false;

    unsigned char* m = (unsigned char*)calloc(1, 1000);
    int k = -1;
    while (Pre) { 
        m[++k] = this->PreM;
        ExchangeWith(Pre);
    }
    
    fprintf(file,"%u",B->P[0].K->Pos);
    fprintf(file, "%u", B->P[0].Q[0]->Pos);
    fprintf(file, "%u", B->P[0].R[0]->Pos);
    fprintf(file, "%u", B->P[0].R[1]->Pos);
    fprintf(file, "%u", B->P[0].N[0]->Pos);
    fprintf(file, "%u", B->P[0].N[1]->Pos);
    fprintf(file, "%u", B->P[0].B[0]->Pos);
    fprintf(file, "%u", B->P[0].B[1]->Pos);

    fprintf(file, "\n");
    FilePrinterRecursive(this,file);
    for (i = k; i >= 0; i--) {
        NewMove(m[i]);
        fprintf(file, "%u ", m[i] + 1);
    }
    fclose(file);
    return true;
}

bool Game::OpenTxtGameFile(char* name) {
    char FullName[100] = GAME_FILES_FOLDER;
    int i = 0;
    while (FullName[i])i++;
    int j = 0;
    while (name[j]) FullName[i++] = name[j++];
    FullName[i++] = '.';
    FullName[i++] = 't';
    FullName[i++] = 'x';
    FullName[i++] = 't';

    FILE* file = fopen(FullName, "r");
    if (!file)return false;

    while (Pre)ExchangeWith(Pre);
    DeleteGameTree();

    unsigned char P;
    B = (Board*)calloc(1, sizeof(Board));

    fscanf(file, "%c", &P);
    B->P[0].K = (King*)NewPiece(B, 1, P - 48, 8);
    B->P[1].K = (King*)NewPiece(B, -1, P + 8, 8);
    fscanf(file, "%c", &P);
    B->P[0].Q[0] = (Queen*)NewPiece(B, 1, P - 48, 9);
    B->P[1].Q[0] = (Queen*)NewPiece(B, -1, P + 8, 9);
    fscanf(file, "%c", &P);
    B->P[0].R[0] = (Rook*)NewPiece(B, 1, P - 48, 6);
    B->P[1].R[0] = (Rook*)NewPiece(B, -1, P + 8, 6);
    fscanf(file, "%c", &P);
    B->P[0].R[1] = (Rook*)NewPiece(B, 1, P - 48, 6);
    B->P[1].R[1] = (Rook*)NewPiece(B, -1, P + 8, 6);
    fscanf(file, "%c", &P);
    B->P[0].N[0] = (Knight*)NewPiece(B, 1, P - 48, 3);
    B->P[1].N[0] = (Knight*)NewPiece(B, -1, P + 8, 3);
    fscanf(file, "%c", &P);
    B->P[0].N[1] = (Knight*)NewPiece(B, 1, P - 48, 3);
    B->P[1].N[1] = (Knight*)NewPiece(B, -1, P + 8, 3);
    fscanf(file, "%c", &P);
    B->P[0].B[0] = (Bishop*)NewPiece(B, 1, P - 48, 4);
    B->P[1].B[0] = (Bishop*)NewPiece(B, -1, P + 8, 4);
    fscanf(file, "%c", &P);
    B->P[0].B[1] = (Bishop*)NewPiece(B, 1, P - 48, 4);
    B->P[1].B[1] = (Bishop*)NewPiece(B, -1, P + 8, 4);
    for (i = 0; i < 8; i++) {
        B->P[0].P[i] = (Pawn*)NewPiece(B, 1, 8 + i, 1);
        B->P[1].P[i] = (Pawn*)NewPiece(B, -1, 48 + i, 1);
    }
    Lines = (Game**)calloc(1, sizeof(void*));
    fscanf(file, "\n");
    while (fscanf(file, "%hhu ", &P) != EOF) {
        if (!P)GoBack();
        else NewMove(P - 1);
    }
    fclose(file);
    return true;
}

bool Game::MergeWithFile(char* name) {
    char FullName[100] = GAME_FILES_FOLDER;
    int i = 0;
    while (FullName[i])i++;
    int j = 0;
    while (name[j]) FullName[i++] = name[j++];
    FullName[i++] = '.';
    FullName[i++] = 't';
    FullName[i++] = 'x';
    FullName[i++] = 't';

    FILE* file = fopen(FullName, "r");
    if (!file)return false;

    unsigned char* m = (unsigned char*)calloc(1, 1000);
    int k = -1;
    while (Pre) {
        m[++k] = this->PreM;
        ExchangeWith(Pre);
    }

    char P;
    fscanf(file, "%c", &P);
    if (P - 48 != B->P[0].K->Pos)return false;
    fscanf(file, "%c", &P);
    if (P - 48 != B->P[0].Q[0]->Pos)return false;
    fscanf(file, "%c", &P);
    if (P - 48 != B->P[0].R[0]->Pos)return false;
    fscanf(file, "%c", &P);
    if (P - 48 != B->P[0].R[1]->Pos)return false;
    fscanf(file, "%c", &P);
    if (P - 48 != B->P[0].N[0]->Pos)return false;
    fscanf(file, "%c", &P);
    if (P - 48 != B->P[0].N[1]->Pos)return false;
    fscanf(file, "%c", &P);
    if (P - 48 != B->P[0].B[0]->Pos)return false;
    fscanf(file, "%c", &P);
    if (P - 48 != B->P[0].B[1]->Pos)return false;
    fscanf(file, "\n");

    while (fscanf(file, "%hhu ", &P) != EOF) {
        if (!P)GoBack();
        else NewMove(P - 1);
    }
    fclose(file);

    while (Pre)ExchangeWith(Pre);
    for (i = k; i >= 0; i--) NewMove(m[i]);
    return true;
}

//GAMING EXAMPLE FUNCTIONS

void Game::ConsoleInputGameExample(){
    char m[20];
    m[0] = 0;
    if(!B){
        system("cls");
        if (!S)m[0] = 1;
        else S = 0;
        Pre=0;
        int s = 0;
        printf("(UTILITZEU MILLOR PANTALLA COMPLETA)\nESCULL LA CONFIGURACIO DEL TAULER INICIAL\n\n\t1. STANDARD\n\t2. FISHER RANDOM\n");
        scanf("%i", &s);
        if (s == 2)B = FisherRandomBoard();
        else B = initialBoard();
        Lines=(Game**)calloc(1,sizeof(void*));
    }

    system("cls");
    fancySmanschyPrintBoard(B);
    
    if(!S)StringMoveList();

    if (m[0]) {
        printf("Per obtenir informacio sobre el funcionament de la app escriu i");
    }
    bool Draw = false;

    if (DrawByRepetition()) {
        B->DeleteAllMoves();
        Draw = true;
        printf("TAULES PER REPETICIO");
    }
    else if (!(B->LegalMoves())) {
        if (B->Check)printf("ESCAC I MAT");
        else printf("REI OFEGAT");
    }
    else if (!(B->SufficientMaterial())) {
        B->DeleteAllMoves();
        Draw = true;
        printf("TAULES PER MATERIAL INSUFICIENT");
    }
    else PrintCurrentLines(this);
    
    printf("\n   ");
    scanf("%s",m);

    int i=-1;
    if (!Draw) {
        while(S[++i]){
                int j=-1;
                while(S[i][++j]){
                    if(S[i][j]!=m[j])break;
                }
                if(S[i][j])continue;
                NewMove(i);
                return ConsoleInputGameExample();
            }
    }

    if ((m[0]=='r' || m[0]=='R') && !m[1])GoBack();

    if (m[0]=='l' || m[0]=='L'){
        if (!m[1])GoToLine(0);
        else {
            int L=0;
            i=1;
            while(m[i]){
                L=10*L;
                L+=m[i]-48;
                i++;
            }
            GoToLine(L-1);
        }
        
    }

    if ((m[0]=='m' || m[0]=='M') && (m[1]=='l' || m[1]=='L'))GoToLine(0);

    if (m[0] > 48 && m[0] < 58 && !m[1])GoToLine(m[0] - 49);

    if (m[0] == 48)return;

    if (m[0] == 'i' || m[0] == 'I' ) {
        printf("\n\nINFO TAB\n\n   Per fer moviments simplement s'escriu el moviment amb notacio d'escacs i s'executara, \n   si es escac no us oblideu de posar el \"+\" al final.\n\n   Aquest programa guardara tots els moviments que hagueu fet \n   per tant si voleu tornar al moviment anterior ho podeu fer escrivint R.\n\n   En cas que volgueu tornar a alguna de les linies que ja heu jugat podeu accedir-hi escrivint la lletra L \n   seguida del nombre de la linia en questio (es guardaran per l'ordre en que les heu introduit). \n\n   Per guardar la partida en la memoria per poder accedir-hi en un altre moment premeu S.\n\n   Per accedir a una partida que hagueu guardat anteriorment premeu O.\n\n   Per comencar una nova partida premeu N.\n\n   Per sortir del programa premeu E.\n\nAquest programa no preten ser un joc en si mateix, sino una demostracio del que pot fer la llibreria ChessInVS,\nespero en un futur no molt llunya implementar aquesta llibreria en un display mes agradable on a traves del ratoli\ni de forma molt mes intuitiva es pugui accedir a totes aquestes funcions, tambe tinc pensat implementar algun tipus\nde Chess Engine amb la que poder jugar o estudiar els moviments, ja sigui Stockfish o una creada per mi mateix.\nDe moment tenim aixo.\nPrem qualsevol tecla i enter per treure en menu d'informacio i comencar a jugar.");
        scanf("%s",m);
    }

    if ((m[0] == 'e' || m[0] == 'E') && !m[1])return;

    if ((m[0] == 'n' || m[0] == 'N') && !m[1]) {
        while (Pre)ExchangeWith(Pre);
        DeleteGameTree();
    }

    if ((m[0] == 's' || m[0] == 'S') && !m[1]) {
        char* name=(char*)calloc(1,20);
        printf("\n   ESCRIU EL NOM DE LA PARTIDA QUE VOLS GUARDAR   ");
        scanf("%s", name);
        GenerateTxtGameFile(name);
    }

    if ((m[0] == 'o' || m[0] == 'O') && !m[1]) {
        char* name = (char*)calloc(1, 20);
        printf("\n   ESCRIU EL NOM DE LA PARTIDA QUE VOLS OBRIR   ");
        scanf("%s", name);
        OpenTxtGameFile(name);
    }

    if ((m[0] == 'd' || m[0] == 'D') && (m[1] == 'l' || m[1] == 'L') && m[2]>48) {
        int L = 0;
        i = 2;
        while (m[i]) {
            L = 10 * L;
            L += m[i] - 48;
            i++;
        }
        DeleteLine(L - 1);
    }

    if ((m[0] == 'm' || m[0] == 'M') && !m[1]) {
        char* name = (char*)calloc(1, 20);
        printf("\n   ESCRIU EL NOM DE LA PARTIDA AMB LA QUE VOLS FUSIONAR AQUESTA   ");
        scanf("%s", name);
        MergeWithFile(name);
    }

    return ConsoleInputGameExample();
}
