#include <stdio.h>
#include <string.h>
#include "curso.h"

// Función para verificar si un código ya existe
int verificarCodigoUnico(const char *codigo, char codigosRegistrados[][20], int cantidadCodigos) {
    for (int i = 0; i < cantidadCodigos; i++) {
        if (strcmp(codigo, codigosRegistrados[i]) == 0) {
            return 0; // Código no es único
        }
    }
    return 1; // Código es único
}

// Función para ingresar los datos de un curso
void ingresarCurso(Curso *curso) {
     while (1) {
        printf("Ingrese el código del curso: ");
        scanf(" %[^\n]", curso->codigo);

        if (verificarCodigoUnico(curso->codigo, codigosRegistrados, *cantidadCodigos)) {
            strcpy(codigosRegistrados[*cantidadCodigos], curso->codigo);
            (*cantidadCodigos)++;
            break;
        } else {
            printf("Error: El código ingresado ya existe. Intente nuevamente.\n");
        }
    }
    printf("Ingrese el nombre de la materia: ");
    scanf(" %[^\n]", curso->materia);
    printf("Ingrese el nombre del profesor responsable: ");
    scanf(" %[^\n]", curso->profesor);
    printf("Ingrese la fecha de inicio (YYYY-MM-DD): ");
    scanf(" %[^\n]", curso->fechaInicio);
    printf("Ingrese la fecha de fin (YYYY-MM-DD): ");
    scanf(" %[^\n]", curso->fechaFin);

    printf("Ingrese la cantidad de estudiantes a registrar (máximo 30): ");
    if (scanf("%d", &curso->numEstudiantes) != 1 || curso->numEstudiantes < 1 || curso->numEstudiantes > 30) {
        fprintf(stderr, "Error: Cantidad de estudiantes inválida. Se establecerá en 0.\n");
        curso->numEstudiantes = 0;
        return;
    }

    for (int i = 0; i < curso->numEstudiantes; i++) {
        printf("\nRegistro del estudiante %d:\n", i + 1);
        ingresarEstudiante(&curso->estudiantes[i]);
    }
    printf("Curso registrado exitosamente.\n");
}

// Función para editar los datos de un curso
void editarCurso(Curso *curso) {
    char opcion;
    printf("\nEditar curso:\n");
    printf("¿Desea modificar el código del curso? (s/n): ");
    scanf(" %c", &opcion);
    if (opcion == 's' || opcion == 'S') {
        printf("Ingrese el nuevo código del curso: ");
        scanf(" %[^\n]", curso->codigo);
    }

    printf("¿Desea modificar la materia? (s/n): ");
    scanf(" %c", &opcion);
    if (opcion == 's' || opcion == 'S') {
        printf("Ingrese el nuevo nombre de la materia: ");
        scanf(" %[^\n]", curso->materia);
    }

    printf("¿Desea modificar el profesor responsable? (s/n): ");
    scanf(" %c", &opcion);
    if (opcion == 's' || opcion == 'S') {
        printf("Ingrese el nuevo nombre del profesor: ");
        scanf(" %[^\n]", curso->profesor);
    }

    printf("¿Desea modificar la fecha de inicio? (s/n): ");
    scanf(" %c", &opcion);
    if (opcion == 's' || opcion == 'S') {
        printf("Ingrese la nueva fecha de inicio (YYYY-MM-DD): ");
        scanf(" %[^\n]", curso->fechaInicio);
    }

    printf("¿Desea modificar la fecha de fin? (s/n): ");
    scanf(" %c", &opcion);
    if (opcion == 's' || opcion == 'S') {
        printf("Ingrese la nueva fecha de fin (YYYY-MM-DD): ");
        scanf(" %[^\n]", curso->fechaFin);
    }

    printf("¿Desea modificar la lista de estudiantes? (s/n): ");
    scanf(" %c", &opcion);
    if (opcion == 's' || opcion == 'S') {
        printf("Ingrese la nueva cantidad de estudiantes (máximo 30): ");
        if (scanf("%d", &curso->numEstudiantes) != 1 || curso->numEstudiantes < 1 || curso->numEstudiantes > 30) {
            fprintf(stderr, "Error: Cantidad de estudiantes inválida. No se realizarán cambios.\n");
            return;
        }
        for (int i = 0; i < curso->numEstudiantes; i++) {
            printf("\nEdición del estudiante %d:\n", i + 1);
            ingresarEstudiante(&curso->estudiantes[i]);
        }
    }

    printf("Curso actualizado exitosamente.\n");
}
