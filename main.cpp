#include <iostream>
#include <fstream>


using namespace std;

int main()
{
  /*   ofstream archivotex("salidaREL.txt");
    if(!archivotex){
         cerr <<"no se pudo abrir el archivo "<<endl;
    }x
    archivotex<<"WWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWW "<<endl;


    */
    char* archivo ="salidaREL.txt";
    ifstream archivo1 (archivo);
    if (!archivo1.is_open()) {
        cerr << "No se pudo abrir el archivo: " << archivo << endl;
        return 1;
    }
    cout << "Leyendo y comprimiendo con RLE..." << endl;

    char c;
    char actual = '\0';
    int conteo = 0;

    while (archivo1.get(c)) {
        if (conteo == 0) {
            // Primer carácter
            actual = c;
            conteo = 1;
        } else if (c == actual) {
            // Mismo carácter, aumentar conteo
            conteo++;
        } else {
            // Carácter distinto, imprimir resultado anterior
            cout << conteo << actual;
            // reiniciar para el nuevo carácter
            actual = c;
            conteo = 1;
        }
    }

    // al salir del while imprimir el último grupo
    if (conteo > 0) {
        cout << conteo << actual;
    }

    cout << endl;

    archivo1.close();




    return 0;
}
