#ifndef CURSO_H
#define CURSO_H

#include "estudiante.h"
#include "profesor.h"
#include "materia.h"

typedef struct {
    char codigo[20];
    char materia[100];
    char profesor[100];
    char fechaInicio[11];
    char fechaFin[11];
    Estudiante estudiantes[30];
    int numEstudiantes;
} Curso;

void ingresarCurso();
void editarCurso();
int verificarCodigoCurso(const char *codigo);

#endif
