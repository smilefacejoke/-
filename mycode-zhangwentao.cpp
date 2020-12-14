//头文件引入
#include<iostream>
#include<stdio.h>
#include<cstring>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<fcntl.h>
#include<ftw.h>
#include<queue>


using namespace std;

//类型定义
#define Long 200//限制单次输入字符串长度
char cmd[Long];//暂时存放命令字符
char split[20][100];//分解字符串


//函数声明
void menu();		//菜单显示
void pwd();			//查看当前路径
void list();		//列出指定目录的所有文件以及目录
void modifydir();	//改变当前工作目录
void makedir();		//新建目录
void deldir();		//删除目录
void exit();		//退出命令解释程序

//扩展命令
void rename();		//重命名一个文件夹或目录
void copy();		//复制一个已存在的文件

int main()
{
	menu();
	while (1)
	{
		int longth = 0;//字符串命令长度计数
		int count = 0;//命令分段数
		cout << "My_Computer@:";
		cin.getline(cmd, Long);//从io设备中读取信息
		for (int i = 0; i < strlen(cmd); i++)
		{
			//分解命令，储存到split二维数组内
			if (cmd[i] == ' ')
			{
				longth = 0;//长度重新计数
				count++;//命令分段数增加
				i++;
			}
			split[count][longth] = cmd[i];
			longth++;//每赋值一个字符长度增加1
		}

		//运行pwd函数
		if (strcmp(split[0], "pwd" )== 0)
		{
			pwd();
			memset(cmd, 0, sizeof cmd);
			memset(split, 0, sizeof split);//将内存初始化以防出现覆盖乱码
		}

		//运行list命令
		else if (strcmp(split[0], "list") == 0)
		{
			list();
			memset(cmd, 0, sizeof cmd);
			memset(split, 0, sizeof split);
		}

		//运行modifydir命令
		else if (strcmp(split[0], "modifydir") == 0)
		{
			modifydir();
			memset(cmd, 0, sizeof cmd);
			memset(split, 0, sizeof split);
		}

		//运行makedir命令
		else if (strcmp(split[0], "makedir") == 0)
		{
			makedir();
			memset(cmd, 0, sizeof cmd);
			memset(split, 0, sizeof split);
		}

		//运行deldir命令
		else if (strcmp(split[0], "deldir") == 0)
		{
			deldir();
			memset(cmd, 0, sizeof cmd);
			memset(split, 0, sizeof split);
		}

		//运行rename命令
		else if (strcmp(split[0], "rename") == 0)
		{
			rename();
			memset(cmd, 0, sizeof cmd);
			memset(split, 0, sizeof split);
		}

		//运行copy命令
		else if (strcmp(split[0], "copy") == 0)
		{
			copy();
			memset(cmd, 0, sizeof cmd);
			memset(split, 0, sizeof split);
		}


		//运行退出函数
		else if(strcmp(split[0], "exit") == 0)
		{
			exit();
		}

	}
	return 0;
}

//菜单函数
void menu() {
	system("clear");
	cout << "---------------      功能清单介绍    --------------" << endl;
	cout << "|                                                 |" << endl;
	cout << "|     pwd       显示当前所在目录的路径名          |" << endl;
	cout << "|                                                 |" << endl;
	cout << "|     list   列出指定目录名中的所有目录及文件     |" << endl;
	cout << "|                                                 |" << endl;
	cout << "|     modifydir	 改变当前工作目录			   |" << endl;
	cout << "|                                                 |" << endl;
	cout << "|     makedir	     新建目录                      |" << endl;
	cout << "|                                                 |" << endl;
	cout << "|     deldir 	     删除目录                      |" << endl;
	cout << "|                                                 |" << endl;
	cout << "|     rename        重命名一个文件或目录          |" << endl;
	cout << "|                                                 |" << endl;
	cout << "|     copy          复制一个已存在的文件          |" << endl;
	cout << "|                                                 |" << endl;
	cout << "|     exit            退出命令解释程序            |" << endl;
	cout << "|                                                 |" << endl;
	cout << "---------------------------------------------------" << endl;
}

//显示当前所在目录的路径名
void pwd()
{
	char show[Long];
	cout << "当前所在目录的路径名:" << endl;
	getcwd(show, Long);
	cout << show << endl << "输出完毕" << endl;
}

//列出指定目录名中的所有目录及文件
void list()
{
	DIR *d;
	struct dirent *dirent;
	if (strcmp("", split[1]) == 0)//当未指定目录名时，打开当前的工作目录
	{
		d = opendir(".");
	}
	else
	{
		d = opendir(split[1]);//指定了目录名后，获取名称并打开显示
	}
	if (d == NULL)
	{
		cout << "目录打开失败！！" << endl;
	}
	while ((dirent = readdir(d)) != NULL)//依次读取目录信息
	{
		if (dirent->d_name[0] != '.')
		{
			cout << dirent->d_name << " ";
		}
	}
	cout << endl;
	closedir(d);//关闭目录
	cout << "输出结束。" << endl;
}

//改变当前工作目录
void modifydir()
{
	if (chdir(split[1]) == -1)
	{
		cout << "所输入命令不存在" << endl;
	}
	else
	{
		cout << "切换目录成功！" << endl;
	}
}

//新建目录
void makedir()
{
	if (mkdir(split[1], 0777) == 0)
	{
		cout << split[1] << "目录新建成功" << endl;
	}
	else
	{
		cout << split[1] << "目录新建失败" << endl;
	}
}

//删除目录
void deldir()
{
	if (rmdir(split[1]) == 0)
	{
		cout << "目录删除成功" << endl;
	}
	else
	{
		cout << "目录删除失败" << endl;
	}
}

//重命名一个文件或目录
void rename()
{
	if (rename(split[1], split[2]) == 0)
	{
		cout << "成功将其重命名" << endl;
	}
	else
	{
		cout << "重命名失败" << endl;
	}
}

//复制一个已存在文件
void copy()
{
	int f1, f2;
	string str = split[2];
	char buffer[Long];
	f1 = open(split[1], O_RDONLY);
	if (f1 == -1)
	{
		cout << "复制失败" << endl;
	}
	else
	{
		f2 = open(split[2], O_RDONLY);
		if (f2 != -1)
		{
			str += "(new)";
			close(f2);
		}
		f2 = open(str.c_str(), O_RDONLY | O_CREAT, S_IRWXU);
		int size = read(f1, buffer, sizeof(buffer));
		write(f2, buffer, size);
		close(f1);
		close(f2);
	}
}

//退出程序部分
void exit()
{
	cout << "退出此命令解释器" << endl;
	exit(0);
}