#include <sys/sysctl.h>
//#include <windows.h>
#include <mach/mach.h>
#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <list>
#include <thread>
#include <atomic>

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

// Windows ver
/*unsigned long long getTotalSystemMemory() {
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return status.ullTotalPhys;
}*/

/*size_t getUsedMemory() {
    PROCESS_MEMORY_COUNTERS_EX memCounter;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&memCounter, sizeof(memCounter));
    return memCounter.WorkingSetSize; // Memoria usada en bytes
}*/

//MacOs ver
unsigned long long getTotalSystemMemory() {
    int mib[2] = { CTL_HW, HW_MEMSIZE };
    uint64_t totalMemory;
    size_t length = sizeof(totalMemory);

    if (sysctl(mib, 2, &totalMemory, &length, NULL, 0) != 0) {
        return 0; 
    }

    return totalMemory;
}

size_t getUsedMemory() {
    task_basic_info_data_t info;
    mach_msg_type_number_t count = TASK_BASIC_INFO_COUNT;

    // Obtener la información básica del proceso actual
    if (task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&info, &count) != KERN_SUCCESS) {
        return 0; // Error al obtener la memoria
    }

    return info.resident_size; // Memoria residente en bytes
}

// Hilo para mostrar la RAM utilizada cada segundo
std::atomic<bool> running(true);
void monitorMemoryUsage() {
    while (running) {
        size_t usedMemory = getUsedMemory() / 1024 / 1024; // Convertir a MB
        std::cout << "Memoria usada: " << usedMemory << " MB" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

/*
void quicksort(std::list<std::string>& lista) {
    
}*/

int main() {
    // Hilo de monitoreo de Ram
    std::thread memoryThread(monitorMemoryUsage);

    size_t ramTotal = getTotalSystemMemory();
    size_t ramStop = ramTotal * 0.2;
    int contadorArchivo = 1;

    std::list<std::string> palabras;
    std::ifstream archivoEntrada("nose.txt");
    std::string palabra;

    while (archivoEntrada >> palabra) {
        palabras.push_back(palabra);

        // Verificar memoria disponible
        size_t ramDisp = getTotalSystemMemory();
        if (ramDisp < ramStop) {
            //ordenar con quicksort aqui

            std::string nombreArchivo = "bitacora" + std::to_string(contadorArchivo) + ".txt";
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
       //ordenar con quicksort aqui

        std::string nombreArchivo = "bitacora" + std::to_string(contadorArchivo) + ".txt";
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

    // Cargar la primera palabra de cada archivo en el heap
    for (int i = 1; i <= contadorArchivo; i++) {
        std::string nombreArchivo = "bitacora" + std::to_string(i) + ".txt";
        std::ifstream archivo(nombreArchivo);

        std::string primeraPalabra;
        if (archivo >> primeraPalabra) {
            minHeap.push({primeraPalabra, i});
        }

        archivo.close();
    }

    std::ofstream archivoSalida("bitacoraOrdenada.txt");

    // Procesar el heap
    while (!minHeap.empty()) {
        auto [palabra, idArchivo] = minHeap.top();
        minHeap.pop();

        archivoSalida << palabra << std::endl;

        std::string nombreArchivo = "bitacora" + std::to_string(idArchivo) + ".txt";
        std::ifstream archivo(nombreArchivo);

        std::string nuevaPalabra;
        if (archivo >> nuevaPalabra) {
            minHeap.push({nuevaPalabra, idArchivo});
        }

        archivo.close();
    }

    archivoSalida.close();
    std::cout << "Archivo ordenado creado: bitacoraOrdenada.txt\n";

    // Finalizar el hilo de monitoreo
    running = false;
    memoryThread.join();

    return 0;
}
