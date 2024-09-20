#include <iostream>

int	s21_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int main() {
	std::cout << s21_isdigit('0' - 1) << std::endl;
	std::cout << ('0' - 1) << std::endl;

}
