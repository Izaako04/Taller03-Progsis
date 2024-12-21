#include <stdio.h>
#include <string.h>
#include "Estudiante.h"

#define ARCHIVO_ESTUDIANTES "estudiantes.txt"

int verificarMatriculaUnica(const char *matricula) {
    FILE *archivo = fopen(ARCHIVO_ESTUDIANTES, "r");
    if (!archivo) return 1;

    char linea[300];
    while (fgets(linea, sizeof(linea), archivo)) {
        Estudiante estudiante;
        sscanf(linea, "%99[^-]-%99[^-]-%19[^-]-%49[^-]-%49[^-]-%d",
               estudiante.nombres, estudiante.apellidos, estudiante.matricula,
               estudiante.usuario, estudiante.clave, &estudiante.estado);
        if (strcmp(matricula, estudiante.matricula) == 0) {
            fclose(archivo);
            return 0;
        }
    }
    fclose(archivo);
    return 1;
}

int verificarEstudianteUnico(const char *usuario) {
    FILE *archivo = fopen(ARCHIVO_ESTUDIANTES, "r");
    if (!archivo) return 1;

    char linea[300];
    while (fgets(linea, sizeof(linea), archivo)) {
        Estudiante estudiante;
        sscanf(linea, "%99[^-]-%99[^-]-%19[^-]-%49[^-]-%49[^-]-%d",
               estudiante.nombres, estudiante.apellidos, estudiante.matricula,
               estudiante.usuario, estudiante.clave, &estudiante.estado);
        if (strcmp(usuario, estudiante.usuario) == 0) {
            fclose(archivo);
            return 0;
        }
    }
    fclose(archivo);
    return 1;
}

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
    estudiante.estado = 1;

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
        perror("Error al abrir el archivo de cursos");
        return 0;
    }

    char linea[500];
    while (fgets(linea, sizeof(linea), archivo)) {
        char codigoCurso[20], codigoMateria[20], cedulaProfesor[20], fechaInicio[11], fechaFin[11];
        char estudiantesMatriculas[500];

        if (sscanf(linea, "%19[^-]-%19[^-]-%19[^-]-%10[^-]-%10[^-]-%499[^\n]",
                   codigoCurso, codigoMateria, cedulaProfesor, fechaInicio, fechaFin, estudiantesMatriculas) != 6) {
            fprintf(stderr, "Error al leer línea del archivo cursos.txt: %s", linea);
            continue;
        }

        char *token = strtok(estudiantesMatriculas, "/");
        while (token != NULL) {
            if (strcmp(token, matricula) == 0) {
                fclose(archivo);
                return 1;
            }
            token = strtok(NULL, "/");
        }
    }

    fclose(archivo);
    return 0;
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

    
    while (fscanf(archivo, "%99[^-]-%99[^-]-%19[^-]-%49[^-]-%49[^-]-%d\n",
                  estudiantes[totalEstudiantes].nombres, estudiantes[totalEstudiantes].apellidos,
                  estudiantes[totalEstudiantes].matricula, estudiantes[totalEstudiantes].usuario,
                  estudiantes[totalEstudiantes].clave, &estudiantes[totalEstudiantes].estado) != EOF) {
        totalEstudiantes++;
    }

    printf("Estudiantes disponibles:\n");
    for (int i = 0; i < totalEstudiantes; i++) {
        printf("%d. %s %s (Matrícula: %s)\n", i + 1, estudiantes[i].nombres, estudiantes[i].apellidos,
               estudiantes[i].matricula);
    }

    printf("\nIngrese la matrícula del estudiante que desea editar: ");
    scanf(" %[^\n]", matricula);

    for (int i = 0; i < totalEstudiantes; i++) {
        if (strcmp(estudiantes[i].matricula, matricula) == 0) {
            encontrado = 1;

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

    fclose(archivo);
    archivo = fopen(ARCHIVO_ESTUDIANTES, "w");
    for (int i = 0; i < totalEstudiantes; i++) {
        fprintf(archivo, "%s-%s-%s-%s-%s-%d\n", estudiantes[i].nombres, estudiantes[i].apellidos,
                estudiantes[i].matricula, estudiantes[i].usuario, estudiantes[i].clave,
                estudiantes[i].estado);
    }

    fclose(archivo);
}
