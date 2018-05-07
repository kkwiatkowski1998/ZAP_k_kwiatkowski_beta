#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

class menu
{

private:
        char wybor;
        string nazwa;
        char symbol;
        ifstream plik;
        string napis;

public:

        int wartosc_gracza;
        string numer; //gracza

    void okno_powitalne();
    void start_exit();
    void gracz_komputer();
    void gracz_vs_gracz();
    void gracz_vs_komputer();
    void kolejna_runda();
    void podaj_wymiary_planszy(int &rozmiar_planszy);
    void zwyciestwo(struct zawodnik gracz);
    void remis();
    string nick(string numer);
    int wartosc(string numer);
    char znak(string numer);
    void test();


    void podaj_ilosc_symboli(int &ilosc_symboli, int &rozmiar_planszy);
};

#endif // MENU_H
