#include <stdio.h>   // Para entrada/salida
#include <string.h>  // Para manejar cadenas
#include <stdbool.h> // Para usar tipo bool
#include <stdlib.h>  // Para exit()

// --------- Gramática G1 ---------
// S → 00 | 11 | 0 | 1
bool acepta_G1(char *cadena) {
    return strcmp(cadena, "00") == 0 || strcmp(cadena, "11") == 0 ||
           strcmp(cadena, "0") == 0 || strcmp(cadena, "1") == 0;
}

// --------- Gramática G2 ---------
// S → b | aS | ε
// (Lenguaje: cero o más 'a' seguidas de una 'b')
bool acepta_G2(char *cadena) {
    int len = strlen(cadena);
    if (len == 0) return false;            // Cadena vacía NO se acepta
    if (cadena[len-1] != 'b') return false; // Debe terminar en 'b'
    for (int i = 0; i < len-1; i++)        // El resto deben ser 'a'
        if (cadena[i] != 'a') return false;
    return true;
}

// --------- Gramática G3 ---------
// S → b | abS
// (Lenguaje: a^n b con n ≥ 0)
bool acepta_G3(char *cadena) {
    int len = strlen(cadena);
    if (len == 0) return false;
    if (cadena[len-1] != 'b') return false;
    for (int i = 0; i < len-1; i++)
        if (cadena[i] != 'a') return false;
    return true;
}

// --------- Gramática G4 ---------
// S → b | aS | ab
// (Lenguaje: a^n b con n ≥ 1)
bool acepta_G4(char *cadena) {
    int len = strlen(cadena);
    if (len < 2) return false;             // Mínimo "ab"
    if (cadena[len-1] != 'b') return false;
    for (int i = 0; i < len-1; i++)
        if (cadena[i] != 'a') return false;
    return true;
}

// --------- Gramática G5 ---------
// S → a | ab
// (Lenguaje: {a, ab})
bool acepta_G5(char *cadena) {
    return strcmp(cadena, "a") == 0 || strcmp(cadena, "ab") == 0;
}

// --------- Procesador ---------
// Recibe una gramática y un archivo
void procesar(bool (*gramatica)(char*), char *archivo) {
    FILE *f = fopen(archivo, "r");  // Abrir archivo
    if (!f) {
        printf("No se pudo abrir el archivo\n");
        return;
    }
    char cadena[100];  // Buffer para leer cada palabra
    while (fscanf(f, "%s", cadena) != EOF) {  // Leer hasta el final
        if (gramatica(cadena))
            printf("%s → acepta\n", cadena);
        else
            printf("%s → NO acepta\n", cadena);
    }
    fclose(f);  // Cerrar archivo
}

// --------- Programa Principal ---------
int main(int argc, char *argv[]) {
    // Se esperan 2 argumentos: gramática y archivo
    if (argc != 3) {
        printf("Uso: ./gramaticas <G1|G2|G3|G4|G5> <archivo.txt>\n");
        return 1;
    }

    char *opcion = argv[1];  // Gramática seleccionada
    char *archivo = argv[2]; // Archivo de prueba

    // Selección de gramática
    if (strcmp(opcion, "G1") == 0) procesar(acepta_G1, archivo);
    else if (strcmp(opcion, "G2") == 0) procesar(acepta_G2, archivo);
    else if (strcmp(opcion, "G3") == 0) procesar(acepta_G3, archivo);
    else if (strcmp(opcion, "G4") == 0) procesar(acepta_G4, archivo);
    else if (strcmp(opcion, "G5") == 0) procesar(acepta_G5, archivo);
    else printf("Gramática no válida. Usa: G1, G2, G3, G4 o G5\n");

    return 0;
}
