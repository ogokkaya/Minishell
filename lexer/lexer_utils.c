#include "../minishell.h"

void	ft_lstadd_back_lexer(t_lexer **lst, t_lexer *new)
{
	t_lexer	*ptr;

	if (*lst == NULL)
		*lst = new;
	else
	{
		ptr = *lst;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
}

t_lexer	*ft_lstnew_lexer(t_mshell *shell ,char *content, t_token_type type)
{
	t_lexer	*new;

	new = ft_calloc(1, sizeof(t_lexer));
	if (!new)
		return (0);
	new->type = type;
	new->content = content;
	new->next = NULL;
    my_malloc(shell->block, content);
    my_malloc(shell->block, new);
	return (new);
}