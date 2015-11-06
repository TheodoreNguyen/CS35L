#include <stdio.h>

int main(int argc, char** argv)
{
	int buffer;
	while((buffer = getchar()) != EOF)
	{
		putchar((char)buffer);
	}
	return 0;
}

