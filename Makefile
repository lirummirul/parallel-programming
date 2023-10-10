CC=g++-13 
CFLAGS = -Wall -std=c++11 -fopenmp
TARGET = hello

SOURCES = num1.cpp num2.cpp num3.cpp num4.cpp num5.cpp
SOURCES2 = num6.cpp num7.cpp num8.cpp num9.cpp
SOURCES3 = num10.cpp num11.cpp num12.cpp num13.cpp

EXECUTABLES = $(SOURCES:.cpp=)
EXECUTABLES2 = $(SOURCES2:.cpp=)
EXECUTABLES3 = $(SOURCES3:.cpp=)

# Цель по умолчанию (собирает все исполняемые файлы)
all: $(EXECUTABLES)

all2: $(EXECUTABLES2)

all3: $(EXECUTABLES3)

# Правило для компиляции каждого исходного файла
%: %.cpp
	$(CC) $(CFLAGS) -o $@ $<

# Очистка собранных файлов
clean:
	rm -f $(EXECUTABLES)
	rm -f $(EXECUTABLES2)
	rm -f $(EXECUTABLES3)
