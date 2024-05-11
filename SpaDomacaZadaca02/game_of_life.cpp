#include "game_of_life.h"
#include <algorithm>
#include<sstream>

bool game_of_life::slucajna_vrijednost()
{
    bool live_or_dead = rand() % 4;
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
    for (int x = -1; x < 2; x++) {
        for (int y = -1; y < 2; y++) {

            if (x == 0 and y == 0) {
                continue;
            }
            if ((i + x) < 0) {
                continue;
            }
            if ((j + y) < 0)
                continue;
            if ((i + x) >= REDAKA)
                continue;
            if ((j + y) >= STUPACA)
                continue;
            if (celija_zauzeta(i + x, j + y)) {
                n++;

                red_next[i][j] += red_now[i + x][j + y];
                green_next[i][j] += green_now[i + x][j + y];
                blue_next[i][j] += blue_now[i + x][j + y];
            }
        }
    }
    return n;
}

void game_of_life::next_gen_is_now_gen(int mode)//kopiranje next_gen u gen
{
    for (int i = 0; i < REDAKA; i++) {
        for (int j = 0; j < STUPACA; j++) {

            //life
            _generacija[i][j] = _sljedeca_generacija[i][j];

            if (_generacija[i][j]) {
                //boje
                red_now[i][j] = red_next[i][j];
                green_now[i][j] = green_next[i][j];
                blue_now[i][j] = blue_next[i][j];

                //resetiraj countere ako je ta celija ziva
                red_next[i][j] = 0;
                green_next[i][j] = 0;
                blue_next[i][j] = 0;
            }
            else {
                red_next[i][j] = 0;
                green_next[i][j] = 0;
                blue_next[i][j] = 0;
            }

        }
    }

    if (mode == 1) {
        count_alive();
    }
}

void game_of_life::random_initialize_grid(int mode)
{

    int randomR ;
    int randomG ;
    int randomB ;
    int randomRd;
    int randomGd;
    int randomBd;

    for (int i = 0; i < REDAKA; i++) {
        for (int j = 0; j < STUPACA; j++) {
            _generacija[i][j] = slucajna_vrijednost();

            //postavi next boje sve na 0;
            red_next[i][j] = 0;
            green_next[i][j] = 0;
            blue_next[i][j] = 0;

            //postavi trenutne boje//

            //borba dviju boja
            if (mode== 1) {
                if (rand() % 2) {
                    red_now[i][j] = 255;
                    green_now[i][j] = 0;
                    blue_now[i][j] = 0;
                }
                else {
                    red_now[i][j] = 0;
                    green_now[i][j] = 0;
                    blue_now[i][j] = 255;
                }
            }

            //3 boje sa efektom da nisu krajnje vrijednosti boja
            if (mode == 3) {
                int random = rand() % 3;
                if (random == 0) {
                    red_now[i][j] = rand() % 156 +100;
                }
                else if (random == 1) {
                    green_now[i][j] = rand() % 156 + 100;
                }
                else {
                    blue_now[i][j] = rand() % 156 + 100;
                }
            }

            //3 boje // full red or fullgreen or full blue
            if (mode == 4) {
                int random;
                random= rand() % 3;
                if (random == 0) {
                    red_now[i][j] = 255;
                }
                else if (random == 1) {
                    green_now[i][j] =  255;
                }
                else {
                    blue_now[i][j] = 255;
                }
            }

            //radnom po gridovima
           /* if (mode == 5) {
                
                if ((i==0 && j==0) || ((i==REDAKA/2) && j==0)) {
                    randomR = rand() % 256;
                    randomG = rand() % 256;
                    randomB = rand() % 256;
                    randomRd = rand() % 256;
                    randomGd = rand() % 256;
                    randomBd = rand() % 256;
                }
                if (j > STUPACA / 2) {
                    red_now[i][j] = randomRd;
                    green_now[i][j] = randomGd;
                    blue_now[i][j] = randomBd;
                  }
                else {
                    red_now[i][j] = randomR;
                    green_now[i][j] = randomG;
                    blue_now[i][j] = randomB;
                }
            }*/

            //trecine vodoravno po bojama aka croatian mode
            if (mode == 2) {
                if (i < REDAKA / 3) {
                    red_now[i][j] = 255;
                    green_now[i][j] = 0;
                    blue_now[i][j] = 0;
                }
                else if (i < 2 * REDAKA / 3) {
                    red_now[i][j] = 255;
                    green_now[i][j] = 255;
                    blue_now[i][j] = 255;
                }
                else {
                    red_now[i][j] = 0;
                    green_now[i][j] = 0;
                    blue_now[i][j] = 255;
                }
            }

        }
    }
}

