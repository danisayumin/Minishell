
#include "headers/minishell.h"
#include <signal.h>
#include <readline/readline.h>

// Função para limpar a linha atual no terminal
void ft_clear_line(void)
{
    // Move o cursor para o início da linha e limpa a linha
    printf("\033[2K\r");
}

void ft_sigint_handler(int num)
{
    (void)num;
    if (g_minishell.signint_child)
    {
        ft_putstr_fd("\n", 1);
        g_minishell.signint_child = false;
        g_minishell.heredoc_sigint = true;
    }
    else
    {
        ft_putstr_fd("\n", 1);
        ft_clear_line();
        rl_on_new_line();
        rl_redisplay();
    }
}

void ft_init_signals(void)
{
    signal(SIGINT, ft_sigint_handler);
    signal(SIGQUIT, SIG_IGN);
}