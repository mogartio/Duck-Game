# Nombre del ejecutable
TARGET = play

# Compilador
CC = g++

# Archivos fuente
SRC = prueba.cpp game/window.cpp game/player.cpp game/image.cpp game/wingState.cpp ../../common/duckState/duckState.cpp 

# Flags de compilación
CFLAGS = -Wall -g

# Librerías de SDL2 y SDL2_image
LDFLAGS = -lSDL2 -lSDL2_image

# Directorios de inclusión (si es necesario)
INCLUDE =

# Regla para compilar y enlazar el programa
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(TARGET) $(SRC) $(LDFLAGS)

# Regla para limpiar los archivos generados
clean:
	rm -f $(TARGET) *.o

# Regla para ejecutar el programa
run: $(TARGET)
	./$(TARGET)
