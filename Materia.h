#ifndef MATERIA_H
#define MATERIA_H

#define MAX_NOMBRE 100
#define MAX_CODIGO 50

typedef struct {
    char nombreMateria[MAX_NOMBRE];
    char codigo[MAX_CODIGO];
    int estado;
} Materia; 

void ingresarMateria(Materia *materia);
void cambiarEstado(Materia *materia, int cursoEnProceso);

#endif MATERIA_H