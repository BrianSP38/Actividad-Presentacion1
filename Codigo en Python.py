import sys   # Para leer argumentos desde la terminal

# --------- Gramática G1 ---------
# S → 00 | 11 | 0 | 1
def acepta_G1(cadena):
    return cadena in ["00", "11", "0", "1"]

# --------- Gramática G2 ---------
# S → b | aS | ε
# (Lenguaje: cero o más 'a' seguidas de una 'b')
def acepta_G2(cadena):
    return cadena.endswith("b") and set(cadena[:-1]) <= {"a"}

# --------- Gramática G3 ---------
# S → b | abS
# (Lenguaje: a^n b con n ≥ 0)
def acepta_G3(cadena):
    return cadena.endswith("b") and all(c == "a" for c in cadena[:-1])

# --------- Gramática G4 ---------
# S → b | aS | ab
# (Lenguaje: a^n b con n ≥ 1)
def acepta_G4(cadena):
    return len(cadena) >= 2 and cadena.endswith("b") and all(c == "a" for c in cadena[:-1])

# --------- Gramática G5 ---------
# S → a | ab
# (Lenguaje: {a, ab})
def acepta_G5(cadena):
    return cadena in ["a", "ab"]

# --------- Procesador ---------
# Esta función recibe una gramática y un archivo
# y verifica cada línea del archivo
def procesar(gramatica, archivo):
    with open(archivo, "r") as f:  # Abrir archivo en modo lectura
        for linea in f:           # Leer cada línea
            cadena = linea.strip()  # Eliminar saltos de línea
            if not cadena:          # Si la línea está vacía, la ignora
                continue
            if gramatica(cadena):   # Verificar con la gramática
                print(f"{cadena} → acepta")
            else:
                print(f"{cadena} → NO acepta")

# --------- Programa Principal ---------
if __name__ == "__main__":
    # Se esperan 2 argumentos: gramática y archivo
    if len(sys.argv) != 3:
        print("Uso: python3 gramaticas.py <G1|G2|G3|G4|G5> <archivo.txt>")
        sys.exit(1)

    opcion = sys.argv[1]   # Gramática seleccionada
    archivo = sys.argv[2]  # Archivo de prueba

    # Selección de gramática
    if opcion == "G1":
        procesar(acepta_G1, archivo)
    elif opcion == "G2":
        procesar(acepta_G2, archivo)
    elif opcion == "G3":
        procesar(acepta_G3, archivo)
    elif opcion == "G4":
        procesar(acepta_G4, archivo)
    elif opcion == "G5":
        procesar(acepta_G5, archivo)
    else:
        print("Gramática no válida. Usa: G1, G2, G3, G4 o G5")
