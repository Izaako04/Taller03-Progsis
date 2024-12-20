#include <stdio.h>
#include <string.h>
#include "Materia.h"
#include "Curso.h"

#define ARCHIVO_MATERIAS "materias.txt"

// Función para verificar si un código ya existe
int verificarCodigoMateria(const char *codigo) {
    FILE *archivo = fopen(ARCHIVO_MATERIAS, "r");
    if (!archivo) return 1; // Si no existe el archivo, el código es único

    char linea[200];
    while (fgets(linea, sizeof(linea), archivo)) {
        Materia materia;
        sscanf(linea, "%99[^-]-%19[^-]-%d",
               materia.nombre, materia.codigo, &materia.estado);
        if (strcmp(codigo, materia.codigo) == 0) {
            fclose(archivo);
            return 0; // Código no es único
        }
    }
    fclose(archivo);
    return 1; // Código es único
}

// Función para ingresar los datos de una materia
void ingresarMateria() {
    Materia materia;

    printf("Ingrese el nombre de la materia: ");
    scanf(" %[^\n]", materia.nombre);

    while (1) {
        printf("Ingrese el código de la materia: ");
        scanf(" %[^\n]", materia.codigo);

        if (verificarCodigoMateria(materia.codigo)) {
            break;
        } else {
            printf("Error: El código ingresado ya existe. Intente nuevamente.\n");
        }
    }

    materia.estado = 1; // Estado inicial activo

    // Guardar en el archivo
    FILE *archivo = fopen(ARCHIVO_MATERIAS, "a");
    if (!archivo) {
        printf("Error al abrir el archivo de materias.\n");
        return;
    }
    fprintf(archivo, "%s-%s-%d\n", materia.nombre, materia.codigo, materia.estado);
    fclose(archivo);

    printf("Materia registrada con estado Activo.\n");
}

int tieneCursoEnProceso(const char *codigoMateria) {
    FILE *archivo = fopen("cursos.txt", "r");
    if (!archivo) {
        printf("Error al abrir el archivo de cursos.\n");
        return 0; // Asumimos que no hay cursos en proceso si no se puede acceder al archivo
    }

    char linea[500];
    while (fgets(linea, sizeof(linea), archivo)) {
        char codigoCurso[20], materia[20], cedulaProfesor[20], fechaInicio[11], fechaFin[11];
        char estudiantesMatriculas[500]; // Cadena para almacenar las matrículas de estudiantes

        // Leer los datos principales del curso
        if (sscanf(linea, "%19[^-]-%19[^-]-%19[^-]-%10[^-]-%10[^-]-%499[^\n]", 
                   codigoCurso, materia, cedulaProfesor, fechaInicio, fechaFin, estudiantesMatriculas) != 6) {
            continue; // Pasar a la siguiente línea si el formato no coincide
        }

        // Comparar el código de la materia con el proporcionado
        if (strcmp(materia, codigoMateria) == 0) {
            fclose(archivo);
            return 1; // Encontramos un curso asociado a esta materia
        }
    }

    fclose(archivo);
    return 0; // No se encontró ningún curso asociado a esta materia
}


void cambiarEstadoMateria() {
    FILE *archivo = fopen(ARCHIVO_MATERIAS, "r+");
    if (!archivo) {
        printf("Error al abrir el archivo de materias.\n");
        return;
    }

    Materia materias[100];
    int totalMaterias = 0;
    char linea[200];

    // Leer materias del archivo
    while (fgets(linea, sizeof(linea), archivo)) {
        sscanf(linea, "%99[^-]-%19[^-]-%d",
               materias[totalMaterias].nombre,
               materias[totalMaterias].codigo,
               &materias[totalMaterias].estado);
        totalMaterias++;
    }

    if (totalMaterias == 0) {
        printf("No hay materias registradas.\n");
        fclose(archivo);
        return;
    }

    // Mostrar menú de materias
    printf("\nMaterias disponibles:\n");
    for (int i = 0; i < totalMaterias; i++) {
        printf("Nombre: %s, Código: %s, Estado: %s\n",
               materias[i].nombre, materias[i].codigo,
               materias[i].estado ? "Activo" : "Inactivo");
    }

    // Solicitar el código de la materia a editar
    char codigoMateria[20];
    printf("\nIngrese el código de la materia que desea editar: ");
    scanf(" %[^\n]", codigoMateria);

    // Buscar la materia por código
    int indice = -1;
    for (int i = 0; i < totalMaterias; i++) {
        if (strcmp(materias[i].codigo, codigoMateria) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Materia con código %s no encontrada.\n", codigoMateria);
        fclose(archivo);
        return;
    }

    // Verificar si la materia está en curso
    if (tieneCursoEnProceso(materias[indice].codigo)) {
        printf("No se puede inactivar la materia porque tiene un curso en proceso.\n");
        fclose(archivo);
        return;
    }

    // Cambiar estado
    printf("El estado actual es: %s\n", materias[indice].estado ? "Activo" : "Inactivo");
    printf("¿Desea cambiar el estado? (1 para Activo, 0 para Inactivo): ");
    int nuevoEstado;
    if (scanf("%d", &nuevoEstado) == 1 && (nuevoEstado == 0 || nuevoEstado == 1)) {
        materias[indice].estado = nuevoEstado;
        printf("Estado actualizado a: %s\n", materias[indice].estado ? "Activo" : "Inactivo");
    } else {
        printf("Entrada inválida. El estado no se cambió.\n");
    }

    // Reescribir archivo con los cambios
    freopen(ARCHIVO_MATERIAS, "w", archivo);
    for (int i = 0; i < totalMaterias; i++) {
        fprintf(archivo, "%s-%s-%d\n", materias[i].nombre, materias[i].codigo, materias[i].estado);
    }

    fclose(archivo);
    printf("Estado de la materia actualizado correctamente.\n");
}
