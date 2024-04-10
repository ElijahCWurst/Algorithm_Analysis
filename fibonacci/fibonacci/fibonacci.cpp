#include <iostream>
// use gnu to get large number of fibonacci



unsigned long long fibonacci(unsigned long long n)
{
	if (n <= 1)
		return n;
	unsigned long long a = 0, b = 1;
	for (unsigned long long i = 2; i <= n; i++)
	{
		unsigned long long c = a + b;
		a = b;
		b = c;
	}
	return b;
}

int main()
{
	std::cout << fibonacci(100000) << std::endl;
}

