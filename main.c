#include "headers/minishell.h"
#include <string.h> // Para strlen e strncpy

// Implementação da função ft_memset
void *ft_memset(void *s, int c, size_t n)
{
    unsigned char *ptr = s;
    while (n--)
        *ptr++ = (unsigned char)c;
    return s;
}

// Implementação da função ft_putstr_fd
void ft_putstr_fd(char *s, int fd)
{
    if (s)
        write(fd, s, strlen(s));
}

// Implementação da função ft_split
char **ft_split(const char *s, char c)
{
    // Implementação básica para dividir a string s por delimitador c
    // Retorna um array de strings (char **)
    // Esta é uma versão simplificada para fins de exemplo
    // Uma implementação completa requer mais código para lidar com casos de erro e alocação
    char **result;
    size_t i = 0, j = 0, k = 0;
    size_t count = 1;
    for (i = 0; s[i]; i++)
        if (s[i] == c)
            count++;
    result = malloc((count + 1) * sizeof(char *));
    if (!result)
        return NULL;
    result[count] = NULL;
    for (i = 0; i < count; i++)
    {
        while (s[j] == c)
            j++;
        k = j;
        while (s[k] && s[k] != c)
            k++;
        result[i] = malloc(k - j + 1);
        if (!result[i])
        {
            while (i--)
                free(result[i]);
            free(result);
            return NULL;
        }
        strncpy(result[i], s + j, k - j);
        result[i][k - j] = '\0';
        j = k;
    }
    return result;
}

// Definição da variável global
t_minishell g_minishell;

// Implementação de funções não fornecidas no exemplo
void ft_init_minishell(char **env);
void ft_init_signals(void);
void ft_clean_ms(void);
char **ft_split_cmd(char *line)
{
    return ft_split(line, ' ');
}
void ft_execute_command(char **args);

int main(int argc, char **argv, char **env)
{
    char    **args;

    (void)argc;
    (void)argv;
    ft_init_minishell(env);
    while (1)
    {
        ft_init_signals();
        g_minishell.line = readline(PROMPT); // Exibe o prompt e lê a linha
        if (!g_minishell.line) // Se o usuário pressionar Ctrl+D (EOF)
        {
            ft_clean_ms();
            ft_putstr_fd("exit\n", 1);
            exit(g_minishell.exit_s);
        }
        if (g_minishell.line[0]) // Se houver uma entrada
        {
            add_history(g_minishell.line); // Adiciona ao histórico
            args = ft_split_cmd(g_minishell.line); // Divide a linha em argumentos
            if (args[0])
                ft_execute_command(args); // Executa o comando
            free(args); // Libera a memória alocada
        }
        free(g_minishell.line); // Libera a linha
    }
    ft_clean_ms();
    return (g_minishell.exit_s);
}


