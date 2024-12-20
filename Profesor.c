#include <stdio.h>
#include <string.h>
#include "Profesor.h"
#include "Curso.h"

#define ARCHIVO_PROFESORES "profesores.txt"

// Función para verificar si una cédula ya existe
int verificarCedulaUnica(const char *cedula) {
    FILE *archivo = fopen(ARCHIVO_PROFESORES, "r");
    if (!archivo) return 1; // Si no existe el archivo, la cédula es única

    char linea[300];
    while (fgets(linea, sizeof(linea), archivo)) {
        Profesor profesor;
        sscanf(linea, "%99[^-]-%99[^-]-%19[^-]-%49[^-]-%49[^-]-%d",
               profesor.nombres, profesor.apellidos, profesor.cedula,
               profesor.usuario, profesor.clave, &profesor.estado);
        if (strcmp(cedula, profesor.cedula) == 0) {
            fclose(archivo);
            return 0; // Cédula no es única
        }
    }
    fclose(archivo);
    return 1; // Cédula es única
}

// Función para verificar si un usuario ya existe
int verificarProfesorUnico(const char *usuario) {
    FILE *archivo = fopen(ARCHIVO_PROFESORES, "r");
    if (!archivo) return 1; // Si no existe el archivo, el usuario es único

    char linea[300];
    while (fgets(linea, sizeof(linea), archivo)) {
        Profesor profesor;
        sscanf(linea, "%99[^-]-%99[^-]-%19[^-]-%49[^-]-%49[^-]-%d",
               profesor.nombres, profesor.apellidos, profesor.cedula,
               profesor.usuario, profesor.clave, &profesor.estado);
        if (strcmp(usuario, profesor.usuario) == 0) {
            fclose(archivo);
            return 0; // Usuario no es único
        }
    }
    fclose(archivo);
    return 1; // Usuario es único
}

void ingresarProfesor() {
    Profesor profesor;
    printf("Ingrese los nombres del profesor: ");
    scanf(" %[^\n]", profesor.nombres);
    printf("Ingrese los apellidos del profesor: ");
    scanf(" %[^\n]", profesor.apellidos);

    // Validar unicidad de cédula
    while (1) {
        printf("Ingrese la cédula del profesor: ");
        scanf(" %[^\n]", profesor.cedula);

        if (verificarCedulaUnica(profesor.cedula)) {
            break;
        } else {
            printf("Error: La cédula ingresada ya existe. Intente nuevamente.\n");
        }
    }

    // Validar unicidad de usuario
    while (1) {
        printf("Ingrese el usuario del profesor: ");
        scanf(" %[^\n]", profesor.usuario);

        if (verificarProfesorUnico(profesor.usuario)) {
            break;
        } else {
            printf("Error: El usuario ingresado ya existe. Intente nuevamente.\n");
        }
    }

    printf("Ingrese la clave: ");
    scanf(" %[^\n]", profesor.clave);
    profesor.estado = 1; // Estado inicial activo

    // Registro de materias
    printf("Ingrese la cantidad de materias que puede dictar (máximo 5): ");
    if (scanf("%d", &profesor.num_materias) != 1 || profesor.num_materias < 1 || profesor.num_materias > 5) {
        fprintf(stderr, "Error: Cantidad de materias inválida. Se establecerá en 1.\n");
        profesor.num_materias = 1;
    }

    char codigosMaterias[5][20]; // Para almacenar los códigos de materias
    for (int i = 0; i < profesor.num_materias; i++) {
        printf("Ingrese el código de la materia %d: ", i + 1);
        char codigoMateria[20];
        scanf(" %[^\n]", codigoMateria);

        // Validar existencia de la materia en materias.txt
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
            if (strcmp(codigoMateria, codigoMateriaArchivo) == 0) {
                materiaEncontrada = 1;
                break;
            }
        }
        fclose(archivoMaterias);

        if (!materiaEncontrada) {
            printf("Error: La materia con código %s no está registrada. Registro del profesor cancelado.\n", codigoMateria);
            return;
        }

        strcpy(codigosMaterias[i], codigoMateria);
    }

    // Guardar en el archivo
    FILE *archivo = fopen("profesores.txt", "a");
    if (!archivo) {
        printf("Error al abrir el archivo de profesores.\n");
        return;
    }

    // Guardar los datos principales del profesor
    fprintf(archivo, "%s-%s-%s-%s-%s-%d",
            profesor.nombres, profesor.apellidos, profesor.cedula,
            profesor.usuario, profesor.clave, profesor.estado);

    // Guardar los códigos de las materias
    for (int i = 0; i < profesor.num_materias; i++) {
        fprintf(archivo, "%s%s", i == 0 ? "-" : "/", codigosMaterias[i]);
    }
    fprintf(archivo, "\n");
    fclose(archivo);

    printf("Profesor registrado con estado Activo.\n");
}

