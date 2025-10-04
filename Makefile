TARGET = main

SRC = src/main.cpp

# Compilador e Flags
CXX = g++ -O1
CXXFLAGS = -Wall -std=c++17

# Flags de ligação com SDL2
SDL_CFLAGS = -I/usr/include/SDL2 -D_REENTRANT
SDL_LDFLAGS = -lSDL2 -lSDL2_ttf

EIGEN_FLAGS = -I/usr/include/eigen3
SERIALIZATION_FLAGS = -lboost_serialization

# Regra padrão
all:
	@$(CXX) $(CXXFLAGS) $(EIGEN_FLAGS) $(SDL_CFLAGS) -o $(TARGET) $(SRC) $(SDL_LDFLAGS) $(SERIALIZATION_FLAGS);
	@./$(TARGET); 
	@rm -f $(TARGET);

debug: 
	@$(CXX) $(CXXFLAGS) $(EIGEN_FLAGS) $(SDL_CFLAGS) -o $(TARGET) $(SRC) $(SDL_LDFLAGS) $(SERIALIZATION_FLAGS);
	@valgrind --show-leak-kinds=all ./$(TARGET); 
	@rm -f $(TARGET);
