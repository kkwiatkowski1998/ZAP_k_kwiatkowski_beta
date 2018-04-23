#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>

#include <mech.h>
#include <menu.h>
#include <plansza.h>



using namespace std;

menu MENU;


// TABLICA;
void mech::wymiary_planszy()
{
    system("cls");
    MENU.okno_powitalne();
    MENU.podaj_wymiary_planszy(rozmiar_planszy);
}

void mech::ilosc_symboli()
{
    system("cls");
    MENU.okno_powitalne();
    MENU.podaj_ilosc_symboli(ilosc_symboli_linia, rozmiar_planszy);
}

void mech::nowa_plansza()
{
    tablica = new char *[rozmiar_planszy];
    for (int i = 0; i < rozmiar_planszy; i++)
        tablica[i] = new char [rozmiar_planszy];

    for (int i = 0; i < rozmiar_planszy; i++)
    {
        for (int j = 0; j < rozmiar_planszy; j++)
        {
            tablica[i][j]= '_';
        }
    }
}

void mech::drukuj_plansze()
{
    for (int i = 0; i < mech::rozmiar_planszy; i++)
    {
        for (int j = 0; j < mech::rozmiar_planszy; j++)
        {
            cout << mech::tablica[i][j] << '\t';
        }
        cout << endl << endl;
    }
}

// GRACZE

void mech::dane_graczy()
{
    gracz1.nick = MENU.nick("pierwszy");
    if(gvsg == true)
    {
        gracz2.nick = MENU.nick("drugi");
    }
    else if(gvsg == false)
    {
        gracz2.nick = "KOMPUTER";
    }


    zmienna_char = MENU.znak(gracz1.nick);
    switch (zmienna_char)
    {
    case 'O':
        gracz1.znak = 'O';
        gracz2.znak = 'X';
        break;
    case 'X':
        gracz1.znak = 'X';
        gracz2.znak = 'O';
        break;
    }

    zmienna_int = MENU.wartosc(gracz1.nick);
    switch (zmienna_int)
    {
    case 1:
        gracz1.wartosc = 1;
        gracz2.wartosc = 0;
        break;
    case 0:
        gracz1.wartosc = 0;
        gracz2.wartosc = 1;
    default:
        break;
    }
}

//GRACZ VS GRACZ

void mech::pelna_mechanika_gg()
{
    mech::wymiary_planszy();
    mech::ilosc_symboli();
    mech::nowa_plansza();
    mech::rozgrywka_gg(gracz1, gracz2, rozmiar_planszy, tablica);

}
void mech::dane_testowe()
{
    gracz1.wartosc = 1;
    gracz2.wartosc = 0;
    gracz1.znak = 'O';
    gracz2.znak = 'X';
    gracz1.nick = "KOLKO";
    gracz2.nick = "KRZYZYK";
    rozmiar_planszy = 3;
    ilosc_symboli_linia = 3;
}
void mech::pelna_mechanika_test()
{
    mech::nowa_plansza();
    mech::rozgrywka_test();
}

void mech::rozgrywka_test()
{
    srand(time(0));
    for(int i = 0; i < rozmiar_planszy*rozmiar_planszy; i++)
    {
        system("cls");

        MENU.okno_powitalne();

        if(gracz1.wartosc == 1)
        {
            zaczynajacy = gracz1;
        }
        else if(gracz1.wartosc == 0)
        {
            zaczynajacy = gracz2;
        }

        drukuj_plansze();
        x = 1+rand()%(rozmiar_planszy);
        y = 1+rand()%(rozmiar_planszy);
        while(tablica[x-1][y-1]!=('_'))
        {
            x = 1+rand()%(rozmiar_planszy-1);
            y = 1+rand()%(rozmiar_planszy-1);
        }
        tablica[x-1][y-1] = zaczynajacy.znak;

        gracz_pomocniczy.wartosc = gracz1.wartosc;
        gracz1.wartosc = gracz2.wartosc;
        gracz2.wartosc = gracz_pomocniczy.wartosc;

        suma = mech::sprawdzenie(tablica);
        wynik();
    }
}

