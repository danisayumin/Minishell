#include "headers/minishell.h"

t_minishell g_minishell;

void ft_init_minishell(char **env)
{
	ft_memset(&g_minishell, 0, sizeof(t_minishell));
	g_minishell.environ = env;
	g_minishell.stdin = dup(0);
	g_minishell.stdout = dup(1);
	tcgetattr(STDIN_FILENO, &g_minishell.original_term);
}

void ft_clear_line(void)
{
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


void ft_execute_command(char **args)
{
	int pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, g_minishell.environ) == -1)
		{
			perror("minishell"); // Se der erro na execução
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
	}
	else
	{
		perror("fork");
	}
}

void ft_clean_ms(void)
{
	clear_history();
	tcsetattr(STDIN_FILENO, TCSANOW, &g_minishell.original_term);
}

char **ft_split_cmd(char *line)
{
	return ft_split(line, ' ');
}

int main(int argc, char **argv, char **env)
{
	char **args;
	((void)argc, (void)argv);
	ft_init_minishell(env);
	while (1)
	{
		ft_init_signals();
		g_minishell.line = readline(PROMPT);
		if (!g_minishell.line) // Se o usuário pressionar Ctrl+D (EOF)
		{
			ft_clean_ms();
			ft_putstr_fd("exit\n", 1);
			exit(g_minishell.exit_s);
		}
		if (g_minishell.line[0])
		{
			add_history(g_minishell.line);
			args = ft_split_cmd(g_minishell.line); //minitokenização
			if (args[0])
				ft_execute_command(args); // Executa o comando
			free(args); // Libera a memória alocada
		}
		free(g_minishell.line);
	ft_clean_ms();
	return (g_minishell.exit_s);
}
}

