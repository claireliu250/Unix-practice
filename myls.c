/**
* 本程序在Mac环境下运行。
* ./a.out /home/
*
**/

#include <sys/types.h>
#include <dirent.h>
#include "ourhdr.h" // 使用 “ ” 来使用当前目录的头文件

int main(int argc, char const *argv[])
{
	DIR *dp;
	struct dirent *dirp;

	
	if(argc != 2) 
		err_quit("a single argument (the directory name) is required"); 

	// 判断是否能打开
	if ((dp = opendir(argv[1])) == NULL) 
		err_sys("can't open %s", argv[1]);  

	// 打印出文件名
	while ((dirp = readdir(dp)) != NULL)
	{
		printf("%s\n", dirp->d_name);
	}

	closedir(dp);

	return 0;
}