
#include "headers/minishell.h"

void ft_init_minishell(char **env)
{
    ft_memset(&g_minishell, 0, sizeof(t_minishell));
    g_minishell.environ = env;
    g_minishell.stdin = dup(0);
    g_minishell.stdout = dup(1);
    tcgetattr(STDIN_FILENO, &g_minishell.original_term);
}

