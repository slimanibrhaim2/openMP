

CXX = g++
# Compiler flags
CXXFLAGS = -fopenmp -Wall -std=c++11

# Target executable
TARGET = integrate

# Default target
all: $(TARGET)

# Normal compilation
$(TARGET): integrate.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) integrate.cpp

# Run the program normally (after regular compilation)
run: $(TARGET)
	./$(TARGET)

# Profiling compilation with gprof
profile: integrate.cpp
	$(CXX) $(CXXFLAGS) -pg -o $(TARGET) integrate.cpp

# Run the program in profiling mode to generate gmon.out
run_profile: $(TARGET)
	./$(TARGET)

# Generate profiling report (profile_report.txt) from gmon.out
generate_report:
	gprof $(TARGET) gmon.out > profile_report.txt
	cat profile_report.txt

# Clean the compiled files and output
clean:
	rm -f $(TARGET) gmon.out profile_report.txt
