#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Curso.h"

#define ARCHIVO_CURSOS "cursos.txt"

int verificarCodigoCurso(const char *codigo) {
    FILE *archivo = fopen(ARCHIVO_CURSOS, "r");
    if (!archivo) return 1;
    char linea[500];
    while (fgets(linea, sizeof(linea), archivo)) {
        char codigoExistente[20];
        sscanf(linea, "%19[^-]", codigoExistente);
        if (strcmp(codigo, codigoExistente) == 0) {
            fclose(archivo);
            return 0;
        }
    }
    fclose(archivo);
    return 1;
}

#include <stdio.h>
#include <string.h>

int validarFechas(const char *fechaInicio, const char *fechaFin) {
    int anioInicio, mesInicio, diaInicio;
    int anioFin, mesFin, diaFin;

    if (sscanf(fechaInicio, "%d-%d-%d", &anioInicio, &mesInicio, &diaInicio) != 3 ||
        sscanf(fechaFin, "%d-%d-%d", &anioFin, &mesFin, &diaFin) != 3) {
        return 0;
    }

    if (anioInicio > anioFin) return 0;
    if (anioInicio == anioFin && mesInicio > mesFin) return 0;
    if (anioInicio == anioFin && mesInicio == mesFin && diaInicio > diaFin) return 0;

    return 1;
}

void ingresarCurso() {
    Curso curso;

    printf("Ingrese el código del curso: ");
    scanf(" %[^\n]", curso.codigo);

    printf("Ingrese el código de la materia: ");
    char codigoMateria[20];
    scanf(" %[^\n]", codigoMateria);

    FILE *archivoMaterias = fopen("materias.txt", "r");
    if (!archivoMaterias) {
        printf("Error al abrir el archivo de materias.\n");
        return;
    }

    int materiaEncontrada = 0;
    char linea[300];
    while (fgets(linea, sizeof(linea), archivoMaterias)) {
        char codigoMateriaArchivo[20];
        sscanf(linea, "%*[^-]-%19[^-]", codigoMateriaArchivo);
        if (strcmp(codigoMateriaArchivo, codigoMateria) == 0) {
            materiaEncontrada = 1;
            break;
        }
    }
    fclose(archivoMaterias);

    if (!materiaEncontrada) {
        printf("Materia con código %s no encontrada.\n", codigoMateria);
        return;
    }

    printf("Ingrese la cédula del profesor responsable: ");
    char cedulaProfesor[20];
    scanf(" %[^\n]", cedulaProfesor);

    FILE *archivoProfesores = fopen("profesores.txt", "r");
    if (!archivoProfesores) {
        printf("Error al abrir el archivo de profesores.\n");
        return;
    }

    int profesorEncontrado = 0;
    while (fgets(linea, sizeof(linea), archivoProfesores)) {
        char cedulaProfesorArchivo[20];
        sscanf(linea, "%*[^-]-%*[^-]-%19[^-]", cedulaProfesorArchivo);
        if (strcmp(cedulaProfesorArchivo, cedulaProfesor) == 0) {
            profesorEncontrado = 1;
            break;
        }
    }
    fclose(archivoProfesores);

    if (!profesorEncontrado) {
        printf("Profesor con cédula %s no encontrado.\n", cedulaProfesor);
        return;
    }

    while (1) {
        printf("Ingrese la fecha de inicio (YYYY-MM-DD): ");
        scanf(" %[^\n]", curso.fechaInicio);
        printf("Ingrese la fecha de fin (YYYY-MM-DD): ");
        scanf(" %[^\n]", curso.fechaFin);

        if (validarFechas(curso.fechaInicio, curso.fechaFin)) {
            break;
        } else {
            printf("Error: La fecha de inicio no puede ser mayor que la fecha de fin. Intente nuevamente.\n");
        }
    }

    printf("Ingrese la cantidad de estudiantes a registrar (máximo 30): ");
    if (scanf("%d", &curso.numEstudiantes) != 1 || curso.numEstudiantes < 1 || curso.numEstudiantes > 30) {
        fprintf(stderr, "Error: Cantidad de estudiantes inválida. No se registrará el curso.\n");
        return;
    }

    char matriculas[30][20];
    for (int i = 0; i < curso.numEstudiantes; i++) {
        printf("\nRegistro del estudiante %d (ingrese matrícula): ", i + 1);
        char matriculaEstudiante[20];
        scanf(" %[^\n]", matriculaEstudiante);

        FILE *archivoEstudiantes = fopen("estudiantes.txt", "r");
        if (!archivoEstudiantes) {
            printf("Error al abrir el archivo de estudiantes.\n");
            return;
        }

        int estudianteEncontrado = 0;
        while (fgets(linea, sizeof(linea), archivoEstudiantes)) {
            char matriculaArchivo[20];
            sscanf(linea, "%*[^-]-%*[^-]-%19[^-]", matriculaArchivo);
            if (strcmp(matriculaArchivo, matriculaEstudiante) == 0) {
                estudianteEncontrado = 1;
                break;
            }
        }
        fclose(archivoEstudiantes);

        if (!estudianteEncontrado) {
            printf("Estudiante con matrícula %s no encontrado. Registro cancelado.\n", matriculaEstudiante);
            return;
        }

        strcpy(matriculas[i], matriculaEstudiante);
    }

    FILE *archivoCursos = fopen("cursos.txt", "a");
    if (!archivoCursos) {
        printf("Error al abrir el archivo de cursos.\n");
        return;
    }

    fprintf(archivoCursos, "%s-%s-%s-%s-%s-", curso.codigo, codigoMateria, cedulaProfesor, curso.fechaInicio, curso.fechaFin);

    for (int i = 0; i < curso.numEstudiantes; i++) {
        fprintf(archivoCursos, "%s%s", i == 0 ? "" : "/", matriculas[i]);
    }
    fprintf(archivoCursos, "\n");

    fclose(archivoCursos);
    printf("Curso registrado exitosamente.\n");
}


