// gcc -Wall printUidAndGid.c libmy.a -o printUidAndGid.out

#include "ourhdr.h"

int main(int argc, char const *argv[])
{
	
	printf("uid = %d ,gid = %d\n", getuid(), getgid());
	exit(0);		
}