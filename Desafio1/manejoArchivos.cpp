#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

unsigned char* lectorArchivo(const char* nombreArchivo, int& tamanoArchivo) {
    ifstream file(nombreArchivo, std::ios::binary | std::ios::ate); // abre al final
    if (!file) {
        tamanoArchivo = 0;
        return nullptr;
    }

    std::streamsize size = file.tellg();                  // obtengo el tamaño del archivo
    if (size <= 0) {
        tamanoArchivo = 0;
        file.close();
        return nullptr;
    }

    // reservar +1 para terminar con '\0' (útil para pistas de texto)
    unsigned char* buffer = new unsigned char[size + 1];

    file.seekg(0, std::ios::beg);                  // vuelvo al inicio del archivo
    file.read(reinterpret_cast<char*>(buffer), size);
    file.close();

    // Ajustar tamanoArchivo (por referencia)
    tamanoArchivo = static_cast<int>(size);

    // Si el archivo es de texto puede terminar con '\n' o '\r\n'.
    // Eliminamos dichos caracteres del final (esto no hace daño si es binario).
    while (tamanoArchivo > 0 && (buffer[tamanoArchivo - 1] == '\n' || buffer[tamanoArchivo - 1] == '\r')) {
        tamanoArchivo--;
    }

    // poner terminador nulo (útil para usar como cadena)
    buffer[tamanoArchivo] = '\0';

    return buffer;
}


void guardarArchivo(const char* nombreArchivoResultados,unsigned char* mensaje, int tamanoDescomprimido, int metodo,int n, int k,int a){

    std::ofstream archivo(nombreArchivoResultados, std::ios::out | std::ios::app);
    if (!archivo) {
        return;
    }

    // Mensaje descomprimido
    for (int i = 0; i < tamanoDescomprimido; i++) {
        archivo << mensaje[i];
    }
    archivo <<"\n";

    //datos (rotacion, met de encriptacion, n° de archivo)
    archivo << "** Encriptado" << a << " **\n";
    if (n == -1){
        archivo << "Error al abrir el archivo/descomprimir" << "\n";
    }
    if (metodo == 1){
        archivo << "Compresión: LZ78" << "\n";
    }
    else if (metodo == 2){
        archivo << "Compresión: RLE"<< "\n";
    }
    archivo << "Compresión: " << metodo << "\n";
    archivo << "Rotación: " << n << "\n";


    // key con formato 0xNN
    archivo << "Key = 0x"
            << std::uppercase << std::hex << std::setw(2) << std::setfill('0')
            << k << std::dec << "\n\n";

    archivo.close();
}