void editarCurso() {
    char codigo[20];
    int encontrado = 0;
    Curso cursos[100];
    int totalCursos = 0;

    FILE *archivo = fopen("cursos.txt", "r");
    if (!archivo) {
        printf("Error al abrir el archivo de cursos.\n");
        return;
    }

    char linea[500];
    while (fgets(linea, sizeof(linea), archivo)) {
        char estudiantesMatriculas[500];
        if (sscanf(linea, "%19[^-]-%19[^-]-%19[^-]-%10[^-]-%10[^-]-%499[^\n]",
                   cursos[totalCursos].codigo, cursos[totalCursos].materia,
                   cursos[totalCursos].profesor, cursos[totalCursos].fechaInicio,
                   cursos[totalCursos].fechaFin, estudiantesMatriculas) != 6) {
            printf("Error al leer los datos del curso en la línea: %s\n", linea);
            continue;
        }

        cursos[totalCursos].numEstudiantes = 0;
        char *token = strtok(estudiantesMatriculas, "/");
        while (token != NULL && cursos[totalCursos].numEstudiantes < 30) {
            strcpy(cursos[totalCursos].estudiantes[cursos[totalCursos].numEstudiantes].matricula, token);
            cursos[totalCursos].numEstudiantes++;
            token = strtok(NULL, "/");
        }
        totalCursos++;
    }
    fclose(archivo);

    printf("\n------------------------------------------------------------\n");
    for (int i = 0; i < totalCursos; i++) {
        printf("Curso #%d\n", i + 1);
        printf("Código del Curso     : %s\n", cursos[i].codigo);
        printf("Código de la Materia : %s\n", cursos[i].materia);
        printf("Cédula del Profesor  : %s\n", cursos[i].profesor);
        printf("Fecha de Inicio      : %s\n", cursos[i].fechaInicio);
        printf("Fecha de Fin         : %s\n", cursos[i].fechaFin);
        printf("Estudiantes Registrados:\n");

        if (cursos[i].numEstudiantes > 0) {
            for (int j = 0; j < cursos[i].numEstudiantes; j++) {
                printf("  - Matrícula: %s\n", cursos[i].estudiantes[j].matricula);
            }
        } else {
            printf("  Ningún estudiante registrado.\n");
        }
        printf("------------------------------------------------------------\n");
    }

    printf("\nIngrese el código del curso que desea editar: ");
    scanf(" %[^\n]", codigo);

    for (int i = 0; i < totalCursos; i++) {
        if (strcmp(cursos[i].codigo, codigo) == 0) {
            encontrado = 1;

            printf("\nEditando Curso:\n");
            printf("Código del Curso     : %s\n", cursos[i].codigo);
            printf("Código de la Materia : %s\n", cursos[i].materia);
            printf("Cédula del Profesor  : %s\n", cursos[i].profesor);
            printf("Fecha de Inicio      : %s\n", cursos[i].fechaInicio);
            printf("Fecha de Fin         : %s\n", cursos[i].fechaFin);

            char opcion;
            char nuevaFecha[11];

            printf("\n¿Desea modificar la fecha de inicio? (s/n): ");
            scanf(" %c", &opcion);
            if (opcion == 's' || opcion == 'S') {
                while (1) {
                    printf("Ingrese la nueva fecha de inicio (YYYY-MM-DD): ");
                    scanf(" %[^\n]", nuevaFecha);
                    if (validarFechas(nuevaFecha, cursos[i].fechaFin)) {
                        strcpy(cursos[i].fechaInicio, nuevaFecha);
                        break;
                    } else {
                        printf("Error: Fecha de inicio inválida o posterior a la fecha de fin. Intente nuevamente.\n");
                    }
                }
            }

            printf("\n¿Desea modificar la fecha de fin? (s/n): ");
            scanf(" %c", &opcion);
            if (opcion == 's' || opcion == 'S') {
                while (1) {
                    printf("Ingrese la nueva fecha de fin (YYYY-MM-DD): ");
                    scanf(" %[^\n]", nuevaFecha);
                    if (validarFechas(cursos[i].fechaInicio, nuevaFecha)) {
                        strcpy(cursos[i].fechaFin, nuevaFecha);
                        break;
                    } else {
                        printf("Error: Fecha de fin inválida o anterior a la fecha de inicio. Intente nuevamente.\n");
                    }
                }
            }
            break;
        }
    }

    if (!encontrado) {
        printf("\nCurso con código %s no encontrado.\n", codigo);
        return;
    }

    archivo = fopen("cursos.txt", "w");
    if (!archivo) {
        printf("Error al abrir el archivo para escritura.\n");
        return;
    }

    for (int i = 0; i < totalCursos; i++) {
        // Formato de escritura corregido (usar %s para las fechas):
        fprintf(archivo, "%s-%s-%s-%s-%s-",
                cursos[i].codigo, cursos[i].materia, cursos[i].profesor,
                cursos[i].fechaInicio, cursos[i].fechaFin);

        for (int j = 0; j < cursos[i].numEstudiantes; j++) {
            fprintf(archivo, "%s%s", j == 0 ? "" : "/", cursos[i].estudiantes[j].matricula);
        }
        fprintf(archivo, "\n");
    }
    fclose(archivo);

    printf("\nCurso actualizado exitosamente.\n");
}
