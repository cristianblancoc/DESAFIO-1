
#include <iostream>
#include <fstream>

using namespace std;

// Rota los bits de un byte a la derecha
unsigned char rotar_derecha(unsigned char valor, int cantidad) {
    return (valor >> cantidad) | (valor << (8 - cantidad));
}


unsigned char rotar_izquierda(unsigned char valor, int cantidad) {
    return (valor << cantidad) | (valor >> (8 - cantidad));
}

// Aplica XOR con 0x5A y luego la rotación
unsigned char descifrar(unsigned char c) {
    return rotar_derecha(c ^ 0x40, 3);
}

// Lee el archivo, aplica XOR + rotación y muestra el resultado
int leer_y_descifrar(const char* nombre, unsigned char* salida, int maximo) {
    ifstream archivo(nombre, ios::binary);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo.\n";
        return -1;
    }

    int tam = 0;
    int byte = 0;

    cout << "\n--- Texto descifrado (XOR + rotacion) ---\n";

    while ((byte = archivo.get()) != EOF && tam < maximo) {
        unsigned char letra = descifrar((unsigned char)byte);
        salida[tam++] = letra;
        cout << letra;
    }

    cout << "\n--- Fin del texto descifrado ---\n";

    archivo.close();
    return tam;
}

// Descompresión con RLE
int descomprimir_RLE(unsigned char* entrada, int tamEntrada, char* salida) {
    int i = 0;
    int j = 0;
    int numero = 0;

    while (i < tamEntrada) {
        if (entrada[i] >= '0' && entrada[i] <= '9') {
            numero = numero * 10 + (entrada[i] - '0');
        } else {
            if (numero == 0) numero = 1;
            for (int k = 0; k < numero; k++) {
                salida[j++] = (char)entrada[i];
            }
            numero = 0;
        }
        i++;
    }

    return j;
}

// Busca una palabra en el texto y devuelve la posición
int buscar_palabra(char* texto, int largo, const char* palabra, int largoPalabra) {
    for (int i = 0; i <= largo - largoPalabra; i++) {
        int coincide = 1;
        for (int j = 0; j < largoPalabra; j++) {
            if (texto[i + j] != palabra[j]) {
                coincide = 0;
                break;
            }
        }
        if (coincide) return i;
    }
    return -1;
}

// Rota el texto a la izquierda desde la posición encontrada
void rotar_texto(char* texto, int largo, int inicio) {
    char* copia = new char[largo];
    int j = 0;
    for (int i = inicio; i < largo; i++) {
        copia[j++] = texto[i];
    }
    for (int i = 0; i < inicio; i++) {
        copia[j++] = texto[i];
    }
    for (int i = 0; i < largo; i++) {
        texto[i] = copia[i];
    }
    delete[] copia;
}

int main() {
    const int MAX = 20000;

    unsigned char* cifrado = new unsigned char[MAX];
    char* descomprimido = new char[MAX * 2];

    const char* archivo = "Encriptado1.txt";

    int tam = leer_y_descifrar(archivo, cifrado, MAX);
    if (tam <= 0) {
        delete[] cifrado;
        delete[] descomprimido;
        return 1;
    }

    int largo = descomprimir_RLE(cifrado, tam, descomprimido);

    // Usamos la pista "rrenosdes"
    const char* pista = "rrenosdes";
    int pos = buscar_palabra(descomprimido, largo, pista, 9);

    if (pos != -1) {
        rotar_texto(descomprimido, largo, pos);
    }

    cout << "\n--- Texto final descomprimido ---\n";
    for (int i = 0; i < largo; i++) {
        cout << descomprimido[i];
    }
    cout << "\n";

    delete[] cifrado;
    delete[] descomprimido;

    return 0;
}



  /*   ofstream archivotex("salidaREL.txt");
    if(!archivotex){
         cerr <<"no se pudo abrir el archivo "<<endl;
    }x
    archivotex<<"WWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWW "<<endl;



    namespace std; unsigned char rotar_derecha(unsigned char valor, int n) { return (valor >> n) | (valor << (8 - n)); } unsigned char rotar_izquierda(unsigned char valor, int n) { return (valor << n) | (valor >> (8 - n)); } //const char dicionario (char* =new valor, char c); int main() { const char* archivo = "salidaREL.txt"; // nombre fijo del archivo ifstream archivo1(archivo, ios::binary); if (!archivo1.is_open()) { cerr << "No se pudo abrir el archivo: " << archivo << endl; return 1; } // === Paso 1: Rotación + XOR === const int MAX = 10000; unsigned char almacenamiento[MAX]; int tam = 0; int byte = 0; while ((byte = archivo1.get()) != EOF && tam < MAX) { unsigned char c = (unsigned char)byte; // 1. XOR con clave 0x40 unsigned char xor_c = c ^ 0x5a ; unsigned char rot_izq = rotar_derecha(xor_c, 3); // 3. (Opcional) Rotación a la derecha 3 bits // unsigned char rot_der = rotar_derecha(rot_izq, 3); // Mostrar el byte transformado (como número) cout << rot_izq ; // Almacenar el resultado almacenamiento[tam++] = rot_izq; } archivo1.close(); // === Elegir tipo de descompresión === int tipoCompresion; cout << "\nTipo de compresion (1 = RLE, 2 = LZ78): "; cin >> tipoCompresion; if (tipoCompresion == 1) { // ===== RLE ===== int count = 0; for (int i = 0; i < tam; ++i) { unsigned char c = almacenamiento[i]; if (c >= '0' && c <= '9') { count = count * 10 + (c - '0'); } else { if (count == 0) count = 1; for (int j = 0; j < count; ++j) { cout << c; } count = 0; } } cout << endl; } else if (tipoCompresion == 2) { // ===== LZ78 ===== char dicc[256][256]; int largos[256]; int numEntradas = 0; int i = 0; while (i + 1 < tam) { int byte1 = almacenamiento[i]; int byte2 = almacenamiento[i + 1]; i += 2; int idx = byte1; char c = (char)byte2; if (idx > numEntradas) { cerr << "Error: índice fuera de rango: " << idx << endl; break; } int longitud = 0; if (idx > 0) { int pos = idx - 1; longitud = largos[pos]; for (int i = 0; i < longitud; i++) { dicc[numEntradas][i] = dicc[pos][i]; } } dicc[numEntradas][longitud] = c; longitud++; largos[numEntradas] = longitud; numEntradas++; for (int i = 0; i < longitud; i++) { cout << dicc[numEntradas - 1][i]; } } cout << endl; } else { cout << "Tipo de compresion no valido." << endl; }

   */









