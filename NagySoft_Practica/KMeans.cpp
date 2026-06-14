#include "KMeans.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <iostream>
#include <algorithm>

double distanciaCuad(const Coord_3D& a, const Coord_3D& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    double dz = a.z - b.z;
    return dx*dx + dy*dy + dz*dz;
}

Coord_3D calcularCentroide(const std::vector<Coord_3D>& puntos) {
    if (puntos.empty()) return {0,0,0};
    Coord_3D suma = {0,0,0};
    for (const auto& p : puntos) {
        suma.x += p.x;
        suma.y += p.y;
        suma.z += p.z;
    }
    double n = puntos.size();
    return {suma.x/n, suma.y/n, suma.z/n};
}

double dispersionCluster(const std::vector<Coord_3D>& puntos, const Coord_3D& centroide) {
    double suma = 0.0;
    for (const auto& p : puntos) {
        suma += distanciaCuad(p, centroide);
    }
    return suma;
}

bool verificarConvergencia(const std::vector<Coord_3D>& centroidesViejos,
                           const std::vector<Coord_3D>& centroidesNuevos,
                           double tolerancia, int k) {
    for (int i = 0; i < k; ++i) {
        if (distanciaCuad(centroidesViejos[i], centroidesNuevos[i]) > tolerancia * tolerancia) {
            return false;
        }
    }
    return true;
}

std::vector<Coord_3D> inicializarCentroides(const std::vector<Coord_3D>& puntos, int k) {
    std::vector<Coord_3D> centroides;
    std::vector<int> indices;
    int n = puntos.size();
    if (k > n) k = n;

    srand(time(NULL));
    while (indices.size() < k) {
        int idx = rand() % n;
        if (std::find(indices.begin(), indices.end(), idx) == indices.end()) {
            indices.push_back(idx);
            centroides.push_back(puntos[idx]);
        }
    }
    return centroides;
}

std::vector<PuntoEtiquetado> kMeans(const std::vector<Coord_3D>& puntos, int k, int maxIteraciones) {
    int n = puntos.size();
    if (n == 0 || k <= 0) return {};
    if (k > n) k = n;

    std::vector<Coord_3D> centroides = inicializarCentroides(puntos, k);
    std::vector<int> asignaciones(n, 0);
    std::vector<PuntoEtiquetado> resultado;

    double tolerancia = 1e-6;

    for (int iter = 0; iter < maxIteraciones; ++iter) {
        for (int i = 0; i < n; ++i) {
            double minDist = std::numeric_limits<double>::max();
            int mejorCluster = 0;
            for (int j = 0; j < k; ++j) {
                double d = distanciaCuad(puntos[i], centroides[j]);
                if (d < minDist) {
                    minDist = d;
                    mejorCluster = j;
                }
            }
            asignaciones[i] = mejorCluster;
        }

        std::vector<Coord_3D> nuevosCentroides(k, {0,0,0});
        std::vector<int> conteo(k, 0);
        for (int i = 0; i < n; ++i) {
            int cluster = asignaciones[i];
            nuevosCentroides[cluster].x += puntos[i].x;
            nuevosCentroides[cluster].y += puntos[i].y;
            nuevosCentroides[cluster].z += puntos[i].z;
            conteo[cluster]++;
        }
        for (int j = 0; j < k; ++j) {
            if (conteo[j] > 0) {
                nuevosCentroides[j].x /= conteo[j];
                nuevosCentroides[j].y /= conteo[j];
                nuevosCentroides[j].z /= conteo[j];
            }
        }

        if (verificarConvergencia(centroides, nuevosCentroides, tolerancia, k)) {
            centroides = nuevosCentroides;
            break;
        }
        centroides = nuevosCentroides;
    }

    for (int i = 0; i < n; ++i) {
        PuntoEtiquetado pe;
        pe.coord = puntos[i];
        pe.etiqueta = static_cast<char>('A' + asignaciones[i]);
        resultado.push_back(pe);
    }

    return resultado;
}