void mech::rozgrywka_gg(zawodnik gracz1, zawodnik gracz2, int rozmiar_planszy, char **&tablica)
{
    for(int i = 0; i < rozmiar_planszy*rozmiar_planszy; i++)
    {
        system("cls");

        MENU.okno_powitalne();

        if(gracz1.wartosc == 1)
        {
            zaczynajacy = gracz1;
        }
        else if(gracz1.wartosc == 0)
        {
            zaczynajacy = gracz2;
        }

        drukuj_plansze();

        cout << zaczynajacy.nick << ", twoj ruch "<< zaczynajacy.znak << endl;
        cout << liczba_ruchow << endl;

        mech::wspolrzedne_ruchu(x, y, rozmiar_planszy);
        while(tablica[x-1][y-1]!=('_'))
        {
            cout << "Pole zajete!" << endl;
            mech::wspolrzedne_ruchu(x, y, rozmiar_planszy);
        }
        tablica[x-1][y-1] = zaczynajacy.znak;

        gracz_pomocniczy.wartosc = gracz1.wartosc;
        gracz1.wartosc = gracz2.wartosc;
        gracz2.wartosc = gracz_pomocniczy.wartosc;

        suma = mech::sprawdzenie(tablica);
        wynik();
    }
}

// RUCH

void mech::powtorka()
{
    mech::nowa_plansza();
    if(gracz1.wartosc == 0)
    {
        gracz1.wartosc = 1;
        gracz2.wartosc = 0;
    }
    else if(gracz1.wartosc == 1)
    {
        gracz1.wartosc = 0;
        gracz2.wartosc = 1;
    }


    if(gvsg == true)
    {
        mech::rozgrywka_gg(gracz1, gracz2, rozmiar_planszy, tablica);
    }
    if(gvsg == false)
    {
        mech::rozgrywka_gvsk();
    }
}

void mech::wspolrzedne_ruchu(int &x, int &y, int rozmiar_planszy)
{
    cout << "Podaj wspolrzedna x " ;
    cin >> x;
    while(x<1 || x>rozmiar_planszy)
    {
        cout << "Podaj wspolrzedna x " ;
        cin >> x;
    }

    cout << "Podaj wspolrzedna y " ;
    cin >> y;
    while(y<1 || y>rozmiar_planszy)
    {
        cout << "Podaj wspolrzedna y " ;
        cin >> y;
    }
}

void mech::analiza_ruchu()
{

    for(int i = 0; i < rozmiar_planszy; i++)
    {
        for (int j = 0; j < rozmiar_planszy; j++)
        {
            if(tablica_pom[i][j] == '_')
            {
                tablica_pom[i][j] = gracz_pomocniczy_2.znak;
                suma = mech::sprawdzenie(tablica_pom);

                if(abs(suma) == ilosc_symboli_linia)
                {
                    x = i;
                    y = j;
                    warunek = true;
                }
                tablica_pom[i][j] = '_';
            }
        }
        if(warunek == true)
        {
            break;
        }
    }
}

void mech::wyp_tab_pom()
{
    for(int i = 0; i < rozmiar_planszy; i++)
    {
        for (int j = 0; j < rozmiar_planszy; j++)
        {
            tablica_pom[i][j] = tablica[i][j];
        }
    }
}

void mech::wspolrzedne_ruchu_komputera()
{
    mech::wyp_tab_pom();

    gracz_pomocniczy_2 = gracz2;
    mech::analiza_ruchu();
    if(warunek != true)
    {
        gracz_pomocniczy_2 = gracz1;
        mech::analiza_ruchu();
    }
    if(warunek != true)
    {
        x = rand()%rozmiar_planszy;
        y = rand()%rozmiar_planszy;
    }
    warunek = false;
}

// G VS K

void mech::pelna_mechanika_gvsk()
{
    mech::wymiary_planszy();
    mech::ilosc_symboli();
    mech::nowa_plansza();
    mech::rozgrywka_gvsk();
}

void mech::rozgrywka_gvsk()
{
    liczba_ruchow = 0;

    tablica_pom = new char *[rozmiar_planszy];
    for (int i = 0; i < rozmiar_planszy; i++)
        tablica_pom[i] = new char [rozmiar_planszy];

    for(int i = 0; i < rozmiar_planszy*rozmiar_planszy; i++)
    {
        system("cls");

        MENU.okno_powitalne();
        drukuj_plansze();

        if(gracz1.wartosc == 1)
        {
            cout << gracz1.nick << ", twoj ruch "<< gracz1.znak << endl;
            cout << liczba_ruchow << endl;

            mech::wspolrzedne_ruchu(x, y, rozmiar_planszy);
            while(tablica[x-1][y-1]!=('_'))
            {
                cout << "Pole zajete!" << endl;
                mech::wspolrzedne_ruchu(x, y, rozmiar_planszy);
            }
            tablica[x-1][y-1] = gracz1.znak;
        }
        else if(gracz1.wartosc == 0)
        {
            mech::wspolrzedne_ruchu_komputera();
            while(tablica[x][y] != ('_'))
            {
                mech::wspolrzedne_ruchu_komputera();
            }
            tablica[x][y] = gracz2.znak;
        }

        gracz_pomocniczy.wartosc = gracz1.wartosc;
        gracz1.wartosc = gracz2.wartosc;
        gracz2.wartosc = gracz_pomocniczy.wartosc;

        suma = mech::sprawdzenie(tablica);
        liczba_ruchow++;
        wynik();
    }
}



