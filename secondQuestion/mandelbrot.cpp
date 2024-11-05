#include <iostream>
#include <complex>
#include <omp.h>
#include <cstdlib>
#include <ctime>

#define X_MIN -2.0
#define X_MAX 2.0
#define Y_MIN -2.0
#define Y_MAX 2.0

bool isInMandelbrot(const std::complex<double>& c) {
    std::complex<double> z = 0;
    const int maxIterations = 1000;

    for (int i = 0; i < maxIterations; ++i) {
        z = z * z + c;
        if (std::abs(z) > 2) return false;
    }
    return true;
}

double monteCarloMandelbrot(int numPoints, int numThreads) {
    int countInSet = 0;

    #pragma omp parallel for num_threads(numThreads) reduction(+:countInSet)
    for (int i = 0; i < numPoints; ++i) {
        double x = X_MIN + (X_MAX - X_MIN) * static_cast<double>(rand()) / RAND_MAX;
        double y = Y_MIN + (Y_MAX - Y_MIN) * static_cast<double>(rand()) / RAND_MAX;
        std::complex<double> c(x, y);

        if (isInMandelbrot(c)) {
            countInSet++;
        }
    }

    double area = ((X_MAX - X_MIN) * (Y_MAX - Y_MIN)) * static_cast<double>(countInSet) / numPoints;
    return area;
}

int main() {
    const int numPoints = 10000000;

    // Read number of threads from the environment variable OMP_NUM_THREADS
    int numThreads = 4; // Default value
    char* envThreads = std::getenv("OMP_NUM_THREADS");
    if (envThreads) {
        numThreads = std::atoi(envThreads);
    }

    srand(static_cast<unsigned int>(time(nullptr)));

    std::cout << "Sequential calculation:\n";
    double startTime = omp_get_wtime();
    double areaSeq = monteCarloMandelbrot(numPoints, 1);
    double timeSeq = omp_get_wtime() - startTime;
    std::cout << "Estimated area (sequential): " << areaSeq << "\n";
    std::cout << "Time (sequential): " << timeSeq << " seconds\n";

    std::cout << "\nParallel calculation with " << numThreads << " threads:\n";
    startTime = omp_get_wtime();
    double areaPar = monteCarloMandelbrot(numPoints, numThreads);
    double timePar = omp_get_wtime() - startTime;
    std::cout << "Estimated area (parallel): " << areaPar << "\n";
    std::cout << "Time (parallel): " << timePar << " seconds\n";

    double speedup = timeSeq / timePar;
    std::cout << "\nSpeedup: " << speedup << "\n";

    return 0;
}
