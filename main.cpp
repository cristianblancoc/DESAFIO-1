
#include <iostream>
#include <fstream>

using namespace std;

/*// Rota los bits de un byte a la derecha
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
*/

int main() {
    ifstream archivo("lz78.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo.\n";
        return 1;
    }

    char indices[100];
    char letras[100];
    int total = 0;

    // Leer pares (índice, letra)
    while (true) {
        char c = archivo.get();
        if (archivo.eof()) break;

        if (c == '(') {
            int num = 0;
            c = archivo.get();

            while (c >= '0' && c <= '9') {
                num = num * 10 + (c - '0');
                c = archivo.get();
            }

            while (c == ',' || c == ' ') c = archivo.get();

            char letra = c;

            while (c != ')' && !archivo.eof()) {
                c = archivo.get();
            }

            indices[total] = (char)num;
            letras[total] = letra;
            total++;
        }
    }

    archivo.close();

    // Diccionario para reconstrucción
    char diccionario[100][100];
    int tamanos[100];
    int totalEntradas = 0;

    char mensaje[10000];
    int largoMensaje = 0;

    for (int k = 0; k < total; k++) {
        int ind = (int)indices[k];
        char l = letras[k];

        int tam = 0;
        if (ind > 0) {
            int pos = ind - 1;
            tam = tamanos[pos];
            for (int j = 0; j < tam; j++) {
                diccionario[totalEntradas][j] = diccionario[pos][j];
            }
        }

        diccionario[totalEntradas][tam] = l;
        tam++;
        tamanos[totalEntradas] = tam;

        for (int j = 0; j < tam; j++) {
            mensaje[largoMensaje++] = diccionario[totalEntradas][j];
        }

        totalEntradas++;
    }

    cout << "\nTexto descomprimido:\n";
    for (int i = 0; i < largoMensaje; i++) {
        cout << mensaje[i];
    }

    // Aplicar organización con la palabra clave
    const char* clave = "rrenosdes";
    int posicion = buscar_palabra(mensaje, largoMensaje, clave, 9);

    if (posicion != -1) {
        rotar_texto(mensaje, largoMensaje, posicion);

        cout << "\n\nTexto organizado:\n";
        for (int i = 0; i < largoMensaje; i++) {
            cout << mensaje[i];
        }
    } else {
        cout << "\n\nNo se encontró la clave. No se reorganizó el texto.\n";
    }

    cout << "\n";
    return 0;
}
  /*   ofstream archivotex("salidaREL.txt");
    if(!archivotex){
         cerr <<"no se pudo abrir el archivo "<<endl;
    }x
    archivotex<<"WWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWW "<<endl;




   */