// SPRAWDZENIA



int mech::sprawdzenie(char **tablica)
{
    suma = 0;

    for(int i = 0; i < rozmiar_planszy; i++)
    {
        for(int j = 0; j < rozmiar_planszy-1; j++)
        {
            if(tablica[i][j]=='X')
            {
                if(suma<1)
                {
                    suma = 1;
                }
                if(tablica[i][j+1] == ('X'))
                {
                    suma++;
                }
                else
                {
                    suma = 0;
                }
            }
            else if(tablica[i][j]=='O')
            {
                if(suma>(-1))
                {
                    suma = -1;
                }
                if(tablica[i][j+1] == ('O'))
                {
                    suma--;
                }
                else
                {
                    suma = 0;
                }
            }
            if(abs(suma)== ilosc_symboli_linia)
            {
                return suma;
            }
        }
        suma = 0;

        for(int j = 0; j < rozmiar_planszy-1; j++)
        {
            if(tablica[j][i]=='X')
            {
                if(suma<1)
                {
                    suma = 1;
                }
                if(tablica[j+1][i] == 'X')
                {
                    suma++;
                }
                else
                {
                    suma = 0;
                }
            }
            else if(tablica[j][i]=='O')
            {
                if(suma > -1)
                {
                    suma = -1;
                }
                if(tablica[j+1][i] == 'O')
                {
                    suma--;
                }
                else
                {
                    suma = 0;
                }
            }
            if(abs(suma)== ilosc_symboli_linia)
            {
                return suma;
            }
        }
        suma = 0;
    }

    for(int a = ilosc_symboli_linia-rozmiar_planszy; a<=rozmiar_planszy-ilosc_symboli_linia; a++)
    {
        for(int i = 0; i < rozmiar_planszy-1; i++)
        {
            if(a+i>=0 && a+i<rozmiar_planszy)
            {
                if(tablica[a+i][i] == 'X')
                {
                    if(suma < 1)
                    {
                        suma = 1;
                    }
                    if(tablica[a+i+1][i+1] == 'X')
                    {
                        suma++;
                    }
                    else
                    {
                        suma = 0;
                    }
                }
                else if(tablica[a+i][i] == 'O')
                {
                    if(suma > -1)
                    {
                        suma = -1;
                    }
                    if(tablica[a+i+1][i+1] == 'O')
                    {
                        suma--;
                    }
                    else
                    {
                        suma = 0;
                    }
                }
                if(abs(suma)== ilosc_symboli_linia)
                {
                    return suma;
                }
            }
        }
        suma = 0;
    }


    for(int a = ilosc_symboli_linia-rozmiar_planszy; a<=rozmiar_planszy-ilosc_symboli_linia; a++)
    {
        for(int i = 0; i < rozmiar_planszy; i++)
        {
            if(rozmiar_planszy-2-i+a>=0 && rozmiar_planszy-1-i+a<rozmiar_planszy)
            {
                if(tablica[rozmiar_planszy-1-i+a][i] == 'X')
                {
                    if(suma < 1)
                    {
                        suma = 1;
                    }
                    if(tablica[rozmiar_planszy-2-i+a][i+1] == 'X')
                    {
                        suma++;
                        if(abs(suma)== ilosc_symboli_linia)
                        {
                            return suma;
                        }
                    }
                    else
                    {
                        suma = 0;
                    }
                }
                else if(tablica[rozmiar_planszy-1-i+a][i] == 'O')
                {
                    if(suma > -1)
                    {
                        suma = -1;
                    }
                    if(tablica[rozmiar_planszy-2-i+a][i+1] == 'O')
                    {
                        suma--;
                        if(abs(suma)== ilosc_symboli_linia)
                        {
                            return suma;
                        }
                    }
                    else
                    {
                        suma = 0;
                    }
                }

            }
        }
        suma = 0;
    }

}
void mech::wynik()
{
    if(liczba_ruchow == (rozmiar_planszy)*(rozmiar_planszy))
    {
        MENU.remis();
    }

    if(suma == ilosc_symboli_linia)
    {
        if(gracz1.znak == 'X')
        {
            MENU.zwyciestwo(gracz1);
        }
        else if(gracz2.znak == 'X')
        {
            MENU.zwyciestwo(gracz2);
        }
    }
    else if(suma == -(ilosc_symboli_linia))
    {
        if(gracz1.znak == 'O')
        {
            MENU.zwyciestwo(gracz1);
        }
        else if(gracz2.znak == 'O')
        {
            MENU.zwyciestwo(gracz2);
        }
    }
}



