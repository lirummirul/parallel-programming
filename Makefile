CC=g++-13 
CFLAGS = -Wall -std=c++11 -fopenmp
TARGET = hello

SOURCES = num1.cpp num2.cpp num3.cpp num4.cpp num5.cpp num6.cpp

EXECUTABLES = $(SOURCES:.cpp=)

# Цель по умолчанию (собирает все исполняемые файлы)
all: $(EXECUTABLES)

# Правило для компиляции каждого исходного файла
%: %.cpp
	$(CC) $(CFLAGS) -o $@ $<

# Очистка собранных файлов
clean:
	rm -f $(EXECUTABLES)
