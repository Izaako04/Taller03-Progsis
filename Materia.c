#include <stdio.h>
#include <string.h>
#include "materia.h"

void ingresarMateria(Materia *materia) {
    printf("Ingrese el nombre de la materia: ");
    scanf(" %[^\n]", materia->nombre); // Leer cadena con espacios
    printf("Ingrese el código de la materia: ");
    scanf(" %[^\n]", materia->codigo);
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