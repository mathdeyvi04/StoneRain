#ifndef GRAPHICX_HPP
#define GRAPHICX_HPP

#define True true
#define False false

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>


/**
 * @brief Representará nossa janela e suas funcionalidades
 */
class Graphicx {
private:

	SDL_Window*   _window   = nullptr;
	SDL_Renderer* _renderer = nullptr;
	const int _width, _height = 0;
	bool _is_running = False;

	int    _FPS = 30;            ///< Quantidade de frames por segundo
	int    _delay = 1000 / _FPS;  ///< Tempo ideal por frame em Milisegundos
	Uint32 _last_frame = 0;      ///< Momento do Último frame 
	int    _frame_time = 0;  	 ///< Intervalo de Tempo Medido
	int   _switch_phase_fps = 0; ///< Contador Auxiliar para Fases do Controle de FPS
	int   _switch_phase_renderer = 0; ///< Contador Auxiliar para Fases do Renderizador
	
	SDL_Event evento;

	int _last_fps = 0;
	TTF_Font* _font = nullptr;
	SDL_Texture* _texture_text = nullptr;
	SDL_Rect _dst;

	int _boost = 1;
	int _last_boost = 0;
	SDL_Texture* _texture_boost = nullptr;
	SDL_Rect _dst_boost; 

public:

	/**
	 * @brief Construtor da Classe
	 * @param nome_da_janela Nome da Janela
	 * @param width Comprimento da Janela
	 * @param height Largura da Janela
	 * @details 
	 * 
	 * Cada inicialização é verificada. Havendo erro, os passos anteriores
	 * são revertidos/liberados.	
	 */
	Graphicx(
		const std::string nome_da_janela,
		int width,
		int height
	) : _width(width),
		_height(height)
	{	

		srand(time(NULL));

		if(
			SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0
		){

			std::cerr << "Erro ao inicializar SDL: "
					  << SDL_GetError() 
					  << std::endl;
		}

		_window = SDL_CreateWindow(
			nome_da_janela.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width, height,
			SDL_WINDOW_SHOWN
		);

		if(
			!_window
		){

			std::cerr << "Erro ao criar Window: "
					  << SDL_GetError() 
					  << std::endl;
			SDL_Quit();
		}

		_renderer = SDL_CreateRenderer(
			_window,
			-1,
			SDL_RENDERER_ACCELERATED
		);

		if(
			!_renderer
		){

			std::cerr << "Erro ao criar Renderer: "
					  << SDL_GetError()
					  << std::endl;
			SDL_DestroyWindow(_window);
			SDL_Quit();
		}

		TTF_Init();

		_font = TTF_OpenFont("src/Roboto-Black.ttf", 16);
		if(
			!_font 
		){

			std::cerr << "Fonte padrão não obtida: "
					  << SDL_GetError() 
					  << std::endl;
		}

		// Se chegou até aqui, foi bem sucedido.
		_is_running = True;

		_dst = {
	    	_width  - 56 - 5, 
	    	_height - 19 - 5, 
	    	56, 
	    	19
	    };

	    _dst_boost = {
	    	_width  - 60 - 5, 
	    	_height - 19 - 5 - 19, 
	    	60, 
	    	19
	    };
	}

	/**
	 * @brief Destrutor da Classe
	 */
	~Graphicx(){

		if( _renderer){ SDL_DestroyRenderer(_renderer);}
		if( _window  ){ SDL_DestroyWindow(_window);    } 
		TTF_CloseFont(_font);
		TTF_Quit();
		SDL_Quit();
	}

	/**
	 * @brief Getter do Window	
	 */
	SDL_Window*
	get_window() const { return _window; }

	/**
	 * @brief Getter do Renderer	
	 */
	SDL_Renderer*
	get_renderer() const { return _renderer; }

	/**
	 * @brief Getter do comprimento
	 */
	const int
	get_width() const { return _width; }

	/**
	 * @brief Getter da largura	
	 */
	const int
	get_height() const { return _height; }

	/**
	 * @brief Verificação de Funcionamento
	 */
	const bool
	if_is_running() const { return _is_running; }

	/**
	 * @brief Responsável por controlar FPS da aplicação.
	 * @details
	 * 
	 * Implementação inteligente e que retira quaisquer responsabilidades
	 * do usuário.
	 */
	void
	controll_fps(){

		if(
			!_switch_phase_fps
		){

			_last_frame = SDL_GetTicks();
		}
		else{

			_frame_time = SDL_GetTicks() - _last_frame;
			if( _delay > _frame_time ){ SDL_Delay( _delay - _frame_time); }
		}

		// Garantimos que não exceda mais que 2.
		_switch_phase_fps = (_switch_phase_fps + 1) % 2;
	}

