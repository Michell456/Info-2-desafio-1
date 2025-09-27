#include <iostream>
#include <fstream>


using namespace std;

unsigned char* descompresorRLE(unsigned char* msj,int tamanoMsj, int* tamanoDescomprimido);
unsigned char* descompresorLZ78(unsigned char* msj,int tamanoArchivo, int* tamanoDescomprimido);
unsigned char* desencriptador(int n,unsigned char key,unsigned char* msj,int tamanoArchivo);
unsigned char* fuerzaBruta(unsigned char* msj, int tamanoArchivo, unsigned char* pista, int* metodo, int* n, unsigned char* k, int* tamanoDescomprimido);
int verificacionDescompresion(unsigned char* desencriptado, int tamanoArchivo);
bool verificacionValidez(unsigned char* pista, unsigned char* descomprimido, int tamanoDescomprimido);
unsigned char* lectorArchivo(const char* nombreArchivo, int& tamanoArchivo);
void guardarArchivo(const char* nombreArchivoResultados,unsigned char* mensaje, int tamanoDescomprimido, int metodo,int n, int k,int a);

int main(){

    int cantArchivos,tamanoArchivo=0,tamanoPista=0,metodo,n,tamanoDescomprimido;
    char nombreArchivo[20];
    unsigned char k;

    cout << "Cuantos archivos deseas leer?: ";
    cin >> cantArchivos;

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

    }

    return 0;
}

