# Objetivo

Construir uma espécie de joguinho no qual _pedras_ caem sobre nosso jogador e o destroem.

Neste trabalho, utilizaremos uma rede neural com os seguintes atributos:

- Explicação da rede neural.

Haverá duas algoritmos centrais para analisar seu desenvolvimento, _assexual_ e _aprendizado por reforço_.

# Como Utilizar

O arquivo `winning_the_rain` é o executável da aplicação.

### `./winning_the_rain`

Uma janela surge apresentando você à chuva e os controles _A-D_ o movimentam.

### `./winning_the_rain 1`

Uma janela surge apresentando a chuva e uma determinada quantidade de jogadores. 
Utilizando o algoritmo genético assexual, geração após geração, novas redes neurais são implementadas.

Em um determinado momento, ainda a ser implementado, a melhor rede será salva.

### `./winning_the_rain 2`

Uma janela surge apresentando a chuva e uma determinada quantidade de jogadores. 
Utilizando o algoritmo de aprendizado por reforço, geração após geração, novas redes neurais são implementadas.

Em um determinado momento, ainda a ser implementado, a melhor rede será salva.

### `./winning_the_rain 3`

Uma seção de entrada será aberta pedindo que você entre com uma rede neural para jogar o jogo.

# Diferenças 

Neste trabalho, usamos:

- `SDL2`

Renderizações gráficas e controle de apresentação.

- `Eigen/Dense`

Representações e operações avançadas com Matrizes.

- `Abstrações`

Classes e métodos abstratos foram definidos para ampliar o polimorfismo.

- `Threading`

Modelo de aplicação multithreading para perfomance.

- `Boost-Serialization`

Salvamento e carregamento de matrizes via serialização, muito otimizado.
