#include "libft.h"

int	ft_isalnum_mshell(int c)
{
	return (ft_isalpha_and_(c) || ft_isdigit(c));
}