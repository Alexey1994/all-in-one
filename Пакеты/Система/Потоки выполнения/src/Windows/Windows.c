export Bit32 run_thread (procedure (*thread_function)(), Bit8* arg)
{
	Bit32 thread_id;

	CreateThread(0, 0, thread_function, arg, 0, &thread_id);

	return thread_id;
}


export void sleep_thread (Bit32 milliseconds)
{
	Sleep(milliseconds);
}
