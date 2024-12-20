#ifndef MATERIA_H
#define MATERIA_H

// Definición de la estructura Materia
typedef struct {
    char nombre[100];   // Nombre de la materia
    char codigo[20];    // Código único de la materia
    int estado;         // 1 para Activo, 0 para Inactivo
} Materia;

// Prototipos de funciones
int verificarCodigoMateria(const char *codigo);
int tieneCursoEnProceso(const char *codigoMateria);
void ingresarMateria();
void cambiarEstadoMateria();

#endif // MATERIA_H
