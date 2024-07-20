
int ft_strcmp(const char *s1, const char *s2)
{
	int i = 0;

	if (!s1 || !s2)
		return (1);
		
	while((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i]-s2[i]);
}