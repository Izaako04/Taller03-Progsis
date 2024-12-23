#include <stdio.h>
#include "materia.h"
#include "estudiante.h"
#include "profesor.h"
#include "curso.h"

#include <stdio.h>
#include <string.h>
#include "curso.h"

void mostrarMenuPrincipal() {
    printf("\nMenu de opciones:\n");
    printf("a. Materia\n");
    printf("b. Estudiante\n");
    printf("c. Profesor\n");
    printf("d. Curso\n");
    printf("e. Salir\n");
    printf("Seleccione una opción: ");
}

void mostrarSubMenu(const char *titulo) {
    printf("\n%s:\n", titulo);
    printf("1. Crear\n");
    printf("2. Editar\n");
    printf("Seleccione una opción: ");
}

int main() {
    char opcionPrincipal;
    char opcionSubmenu;

    do {
        mostrarMenuPrincipal();
        scanf(" %c", &opcionPrincipal);

        switch (opcionPrincipal) {
            case 'a':
                mostrarSubMenu("Materia");
                scanf(" %c", &opcionSubmenu);

                if (opcionSubmenu == '1') {
                    ingresarMateria();
                } else if (opcionSubmenu == '2') {
                    cambiarEstadoMateria();
                } else {
                    printf("Opción inválida.\n");
                }
                break;

            case 'b':
                mostrarSubMenu("Estudiante");
                scanf(" %c", &opcionSubmenu);

                if (opcionSubmenu == '1') {
                    ingresarEstudiante();
                } else if (opcionSubmenu == '2') {
                    editarEstudiante();
                } else {
                    printf("Opción inválida.\n");
                }
                break;

            case 'c':
                mostrarSubMenu("Profesor");
                scanf(" %c", &opcionSubmenu);

                if (opcionSubmenu == '1') {
                    ingresarProfesor();
                } else if (opcionSubmenu == '2') {
                    editarProfesor();
                } else {
                    printf("Opción inválida.\n");
                }
                break;

            case 'd':
                mostrarSubMenu("Curso");
                scanf(" %c", &opcionSubmenu);

                if (opcionSubmenu == '1') {
                    ingresarCurso();
                } else if (opcionSubmenu == '2') {
                    editarCurso();
                } else {
                    printf("Opción inválida.\n");
                }
                break;

            case 'e':
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opción inválida. Intente nuevamente.\n");
        }
    } while (opcionPrincipal != 'e');

    return 0;
}