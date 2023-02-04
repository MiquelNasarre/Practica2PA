#pragma once

class GAME_API Game{
public:
    unsigned char PreM;
    Game* Pre;
    Game** Lines;
    Board* B=0;
    char** S=0;

    void NewMove(unsigned char m);
    void GoBack();
    void GoToLine(unsigned char i);
    void ExchangeWith(Game* G);
    void StringMoveList();
    void DeleteGameTree();
    void DeleteLine(unsigned char l);
    bool DrawByRepetition();

    bool GenerateTxtGameFile(char* name);
    bool OpenTxtGameFile(char* name);
    bool MergeWithFile(char* name);
    

    void ConsoleInputGameExample();

};
