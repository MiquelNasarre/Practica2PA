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
    void GenerateTxtGameFile(char* name);
    void OpenTxtGameFile(char* name);
    void DeleteLine(unsigned char l);
    bool DrawByRepetition();

    void ConsoleInputGameExample();

};
