#ifndef PROFESOR_H
#define PROFESOR_H

enum Tipo{
    profesor
}

typedef struct {
    char nombres[100];
    char apellidos[100];
    char cedula[20]; // C.C. (Cédula de Ciudadanía)
    char usuario[50];
    char clave[50];
    int estado; // 1 para Activo, 0 para Inactivo
    char materias[5][100]; // Hasta 5 materias que puede dictar
    int num_materias; // Número actual de materias registradas
} Profesor;

// Prototipos de funciones
void ingresarProfesor(Profesor *profesor);
int verificarCedulaUnica(const char *cedula, char cedulasRegistradas[][20], int cantidadCedulas);
int verificarUsuarioUnico(const char *usuario, char usuariosRegistrados[][50], int cantidadUsuarios);
void editarProfesor(Profesor *profesor, int cursoEnProceso);

#endif // PROFESOR_H
