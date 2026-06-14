#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
#include "DataLoader.h"
#include "KMeans.h"

double dispersionTotal(const std::vector<PuntoEtiquetado>& puntosEtiquetados, int k) {
    std::vector<std::vector<Coord_3D>> clusters(k);
    for (const auto& pe : puntosEtiquetados) {
        int idx = pe.etiqueta - 'A';
        if (idx >= 0 && idx < k) {
            clusters[idx].push_back(pe.coord);
        }
    }

    double sumaTotal = 0.0;
    for (int i = 0; i < k; ++i) {
        if (!clusters[i].empty()) {
            Coord_3D centroide = calcularCentroide(clusters[i]);
            sumaTotal += dispersionCluster(clusters[i], centroide);
        }
    }
    return sumaTotal;
}

int encontrarMejorK(const std::vector<Coord_3D>& puntos, int maxK) {
    std::vector<double> dispersiones;
    std::cout << "Evaluando k desde 1 hasta " << maxK << ":" << std::endl;

    for (int k = 1; k <= maxK; ++k) {
        auto resultado = kMeans(puntos, k);
        double disp = dispersionTotal(resultado, k);
        dispersiones.push_back(disp);
        std::cout << "  k=" << k << " -> dispersion total = " << disp << std::endl;
    }

    if (dispersiones.size() < 2) return 1;

    double mejoraInicial = (dispersiones[0] - dispersiones[1]) / dispersiones[0];
    for (int k = 2; k <= maxK; ++k) {
        double mejora = (dispersiones[k-2] - dispersiones[k-1]) / dispersiones[k-2];
        if (mejora < 0.1 * mejoraInicial) {
            return k-1;
        }
    }
    return maxK;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: cluster <k> <datos.csv>" << std::endl;
        std::cerr << "Ejemplo: cluster 6 datos.csv" << std::endl;
        return 1;
    }

    int kUsuario = std::stoi(argv[1]);
    std::string archivoDatos = argv[2];

    std::vector<Coord_3D> puntos = cargarDatos(archivoDatos);
    if (puntos.empty()) {
        std::cerr << "Error: No se cargaron datos." << std::endl;
        return 1;
    }
    std::cout << "Cargados " << puntos.size() << " puntos." << std::endl;

    int kOptimo = kUsuario;
    if (kUsuario > 6) {
        std::cout << "Advertencia: El Dr. Szilard recomienda no usar mas de 6 clusters." << std::endl;
        std::cout << "Evaluando mejor k automaticamente..." << std::endl;
        kOptimo = encontrarMejorK(puntos, 6);
        std::cout << "Mejor k segun criterio de codo: " << kOptimo << std::endl;
    }

    std::vector<PuntoEtiquetado> resultado = kMeans(puntos, kOptimo);

    std::ofstream archivoClasificados("clasificados.csv");
    if (!archivoClasificados.is_open()) {
        std::cerr << "Error: No se pudo crear clasificados.csv" << std::endl;
        return 1;
    }

    for (const auto& pe : resultado) {
        archivoClasificados << std::fixed << std::setprecision(6)
                           << pe.coord.x << "," << pe.coord.y << "," << pe.coord.z
                           << "," << pe.etiqueta << std::endl;
    }
    archivoClasificados.close();
    std::cout << "Generado clasificados.csv con " << resultado.size() << " puntos." << std::endl;

    std::vector<std::vector<Coord_3D>> clusters(kOptimo);
    for (const auto& pe : resultado) {
        int idx = pe.etiqueta - 'A';
        clusters[idx].push_back(pe.coord);
    }

    std::ofstream archivoSummary("summary.txt");
    if (!archivoSummary.is_open()) {
        std::cerr << "Error: No se pudo crear summary.txt" << std::endl;
        return 1;
    }

    for (int i = 0; i < kOptimo; ++i) {
        char etiqueta = static_cast<char>('A' + i);
        int n = clusters[i].size();
        Coord_3D centroide = calcularCentroide(clusters[i]);
        double dispersion = dispersionCluster(clusters[i], centroide);

        archivoSummary << etiqueta << ": " << n << ", ("
                      << std::fixed << std::setprecision(6)
                      << centroide.x << ", " << centroide.y << ", " << centroide.z
                      << "), " << dispersion << std::endl;
    }
    archivoSummary.close();
    std::cout << "Generado summary.txt para k=" << kOptimo << std::endl;

    std::cout << "\nProceso completado exitosamente. Revise los archivos generados." << std::endl;

    return 0;
}