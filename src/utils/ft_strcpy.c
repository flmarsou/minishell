#include "minishell.h"

unsigned char	*ft_strcpy(unsigned char *dest, unsigned char *src, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
