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
void ingresarEstudiante(Estudiante *estudiante);
void editarEstudiante(Estudiante *estudiante, int cursoEnProceso);

#endif // ESTUDIANTE_H
