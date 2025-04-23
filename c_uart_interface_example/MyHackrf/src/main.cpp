#include "hackrf.h"
#include "general.h"
#include <math.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <complex.h>
#include <stdint.h>
#include "Receiver.h"
#include "Journal.h"

// #define ENABLE_TRACE

int transfer_callback(hackrf_transfer* transfer) {
    int8_t* signed_buffer = (int8_t*)transfer->buffer;

    std::vector<double> data = ToDouble(signed_buffer, transfer->buffer_length);
    RemoveConst(data);
    RemoveConst(data);

    double E = 0;
    bool iq = true;

    for (auto& item : data)
    {
        E += item * item;

        //int val = signed_buffer[i];
        //fprintf(stdout,"RX Buffer i: %d\n\r", val);
        if (iq)
        {
            fprintf(stdout, "RX I: %.3f\t", item);
            iq = !iq;
        }
        else
        {
            fprintf(stdout, "RX Q: %.3f\n\r", item);
            iq = !iq;
        }
    }
    sleep(100);

    E /= transfer->buffer_length;
    E = sqrt(E);
    fprintf(stdout, "RX E: %.3f\n\r", E);

    return 0;
}

hackrf_device* device = NULL;
int result = 0;
bool ExitReached = false;
void ExitHandler()
{
    if (ExitReached)return;
    result = hackrf_stop_rx(device);
    ErrorHandler(result);
    result = hackrf_close(device);
    ErrorHandler(result);
    result = hackrf_exit();
    ErrorHandler(result);
}

const int samplerate = 8e6;
const int frequency = 935e6;
const int BB = 20;
const int IF = 16;

/*
int main(int argc, char** argv)
{
    atexit(ExitHandler);
    Receiver rec;
    rec.SetAmplify(IF);
    rec.SetFrequency(frequency);
    rec.SetSamplerate(samplerate);
    rec.StartRX();
    sleep(1);
    std::vector<double> data = rec.GetData();
    rec.StopRX();
    PrintSignal(data);
    /*result = hackrf_init();
    ErrorHandler(result);
    result = hackrf_open(&device);
    ErrorHandler(result);

    result = hackrf_set_sample_rate(device, samplerate);
    ErrorHandler(result);

    result = hackrf_set_freq(device, frequency);
    ErrorHandler(result);

    result = hackrf_set_vga_gain(device, BB);
    ErrorHandler(result);

    result = hackrf_set_lna_gain(device, IF);
    ErrorHandler(result);

    result = hackrf_set_amp_enable(device, 1);
    ErrorHandler(result);

    result = hackrf_start_rx(device, transfer_callback, NULL);
    ErrorHandler(result);

    sleep(1000);

    result = hackrf_stop_rx(device);
    ErrorHandler(result);
    result = hackrf_close(device);
    ErrorHandler(result);
    result = hackrf_exit();
    ErrorHandler(result);
    ExitReached = true; // 
    return 0;
}

*/