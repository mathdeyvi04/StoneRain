#ifndef AI_HPP
#define AI_HPP

#include "Player.hpp"
#include "NeuralNetwork.hpp"
#include <mutex>
#include <iostream>

/**
 * @brief Struct para representar os objetos que serão jogados pelas threads.
 */
struct Bot {
	double pos[2] = {0, 0};
	SDL_Rect rect{0, 0, 15, 15};
	int r = Object::get_random(0, 255);
	int g = Object::get_random(0, 255);
	int b = Object::get_random(0, 255);
};


class AIPlayer : public Player {
private: 

	const int max_threads = 1;
	std::atomic<int> var{0};

	std::vector<bool> running_flags;
	std::vector<std::thread> workers;
	std::vector<Bot> players;
	std::mutex mtx; ///< Mutex para garantir unicidade no acesso às cores renderizadas


	/**
	 * @brief As threads jogarão utilizando essa função.
	 */
	void
	run(int id = -1) override {

		// Não ocupará nova memória, lembra?
		const std::vector<Object>& obsts = rain->get_obsts();

		// Vamos colocá-lo no meio.
		players[id].pos[0] = rain->get_width() / 2.0;
		players[id].pos[1] = rain->get_height() - 15;

		// Vamos definir aqui o que fazer com a "mente do jogador".
		NeuralNetwork nn("nn0.bin");

		// Testar salvamento
		while(
			running_flags[id]
		){









			SDL_Delay(50);
		}

		var--;
		fprintf(stderr, "\nSai da thread %d", id);
	}

public:
	AIPlayer() = default;

	/**
	 * @brief Responsável por desligar cada uma das threads ligadas.	
	 */
	~AIPlayer(){

		// Forçar desligamento de todas
		for(
			int i = 0;
				i < max_threads;
				i++
		){

			running_flags[i] = False;
			if(workers[i].joinable()){
				workers[i].join();
			}
		}
	}

	/**
	 * @brief Contará quantas threads ainda estão vivas.	
	 */
	bool
	is_alive() override { return var.load() > 0; };

	/**
	 * @brief Iniciará as threads.	
	 */
	void
	init() override {

		workers.reserve(max_threads);
		running_flags.reserve(max_threads);
		players.reserve(max_threads);
		for(
			int i = 0;
				i < max_threads;
				i++
		){

			running_flags.emplace_back(True);
			players.emplace_back();
			workers.emplace_back(
				[this, i](){ run(i); }
			);
			var++;
		}
	}

	/**
	 * @brief Apresentará todos os objetos.
	 * @details
	 * 
	 * Há um mutex protegendo o acesso às cores do SDL.
	 */
	void
	move_and_print( SDL_Renderer* renderer, double interv ) override {
		for(
			auto& p : players
		){

			p.rect.x = p.pos[0];
			p.rect.y = p.pos[1];

			// O ponto é que este valor aqui necessita de um mutex.
			mtx.lock();
			SDL_SetRenderDrawColor(renderer, 
											p.r,
											p.g,
											p.b,
											255);
			SDL_RenderFillRect(
				renderer,
				&p.rect
			);
			mtx.unlock();
		}
	}
};

#endif // AI_HPP