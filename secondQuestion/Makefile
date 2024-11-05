CC = g++
CFLAGS = -fopenmp -O2

TARGET = mandelbrot

all: $(TARGET)

$(TARGET): mandelbrot.cpp
	$(CC) $(CFLAGS) -o $(TARGET) mandelbrot.cpp

run: $(TARGET)
	@echo "Running without profiling...\n"
	@echo "===== Running with 1 thread =====\n"
	OMP_NUM_THREADS=1 ./$(TARGET) | tee results_1_thread.txt
	@echo "\n===== Results saved in results_1_thread.txt =====\n"

	@echo "===== Running with 2 threads =====\n"
	OMP_NUM_THREADS=2 ./$(TARGET) | tee results_2_threads.txt
	@echo "\n===== Results saved in results_2_threads.txt =====\n"

	@echo "===== Running with 4 threads =====\n"
	OMP_NUM_THREADS=4 ./$(TARGET) | tee results_4_threads.txt
	@echo "\n===== Results saved in results_4_threads.txt =====\n"

	@echo "===== Running with 8 threads =====\n"
	OMP_NUM_THREADS=8 ./$(TARGET) | tee results_8_threads.txt
	@echo "\n===== Results saved in results_8_threads.txt =====\n"

profile_build: mandelbrot.cpp
	$(CC) $(CFLAGS) -pg -o $(TARGET) mandelbrot.cpp

profile: profile_build
	@echo "Running with profiling enabled...\n"
	@echo "===== Profiling with 1 thread =====\n"
	OMP_NUM_THREADS=1 ./$(TARGET) | tee profile_1_thread.txt
	gprof $(TARGET) gmon.out > profile_1_thread.txt
	mv gmon.out gmon_1_thread.out
	@echo "\n===== Profiling results saved in profile_1_thread.txt =====\n"

	@echo "===== Profiling with 2 threads =====\n"
	OMP_NUM_THREADS=2 ./$(TARGET) | tee profile_2_threads.txt
	gprof $(TARGET) gmon.out > profile_2_threads.txt
	mv gmon.out gmon_2_threads.out
	@echo "\n===== Profiling results saved in profile_2_threads.txt =====\n"

	@echo "===== Profiling with 4 threads =====\n"
	OMP_NUM_THREADS=4 ./$(TARGET) | tee profile_4_threads.txt
	gprof $(TARGET) gmon.out > profile_4_threads.txt
	mv gmon.out gmon_4_threads.out
	@echo "\n===== Profiling results saved in profile_4_threads.txt =====\n"

	@echo "===== Profiling with 8 threads =====\n"
	OMP_NUM_THREADS=8 ./$(TARGET) | tee profile_8_threads.txt
	gprof $(TARGET) gmon.out > profile_8_threads.txt
	mv gmon.out gmon_8_threads.out
	@echo "\n===== Profiling results saved in profile_8_threads.txt =====\n"

clean:
	rm -f $(TARGET) results_*.txt profile_*.txt gmon_*.out
