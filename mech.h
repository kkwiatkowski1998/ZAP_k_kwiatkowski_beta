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
        int x, y;
        int wartosc_ruchu;
        int maksymalna_wartosc_ruchu;

        int rozmiar_planszy;
        int ilosc_symboli_linia;
        char **tablica, **tablica_pom;
        int zmienna_int;
        char zmienna_char;
        zawodnik gracz_pomocniczy;
        bool warunek = false;
public:
        bool gvsg, test = 0;
        zawodnik gracz1, gracz2;
        int suma = 0;
        int liczba_ruchow = 0;

    void wymiary_planszy();
    void ilosc_symboli();
    void nowa_plansza();
    void drukuj_plansze();

    void dane_graczy();

    void pelna_mechanika_gg();
    void rozgrywka_gg();
    void wspolrzedne_ruchu(zawodnik gracz);

    void pelna_mechanika_gvsk();
    void rozgrywka_gvsk();
    int wspolrzedne_ruchu_komputera(char gracz, int poziom);

    bool sprawdzenie(char **tablica, char znak);
    void wynik();

    void usuwanie_dynamicznych();
    void powtorka();

    void pelna_mechanika_test();
    void dane_testowe();
    void rozgrywka_test();
};
#endif // MECH_H
