#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <vector>
	
/**
 * @brief Representará os objetos de uma maneira geral e abstrata.
 */
class Object {
protected:

	SDL_Rect rect{0, 0, 15, 15};

	double pos[2]  = {0, 0};
	double vel[2]  = {0, 0};
	double acel[2] = {0, 0};
public:

	/**
	 * @brief Função estática para gerar números aleatórios.
	 */
	static int
	get_random(int min, int max){ return min + (rand() % (max - min + 1)); }

	Object() = default;

	/**
	 * @brief Construtor da Classe Objeto	
	 */
	Object(
		int _x,
		int _y,
		int _w,
		int _h
	) : rect{_x, _y, _w, _h},
		pos{(double)_x, (double)_y}
	{}

	/**
	 * @brief Getter do Retângulo	
	 */
	const SDL_Rect&
	get_rect() const { return rect; }

	/**
	 * @brief Setter das características cinemáticas
	 */
	void
	set_kinematic(
		int x,
		int y, 
		int vel_x,
		int vel_y,
		int acel_x,
		int acel_y
	){

		pos[0] = x;
		pos[1] = y;
		rect.x = x;
		rect.y = y;

		vel[0] = vel_x;
		vel[1] = vel_y;

		acel[0] = acel_x;
		acel[1] = acel_y;
	}

	/**
	 * @brief Setter do eixo x e do eixo y.
	 * @param valor Valor a ser setado.
	 * @param i Indice indicador se setará x ou y.	
	 */
	void 
	set_pos(
		int valor,
		int i
	){
		if( i > 2){ return; }

		pos[i] = valor;
	}

	/**
	 * @brief Setter de Velocidade do eixo x e y.	
	 * @param valor Valor a ser setado.
	 * @param i Indice indicador se setará x ou y.	
	 */
	void 
	set_vel(
		int valor, 
		int i
	){

		if(i > 2){ return; }
		vel[i] = valor;
	}

	/**
	 * @brief Responsável por apresentar o objeto.	
	 * @details
	 * 
	 * Executa individualmente o preenchimento do retângulo.
	 * Não se responsabiliza pela definição de cor.
	 */
	void
	print(
		SDL_Renderer* renderer
	){

		SDL_RenderFillRect(
			renderer,
			&rect
		);
	}

	/**
	 * @brief Responsável por prover a movimentação do objeto.	
	 * @param interv Intervalo de Tempo
	 */
	void
	move(
		double interv
	){	

		// Usamos intermediárias já que o rect aceita apenas inteiros
		// e com isso perderíamos precisão.
		vel[0] += acel[0] * interv;
		vel[1] += acel[1] * interv;
		pos[0] += vel[0] * interv;
		pos[1] += vel[1] * interv;

		rect.x = pos[0]; // Sempre estarão atualizados.
		rect.y = pos[1];
	}
};
	
/**
 * @brief Representará os obstáculos de chuva.
 * @details
 * 
 * Responsável por agrupar funcionalidades inerentes à chuva.
 */
class StoneRain {
private:

	std::vector<Object> obsts;
	int _height;
	int _width;

public:

	/**
	 * @brief Construtor da Classe 
	 * @param quantidade Quantidade de Pedras
	 * @param lim_inf_x Limite inferior X dos objetos
	 * @param lim_sup_x Limite Superior X dos objetos
	 * @param lim_inf_y Limite Inferior Y dos objetos
	 * @param lim_sup_y Limite Superior Y dos objetos
	 */
	StoneRain(
		int quantidade,
		int lim_inf_x, 
		int lim_sup_x,
		int lim_inf_y,
		int lim_sup_y
	)
	{
		if(quantidade <= 0){ quantidade = 10; }
		obsts.reserve(quantidade);
		for(
			int i = 0;
				i < quantidade;
				i++
		){
			obsts.push_back(Object()); // vai chamar default

			obsts[i].set_kinematic(
								   Object::get_random(lim_inf_x, lim_sup_x),
								   Object::get_random(lim_inf_y, lim_sup_y),
								   0,
								   1000,  // Velocidade padrão da chuva
								   0, 
								   100
				                  );

			_height = lim_sup_y;
			_width  = lim_sup_x;
		}
	}

	/**
	 * @brief Responsável por apresentar todos os elementos de chuva.	
	 * @param renderer Renderizador da Janela
	 * @param interv Intervalo de Tempo
	 */
	void
	move_and_print_rain(
		SDL_Renderer* renderer,
		double interv
	){

		for(
			int i = 0;
				i < (int)obsts.size();
				i++
		){

			obsts[i].move(interv);

			this->recycling(obsts[i]);


			obsts[i].print(renderer);
		}
	}

	/**
	 * @brief Responsável por criar o algoritmo de reciclagem dos obstáculos
	 * @details
	 * 
	 * A cada momento que um elemento saí da tela, ele deve ser redirecionado para o topo.	
	 */
	void
	recycling(
		Object& elemento
	){

		if(
			elemento.get_rect().y > _height 
		){

			elemento.set_pos(0, 1);
			elemento.set_pos(
						    Object::get_random(0, _width - 15),
						    0
							);
			elemento.set_vel(
							Object::get_random(800, 1500),
							1
							);
		}
	}

	/**
	 * @brief Getter de comprimento	
	 */
	const int
	get_width() const { return _width; }

	/**
	 * @brief Getter de largura
	 */
	const int
	get_height() const { return _height; }

	/**
	 * @brief Getter dos obstáculos	
	 */
	const std::vector<Object>&
	get_obsts(){ return obsts; }
};

#endif // OBJECT_HPP