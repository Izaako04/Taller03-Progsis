#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

typedef struct {
    char nombres[100];
    char apellidos[100];
    char matricula[20]; // Número único de matrícula
    char usuario[50];
    char clave[50];
    int estado; // 1 para Activo, 0 para Inactivo
} Estudiante;

// Prototipos de funciones
void ingresarEstudiante(Estudiante *estudiante, char matriculasRegistradas[][20], int *cantidadMatriculas);
int verificarMatriculaUnica(const char *matricula, char matriculasRegistradas[][20], int cantidadMatriculas);
int verificarUsuarioUnico(const char *usuario, char usuariosRegistrados[][50], int cantidadUsuarios);
void editarEstudiante(Estudiante *estudiante, int cursoEnProceso);

#endif // ESTUDIANTE_H
