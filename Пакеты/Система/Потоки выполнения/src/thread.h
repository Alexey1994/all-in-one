#ifndef THREAD_H_INCLUDED
#define THREAD_H_INCLUDED


import function  Byte* run_thread   (procedure (*thread_function)(), Byte *arg);
import procedure       sleep_thread (N_32 milliseconds);


#endif // THREAD_H_INCLUDED
