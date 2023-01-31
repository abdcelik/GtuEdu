#include "Signal.h"

sig_atomic_t sigint_count = 0;

void changeSignalAction(void (*handler)(int), int signal)
{
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler;

	x_sigfillset(&sa.sa_mask);
	x_sigaction(signal, &sa, NULL);
}

void SIGINT_handler(int signal_number)
{
	++sigint_count;
}

void checkSIGINT()
{
	if(sigint_count)
		exit(EXIT_FAILURE);
}

int isSIGINT()
{
	return sigint_count != 0;
}