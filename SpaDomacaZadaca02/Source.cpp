#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include "game_of_life.h"
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;


int main() {

	srand(time(nullptr));

	int refresh_rate;
	cout << "Upisite brzinu refresh rate (u milisekundama, preporuca se: 42): ";
	cin >> refresh_rate;
	if (refresh_rate < 16)
		refresh_rate = 16;
	cout << endl;

	int mode_counter=2; 
	cout << "\nOpcije:\n\t"
		               <<"Unos '0' za basic mode\n\t"
					   <<"Unos '1' za Borba dviju boja(Red vs Blue)\n\t"
					   <<"Unos '2' za croatian_mode\n\t"
					   <<"Unos '3' za 3 boje(ali sa razlicitim nijansama)\n\t"
					   <<"Unos '4' za ciste 3 boje (Red green and blue)";
	cout << "\n\n\n\n\nUnos: ";
	cin >> mode_counter;


	sf::RenderWindow window(sf::VideoMode(1200, 800), "Hello, SFML world!");
	window.setFramerateLimit(60);

	game_of_life* game =new game_of_life(&window,mode_counter);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
			window.clear();
			//cvijet.draw();
			game->iscrtaj(mode_counter);
			game->sljedeca_generacija(mode_counter);
			window.display();

			this_thread::sleep_for(milliseconds (refresh_rate));
	}

	return 0;
}