#include <iostream>
#include <fstream>

using namespace std;

unsigned char* descompresorRLE(unsigned char* msj,int tamanoMsj, int* tamanoDescomprimido);
unsigned char* descompresorLZ78(unsigned char* msj,int tamanoArchivo, int* tamanoDescomprimido);
unsigned char* desencriptador(int n,unsigned char key,unsigned char* msj,int tamanoArchivo);
unsigned char* fuerzaBruta(unsigned char* msj, int tamanoArchivo, unsigned char* pista, int* metodo, int* n, unsigned char* k);
int verificacionDescompresion(unsigned char* desencriptado, int tamanoArchivo);
bool verificacionValidez(unsigned char* pista, unsigned char* descomprimido, int tamanoDescomprimido);
unsigned char* lectorArchivo(const char* nombreArchivo, int& tamanoArchivo);


int main(){

    int cantArchivos,tamanoArchivo=0,tamanoPista=0,metodo,n;
    unsigned char nombreArchivo[20],k;

    cout << "Cuantos archivos deseas leer?: ";
    cin >> cantArchivos;

    for (int a = 1; a <= cantArchivos; a++) {
        sprintf(nombreArchivo, "Encriptado%d.txt", a);
        unsigned char* msj = leectorArchivo(nombreArchivo, tamanoArchivo);

        sprintf(nombreArchivo,"pista%d.txt",a);
        unsigned char* pista = leectorArchivo(nombreArchivo, tamanoPista);

        unsigned char* resultadoMsj = fuerzaBruta(msj,tamanoArchivo,pista,metodo,n,k);
    }

    return 0;
}

