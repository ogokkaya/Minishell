#include "../minishell.h"
#include <stdio.h>


char *find_env(t_mshell *shell, char *path)
{
    t_env *search_env;

    search_env = shell->env;
    while(search_env != NULL)
    {
        // bu kısma bak 
        if((ft_strncmp(search_env->name, path, ft_strlen(search_env->name)) == 0) && (ft_strncmp(search_env->name, path, ft_strlen(path)) == 0))
            return(ft_strdup(search_env->content));
        search_env = search_env->next;
    }
    return(ft_strdup(""));
    // bu kısım düşünülmeli
}

int *exit_status(void)
{
    static int exit_status = 0;

    return(&exit_status);
}

int count_char(const char *str, char quote)
{
    int quote_count;

    quote_count = 0;
    while(*str)
    {
        if(*str == quote)
        {
            quote_count++;
        }
        str++;
    }
    return(quote_count % 2);
}

int check_quotes(const char *before, const char *after)
{
    int single_quote_before = count_char(before, '\'');
    int single_quote_after = count_char(after, '\'');
    int double_quote_before = count_char(before, '\"');
    int double_quote_after = count_char(after, '\"');

    // Çift tırnakta "$" koşulu için
    if (!double_quote_after && after[1] == '\"')
        return (0);
    // sadece tek tırnak olduğunda
    else if((single_quote_before && single_quote_after) && (!double_quote_before && after[ft_strlen(after -1)] != '\"'))
        return(0);
    // çift tırnaklar düzgün kapandıysa ve tek tırnak yoksa
    else if ((double_quote_before && double_quote_after) && (!single_quote_after && !single_quote_before))
        return (1);
    // Tek tırnaklarda düzensiz kapanma varsa
    else if ((!single_quote_after && single_quote_before) || (!single_quote_before && single_quote_after))
        return (1);
    // Hem tek tırnak hem de çift tırnak yoksa
    else if ((!single_quote_after && !single_quote_before) && (!double_quote_after && !double_quote_before))
        return (1);
    else if ((single_quote_after && single_quote_before) && (double_quote_after && double_quote_before))
        return (1);
    return 0;
}
