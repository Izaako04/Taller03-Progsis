#ifndef CURSO_H
#define CURSO_H

#include "estudiante.h"
#include "profesor.h"
#include "materia.h"

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
void ingresarCurso(Curso *curso, char codigosRegistrados[][20], int *cantidadCodigos);
int verificarCodigoUnico(const char *codigo, char codigosRegistrados[][20], int cantidadCodigos);
void editarCurso(Curso *curso);

#endif // CURSO_H
