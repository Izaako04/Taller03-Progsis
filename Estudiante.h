#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

// Función auxiliar para listar todos los estudiantes
typedef struct {
    char nombres[100];
    char apellidos[100];
    char matricula[20];
    char usuario[50];
    char clave[50];
    int estado; // 1 para Activo, 0 para Inactivo
} Estudiante;

void ingresarEstudiante();
void editarEstudiante();
int verificarMatriculaUnica(const char *matricula);
int verificarEstudianteUnico(const char *usuario);
int estaCursandoCurso(const char *matricula);

#endif