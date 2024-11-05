
#include <iostream>
#include <cmath>
#include <omp.h>

// Function to compute the value of f(x) = ln(x) / x
double f(double x) {
    return std::log(x) / x;
}

int main() {
    int N;
    int a = 1;
    int b = 10;
    int num_threads;

    //enter the number of rectangles (N) and threads
    std::cout << "Enter the number of rectangles (N) for the approximation: ";
    std::cin >> N;
    std::cout << "Enter the number of threads: ";
    std::cin >> num_threads;

    // Set the number of threads for parallel execution
    omp_set_num_threads(num_threads);

    double width = static_cast<double>(b - a) / N;
    double total_area = 0.0; // Variable to hold the accumulated area

    // Parallel region to calculate the area under the curve
    #pragma omp parallel for reduction(+:total_area)
    for (int i = 0; i < N; ++i) {
        // Calculate the x position at the center of the rectangle
        double x = a + i * width + width / 2.0;

        total_area += f(x) * width;
    }

    // Display the result with formatted output
    std::cout << "\n-------------------------------------------------\n\n";
    std::cout << "Approximate integral of ln(x)/x from " << a << " to " << b << ":\n";
    std::cout << "Using " << N << " rectangles and " << num_threads << " threads.\n";
    std::cout << "Result: " << total_area << "\n";
    std::cout << "\n-------------------------------------------------\n";

    return 0;
}
