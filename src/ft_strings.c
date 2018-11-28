#include "scop.h"

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int		ft_strdel(char **as)
{
	if (as != NULL)
	{
		free(*as);
		*as = NULL;
	}
	return (1);
}

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*str;

	i = -1;
	if (!(str = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (++i <= size)
		str[i] = 0;
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*new;

	i = -1;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(new = ft_strnew(len1 + len2)))
		return (NULL);
	while (++i < len1 + len2)
		new[i] = (i < len1 ? s1[i] : s2[i - len1]);
	new[i] = '\0';
	return (new);
}