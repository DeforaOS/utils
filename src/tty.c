/* tty.c */



#include <unistd.h>
#include <stdio.h>


/* tty */
int tty(void)
{
	if(isatty(0) == 1)
	{
		char* tty;

		if((tty = ttyname(0)) == NULL)
			return 2;
		printf("%s\n", ttyname(0));
		return 0;
	}
	printf("not a tty\n");
	return 1;
}


/* usage */
int usage(void)
{
	fprintf(stderr, "%s", "Usage: tty\n");
	return 1;
}


/* main */
int main(int argc, char * argv[])
{
	/* parse command line arguments */
	if(argc != 1)
		return usage();
	return tty();
}
