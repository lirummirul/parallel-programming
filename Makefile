CC=g++-13 
CFLAGS = -Wall -std=c++11 -fopenmp
TARGET = hello

SOURCES = hello.cpp twoParallelAreas.cpp

EXECUTABLES = $(SOURCES:.cpp=)

# Цель по умолчанию (собирает все исполняемые файлы)
all: $(EXECUTABLES)

# Правило для компиляции каждого исходного файла
%: %.cpp
	$(CC) $(CFLAGS) -o $@ $<

# Очистка собранных файлов
clean:
	rm -f $(EXECUTABLES)