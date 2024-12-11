#include <stdio.h>
#include <string.h>
#include "profesor.h"

// Función para ingresar los datos de un profesor
void ingresarProfesor(Profesor *profesor) {
    printf("Ingrese los nombres del profesor: ");
    scanf(" %[^\n]", profesor->nombres); // Leer cadena con espacios
    printf("Ingrese los apellidos del profesor: ");
    scanf(" %[^\n]", profesor->apellidos);
    printf("Ingrese la Cédula de Ciudadanía (C.C.): ");
    scanf(" %[^\n]", profesor->cedula);
    printf("Ingrese el usuario: ");
    scanf(" %[^\n]", profesor->usuario);
    printf("Ingrese la clave: ");
    scanf(" %[^\n]", profesor->clave);
    profesor->estado = 1; // Estado inicial activo

    // Registro de materias
    printf("Ingrese la cantidad de materias que puede dictar (máximo 5): ");
    if (scanf("%d", &profesor->num_materias) != 1 || profesor->num_materias < 1 || profesor->num_materias > 5) {
        fprintf(stderr, "Error: Cantidad de materias inválida. Se establecerá en 1.\n");
        profesor->num_materias = 1;
    }
    for (int i = 0; i < profesor->num_materias; i++) {
        printf("Ingrese el nombre de la materia %d: ", i + 1);
        scanf(" %[^\n]", profesor->materias[i]);
    }
    printf("Profesor registrado con estado Activo.\n");
}

// Función para editar los datos de un profesor
void editarProfesor(Profesor *profesor, int cursoEnProceso) {
    if (cursoEnProceso) {
        printf("No se puede inactivar el profesor porque tiene un curso en proceso.\n");
    } else {
        printf("Estado actual del profesor: %s\n", profesor->estado ? "Activo" : "Inactivo");
        printf("¿Desea cambiar el estado del profesor? (1 para Activo, 0 para Inactivo): ");
        int nuevoEstado;
        if (scanf("%d", &nuevoEstado) == 1 && (nuevoEstado == 0 || nuevoEstado == 1)) {
            profesor->estado = nuevoEstado;
            printf("Estado actualizado a: %s\n", profesor->estado ? "Activo" : "Inactivo");
        } else {
            printf("Entrada inválida. El estado no se cambió.\n");
        }
    }

    printf("¿Desea cambiar la clave del profesor? (1 para Sí, 0 para No): ");
    int cambiarClave;
    if (scanf("%d", &cambiarClave) == 1 && cambiarClave == 1) {
        printf("Ingrese la nueva clave: ");
        scanf(" %[^\n]", profesor->clave);
        printf("Clave actualizada correctamente.\n");
    } else {
        printf("Clave no modificada.\n");
    }
}
