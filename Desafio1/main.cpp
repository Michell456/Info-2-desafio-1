#include <iostream>
#include <fstream>


using namespace std;

unsigned char* fuerzaBruta(unsigned char* msj, int tamanoArchivo, unsigned char* pista, int* metodo, int* n, unsigned char* k, int* tamanoDescomprimido);
unsigned char* lectorArchivo(const char* nombreArchivo, int& tamanoArchivo);
void guardarArchivo(const char* nombreArchivoResultados,unsigned char* mensaje, int tamanoDescomprimido, int metodo,int n, int k,int a);

int main(){

    int cantArchivos,tamanoArchivo=0,tamanoPista=0,metodo,n,tamanoDescomprimido;
    char nombreArchivo[20];
    unsigned char k;

    while (true) {
        cantArchivos = 0;
        bool verif = true;
        char entrada[3];

        cout << "Cuantos archivos desea descencriptar?: ";
        cin >> entrada;

        int i = 0;
        while (entrada[i] != '\0') {
            if (entrada[i] < '0' || entrada[i] > '9') {
                cout << "Entrada invalida. Solo se permiten numeros." << endl;
                verif = false;
                break;
            }
            i++;
        }

        if (verif) {
            i = 0;
            while (entrada[i] != '\0') {
                cantArchivos = cantArchivos * 10 + (entrada[i] - '0');
                i++;
            }

            if (cantArchivos == 0) {
                cout << "Debe ingresar un numero mayor que cero." << endl;
                verif = false;
            }
        }

        if (verif) break; // salir si todo está correcto
    }

    for (int a = 1; a <= cantArchivos; a++) {

        metodo = -1;
        n = -1;
        k = 0;
        tamanoDescomprimido = 0;


        sprintf(nombreArchivo, "Encriptado%d.txt", a);
        unsigned char* msj = lectorArchivo(nombreArchivo, tamanoArchivo);

        sprintf(nombreArchivo,"pista%d.txt",a);
        unsigned char* pista = lectorArchivo(nombreArchivo, tamanoPista);

        unsigned char* resultadoMsj = nullptr;
        if (pista == nullptr || msj == nullptr){

            tamanoDescomprimido = 0;
            metodo = -1;
            n = -1;
            k = 0;

        }
        else{


            resultadoMsj = fuerzaBruta(msj,tamanoArchivo,pista,&metodo,&n,&k,&tamanoDescomprimido);

            if (resultadoMsj == nullptr){

                tamanoDescomprimido = 0;
                metodo = -1;
                n = -1;
                k = 0;
            }
        }
        guardarArchivo("resultado.txt",resultadoMsj,tamanoDescomprimido,metodo,n,k,a);
        delete[] resultadoMsj;
        delete[] msj;
        delete[] pista;
        n = 0;
        k = 1;

    }

    return 0;
}

