cmake_minimum_required(VERSION 3.16)

project(Desafio1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Agregar todos los archivos fuente
add_executable(Desafio1
    main.cpp
    manejoArchivos.cpp
    busquedaVerificacion.cpp
    desCompresorEncriptador.cpp
)

include(GNUInstallDirs)
install(TARGETS Desafio1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
