#include "s21_common.h"

static void	recursive_convert_to_str(char **itoa, int n)
{
	static int	index;

	index = 0;
	if (n < 0)
	{
		(*itoa)[index++] = '-';
		n *= -1;
	}
	if (n >= 10)
		recursive_convert_to_str(itoa, n / 10);
	(*itoa)[index++] = n % 10 + 48;
	(*itoa)[index] = '\0';
}

char	*s21_itoa(int n)
{
	char	*itoa;
	char min_int[12] = "-2147483648";

	itoa = (char *)malloc(11);
	if (n == MIN_INT) {
		int i = 0;
		while(min_int[i] != '\0') {
			itoa[i] = min_int[i];
			i++;
		}
		itoa[i] = '\0';
		return (itoa);
	}
	recursive_convert_to_str(&itoa, n);
	return (itoa);
}
