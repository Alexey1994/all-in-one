#ifndef SYSTEM_THREAD_H_INCLUDED
#define SYSTEM_THREAD_H_INCLUDED


import Bit32 run_thread   (void (*thread_function)(), Bit8* arg);
import void  sleep_thread (Bit32 milliseconds);


#endif // SYSTEM_THREAD_H_INCLUDED
