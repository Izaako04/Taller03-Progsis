# Nombre del ejecutable
EXEC = Main.exe

# Archivos objeto
OBJS = Curso.o Estudiante.o Materia.o Profesor.o Main.o

# Compilador
CC = gcc

# Flags del compilador (opcional, pero recomendado)
CFLAGS = -Wall -g

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) $(OBJS)