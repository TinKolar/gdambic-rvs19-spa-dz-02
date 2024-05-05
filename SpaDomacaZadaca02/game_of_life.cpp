#include "game_of_life.h"
#include <algorithm>

bool game_of_life::slucajna_vrijednost()
{

    int n = rand() % 4;
    bool live_or_dead = n;
    if (live_or_dead) {
        return false;
    }
    else {
        return true;
    }
}

bool game_of_life::celija_zauzeta(int i, int j){

    if (_generacija[i][j])
        return true;
    return false;
}

int game_of_life::broj_zivih_celija_susjeda(int i, int j)
{
    int n = 0;
    if (celija_zauzeta(i - 1, j - 1))
        n++;
    if (celija_zauzeta(i - 1, j))
        n++;
    if (celija_zauzeta(i - 1, j + 1))
        n++;
    if (celija_zauzeta(i, j - 1))
        n++;
    if (celija_zauzeta(i, j + 1))
        n++;
    if (celija_zauzeta(i + 1, j - 1))
        n++;
    if (celija_zauzeta(i + 1, j))
        n++;
    if (celija_zauzeta(i + 1, j + 1))
        n++;


    return n;
}

void game_of_life::next_gen_is_now_gen()
{
    for (int i = 0; i < REDAKA; i++) {
        for (int j = 0; j < STUPACA; j++) {
            _generacija[i][j] = _sljedeca_generacija[i][j];
        }
    }
}

game_of_life::game_of_life()
{
    for (int i = 0; i < REDAKA; i++) {
        for (int j = 0; j < STUPACA; j++) {
            _generacija[i][j] = slucajna_vrijednost();
        }
    }
}

void game_of_life::sljedeca_generacija()
{
    for (int i = 0; i < REDAKA; i++) {
        for (int j = 0; j < STUPACA; j++) {

            //ako je ta celija ziva onda gledamo dali ce umrijeti: 2/3 ostaje ziva
            if (celija_zauzeta(i, j)) {
                if (broj_zivih_celija_susjeda(i, j) > 1 && broj_zivih_celija_susjeda(i, j) < 4)
                    _sljedeca_generacija[i][j] = true;
                else
                    _sljedeca_generacija[i][j] = false;
            }

            //ako nije ziva onda gledamo dali ce ozivjeti: ozivljava ako ima tocno 3 susjeda ziva
            else {
                if (broj_zivih_celija_susjeda(i, j) == 3)
                    _sljedeca_generacija[i][j] = true;
                else
                    _sljedeca_generacija[i][j] = false;
            }
        }
    }
    next_gen_is_now_gen();
}

void game_of_life::iscrtaj()
{
    for (int i = 0; i < REDAKA; i++) {
        for (int j = 0; j < STUPACA; j++) {
            if (_generacija[i][j]) {
                cout << "O";
            }
            else {
                cout << " ";
            }
        }
        cout << endl;
    }
}
