#ifndef PROFESOR_H
#define PROFESOR_H

// Definición de la estructura de Profesor
typedef struct {
    char nombres[100];
    char apellidos[100];
    char cedula[20]; // Cédula única
    char usuario[50]; // Usuario único
    char clave[50];
    int estado; // 1 para Activo, 0 para Inactivo
    char materias[5][100]; // Materias que puede dictar (máximo 5)
    int num_materias; // Número de materias registradas
} Profesor;

// Prototipos de funciones
int verificarCedulaUnica(const char *cedula);
int verificarProfesorUnico(const char *usuario);
void ingresarProfesor();
void editarProfesor();

#endif // PROFESOR_H
