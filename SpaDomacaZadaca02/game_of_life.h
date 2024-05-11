#ifndef _GAME_OF_LIFE_H_
#define _GAME_OF_LIFE_H_
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <fstream>


using namespace std;

class game_of_life {
private:
	sf::RenderWindow* ekran;

	sf::RectangleShape celija;
	sf::RectangleShape background;

	int mode_counter=0;

	static const unsigned int STUPACA = 90; //40
	static const unsigned int REDAKA = 60; //20 /// dostupno je 800 x 600
	bool _generacija[REDAKA][STUPACA];
	bool _sljedeca_generacija[REDAKA][STUPACA];
	bool slucajna_vrijednost();
	bool celija_zauzeta(int i, int j);
	int broj_zivih_celija_susjeda(int i,int j);
	void next_gen_is_now_gen(int mode);
	void random_initialize_grid(int mode);
	void croatian_flag_mode();

	void draw_celija(int i, int j);

	int  csd = 10; //control_size_and_distances = 10;

	//kako rijesiti boje???
		int red_now[REDAKA][STUPACA];
		int green_now[REDAKA][STUPACA];
		int blue_now[REDAKA][STUPACA];

		int red_next[REDAKA][STUPACA];
		int green_next[REDAKA][STUPACA];
		int blue_next[REDAKA][STUPACA];

		int mix_boja(int zbroj, int n);

		void count_alive();
		int red_counter = 0;
		int blue_counter = 0;

		void background_iscrtaj(int mode);
		void counters_draw();


public:
	game_of_life(sf::RenderWindow* window,int mode);
	void sljedeca_generacija(int mode);
	void iscrtaj(int mode);
};


#endif
