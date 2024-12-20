#include <stdio.h>
#include <string.h>
#include "Estudiante.h"

#define ARCHIVO_ESTUDIANTES "estudiantes.txt"

// Función para verificar si una matrícula ya existe
int verificarMatriculaUnica(const char *matricula) {
    FILE *archivo = fopen(ARCHIVO_ESTUDIANTES, "r");
    if (!archivo) return 1; // Si no existe el archivo, se asume que la matrícula es única

    char linea[300];
    while (fgets(linea, sizeof(linea), archivo)) {
        Estudiante estudiante;
        sscanf(linea, "%99[^-]-%99[^-]-%19[^-]-%49[^-]-%49[^-]-%d",
               estudiante.nombres, estudiante.apellidos, estudiante.matricula,
               estudiante.usuario, estudiante.clave, &estudiante.estado);
        if (strcmp(matricula, estudiante.matricula) == 0) {
            fclose(archivo);
            return 0; // Matrícula no es única
        }
    }
    fclose(archivo);
    return 1; // Matrícula es única
}

// Función para verificar si un usuario ya existe
int verificarEstudianteUnico(const char *usuario) {
    FILE *archivo = fopen(ARCHIVO_ESTUDIANTES, "r");
    if (!archivo) return 1; // Si no existe el archivo, se asume que el usuario es único

    char linea[300];
    while (fgets(linea, sizeof(linea), archivo)) {
        Estudiante estudiante;
        sscanf(linea, "%99[^-]-%99[^-]-%19[^-]-%49[^-]-%49[^-]-%d",
               estudiante.nombres, estudiante.apellidos, estudiante.matricula,
               estudiante.usuario, estudiante.clave, &estudiante.estado);
        if (strcmp(usuario, estudiante.usuario) == 0) {
            fclose(archivo);
            return 0; // Usuario no es único
        }
    }
    fclose(archivo);
    return 1; // Usuario es único
}

// Función para ingresar un estudiante
void ingresarEstudiante() {
    Estudiante estudiante;
    printf("Ingrese los nombres del estudiante: ");
    scanf(" %[^\n]", estudiante.nombres);
    printf("Ingrese los apellidos del estudiante: ");
    scanf(" %[^\n]", estudiante.apellidos);

    while (1) {
        printf("Ingrese el número de matrícula: ");
        scanf(" %[^\n]", estudiante.matricula);

        if (verificarMatriculaUnica(estudiante.matricula)) {
            break;
        } else {
            printf("Error: La matrícula ingresada ya existe. Intente nuevamente.\n");
        }
    }

    while (1) {
        printf("Ingrese el usuario: ");
        scanf(" %[^\n]", estudiante.usuario);

        if (verificarEstudianteUnico(estudiante.usuario)) {
            break;
        } else {
            printf("Error: El usuario ingresado ya existe. Intente nuevamente.\n");
        }
    }

    printf("Ingrese la clave: ");
    scanf(" %[^\n]", estudiante.clave);
    estudiante.estado = 1; // Estado inicial activo

    // Guardar el estudiante en el archivo
    FILE *archivo = fopen(ARCHIVO_ESTUDIANTES, "a");
    if (!archivo) {
        printf("Error al abrir el archivo para guardar el estudiante.\n");
        return;
    }
    fprintf(archivo, "%s-%s-%s-%s-%s-%d\n", estudiante.nombres, estudiante.apellidos,
            estudiante.matricula, estudiante.usuario, estudiante.clave, estudiante.estado);
    fclose(archivo);

    printf("Estudiante registrado exitosamente con estado Activo.\n");
}

