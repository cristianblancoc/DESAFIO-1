#include <iostream>
#include <fstream>
# include<string>

using namespace std;

int main()
{
     ofstream archivotex("salidaREL.txt");
    if(!archivotex){
         cerr <<"no se pudo abrir el archivo "<<endl;
    }
    archivotex<<"WWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWW "<<endl;



    string archivo ="salidaREL.txt";
    ifstream archivo1 (archivo);
    if (!archivo1.is_open()) {
        cerr << "No se pudo abrir el archivo: " << archivo << endl;
        return 1;
    }
    cout <<"leyendo char por char"<<endl;
    char c;
    while (archivo1.get(c)){
        cout <<c;
    }
    archivo1.close();


    return 0;
}
