#include "Graphicx.hpp"
#include "Object.hpp"
#include "AIPlayer.hpp"
#include "HumanPlayer.hpp"

void
simulate_rain(
	Player* player
){

	Graphicx aplication(
		"Stone Rain",
		800, 600
	);

	StoneRain rain(
				  20,
				  0,
				  aplication.get_width(),
				  0,
				  aplication.get_height()
				 );

	player->set_obsts(&rain);
	player->init();

	while(
		aplication.if_is_running() and player->is_alive()
	){

		aplication.controll_fps();
		aplication.get_keys(&player->flag_user_play);
		aplication.set_renderer();

		SDL_SetRenderDrawColor(aplication.get_renderer(), 0, 0, 0, 255);

		// Avanço do tempo
		player->move_and_print(aplication.get_renderer(), aplication.get_delta_time());
		SDL_SetRenderDrawColor(aplication.get_renderer(), 0, 0, 0, 255);
		rain.move_and_print_rain(aplication.get_renderer(), aplication.get_delta_time());
		aplication.print_fps();
		aplication.print_boost();
		aplication.set_renderer();
		aplication.controll_fps();
	}
}

int main(
	int argc,
	char* argv[]
){

	if(argc == 1){
		// Desejamos fazer o usuário jogar.

		Player* p = new AIPlayer();

		simulate_rain(p);

		delete p;
	}

	printf("\n");
	return 0;
}