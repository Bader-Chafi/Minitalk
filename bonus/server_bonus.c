#include "minitalk_bonus.h"

void sig_usr(int sig, siginfo_t *info, void *context)
{
    static unsigned char    accumulator;
    static int              bit_count;
    static int              c_pid;

    (void)context;
    if (c_pid != info->si_pid)
        (1) && (accumulator = 0, bit_count = 0, c_pid = info->si_pid);
    accumulator = accumulator << 1;
    if (sig == SIGUSR2)
        accumulator |= 1;
    bit_count++;
    if (bit_count == 8)
    {
        ft_printf("%c", accumulator);
        if (accumulator == '\0')
        {   
            ft_printf("\n");
            kill(c_pid, SIGUSR1);
        }
        (1) && (accumulator = 0, bit_count = 0);
    }
}


int main(void)
{
    struct sigaction sa;

    ft_printf("PID: %d\n", getpid());
    sa.sa_sigaction = sig_usr;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
        exit(EXIT_FAILURE);
    while(1) pause();
}