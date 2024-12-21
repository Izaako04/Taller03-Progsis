#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

typedef struct {
    char nombres[100];
    char apellidos[100];
    char matricula[20];
    char usuario[50];
    char clave[50];
    int estado;
} Estudiante;

void ingresarEstudiante();
void editarEstudiante();
int verificarMatriculaUnica(const char *matricula);
int verificarEstudianteUnico(const char *usuario);
int estaCursandoCurso(const char *matricula);

#endif