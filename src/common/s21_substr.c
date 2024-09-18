#include "s21_common.h"

char	*s21_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*sub_str;

	i = 0;
	if (s21_strlen(s) < start)
		return (malloc(1));
	else
		sub_str = malloc(1);
	if (!sub_str || !s)
		return (NULL);
	while (len-- > 0 && s[start])
		sub_str[i++] = s[start++];
	sub_str[i] = '\0';
	return (sub_str);
}