int estaCursandoCurso(const char *matricula) {
    FILE *archivo = fopen("cursos.txt", "r");
    if (!archivo) {
        printf("Error al abrir el archivo de cursos.\n");
        return 0; // Asumimos que no tiene curso en proceso si no se puede acceder al archivo
    }

    char linea[500];
    while (fgets(linea, sizeof(linea), archivo)) {
        char codigoCurso[20], codigoMateria[20], cedulaProfesor[20], fechaInicio[11], fechaFin[11];
        char estudiantesMatriculas[500]; // Cadena para almacenar las matrículas separadas por `/`

        // Leer los datos principales del curso
        if (sscanf(linea, "%19[^-]-%19[^-]-%19[^-]-%10[^-]-%10[^-]-%499[^\n]",
                   codigoCurso, codigoMateria, cedulaProfesor, fechaInicio, fechaFin, estudiantesMatriculas) != 6) {
            continue; // Pasar a la siguiente línea si el formato no coincide
        }

        // Si hay solo una matrícula (sin `/`), comparar directamente
        if (strcmp(estudiantesMatriculas, matricula) == 0) {
            fclose(archivo);
            return 1; // Estudiante encontrado en un curso
        }

        // Separar las matrículas de estudiantes si hay múltiples
        char *token = strtok(estudiantesMatriculas, "/");
        while (token != NULL) {
            if (strcmp(token, matricula) == 0) {
                fclose(archivo);
                return 1; // Estudiante encontrado en un curso
            }
            token = strtok(NULL, "/");
        }
    }

    fclose(archivo);
    return 0; // No se encontró ningún curso asociado al estudiante
}



void editarEstudiante() {
    char matricula[20];
    int encontrado = 0;

    FILE *archivo = fopen(ARCHIVO_ESTUDIANTES, "r+");
    if (!archivo) {
        printf("Error al abrir el archivo de estudiantes.\n");
        return;
    }

    Estudiante estudiantes[100];
    int totalEstudiantes = 0;

    // Leer estudiantes del archivo
    while (fscanf(archivo, "%99[^-]-%99[^-]-%19[^-]-%49[^-]-%49[^-]-%d\n",
                  estudiantes[totalEstudiantes].nombres, estudiantes[totalEstudiantes].apellidos,
                  estudiantes[totalEstudiantes].matricula, estudiantes[totalEstudiantes].usuario,
                  estudiantes[totalEstudiantes].clave, &estudiantes[totalEstudiantes].estado) != EOF) {
        totalEstudiantes++;
    }

    // Mostrar estudiantes
    printf("Estudiantes disponibles:\n");
    for (int i = 0; i < totalEstudiantes; i++) {
        printf("%d. %s %s (Matrícula: %s)\n", i + 1, estudiantes[i].nombres, estudiantes[i].apellidos,
               estudiantes[i].matricula);
    }

    // Solicitar matrícula del estudiante a editar
    printf("\nIngrese la matrícula del estudiante que desea editar: ");
    scanf(" %[^\n]", matricula);

    // Buscar estudiante
    for (int i = 0; i < totalEstudiantes; i++) {
        if (strcmp(estudiantes[i].matricula, matricula) == 0) {
            encontrado = 1;

            // Verificar si el estudiante tiene curso en proceso
            if (estaCursandoCurso(matricula)) {
                printf("No se puede inactivar el estudiante porque tiene un curso en proceso.\n");
            } else {
                printf("Estado actual del estudiante: %s\n", estudiantes[i].estado ? "Activo" : "Inactivo");
                printf("¿Desea cambiar el estado del estudiante? (1 para Activo, 0 para Inactivo): ");
                int nuevoEstado;
                if (scanf("%d", &nuevoEstado) == 1 && (nuevoEstado == 0 || nuevoEstado == 1)) {
                    estudiantes[i].estado = nuevoEstado;
                    printf("Estado actualizado a: %s\n", estudiantes[i].estado ? "Activo" : "Inactivo");
                } else {
                    printf("Entrada inválida. El estado no se cambió.\n");
                }
            }

            // Cambiar clave del estudiante
            printf("¿Desea cambiar la clave del estudiante? (1 para Sí, 0 para No): ");
            int cambiarClave;
            if (scanf("%d", &cambiarClave) == 1 && cambiarClave == 1) {
                printf("Ingrese la nueva clave: ");
                scanf(" %[^\n]", estudiantes[i].clave);
                printf("Clave actualizada correctamente.\n");
            } else {
                printf("Clave no modificada.\n");
            }

            break;
        }
    }

    if (!encontrado) {
        printf("Estudiante con matrícula %s no encontrado.\n", matricula);
    }

    // Reescribir archivo con los cambios
    fclose(archivo);
    archivo = fopen(ARCHIVO_ESTUDIANTES, "w");
    for (int i = 0; i < totalEstudiantes; i++) {
        fprintf(archivo, "%s-%s-%s-%s-%s-%d\n", estudiantes[i].nombres, estudiantes[i].apellidos,
                estudiantes[i].matricula, estudiantes[i].usuario, estudiantes[i].clave,
                estudiantes[i].estado);
    }

    fclose(archivo);
}
