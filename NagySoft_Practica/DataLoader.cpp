#include "DataLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Coord_3D> cargarDatos(const std::string& nombreArchivo) {
    std::vector<Coord_3D> puntos;
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return puntos;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        Coord_3D p;
        char coma;
        ss >> p.x >> coma >> p.y >> coma >> p.z;
        puntos.push_back(p);
    }
    archivo.close();
    return puntos;
}