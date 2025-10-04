#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <Eigen/Dense>  ///< Assim, não reinventaremos a roda.
#define Matrix Eigen::MatrixXd ///< Apenas para não ficarmos escrevendo coisas desnecessárias.

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/array.hpp>

/**
 * @namespace boost
 * @brief Responsável por prover as ferramentas de serialização
 */
namespace boost {
	namespace serialization {
		template<class Arquivo>
		void
		serialize(
			Arquivo& ar,
			Matrix& mat,
			const unsigned int version
		){

			boost::serialization::split_free(
											ar,
											mat,
											version
				                            );
		}

		template<class Arquivo> 
		void
		save(
			Arquivo& ar,
			const Matrix& mat,
			const unsigned int /*version*/
		){
			// O tamanho já é padronizado

			int linhas = mat.rows();
			int colunas = mat.cols();

			ar & linhas;
			ar & colunas;

			ar & boost::serialization::make_array(mat.data(), linhas * colunas);
		}

		template<class Arquivo>
		void
		load(
			Arquivo& ar,
			Matrix& mat,
			const unsigned int /*version*/
		){

			int linhas, colunas;

			ar & linhas;
			ar & colunas;

			mat.resize(linhas, colunas);

			ar & boost::serialization::make_array(mat.data(), linhas * colunas);
		}
	}
}

/**
 * @brief Representará nossa rede neural.
 * @details
 * 
 * Apenas definimos operações de salvamento e de carregamento
 * de matrizes, o restante é completamente obtido de MatrixXd.
 */
class NeuralNetwork {
private:

	friend class boost::serialization::access; ///< Assim, obtemos acesso a membros privados
	Matrix mat;

public:

	/**
	 * @brief Construtor base, focado em gerar matrizes dos tipos desejados e valores aleatórios.
	 * @details Como nada é passado, considera 2x2.
	 */
	NeuralNetwork(){

		mat.resize(2, 2);
		mat.setRandom(2, 2);
	}

	/**
	 * @brief Construtor com argumento de nome de arquivo, indica que desejamos carregar uma rede.	
	 * @param nome_do_arquivo Arquivo binário que desejamos carregar
	 */
	NeuralNetwork(
		const std::string& nome_do_arquivo
	){

		this->carregar(nome_do_arquivo);
	}

	Matrix& data() { return mat; }  ///< Getter da referência da matriz
	const Matrix& data() const { return mat; } ///< Getter da referência constante da matriz

	/**
	 * @brief Salvará a matriz de forma legível, apenas para curiosidade.
	 * @param nome_do_arquivo Arquivo Legível no qual salvaremos
	 */
	void
	salvar_como_legivel(
		const std::string& nome_do_arquivo
	) const {

		std::ofstream file(nome_do_arquivo);
		if( file.is_open() ){ file << mat << "\n"; }

		file.close();
	}

	/**
	 * 	@brief Responsável por salvar informações em binário.
	 */
	void
	salvar(
		int id
	){

		std::stringstream ss;
		ss << "nn"
		   << id 
		   << ".bin";

		std::ofstream ofs(ss.str(), std::ios::binary);
		boost::archive::binary_oarchive oa(ofs);
		oa << data();
	}

	/**
	 * @brief Responsável por carregar uma rede.
	 */
	void
	carregar(
		const std::string& nome_do_arquivo 
	){
		std::ifstream ifs(nome_do_arquivo, std::ios::binary);
		if(!ifs){

			std::cout << "Rede inexistente, inseri random." << std::endl;
		}
		else{
			
			boost::archive::binary_iarchive ia(ifs);
			ia >> mat;
		}
	}

	////////////////////////////////////////////////////////////////////////
	/**
	 * Implementaremos métodos intrínsecos ao pensamento em IA.
	 * 
	 * Vamos criar arquiteturas diferentes de IA.
	 * 
	 * A ideia é que tenhamos uma simples e uma complexa, verificando o desempenho de ambas.
	 */
























};

#endif //NEURALNETWORK_HPP