int estaDandoCurso(const char *cedulaProfesor) {
    FILE *archivo = fopen("cursos.txt", "r");
    if (!archivo) {
        printf("Error al abrir el archivo de cursos.\n");
        return 0; // Asumimos que no hay cursos en proceso si no se puede acceder al archivo
    }

    char linea[500];
    while (fgets(linea, sizeof(linea), archivo)) {
        char codigoCurso[20], codigoMateria[20], cedula[20], fechaInicio[11], fechaFin[11];
        char estudiantesMatriculas[500]; // Para leer el resto de la línea con matrículas

        // Leer los datos principales del curso
        if (sscanf(linea, "%19[^-]-%19[^-]-%19[^-]-%10[^-]-%10[^-]-%499[^\n]", 
                   codigoCurso, codigoMateria, cedula, fechaInicio, fechaFin, estudiantesMatriculas) != 6) {
            continue; // Pasar a la siguiente línea si el formato no coincide
        }

        // Comparar la cédula del profesor con la proporcionada
        if (strcmp(cedula, cedulaProfesor) == 0) {
            fclose(archivo);
            return 1; // Encontramos un curso asociado a este profesor
        }
    }

    fclose(archivo);
    return 0; // No se encontró ningún curso asociado a este profesor
}



void editarProfesor() {
    FILE *archivo = fopen(ARCHIVO_PROFESORES, "r+");
    if (!archivo) {
        printf("Error al abrir el archivo de profesores.\n");
        return;
    }

    Profesor profesores[100];
    int totalProfesores = 0;

    // Leer profesores del archivo
    char linea[300];
    while (fgets(linea, sizeof(linea), archivo)) {
        sscanf(linea, "%99[^-]-%99[^-]-%19[^-]-%49[^-]-%49[^-]-%d",
               profesores[totalProfesores].nombres, profesores[totalProfesores].apellidos,
               profesores[totalProfesores].cedula, profesores[totalProfesores].usuario,
               profesores[totalProfesores].clave, &profesores[totalProfesores].estado);
        totalProfesores++;
    }

    if (totalProfesores == 0) {
        printf("No hay profesores registrados.\n");
        fclose(archivo);
        return;
    }

    // Mostrar menú de profesores
    printf("\nProfesores disponibles:\n");
    for (int i = 0; i < totalProfesores; i++) {
        printf("Cédula: %s, Nombre: %s %s, Estado: %s\n",
               profesores[i].cedula, profesores[i].nombres, profesores[i].apellidos,
               profesores[i].estado ? "Activo" : "Inactivo");
    }

    // Solicitar cédula del profesor a editar
    char cedula[20];
    printf("\nIngrese la cédula del profesor que desea editar: ");
    scanf(" %[^\n]", cedula);

    // Buscar profesor por cédula
    int indice = -1;
    for (int i = 0; i < totalProfesores; i++) {
        if (strcmp(profesores[i].cedula, cedula) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Profesor con cédula %s no encontrado.\n", cedula);
        fclose(archivo);
        return;
    }

    // Verificar si el profesor tiene un curso en proceso
    if (estaDandoCurso(profesores[indice].cedula)) {
        printf("No se puede inactivar al profesor porque tiene un curso en proceso.\n");
        fclose(archivo);
        return;
    }

    // Cambiar estado del profesor
    printf("Estado actual del profesor: %s\n", profesores[indice].estado ? "Activo" : "Inactivo");
    printf("¿Desea cambiar el estado del profesor? (1 para Activo, 0 para Inactivo): ");
    int nuevoEstado;
    if (scanf("%d", &nuevoEstado) == 1 && (nuevoEstado == 0 || nuevoEstado == 1)) {
        profesores[indice].estado = nuevoEstado;
        printf("Estado actualizado a: %s\n", profesores[indice].estado ? "Activo" : "Inactivo");
    } else {
        printf("Entrada inválida. El estado no se cambió.\n");
    }

    // Cambiar clave del profesor
    printf("¿Desea cambiar la clave del profesor? (1 para Sí, 0 para No): ");
    int cambiarClave;
    if (scanf("%d", &cambiarClave) == 1 && cambiarClave == 1) {
        printf("Ingrese la nueva clave: ");
        scanf(" %[^\n]", profesores[indice].clave);
        printf("Clave actualizada correctamente.\n");
    } else {
        printf("Clave no modificada.\n");
    }

    // Reescribir archivo con los cambios
    freopen(ARCHIVO_PROFESORES, "w", archivo);
    for (int i = 0; i < totalProfesores; i++) {
        fprintf(archivo, "%s-%s-%s-%s-%s-%d\n", profesores[i].nombres, profesores[i].apellidos,
                profesores[i].cedula, profesores[i].usuario, profesores[i].clave, profesores[i].estado);
    }

    fclose(archivo);
    printf("Profesor actualizado exitosamente.\n");
}
