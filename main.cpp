#include <iostream>
#include <fstream>


using namespace std;
unsigned char rotar_derecha(unsigned char valor, int n) {
    return (valor >> n) | (valor << (8 - n));
}

unsigned char rotar_izquierda(unsigned char valor, int n) {
    return (valor << n) | (valor >> (8 - n));
}

int main()
{
  /*   ofstream archivotex("salidaREL.txt");
    if(!archivotex){
         cerr <<"no se pudo abrir el archivo "<<endl;
    }x
    archivotex<<"WWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWW "<<endl;


    */
    const char* archivo = "salidaREL.txt"; // nombre del archivo
    ifstream archivo1(archivo, ios::binary); // abrir desde el inicio

    if (!archivo1.is_open()) {
        cerr << "No se pudo abrir el archivo: " << archivo << endl;
        return 1;
    }

    int byte;
    while ((byte = archivo1.get()) != EOF) {
        unsigned char c = static_cast<unsigned char>(byte);
        // Primera rotación y XOR
        unsigned char rotado = rotar_derecha(c, 2);
        rotado ^= 0x5A;

        // Segunda rotación y XOR sobre el resultado anterior
        unsigned char rotado2 = rotar_derecha(rotado,2);
        rotado2 ^= 0x5A;
        //cout<<rotado2;

        // tercera rotación y XOR sobre el resultado anterior
       unsigned char rotado3 = rotar_izquierda(rotado2, 2);
        rotado3 ^= 0x5A;
        cout<<rotado3;
    }

    archivo1.close();














    return 0;
}
