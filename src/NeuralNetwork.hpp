#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#define Matrix Eigen::MatrixXd
#define Vector Eigen::VectorXd

#define out_arch boost::archive::text_oarchive
#define in_arch  boost::archive::text_iarchive

/**
 * @brief Responsável por representar a classe abstrata de camada 
 */
class Layer {
public:

	virtual 
	~Layer() = default;

	virtual 
	std::string 
	type() const = 0;

	virtual 
	void 
	save(
		out_arch& ar
		)  const = 0;

	virtual
	void 
	load(
		in_arch& ar
		) = 0;
};

class DenseLayer : public Layer {
private:

	Matrix weights;
	Vector biases;

public:
	DenseLayer() = default;
	
	/**
	 * @brief Construtor de inicialização base	
	 */
	DenseLayer(
		size_t in,
		size_t out
	){

	}

	std::string
	type() const override { return "Dense"}


}









#endif //NEURALNETWORK_HPP