void game_of_life::croatian_flag_mode()
{
    int checker;
    bool crvene = true;

    int i_start = 20;
    int j_start = 34;

    int istaknutost = 3;
    int kockice_size = 5;

    //sahovnica
    for (int i = i_start; i < (i_start+5*kockice_size); i++) {
        if (i < i_start+kockice_size*1) {
            crvene = true;
            checker = kockice_size;
        }
        else if (i < i_start + kockice_size * 2) {
            crvene = false;
            checker = 0;
        }
        else if (i < i_start + kockice_size * 3) {
            crvene = true;
            checker = kockice_size;
        }
        else if (i < i_start + kockice_size * 4) {
            crvene = false;
            checker = 0;
        }
        else {
            crvene = true;
            checker = kockice_size;
        }
        for (int j = j_start; j < j_start+5*kockice_size; j++) {

            if(rand() % istaknutost>0)
            _generacija[i][j] = true;

            if (checker > 0 && crvene) {
                checker--;
                red_now[i][j] = 255;
                green_now[i][j] = 0;
                blue_now[i][j] = 0;
            }
            if(checker==0 && crvene) {
                crvene = false;
                continue;
            }
            if (checker < kockice_size && !crvene) {
                checker++;
                red_now[i][j] = 255;
                green_now[i][j] = 255;
                blue_now[i][j] = 255;
            }
            if (checker == kockice_size && !crvene) {
                crvene = true;
            }

        }
    }

    //rijesavanje rubova dolje
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < i; j++) {
            _generacija[40 + i][34 + j] = false;
            _generacija[40 + i][58 - j] = false;

        }
    }

    //kruna
    for (int i = 13; i < 20; i++) {
        for (int j = j_start; j < j_start + 25; j++) {


            if (i < 18) {
                if ((j - 1) % 5 == 0) {
                    _generacija[i][j] = true;
                }
                if ((j % 5 == 0 || (j-2)%5==0)  && i>13) {
                    _generacija[i][j] = true;
                }
                if(((j+1)%5==0||(j+2)%5==0) && i>14){
                    _generacija[i][j] = true;
                }
            }
            else {
                _generacija[i][j] = true;
            }
            if (j < 39) {
                red_now[i][j] = 55;
                green_now[i][j] = 198;
                blue_now[i][j] = 255;
            }
            else if (j < 44) {
                red_now[i][j] = 0;
                green_now[i][j] = 0;
                blue_now[i][j] = 225;
            }
            else if (j < 49) {
                red_now[i][j] = 55;
                green_now[i][j] = 198;
                blue_now[i][j] = 255;
            }
            else if (j < 54) {
                red_now[i][j] = 0;
                green_now[i][j] = 0;
                blue_now[i][j] = 225;
            }
            else if (j < 59) {
                red_now[i][j] = 55;
                green_now[i][j] = 198;
                blue_now[i][j] = 255;
            }

            if (rand() % istaknutost > 0)
                _generacija[i][j] = false;
        }
    }

}

void game_of_life::draw_celija(int i, int j)
{
    int offset_x = 150;
    int offset_y = 100;

    celija.setSize(sf::Vector2f(csd, csd));
    celija.setPosition(sf::Vector2f((j * csd) + offset_x, (i * csd) + offset_y));
    celija.setFillColor(sf::Color(red_now[i][j], green_now[i][j], blue_now[i][j]));

    ekran->draw(celija);
}


/// ///////////////////////////////////////Public//////////////////////////////////////////


int game_of_life::mix_boja(int zbroj, int n)
{
    return zbroj / n;
}

void game_of_life::count_alive()
{
    for (int i = 0; i < REDAKA; i++) {
        for (int j = 0; j < STUPACA; j++) {
            if (red_now[i][j] > blue_now[i][j] && _generacija[i][j]==true) {
                red_counter++;
            }
            else if (blue_now[i][j]>red_now[i][j] && _generacija[i][j] == true) {
                blue_counter++;
            }
        }
    }
   
}

