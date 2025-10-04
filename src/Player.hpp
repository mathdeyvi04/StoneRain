#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Object.hpp"
#include "Graphicx.hpp"
#include <thread>
#include <atomic>

/**
 * @brief Representará o usuário ou as redes neurais.
 * @details 
 * 
 * Definiremos coisas básicas nesta classe e implementaremos posteriormente.
 */
class Player {
protected:

	StoneRain* rain = nullptr;

public:

	int flag_user_play;

	virtual
	~Player() = default;

	virtual void
	run(int id = 0) = 0;

	virtual void
	move_and_print( SDL_Renderer* renderer, double interv ) = 0;

	virtual bool
	is_alive() = 0;

	virtual void
	init() = 0;

	/**	
	 * @brief Armazenaremos as informações dos obstáculos de uma vez.	
	 */
	void
	set_obsts(
		StoneRain* rain_ 
	){

		rain = rain_;
	}

	/**
	 * @brief Responsável por analisar colisões	entre objetos.
	 * @param other_object Outro Objeto
	 */
	static bool
	check_colision(
		SDL_Rect* rect,
		SDL_Rect* other_rect		
	){
		return SDL_HasIntersection(
									rect,
									other_rect
			                      );
	}
};

#endif // PLAYER_HPP