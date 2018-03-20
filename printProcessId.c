// gcc -Wall printProcessId.c libmy.a -o printProcessId.out
#include "ourhdr.h"

int main(int argc, char const *argv[])
{
	printf("hello world from process Id %d\n", getpid());
	exit(0);
}
