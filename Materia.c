#include <stdio.h>
#include <string.h>
#include "materia.h"

// Función para verificar si un código ya existe
int verificarCodigoUnico(const char *codigo, char codigosRegistrados[][20], int cantidadCodigos) {
    for (int i = 0; i < cantidadCodigos; i++) {
        if (strcmp(codigo, codigosRegistrados[i]) == 0) {
            return 0; // Código no es único
        }
    }
    return 1; // Código es único
}

// Función para ingresar los datos de una materia
void ingresarMateria(Materia *materia, char codigosRegistrados[][20], int *cantidadCodigos) {
    printf("Ingrese el nombre de la materia: ");
    scanf(" %[^\n]", materia->nombre);

    while (1) {
        printf("Ingrese el código de la materia: ");
        scanf(" %[^\n]", materia->codigo);

        if (verificarCodigoUnico(materia->codigo, codigosRegistrados, *cantidadCodigos)) {
            strcpy(codigosRegistrados[*cantidadCodigos], materia->codigo);
            (*cantidadCodigos)++;
            break;
        } else {
            printf("Error: El código ingresado ya existe. Intente nuevamente.\n");
        }
    }

    materia->estado = 1; // Estado inicial activo
    printf("Materia registrada con estado Activo.\n");
}

// Función para cambiar el estado de una materia
void cambiarEstadoMateria(Materia *materia, int cursoEnProceso) {
    if (cursoEnProceso) {
        printf("No se puede inactivar la materia porque tiene un curso en proceso.\n");
    } else {
        printf("El estado actual es: %s\n", materia->estado ? "Activo" : "Inactivo");
        printf("¿Desea cambiar el estado? (1 para Activo, 0 para Inactivo): ");
        int nuevoEstado;
        if (scanf("%d", &nuevoEstado) == 1 && (nuevoEstado == 0 || nuevoEstado == 1)) {
            materia->estado = nuevoEstado;
            printf("Estado actualizado a: %s\n", materia->estado ? "Activo" : "Inactivo");
        } else {
            printf("Entrada inválida. El estado no se cambió.\n");
        }
    }
}