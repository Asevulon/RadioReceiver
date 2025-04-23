#include "hackrf.h"
#include "mutex"
#include "thread"
#include <vector>
#include <pthread.h>
//только один экземпляр
class Receiver
{
private:
    /* data */
    int samplerate = 8e6;
    int frequency = 935e6;
    int IF = 16;

    hackrf_device *device = nullptr;
    std::vector<double>data;
    pthread_mutex_t datamutex;
    pthread_mutex_t waitmutex;
    pthread_cond_t waitcond;
    
    std::thread* pRXthread;
    pthread_mutex_t startmutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t startcond = PTHREAD_COND_INITIALIZER;

    hackrf_error LastError = hackrf_error::HACKRF_SUCCESS;
    int LastResult = 0;

    int Receive();
    static int transfer_callback(hackrf_transfer *transfer);
    void CloseDevice();

public:
    Receiver(/* args */);
    ~Receiver();

    hackrf_error SetSamplerate(const int value);
    hackrf_error SetFrequency(const int value);
    hackrf_error SetAmplify(const int value);

    hackrf_error GetLastError();

    hackrf_error StopRX();
    hackrf_error StartRX();

    std::vector<double>GetData();
};

