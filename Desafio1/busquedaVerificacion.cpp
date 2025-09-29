#include <iostream>

using namespace std;

unsigned char* descompresorRLE(unsigned char* msj,int tamanoMsj, int* tamanoDescomprimido);
unsigned char* descompresorLZ78(unsigned char* msj,int tamanoArchivo, int* tamanoDescomprimido);
unsigned char* desencriptador(int n,unsigned char key,unsigned char* msj,int tamanoArchivo);
int verificacionDescompresion(unsigned char* desencriptado, int tamanoArchivo);
bool verificacionValidez(unsigned char* pista, unsigned char* descomprimido, int tamanoDescomprimido);


unsigned char* fuerzaBruta(unsigned char* msj, int tamanoArchivo, unsigned char* pista, int* metodo, int* n, unsigned char* k, int* tamanoDescomprimido) {

    for (int nn = 1; nn <= 7; nn++) {
        for (int kk = 0; kk <= 255; kk++) {
            unsigned char key = (unsigned char)kk;

            unsigned char* msjDesencriptado = desencriptador(nn, key, msj, tamanoArchivo);
            *metodo = verificacionDescompresion(msjDesencriptado, tamanoArchivo);

            unsigned char* resultadoMsj = nullptr;

            if (*metodo == 1) {

                resultadoMsj = descompresorLZ78(msjDesencriptado, tamanoArchivo, tamanoDescomprimido);

            } else if (*metodo == 2) {

                resultadoMsj = descompresorRLE(msjDesencriptado, tamanoArchivo, tamanoDescomprimido);

            }

            delete[] msjDesencriptado;

            if (resultadoMsj != nullptr){

                bool encontrado = verificacionValidez(pista,resultadoMsj,*tamanoDescomprimido);

                if (encontrado==true) {
                    *n = nn;
                    *k = key;
                    return resultadoMsj;
                }

                delete[] resultadoMsj;

            }
        }
    }

    return nullptr;
}



int verificacionDescompresion(unsigned char* desencriptado, int tamanoArchivo) {

    int metodoDescomp=0;

    for (int i=2; i<tamanoArchivo; i+=3) {
        if (!((desencriptado[i] >= 'A' && desencriptado[i] <= 'Z')||(desencriptado[i] >= 'a' && desencriptado[i] <= 'z')||(desencriptado[i] >= '0' && desencriptado[i] <= '9'))) {
            return metodoDescomp; //Se descarta la combinacion
        }
    }

    int index = ( (int)desencriptado[0] << 8 ) | (int)desencriptado[1];
    if (index==0){
        metodoDescomp=1; //Se usara LZ78
        return metodoDescomp;
    }

    else{
        metodoDescomp=2; //Se usara RLE
        return metodoDescomp;
    }
}

bool verificacionValidez(unsigned char* pista, unsigned char* descomprimido, int tamanoDescomprimido){

    int valido=0;
    int tamanoPista=0;

    for (int i=0; pista[i]!='\0'; i++){
        tamanoPista++;
    }

    for (int i=0; i<tamanoDescomprimido; i++){
        int j=0;
        while (descomprimido[i+j]!='\0' && pista[j]!='\0' && descomprimido[i+j]==pista[j]){
            j++;
        }

        if (j==tamanoPista){
            return true;
        }

    }

    return false;
}
