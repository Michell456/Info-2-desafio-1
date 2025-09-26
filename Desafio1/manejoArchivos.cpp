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
