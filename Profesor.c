#include <stdio.h>
#include <string.h>
#include "profesor.h"

// Función para verificar si una cédula ya existe
int verificarCedulaUnica(const char *cedula, char cedulasRegistradas[][20], int cantidadCedulas) {
    for (int i = 0; i < cantidadCedulas; i++) {
        if (strcmp(cedula, cedulasRegistradas[i]) == 0) {
            return 0; // Cédula no es única
        }
    }
    return 1; // Cédula es única
}

// Función para verificar si un usuario ya existe
int verificarUsuarioUnico(const char *usuario, char usuariosRegistrados[][50], int cantidadUsuarios) {
    for (int i = 0; i < cantidadUsuarios; i++) {
        if (strcmp(usuario, usuariosRegistrados[i]) == 0) {
            return 0; // Usuario no es único
        }
    }
    return 1; // Usuario es único
}

// Función para ingresar los datos de un profesor
void ingresarProfesor(Profesor *profesor) {
    printf("Ingrese los nombres del profesor: ");
    scanf(" %[^\n]", profesor->nombres); // Leer cadena con espacios
    printf("Ingrese los apellidos del profesor: ");
    scanf(" %[^\n]", profesor->apellidos);
     // Validar unicidad de cédula
    while (1) {
        printf("Ingrese la cédula del profesor: ");
        scanf(" %[^\n]", profesor->cedula);

        if (verificarCedulaUnica(profesor->cedula, cedulasRegistradas, *cantidadCedulas)) {
            strcpy(cedulasRegistradas[*cantidadCedulas], profesor->cedula);
            (*cantidadCedulas)++;
            break;
        } else {
            printf("Error: La cédula ingresada ya existe. Intente nuevamente.\n");
        }
    }
     // Validar unicidad de usuario
    while (1) {
        printf("Ingrese el usuario del profesor: ");
        scanf(" %[^\n]", profesor->usuario);

        if (verificarUsuarioUnico(profesor->usuario, usuariosRegistrados, *cantidadUsuarios)) {
            strcpy(usuariosRegistrados[*cantidadUsuarios], profesor->usuario);
            (*cantidadUsuarios)++;
            break;
        } else {
            printf("Error: El usuario ingresado ya existe. Intente nuevamente.\n");
        }
    }
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
