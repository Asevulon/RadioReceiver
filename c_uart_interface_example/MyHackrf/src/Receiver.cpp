#include"Receiver.h"
#include"general.h"

pthread_mutex_t* pdatamutex;
std::vector<double>* pdata;

int Receiver::Receive()
{
    pthread_mutex_lock(&startmutex);

    LastResult = hackrf_init();
    ErrorHandler(LastResult);
    if(LastResult != HACKRF_SUCCESS)
    { 
        CloseDevice(); 
        pthread_cond_broadcast(&startcond);
        pthread_mutex_unlock(&startmutex);
        return LastResult;
    }
    
    LastResult = hackrf_open(&device);
    ErrorHandler(LastResult);
    if(LastResult != HACKRF_SUCCESS)
    { 
        CloseDevice(); 
        pthread_cond_broadcast(&startcond);
        pthread_mutex_unlock(&startmutex);
        return LastResult;
    }

    LastResult = hackrf_set_sample_rate(device, samplerate);
    ErrorHandler(LastResult);
    if(LastResult != HACKRF_SUCCESS)
    { 
        CloseDevice(); 
        pthread_cond_broadcast(&startcond);
        pthread_mutex_unlock(&startmutex);
        return LastResult;
    }

    LastResult = hackrf_set_freq(device, frequency);
    ErrorHandler(LastResult);
    if(LastResult != HACKRF_SUCCESS)
    { 
        CloseDevice(); 
        pthread_cond_broadcast(&startcond);
        pthread_mutex_unlock(&startmutex);
        return LastResult;
    }

    LastResult = hackrf_set_lna_gain(device, IF);
    ErrorHandler(LastResult);
    if(LastResult != HACKRF_SUCCESS)
    { 
        CloseDevice(); 
        pthread_cond_broadcast(&startcond);
        pthread_mutex_unlock(&startmutex);
        return LastResult;
    }

    LastResult = hackrf_set_amp_enable(device, 1);
    ErrorHandler(LastResult);
    if(LastResult != HACKRF_SUCCESS)
    { 
        CloseDevice(); 
        pthread_cond_broadcast(&startcond);
        pthread_mutex_unlock(&startmutex);
        return LastResult;
    }

    LastResult = hackrf_start_rx(device, Receiver::transfer_callback, NULL);
    ErrorHandler(LastResult);
    if(LastResult != HACKRF_SUCCESS)
    { 
        CloseDevice(); 
        pthread_cond_broadcast(&startcond);
        pthread_mutex_unlock(&startmutex);
        return LastResult;
    }

    pthread_cond_broadcast(&startcond);
    pthread_mutex_unlock(&startmutex);

    pthread_mutex_lock(&waitmutex);
    pthread_cond_wait(&waitcond, &waitmutex);

    CloseDevice();
    return 0;
}
Receiver::Receiver(/* args */)
{
    datamutex = PTHREAD_MUTEX_INITIALIZER;
    waitmutex = PTHREAD_MUTEX_INITIALIZER;
    waitcond = PTHREAD_COND_INITIALIZER;
    pdatamutex = &datamutex;
    pdata = &data;
}

Receiver::~Receiver()
{
    CloseDevice();
}

hackrf_error Receiver::SetSamplerate(const int value)
{
    samplerate = value;
    LastError = hackrf_error::HACKRF_SUCCESS;
    return LastError;
}

hackrf_error Receiver::SetFrequency(const int value)
{
    frequency = value;
    LastError = hackrf_error::HACKRF_SUCCESS;
    return LastError;
}

hackrf_error Receiver::SetAmplify(const int value)
{
    IF = value;
    LastError = hackrf_error::HACKRF_SUCCESS;
    return LastError;
}

hackrf_error Receiver::GetLastError()
{
    return LastError;
}

hackrf_error Receiver::StopRX()
{
    pthread_mutex_lock(&waitmutex);
    pthread_cond_broadcast(&waitcond);
    pthread_mutex_unlock(&waitmutex);
    return hackrf_error::HACKRF_SUCCESS;
}

hackrf_error Receiver::StartRX()
{
    pthread_mutex_lock(&startmutex);
    pRXthread = new std::thread([&](){Receive();}
    );
    pthread_cond_wait(&startcond, &startmutex);
    pRXthread->detach();

    return hackrf_error(LastResult);
}

std::vector<double> Receiver::GetData()
{
    pthread_mutex_lock(&datamutex);
    auto temp = data;
    pthread_mutex_unlock(&datamutex);
    return temp;
}

int Receiver::transfer_callback(hackrf_transfer *transfer) 
{
    int8_t *signed_buffer = (int8_t*)transfer->buffer;

    std::vector<double> tdata = ToDouble(signed_buffer, transfer->buffer_length);
    RemoveConst(tdata);

    pthread_mutex_lock(pdatamutex);
    *pdata = tdata;
    pthread_mutex_unlock(pdatamutex);

    return 0;
}

void Receiver::CloseDevice()
{
    if(device == nullptr)return;
    LastResult = hackrf_stop_rx(device);
    ErrorHandler(LastResult);
    LastResult = hackrf_close(device);
    ErrorHandler(LastResult);
    LastResult = hackrf_exit();
    ErrorHandler(LastResult);
    device = nullptr;
}
