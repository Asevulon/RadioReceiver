#include "Detecter.h"
#include <math.h>

#define pow2(x) ((x) * (x))
void Detecter::SetData(std::vector<double> &val)
{
    data = val;
}

std::vector<double> Detecter::GetData()
{
    return data;
}

int Detecter::GetLastResult()
{
    return LastResult;
}

double SignalEnergyDetecter::CalcEnergy(std::vector<double> &source)
{
    double res = 0;

    for(int i = 0; i < source.size(); i+=2)
    {
        res+= pow2(source[i]) + pow2(source[i + 1]);
    }
    return res;
}

void SignalEnergyDetecter::SetThreshold(double val)
{
    Threshold = val;
}

void SignalEnergyDetecter::ProcessData()
{
    double E = CalcEnergy(data);
    if(E >= Threshold)
    {
        LastResult = 1;
    }
    else
    {
    LastResult = 0;
    }
}