void game_of_life::background_iscrtaj(int mode)
{

    sf::Color background_color;

    if (mode == 2) {
        background_color=sf::Color(149, 223, 255);
    }
    else if (mode == 1) {
        background_color = sf::Color(30, 30, 30);//40,60,90
    }
    else {
        background_color = sf::Color(75, 75, 75);

    }
    

    //draw background
    background.setSize(sf::Vector2f(1200, 800));
    background.setFillColor(background_color);
    background.setPosition(sf::Vector2f(0, 0));
    ekran->draw(background);

    //uspravne linije okvira
    background.setSize(sf::Vector2f(4, 608));
    background.setFillColor(sf::Color(0, 0, 0));
    background.setPosition(sf::Vector2f(146, 96));
    ekran->draw(background);

    background.setPosition(sf::Vector2f(1050, 96));
    ekran->draw(background);

    //vodoravne linije okvira
    background.setSize(sf::Vector2f(904, 4));
    background.setFillColor(sf::Color(0, 0, 0));
    background.setPosition(sf::Vector2f(146, 96));
    ekran->draw(background);

    background.setSize(sf::Vector2f(904, 4));
    background.setFillColor(sf::Color(0, 0, 0));
    background.setPosition(sf::Vector2f(146, 700));
    ekran->draw(background);

}

void game_of_life::counters_draw()
{
    sf::Text red, blue,desc;

    sf::Font font;
    if (!font.loadFromFile("Light Stories.ttf"))
    {
        // error...
    }

    desc.setFillColor(sf::Color(255, 50, 255));

    stringstream ss,ss1;
    ss <<"RED_ COUNTER\n\t\t" << red_counter;
    string temp=ss.str();
    red.setString(temp);
    temp = "";
    ss1 << "BLUE COUNTER\n\t\t" << blue_counter;
    temp = ss1.str();
    blue.setString(temp);

    desc.setString("RED COUNTER se povecava ako ime vise nijanse crvene nego plave\nBLUE COUNTER se povecava ako ima vise nijane plave nego crvene");

    red.setPosition(sf::Vector2f(350, 20));
    blue.setPosition(sf::Vector2f(700, 20));
    desc.setPosition(sf::Vector2f(150, 720));

    // set the character size
    red.setCharacterSize(28); // in pixels, not points!
    blue.setCharacterSize(28); // in pixels, not points!
    desc.setCharacterSize(28);


    // set the color
    red.setFillColor(sf::Color::Red);
    blue.setFillColor(sf::Color(0,150,255));
    red.setFont(font );
    blue.setFont(font);
    desc.setFont(font);


    ekran->draw(red);
    ekran->draw(blue);
    ekran->draw(desc);


    cout << "RED: " << red_counter << endl;
    cout << "BLUE:" << blue_counter << endl;

    red_counter = 0;
    blue_counter = 0;
}


game_of_life::game_of_life(sf::RenderWindow* window, int mode) :ekran(window)//konstruktor koj odma stvara "svijet"
{
    random_initialize_grid(mode);

    //croatia mode grb hardcoded
    if (mode == 2) {
        croatian_flag_mode();
        mode_counter = mode * 20;
    }
}

void game_of_life::sljedeca_generacija(int mode)
{
    for (int i = 0; i < REDAKA; i++) {
        for (int j = 0; j < STUPACA; j++) {
            int n = broj_zivih_celija_susjeda(i, j);
            //ako je ta celija ziva onda gledamo dali ce umrijeti: 2/3 ostaje ziva
            if (celija_zauzeta(i, j)) {
                if (n > 1 && n < 4) {
                    _sljedeca_generacija[i][j] = true;
                    //red next izmiksamo tako da dobijemo finalnu boju
                    red_next[i][j] = mix_boja(red_next[i][j], n);
                    green_next[i][j] = mix_boja(green_next[i][j], n);
                    blue_next[i][j] = mix_boja(blue_next[i][j], n);
                }
                else {
                    _sljedeca_generacija[i][j] = false;
                }
            }

            //ako nije ziva onda gledamo dali ce ozivjeti: ozivljava ako ima tocno 3 susjeda ziva
            else {
                if (n == 3) {
                    _sljedeca_generacija[i][j] = true;

                    red_next[i][j] = mix_boja(red_next[i][j], n);
                    green_next[i][j] = mix_boja(green_next[i][j], n);
                    blue_next[i][j] = mix_boja(blue_next[i][j], n);
                }
                else
                    _sljedeca_generacija[i][j] = false;
            }
        }
    }
    next_gen_is_now_gen(mode);

    if (mode == 2 && mode_counter > 0) {
            croatian_flag_mode();  
            mode_counter--;
    }
}

void game_of_life::iscrtaj(int mode)
{
    background_iscrtaj(mode);

    if (mode == 1) {
        counters_draw();
    }

    for (int i = 0; i < REDAKA; i++) {
        for (int j = 0; j < STUPACA; j++) {
            if (_generacija[i][j]) {
                draw_celija(i, j);
            }
        }
    }
}