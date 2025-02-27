#include <unistd.h>
#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <list>
#include <thread>
#include <atomic>

#include <iostream>
#include <unistd.h>

#if defined(__linux__)
#include <fstream>

size_t getUsedMemory() {
    std::ifstream statm("/proc/self/statm");
    size_t total_pages, resident_pages;
    
    if (statm >> total_pages >> resident_pages) {
        long page_size = sysconf(_SC_PAGE_SIZE);
        return resident_pages * page_size; // Retorna memoria usada en bytes
    }

    return 0; // Error al leer
}

#elif defined(__APPLE__) && defined(__MACH__)
#include <mach/mach.h>

size_t getUsedMemory() {
    struct task_basic_info info;
    mach_msg_type_number_t count = TASK_BASIC_INFO_COUNT;
    
    if (task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&info, &count) != KERN_SUCCESS) {
        return 0;
    }

    return info.resident_size; // Retorna memoria usada en bytes
}

#else
#error "Sistema operativo no soportado"
#endif



// Comparador para el Min-Heap
struct Comparador {
    bool operator()(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        if (isdigit(a.first[0]) && isdigit(b.first[0])) 
            return a.first > b.first;  

        if (isdigit(a.first[0]) && isalpha(b.first[0])) 
            return true;  

        if (isdigit(b.first[0]) && isalpha(a.first[0])) 
            return false;  

        return a.first > b.first;
    }
};

//Funciones de internet para poder leer la RAM
unsigned long long getTotalSystemMemory() {
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    return pages * page_size;
}

/*
//Monitoreo de RAM
std::atomic<bool> running(true);
void monitorMemoryUsage() {
    while (running) {
        size_t usedMemory = getUsedMemory() / 1024 / 1024; // Convertir a MB
        std::cout << "Memoria usada: " << usedMemory << " MB" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
*/

int main() {
    // Hilo de monitoreo de Ram
    //std::thread memoryThread(monitorMemoryUsage);

    //size_t ramTotal = getTotalSystemMemory();
    //para hardcodear la RAM
    size_t ramTotal = 8 * 1024 * 1024;
    std::cout << ramTotal << std::endl;
    int contadorArchivo = 1;

    std::vector<std::string> palabras;
    std::ifstream archivoEntrada("data.txt");
    std::string palabra;
    
    while (archivoEntrada >> palabra) {
        palabras.push_back(palabra);

        //mover el multiplicador para el safe gap
        if (getUsedMemory() > ramTotal * 0.85) {
            //Ordenar pedazo de archivo
            std::sort(palabras.begin(),palabras.end());


            std::string nombreArchivo = "data" + std::to_string(contadorArchivo) + ".txt";
            std::ofstream archivoSalida(nombreArchivo);

            for (const auto& x : palabras) {
                archivoSalida << x << std::endl;
            }
            palabras.clear(); 

            archivoSalida.close();
            contadorArchivo++;
        }
    }

    if (!palabras.empty()) {
        std::sort(palabras.begin(),palabras.end());

        std::string nombreArchivo = "data" + std::to_string(contadorArchivo) + ".txt";
        std::ofstream archivoSalida(nombreArchivo);

        for (const auto& x : palabras) {
            archivoSalida << x << std::endl;
        }

        archivoSalida.close();
    }

    archivoEntrada.close();

    // ------------------------------
    // MERGE
    // ------------------------------
    std::priority_queue<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>, Comparador> minHeap; 
    std::unordered_map<int, std::ifstream> archivos;

    for (int i = 1; i <= contadorArchivo; i++) {
        std::string nombreArchivo = "data" + std::to_string(i) + ".txt";
        archivos[i] = std::ifstream(nombreArchivo);

        std::string primeraPalabra;
        if (archivos[i] >> primeraPalabra) {
            minHeap.push({primeraPalabra, i});
        }
    }

    std::ofstream archivoSalida("sorted_data.txt");

    while (!minHeap.empty()) {
        auto [palabra, idArchivo] = minHeap.top();
        minHeap.pop();

        archivoSalida << palabra << std::endl;

        std::string nuevaPalabra;
        if (archivos[idArchivo] >> nuevaPalabra) {
            minHeap.push({nuevaPalabra, idArchivo});
        }
    }

    for (auto& [id, file] : archivos) {
        file.close();
    }

    archivoSalida.close();
    std::cout << "Archivo ordenado creado: sorted_data.txt\n";

    for (int i = 1; i <= contadorArchivo; i++) {
        std::string nombreArchivo = "data" + std::to_string(i) + ".txt";
        if (std::remove(nombreArchivo.c_str()) != 0) {
            std::cerr << "Error al eliminar el archivo: " << nombreArchivo << std::endl;
        } else {
            std::cout << "Archivo temporal eliminado: " << nombreArchivo << std::endl;
        }
    }

    // Finalizar el hilo de monitoreo
    //running = false;
    //memoryThread.join();

    return 0;
}
