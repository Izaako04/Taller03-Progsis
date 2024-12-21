#ifndef MATERIA_H
#define MATERIA_H

typedef struct {
    char nombre[100];
    char codigo[20]; 
    int estado;
} Materia;

int verificarCodigoMateria(const char *codigo);
int tieneCursoEnProceso(const char *codigoMateria);
void ingresarMateria();
void cambiarEstadoMateria();

#endif
