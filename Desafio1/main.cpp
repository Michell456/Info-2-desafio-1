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

unsigned char* descomprimidorRLE(unsigned char* msj,int tamanoMsj){

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

        }
    }

    resultadoMsj[contador] = '\0';
    return resultadoMsj;
}

unsigned char* descompresorLZ78(unsigned char msj[],int tamanoArchivo){

    int cant_pares=tamanoArchivo/3;
    int *tamanos= new int[cant_pares];
    int longitud=0, total =0;

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
        }
        else{
            int entrada_inicial=entradas;
            for (int c=0; c<tamanos[index-1];c++){
                descomprimido[entradas]=descomprimido[posiciones[index-1]+c];
                entradas++;
            }
            descomprimido[entradas]=caracter_actual;
            entradas++;
            posiciones[i]=entrada_inicial;
            i++;
        }
    }

    delete[] tamanos;
    delete[] posiciones;

    return descomprimido;
}


unsigned char* desencriptador(int n,unsigned char key,unsigned char msj[],int tamanoArchivo){

    unsigned char *desencriptado= new unsigned char[tamanoArchivo];

    for (int j=0; j<tamanoArchivo; j++){

        unsigned char byte_result = msj[j] ^ key;
        desencriptado[j]=(byte_result>>n)|(byte_result<<(8-n));
    }

    return desencriptado;
}

