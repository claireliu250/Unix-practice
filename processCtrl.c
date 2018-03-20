// gcc -Wall processCtrl.c libmy.a -o processCtrl.out

/**

该 程 序 从 标 准 输 入 读 命令，然后执行这些命令。这是一个类似于 s h e l l 程序的基本实施部分。在这个 3 0 行 的 程 序 中 ， 有很多功能需要思考:
• 用标准 I / O 函数 f g e t s 从标准输入一次读一行，当键入文件结束字符(通常是 C t r l - D )作为 行的第1个字符时，fgets返回一个null指针，于是循环终止，进程也就终止。第 11章将说明所有 特殊的终端字符 (文件结束、退格字符、整行擦除等等 )，以及如何改变它们。
• 因为 f g e t s 返回的每一行都以新行符终止，后随一个 n u l l字节，故用标准 C 函数 s t r l e n计算此 字 符 串 的 长 度 ， 然 后 用 一 个 n u l l 字 节 替 换 新 行 符 。 这 一 操 作 的 目 的 是 因 为 e x e c l p函 数 要 求 的 是 以 n u l l 结束的参数，而不是以新行符结束的参数。
• 调用 f o r k 创 建 一 个 新 进 程 。 新 进 程 是 调 用 进 程 的 复 制 品 ， 故 称 调 用 进 程 为 父 进 程 ， 新 创 建的进程为子进程。 f o r k 对父进程返回新子进程的非负进程 I D ，对子进程则返回 0 。因为 f o r k创 建一新进程，所以说它被调用一次(由父进程)，但返回两次(在父进程中和在子进程中)。
• 在子进程中，调用 e x e c l p以 执 行 从 标 准 输 入 读 入 的 命 令 。 这 就 用 新 的 程 序 文 件 替 换 了 子 进程。 f o r k 和跟随其后的 e x e c的组合是某些操作系统所称的产生一个新进程。在 U N I X 中，这两 个部分分成两个函数。第 8章将对这些函数作更多说明。
• 子进程调用 e x e c l p 执行新程序文件，而父进程希望等待子进程终止，这一要求由调用 w a i t p i d 实 现 ， 其 参 数 指 定 要 等 待 的 进 程 ( 在这里， p i d 参 数 是 子 进 程 I D ) 。 w a i t p i d 函 数 也 返 回 子 进 程 的 终 止 状 态 ( s t a t u s 变量 ) 。 在 此 简 单 程 序 中 ， 没 有 使 用 该 值 。 如 果 需 要 ， 可 以 用 此 值 精 确 地 确定子进程是如何终止的。
• 该程序的最主要限制是不能向执行的命令传递参数。例如不能指定列出的目录名，只能 对工作目录执行 l s 命令。为了传递参数，先要分析输入行，然后用某种约定把参数分开 (很可能 使用空格或制表符 ) ，然后将分隔后的各个参数传递给 e x e c l p 函 数 。 尽 管 如 此 ， 此 程 序 仍 可 用 来 说明 U N I X的进程控制功能。

**/

#include <sys/types.h>
#include <sys/wait.h>
#include "ourhdr.h"

int main(int argc, char const *argv[])
{
	
	char buf[MAXLINE];
	pid_t pid;
	int status;

	printf("%% ");

	while (fgets(buf, MAXLINE, stdin) != NULL) {

		buf[strlen(buf) - 1] = 0; 

		if ( ( pid = fork()) < 0)
			err_sys("fork error");

		else if (pid ==0) 
		{
			execlp(buf , buf , (char * ) 0);
			err_ret("couldn't execute: %s ", buf);
			exit(127);
		}

		if( (pid = waitpid(pid, &status, 0)) < 0)
			err_sys("waitpid error");

		printf("%% ");
	}

	exit(0);
}

