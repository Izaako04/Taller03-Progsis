#ifndef CURSO_H
#define CURSO_H

#include "estudiante.h"
#include "profesor.h"
#include "materia.h"

// Estructura encapsulada dentro de curso.c
typedef struct {
    char codigo[20];
    char materia[100];
    char profesor[100]; // Nombre del profesor responsable
    char fechaInicio[11]; // Formato: YYYY-MM-DD
    char fechaFin[11]; // Formato: YYYY-MM-DD
    Estudiante estudiantes[30]; // Lista de hasta 30 estudiantes
    int numEstudiantes; // Cantidad de estudiantes registrados
} Curso;

// Prototipos de funciones
void ingresarCurso();
void editarCurso();
int verificarCodigoCurso(const char *codigo);

#endif
