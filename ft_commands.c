
#include "headers/minishell.h"
#include <unistd.h>
#include <sys/wait.h>

void ft_execute_command(char **args)
{
    pid_t pid;
    int status;

    pid = fork(); // Criando um processo filho
    if (pid == 0)
    {
        // Processo filho: tenta executar o comando
        if (execve(args[0], args, g_minishell.environ) == -1)
        {
            perror("minishell"); // Se der erro na execução
            exit(EXIT_FAILURE);
        }
    }
    else if (pid > 0)
    {
        // Processo pai: espera o filho terminar
        waitpid(pid, &status, 0);
    }
    else
    {
        perror("fork"); // Se der erro ao criar o processo
    }
}



void ft_clean_ms(void)
{
    // Limpa a memória e restaura o terminal
    clear_history();
    tcsetattr(STDIN_FILENO, TCSANOW, &g_minishell.original_term);
}
