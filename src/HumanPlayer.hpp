#ifndef HUMANPLAYER_HPP
#define HUMANPLAYER_HPP

#include "Player.hpp"

/**
 * @brief Classe responsável por representar o usuário jogando.
 * @details
 * 
 * A implementação segue essa necessidade. 
 */
class HumanPlayer : public Player {
private:
	std::thread worker;  ///, Thread que representará nosso jogador.
	std::atomic<bool> is_running{True};  ///< Flag de execução.

	double pos[2] = {0, 0};
	SDL_Rect rect = {0, 0, 15, 15};

	/**
	 * @brief Faremos verificações de entrada para mover o usuário.	
	 * @details
	 * 
	 * Também responsável por verificar colisões encerrar a simulação.
	 */
	void run(int id = 0) override {

		// Garantimos que haverá informações de obstáculos disponíveis.
		const std::vector<Object>& obsts = rain->get_obsts();

		// Vamos colocá-lo no meio.
		pos[0] = rain->get_width() / 2.0;
		pos[1] = rain->get_height() - 15;

		fprintf(stderr, "\nEntrando na thread.");

		while(is_running.load()){

			// Atualizamos entradas
			if(
				flag_user_play > 0
			){

				pos[0] += 20;

			}
			else if( flag_user_play < 0 ) {

				pos[0] -= 20;
			}
			flag_user_play = 0;

			// Devemos verificar se ele foi explodido de alguma forma.
			for(
				int i = 0;
					i < (int)obsts.size();
					i++
			){
				SDL_Rect obj_rect = obsts[i].get_rect();

				if(
					obj_rect.y > pos[1] * 0.70 && 
					obj_rect.x > pos[0] - 50 && 
					obj_rect.x < pos[0] + 50
				){	

					if(
						Player::check_colision(
							&rect,
							&obj_rect
						)
					){

						is_running.exchange(False);
						return;
					}
				}
			}

			SDL_Delay(50); // Evitar superuso
		}
	}

public:

	/**
	 * @brief Iniciamos a thread de entradas.	
	 */
	void
	init() override {
		worker = std::thread([this]() { run(); });
	}

	/**
	 * @brief Desliga a thread de pensamento.	
	 */
	~HumanPlayer(){
		is_running.exchange(False);
		

		if(
			worker.joinable()
		){
			worker.join();
			fprintf(stderr, "\nDesliguei.");
		}
	}

	/**
	 * @brief Responsável por apresentar o rect no momento correto e movê-lo.
	 * @param renderer Renderizador da Janela
	 * @param interv Intervalo de Tempo
	 */
	void
	move_and_print(
		SDL_Renderer* renderer,
		double interv
	) override {

		rect.x = pos[0];
		rect.y = pos[1];
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

		SDL_RenderFillRect(
			renderer,
			&rect
		);
	}

	/**
	 * @brief Verificará se há um jogador vivo.	
	 */
	bool
	is_alive() override {

		return is_running.load();
	}
};

#endif //HUMANPLAYER_HPP