	/**
	 * @brief Responsável por printar informação de FPS	
	 * @details
	 * 
	 * A fim de otimizar o processo, foi criado uma flag para verificar se 
	 * houve alteração do fps, assim reduzimos muito.
	 */
	void
	print_fps(){

		if(
			!_font
		){
			return;
		}

		if(
			_last_fps != _FPS
		){

			// Então, houve alteração do fps.
			if(_texture_text){ SDL_DestroyTexture(_texture_text); }

			std::stringstream ss;
			ss << "FPS: "
			   << _FPS;

			SDL_Surface* surface = TTF_RenderText_Solid(_font, ss.str().c_str(), {0, 0, 0, 255});
	        _texture_text = SDL_CreateTextureFromSurface(_renderer, surface);

	        SDL_RenderCopy(_renderer, _texture_text, nullptr, &_dst);
	        SDL_FreeSurface(surface);
	        
	        // Atualizações 
	        _last_fps = _FPS;
	        _delay = 1000 / _FPS;
	    }
	    else{

	    	// Se continua o mesmo, basta que apresentemos.
	    	SDL_RenderCopy(_renderer, _texture_text, nullptr, &_dst);
	    }
	}

	/**
	 * @brief Responsável por printar informações de boost.	
	 */
	void
	print_boost(){

		if(
			!_font
		){
			return;
		}

		if(
			_last_boost != _boost
		){

			// Então, houve alteração do fps.
			if(_texture_boost){ SDL_DestroyTexture(_texture_boost); }

			std::stringstream ss;
			ss << "Boost: "
			   << _boost;

			SDL_Surface* surface = TTF_RenderText_Solid(_font, ss.str().c_str(), {0, 0, 0, 255});
	        _texture_boost = SDL_CreateTextureFromSurface(_renderer, surface);

	        SDL_RenderCopy(_renderer, _texture_boost, nullptr, &_dst_boost);
	        SDL_FreeSurface(surface);
	        _last_boost = _boost;
	    }
	    else{

	    	// Se continua o mesmo, basta que apresentemos.
	    	SDL_RenderCopy(_renderer, _texture_boost, nullptr, &_dst_boost);
	    }
	}

	/**
	 * @brief Controlador de Inputs
	 * @param[out] flag Flag para direcionais
	 * @details
	 * 
	 * Usamos um `while(SDL_PollEvent(...))` para garantir que todos 
	 * as entradas sejam tratadas antes do próximo frame.
	 */
	void
	get_keys(int* flag){

		while(
			SDL_PollEvent(&evento)
		){

			switch(evento.type){

				case SDL_QUIT: {
					
					_is_running = False;
					break;
				}

				case SDL_KEYDOWN: {

					switch (evento.key.keysym.sym){

						// Essas funcionalidades estarão disponíveis apenas
						// se tiver alguma informação sendo printada.
						case SDLK_UP: {

							if(_FPS < 60 and _font){ _FPS += 1; }
							break;
						}

						case SDLK_DOWN: {

							if(_FPS > 5 and _font){ _FPS -= 1; }
							break;
						}

						case SDLK_RIGHT: {

							if(_boost < 10 and _font){ _boost += 1; }
							break;
						}

						case SDLK_LEFT: {
							if(_boost > 1 and _font){ _boost -= 1; }
							break;
						}

						case SDLK_a: {

							*flag -= 1;
							break;
						}

						case SDLK_d: {
							*flag += 1;
							break;
						}
						default:
							break;
					}

					break;
				}

				default:
					break;
			}
		}
	}

	/**
	 * @brief Renderizador básico
	 * @details
	 * 
	 * Se concentra em limpar a tela e preenchê-la.	
	 */
	void
	set_renderer(){

		if(
			!_switch_phase_renderer
		){

			SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255); // Branco
			SDL_RenderClear(_renderer);
		}
		else{

			SDL_RenderPresent(_renderer);
		}

		_switch_phase_renderer = (_switch_phase_renderer + 1) % 2;
	}


	/**
	 * @brief Obtém o intervalo de tempo para realizar cálculos.
	 */
	double 
	get_delta_time() { return (_frame_time / 1000.0) * _boost; }

};

#endif // GRAPHICX_HPP