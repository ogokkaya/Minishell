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


static int count_char(const char *str, char quote)
{
    int quote_count;

    quote_count = 0;
    while(*str)
    {
        if(*str == quote)
            quote_count++;
        str++;
    }
    return(quote_count % 2);
}

int check_quotes(const char *before, const char *after)
{
    int single_qoute_before;
    int single_qoute_after;
    int double_qoute_before;
    int double_qoute_after;

    // echo "'$USER'" koşulu gibi koşullarda direkt sonuc
    if(before[0] == '\"' && after[ft_strlen(after) - 1] == '\"')
        return(1);
    single_qoute_before = count_char(before, '\'');
    single_qoute_after = count_char(after, '\'');
    double_qoute_before = count_char(before, '\"');
    double_qoute_after = count_char(after, '\"');

    // cift tırnakta "$" koşul için
    if(!double_qoute_after && after[1] == '\"')
        return(0);
    // sadece cift tırnak
    else if(double_qoute_before && double_qoute_after && !single_qoute_after && !single_qoute_before)
        return(1);
    //tek tırnak düzensiz kapanma koşulunda koydum input controlde kalırsa buna gerek yok
    else if((!single_qoute_after && single_qoute_before) || (!single_qoute_before && single_qoute_after))
        return(1);
    // hem tırnaksızda hem de tırnaksızdan sonra gelen tırnakda $USER"$USER"
    else if(!single_qoute_after && !single_qoute_before && !double_qoute_after && !double_qoute_before)
        return(1);
    return(0);
}
