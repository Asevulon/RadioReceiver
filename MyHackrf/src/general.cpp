#include "general.h"
#include "hackrf.h"
#include <stdio.h>
#include <cstdlib>

int ErrorHandler(int error)
{
    if (error != HACKRF_SUCCESS)
    {
        fprintf(stderr,
                "hackrf_init() failed: %s (%d)\n",
                hackrf_error_name(static_cast<hackrf_error>(error)),
                error);
        return EXIT_FAILURE;
    }
    return 0;
}

template<typename T>
void RemoveConst(std::vector<T>& target)
{
    double Iavg = 0;
    double Qavg = 0;

    int size = target.size();

    for(int i  = 0; i < size; i++)
    {
        if(i % 2)
        {
            Qavg+=target[i];
        }
        else
        {
            Iavg+=target[i];
        }
    }

    Iavg /= size / 2;
    Qavg /= size / 2;

    for(int i = 0; i < size; i++)
    {
        if(i%2)
        {
            target[i]-=Qavg;
        }
        else
        {
            target[i]-=Iavg;
        }
    }

    //fprintf(stdout, "Iavg: %.3f\tQavg: %.3f\n\r", Iavg, Qavg);
}
template void RemoveConst<double>(std::vector<double>& target);

std::vector<double> ToDouble(int8_t* target, int size)
{
    std::vector<double>res;
    res.resize(size);
    for(int i = 0; i < size; i++)
    {
        res[i] = target[i];
    }
    return res;
}

template <typename T>
void Normalize(std::vector<T>& target, const T Norma)
{
    for(auto&item:target)item/=Norma;
}

void PrintSignal(std::vector<double> &target, const char *title)
{
    fprintf(stdout, title);
    fprintf(stdout, "\n\r");
    bool IQtype = true;
    for(auto&item:target)
    {
        if(IQtype)
        {
            fprintf(stdout, "I: %.3f\t", item);
            IQtype = !IQtype;
        }
        else
        {
            fprintf(stdout, "Q: %.3f\n\r", item);
            IQtype = !IQtype;
        }
    }
}
