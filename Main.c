#include <stdio.h>
#include "materia.h"
#include "estudiante.h"
#include "profesor.h"
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
            case 'a': // Materia
                mostrarSubMenu("Materia");
                scanf(" %c", &opcionSubmenu);

                if (opcionSubmenu == '1') {
                    Materia materia;
                    ingresarMateria(&materia);
                } else if (opcionSubmenu == '2') {
                    Materia materia;
                    // Aquí puedes cargar los datos existentes de la materia, si corresponde.
                    int cursoEnProceso = 0; // Cambiar según tu lógica
                    cambiarEstadoMateria(&materia, cursoEnProceso);
                } else {
                    printf("Opción inválida.\n");
                }
                break;

            case 'b': // Estudiante
                mostrarSubMenu("Estudiante");
                scanf(" %c", &opcionSubmenu);

                if (opcionSubmenu == '1') {
                    Estudiante estudiante;
                    ingresarEstudiante(&estudiante);
                } else if (opcionSubmenu == '2') {
                    Estudiante estudiante;
                    // Aquí puedes cargar los datos existentes del estudiante, si corresponde.
                    int cursoEnProceso = 0; // Cambiar según tu lógica
                    editarEstudiante(&estudiante, cursoEnProceso);
                } else {
                    printf("Opción inválida.\n");
                }
                break;

            case 'c': // Profesor
                mostrarSubMenu("Profesor");
                scanf(" %c", &opcionSubmenu);

                if (opcionSubmenu == '1') {
                    Profesor profesor;
                    ingresarProfesor(&profesor);
                } else if (opcionSubmenu == '2') {
                    Profesor profesor;
                    // Aquí puedes cargar los datos existentes del profesor, si corresponde.
                    int cursoEnProceso = 0; // Cambiar según tu lógica
                    editarProfesor(&profesor, cursoEnProceso);
                } else {
                    printf("Opción inválida.\n");
                }
                break;

            case 'd': // Curso
                mostrarSubMenu("Curso");
                scanf(" %c", &opcionSubmenu);

                if (opcionSubmenu == '1') {
                    Curso curso;
                    ingresarCurso(&curso);
                } else if (opcionSubmenu == '2') {
                    Curso curso;
                    // Aquí puedes cargar los datos existentes del curso, si corresponde.
                    editarCurso(&curso);
                } else {
                    printf("Opción inválida.\n");
                }
                break;

            case 'e': // Salir
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opción inválida. Intente nuevamente.\n");
        }
    } while (opcionPrincipal != 'e');

    return 0;
}
