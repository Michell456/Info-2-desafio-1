#include <iostream>
#include <fstream>

using namespace std;

unsigned char* lectorArchivo(const char* nombreArchivo, int& tamanoArchivo) {
    ifstream file(nombreArchivo, std::ios::binary | std::ios::ate); // abre al final
    if (!file) {
        cerr << "No se pudo abrir el archivo\n";
        tamanoArchivo = 0;
        return nullptr;
    }

    tamanoArchivo = file.tellg();                  // obtengo el tamaño del archivo
    unsigned char* buffer = new unsigned char[tamanoArchivo]; // creo el arreglo dinámico

    file.seekg(0, std::ios::beg);                  // vuelvo al inicio del archivo
    file.read(reinterpret_cast<char*>(buffer), tamanoArchivo);

    file.close();
    return buffer;
}

unsigned char* descompresorRLE(unsigned char* msj,int tamanoMsj, int* tamanoDescomprimido){

    int tamanoFinal=0;

    unsigned int numero,contador = 0, tamanoTotal = 0;
    char caracter;
    for (int i=0;i<tamanoMsj;i += 2){

        tamanoTotal += msj[i];

    }

    tamanoTotal ++;
    unsigned char* resultadoMsj = new unsigned char[tamanoTotal];

    for (int i = 0;i<tamanoMsj;i += 2){

        numero = msj[i];
        caracter = msj[i+1];

        for (int j = 0;j<numero;j++){

            resultadoMsj[contador] = caracter;
            contador++;
            tamanoFinal++;

        }
    }

    *tamanoDescomprimido=tamanoFinal;

    resultadoMsj[contador] = '\0';
    return resultadoMsj;
}

unsigned char* descompresorLZ78(unsigned char* msj,int tamanoArchivo, int* tamanoDescomprimido){

    int cant_pares=tamanoArchivo/3;
    int *tamanos= new int[cant_pares];
    int longitud=0, total =0;

    int tamanoFinal=0;

    int j=0, i=0;
    while (j<tamanoArchivo){

        unsigned char byte1=msj[j], byte2=msj[j+1];
        int index=(byte1<<8)|byte2;
        j+=3;

        if (index==0){
            longitud=1;
        }
        else{
            longitud=tamanos[index-1]+1;
        }

        total+=longitud;
        tamanos[i]=longitud;
        i++;
    }

    unsigned char *descomprimido= new unsigned char[total];
    int *posiciones= new int[cant_pares];

    j=0, i=0;
    int entradas=0;

    while (j<tamanoArchivo){

        unsigned char byte1=msj[j], byte2=msj[j+1], caracter_actual=msj[j+2];
        int index=(byte1<<8)|byte2;
        j+=3;

        if (index==0){
            descomprimido[entradas]=caracter_actual;
            posiciones[i]=entradas;
            entradas++;
            i++;
            tamanoFinal++;
        }
        else{
            int entrada_inicial=entradas;
            for (int c=0; c<tamanos[index-1];c++){
                descomprimido[entradas]=descomprimido[posiciones[index-1]+c];
                entradas++;
                tamanoFinal++;
            }
            descomprimido[entradas]=caracter_actual;
            entradas++;
            posiciones[i]=entrada_inicial;
            i++;
            tamanoFinal++;
        }
    }

    delete[] tamanos;
    delete[] posiciones;

    *tamanoDescomprimido=tamanoFinal;

    descomprimido[tamanoFinal]='\0';

    return descomprimido;
}


unsigned char* desencriptador(int n,unsigned char key,unsigned char* msj,int tamanoArchivo){

    unsigned char *desencriptado= new unsigned char[tamanoArchivo];

    for (int j=0; j<tamanoArchivo; j++){

        unsigned char byte_result = msj[j] ^ key;
        desencriptado[j]=(byte_result>>n)|(byte_result<<(8-n));
    }

    return desencriptado;
}

int verificacionDescompresion(unsigned char* desencriptado, int tamanoArchivo) {

    int metodoDescomp=0;

    for (int i=3; i<tamanoArchivo; i+=3) {

        if (!((desencriptado[i] >= 'A' && desencriptado[i] <= 'Z')||(desencriptado[i] >= 'a' && desencriptado[i] <= 'z')||(desencriptado[i] >= '0' && desencriptado[i] <= '9'))) {
            return metodoDescomp; //Se descarta la combinacion
        }
    }

    if (desencriptado[0]==0){
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

unsigned char* fuerzaBruta(unsigned char* msj, int tamanoArchivo, unsigned char* pista) {
    int tamanoDescomprimido;

    for (int n = 1; n <= 7; n++) {
        for (int k = 0; k <= 255; k++) {
            unsigned char key = (unsigned char)k;

            unsigned char* msjDesencriptado = desencriptador(n, key, msj, tamanoArchivo);

            int metodo = verificacionDescompresion(msjDesencriptado, tamanoArchivo);

            unsigned char* resultadoMsj = nullptr;

            if (metodo == 1) {

                resultadoMsj = descompresorLZ78(msjDesencriptado, tamanoArchivo, &tamanoDescomprimido);

            } else if (metodo == 2) {

                resultadoMsj = descompresorRLE(msjDesencriptado, tamanoArchivo, &tamanoDescomprimido);
            }

            if (resultadoMsj != nullptr){

                bool encontrado = verificacionValidez(pista,resultadoMsj,tamanoDescomprimido);

                if (encontrado) {
                    return resultadoMsj;
                }

                delete[] resultadoMsj;

            }

        }
    }
}

int main(){

    return 0;
}

