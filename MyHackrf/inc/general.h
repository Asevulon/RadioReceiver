#include <stdint.h>
#include<vector>
int ErrorHandler(int error);

/*
Удаляет постоянную из сигнала в I/Q представлении.
I - четные, Q - нечетные.
*/

template<typename T>
void RemoveConst(std::vector<T>& target);


std::vector<double> ToDouble(int8_t* target, int size);

template <typename T>
void Normalize(std::vector<T>& target, const T Norma);


void PrintSignal(std::vector<double>& target, const char* title = "no title");