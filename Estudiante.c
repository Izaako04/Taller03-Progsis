#include <stdio.h>
#include <string.h>
#include "estudiante.h"

// Función para verificar si un usuario ya existe
int verificarUsuarioUnico(const char *usuario, char usuariosRegistrados[][50], int cantidadUsuarios) {
    for (int i = 0; i < cantidadUsuarios; i++) {
        if (strcmp(usuario, usuariosRegistrados[i]) == 0) {
            return 0; // Usuario no es único
        }
    }
    return 1; // Usuario es único
}

// Función para verificar si una matrícula ya existe
int verificarMatriculaUnica(const char *matricula, char matriculasRegistradas[][20], int cantidadMatriculas) {
    for (int i = 0; i < cantidadMatriculas; i++) {
        if (strcmp(matricula, matriculasRegistradas[i]) == 0) {
            return 0; // Matrícula no es única
        }
    }
    return 1; // Matrícula es única
}

// Función para ingresar los datos de un estudiante
void ingresarEstudiante(Estudiante *estudiante) {
    printf("Ingrese los nombres del estudiante: ");
    scanf(" %[^\n]", estudiante->nombres); // Leer cadena con espacios
    printf("Ingrese los apellidos del estudiante: ");
    scanf(" %[^\n]", estudiante->apellidos);
    while (1) {
        printf("Ingrese el número de matrícula: ");
        scanf(" %[^\n]", estudiante->matricula);

        if (verificarMatriculaUnica(estudiante->matricula, matriculasRegistradas, *cantidadMatriculas)) {
            strcpy(matriculasRegistradas[*cantidadMatriculas], estudiante->matricula);
            (*cantidadMatriculas)++;
            break;
        } else {
            printf("Error: La matrícula ingresada ya existe. Intente nuevamente.\n");
        }
    }
    // Validar unicidad de usuario
    while (1) {
        printf("Ingrese el usuario: ");
        scanf(" %[^\n]", estudiante->usuario);

        if (verificarUsuarioUnico(estudiante->usuario, usuariosRegistrados, *cantidadUsuarios)) {
            strcpy(usuariosRegistrados[*cantidadUsuarios], estudiante->usuario);
            (*cantidadUsuarios)++;
            break;
        } else {
            printf("Error: El usuario ingresado ya existe. Intente nuevamente.\n");
        }
    }
    printf("Ingrese la clave: ");
    scanf(" %[^\n]", estudiante->clave);
    estudiante->estado = 1; // Estado inicial activo
    printf("Estudiante registrado con estado Activo.\n");
}

// Función para editar los datos de un estudiante
void editarEstudiante(Estudiante *estudiante, int cursoEnProceso) {
    if (cursoEnProceso) {
        printf("No se puede inactivar el estudiante porque tiene un curso en proceso.\n");
    } else {
        printf("Estado actual del estudiante: %s\n", estudiante->estado ? "Activo" : "Inactivo");
        printf("¿Desea cambiar el estado del estudiante? (1 para Activo, 0 para Inactivo): ");
        int nuevoEstado;
        if (scanf("%d", &nuevoEstado) == 1 && (nuevoEstado == 0 || nuevoEstado == 1)) {
            estudiante->estado = nuevoEstado;
            printf("Estado actualizado a: %s\n", estudiante->estado ? "Activo" : "Inactivo");
        } else {
            printf("Entrada inválida. El estado no se cambió.\n");
        }
    }

    printf("¿Desea cambiar la clave del estudiante? (1 para Sí, 0 para No): ");
    int cambiarClave;
    if (scanf("%d", &cambiarClave) == 1 && cambiarClave == 1) {
        printf("Ingrese la nueva clave: ");
        scanf(" %[^\n]", estudiante->clave);
        printf("Clave actualizada correctamente.\n");
    } else {
        printf("Clave no modificada.\n");
    }
}
