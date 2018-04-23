#ifndef MECH_H
#define MECH_H
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

struct zawodnik
{
    string nick;
    bool wartosc;
    char znak;
};



class mech
{
private:    
        int x, y, pom_x, pom_y;
        int rozmiar_planszy;
        int ilosc_symboli_linia;
        char **tablica, **tablica_pom;
        int zmienna_int;
        char zmienna_char;
        zawodnik gracz_pomocniczy, gracz_pomocniczy_2, zaczynajacy;
        bool warunek = false, warunek_tpom = false;
public:
        bool gvsg;
        zawodnik gracz1, gracz2;
        int suma = 0;
        int liczba_ruchow = 0;
        int wynik_sprawdzenia;

    void wymiary_planszy();
    void ilosc_symboli();
    void nowa_plansza();
    void drukuj_plansze();
    void pelna_mechanika_gg();
    void pelna_mechanika_gvsk();
    void dane_graczy();
    void analiza_ruchu();
    void wyp_tab_pom();
    void rozgrywka_gg(zawodnik gracz1, zawodnik gracz2, int rozmiar_planszy, char **&tablica);
    void rozgrywka_gvsk();
    void wspolrzedne_ruchu(int &x, int &y, int rozmiar_planszy);
    void wspolrzedne_ruchu_komputera();
    int sprawdzenie(char **tablica);
    int spr_kolumny();
    int spr_wiersze();
    int spr_przekatna_1();
    int spr_przekatna_2();
    void wynik();
    void zwrocenie_sumy();
    void powtorka();

    void pelna_mechanika_test();
    void dane_testowe();
    void rozgrywka_test();

};
#endif // MECH_H
