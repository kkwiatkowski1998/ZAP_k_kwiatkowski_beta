#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>

#include <mech.h>
#include <menu.h>
#include <plansza.h>

using namespace std;



using namespace std;

mech MECH;

// MENU PODSTAWOWE

void menu::okno_powitalne()
{
    cout << "Kolko i Krzyzyk v1.1"  << endl;
}

void menu::start_exit()
{
    menu::okno_powitalne();

    cout << "WERSJA 2, dodanie wyboru ilosci symboli w linii do zwyciestwa, cofania ruchu oraz gracz vs komputer" << endl;

    cout << "Nowa gra,  wybierz 1" << endl << "Wyjscie, wybierz 0"  << endl;
    cin >> wybor;
    switch (wybor)
    {
    case '1':
        menu::gracz_komputer();
        break;
    case '0':
        exit(0);
        break;
    case 't':
       // menu::test();
        break;
    default:
        system("cls");
        menu::okno_powitalne();
        menu::start_exit();
    }
}

void menu::gracz_komputer()
{
    system("cls");
    menu::okno_powitalne();
    cout << "Dwoch graczy, wybierz 1" << endl << "Jeden gracz, wybierz 0" << endl;
    cin >> wybor;
    switch (wybor)
    {
    case '1':
        menu::gracz_vs_gracz();
        break;
    case '0':
        menu::gracz_vs_komputer();
        break;

    default:
        system("cls");
        menu::okno_powitalne();
        menu::gracz_komputer();
    }
}

void menu::gracz_vs_gracz()
{
    MECH.gvsg = 1;
    MECH.dane_graczy();
    MECH.pelna_mechanika_gg();
}

void menu::gracz_vs_komputer()
{
    MECH.gvsg = 0;
    MECH.dane_graczy();
    MECH.pelna_mechanika_gvsk();
}

void menu::test()
{
    MECH.dane_testowe();
    MECH.pelna_mechanika_test();
}

// PARAMETRY GRACZY I PLANSZY

void menu::podaj_wymiary_planszy(int &rozmiar_planszy)
{
    cout << "Podaj wymiary planszy" << endl;
    cin >> rozmiar_planszy;
    while(rozmiar_planszy<3)
    {
        menu::podaj_wymiary_planszy(rozmiar_planszy);
    }
}

void menu::podaj_ilosc_symboli(int &ilosc_symboli_linia, int &rozmiar_planszy)
{
    cout << "Podaj ilosc symboli w rzedzie dajacy zwyciestwo" <<endl;
    cin >> ilosc_symboli_linia;
    while(ilosc_symboli_linia < 1||ilosc_symboli_linia > rozmiar_planszy)
    {
        menu::podaj_ilosc_symboli(ilosc_symboli_linia, rozmiar_planszy);
    }
}

string menu::nick(string numer)
{
    system("cls");
    menu::okno_powitalne();

    cout << "Gracz " << numer << " podaj nick" << endl;
    cin >> nazwa;
    return nazwa;
}

char menu::znak(string numer)
{
    srand (time(0));

    system("cls");
    menu::okno_powitalne();

    cout << numer << ", jezeli wybierasz O, wcisnij 1" << endl;
    cout << "Jezeli wybierasz X, wcisnij 2" << endl;
    cout << "Losuj, wybierz 0" << endl;
    cin >> wybor;
    switch (wybor)
    {
    case '1':
        symbol = 'O';
        return symbol;
    case '2':
        symbol = 'X';
        return symbol;
        break;
    case '0':
        wartosc_gracza = rand()%2;
        if(wartosc_gracza == 1)
        {
            symbol = 'O';
        }
        if(wartosc_gracza == 0)
        {
            symbol = 'X';
        }
        return symbol;
        break;
    default:
        menu::znak(numer);
        break;
    }
}

int menu::wartosc(string numer)
{
    system ("cls");
    menu::okno_powitalne();

    srand(time(0));

    cout << numer << ", jezeli chcesz zaczac rozgrywke, wybierz 1" << endl;
    cout << "Jezeli chcesz aby przeciwnik rozpoczal, wybierz 2" << endl;
    cout << "Losowanie, wybierz 0" << endl;

    cin >> wybor;
    switch (wybor)
    {
    case '1':
        wartosc_gracza = 1;
        return wartosc_gracza;
    case'2':
        wartosc_gracza = 0;
        return wartosc_gracza;
        break;
    case'0':
        wartosc_gracza = rand()%2;
        return wartosc_gracza;
        break;
    default:
        menu::wartosc(numer);
        break;
    }
}

// PO ZAKONCZENIU

void menu::kolejna_runda()
{
    cout << "Rewanz???" << endl <<"Jezeli tak, wybierz 1" << endl << "Jezeli chcesz wyjsc, wybierz 0" << endl;
    cin >> wybor;
    switch (wybor)
    {
    case '1':
        MECH.powtorka();
        break;
    case '0':
        exit(0);
        break;
    default:
        system("cls");
        menu::kolejna_runda();
    }
}

void menu::zwyciestwo(zawodnik gracz)
{
    system("cls");
    menu::okno_powitalne();
    MECH.drukuj_plansze();
    cout << "Wygral " << gracz.nick <<endl << endl;
    MECH.liczba_ruchow = 0;
    menu::kolejna_runda();
}

void menu::remis()
{
    system("cls");
    menu::okno_powitalne();
    MECH.drukuj_plansze();
    cout << "REMIS " << endl << endl;
    MECH.liczba_ruchow = 0;
    menu::kolejna_runda();
}


