#ifndef KMEANS_H
#define KMEANS_H

#include <vector>
#include "Coord_3D.h"

struct PuntoEtiquetado {
    Coord_3D coord;
    char etiqueta;
};

std::vector<PuntoEtiquetado> kMeans(const std::vector<Coord_3D>& puntos, int k, int maxIteraciones = 100);
Coord_3D calcularCentroide(const std::vector<Coord_3D>& puntos);
double dispersionCluster(const std::vector<Coord_3D>& puntos, const Coord_3D& centroide);

#endif