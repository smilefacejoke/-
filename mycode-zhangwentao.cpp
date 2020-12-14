//ͷ�ļ�����
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

//���Ͷ���
#define Long 200//���Ƶ��������ַ�������
char cmd[Long];//��ʱ��������ַ�
char split[20][100];//�ֽ��ַ���


//��������
void menu();		//�˵���ʾ
void pwd();			//�鿴��ǰ·��
void list();		//�г�ָ��Ŀ¼�������ļ��Լ�Ŀ¼
void modifydir();	//�ı䵱ǰ����Ŀ¼
void makedir();		//�½�Ŀ¼
void deldir();		//ɾ��Ŀ¼
void exit();		//�˳�������ͳ���

//��չ����
void rename();		//������һ���ļ��л�Ŀ¼
void copy();		//����һ���Ѵ��ڵ��ļ�

int main()
{
	menu();
	while (1)
	{
		int longth = 0;//�ַ�������ȼ���
		int count = 0;//����ֶ���
		cout << "My_Computer@:";
		cin.getline(cmd, Long);//��io�豸�ж�ȡ��Ϣ
		for (int i = 0; i < strlen(cmd); i++)
		{
			//�ֽ�������浽split��ά������
			if (cmd[i] == ' ')
			{
				longth = 0;//�������¼���
				count++;//����ֶ�������
				i++;
			}
			split[count][longth] = cmd[i];
			longth++;//ÿ��ֵһ���ַ���������1
		}

		//����pwd����
		if (strcmp(split[0], "pwd" )== 0)
		{
			pwd();
			memset(cmd, 0, sizeof cmd);
			memset(split, 0, sizeof split);//���ڴ��ʼ���Է����ָ�������
		}

		//����list����
		else if (strcmp(split[0], "list") == 0)
		{
			list();
			memset(cmd, 0, sizeof cmd);
			memset(split, 0, sizeof split);
		}

		//����modifydir����
		else if (strcmp(split[0], "modifydir") == 0)
		{
			modifydir();
			memset(cmd, 0, sizeof cmd);
			memset(split, 0, sizeof split);
		}

		//����makedir����
		else if (strcmp(split[0], "makedir") == 0)
		{
			makedir();
			memset(cmd, 0, sizeof cmd);
			memset(split, 0, sizeof split);
		}

		//����deldir����
		else if (strcmp(split[0], "deldir") == 0)
		{
			deldir();
			memset(cmd, 0, sizeof cmd);
			memset(split, 0, sizeof split);
		}

		//����rename����
		else if (strcmp(split[0], "rename") == 0)
		{
			rename();
			memset(cmd, 0, sizeof cmd);
			memset(split, 0, sizeof split);
		}

		//����copy����
		else if (strcmp(split[0], "copy") == 0)
		{
			copy();
			memset(cmd, 0, sizeof cmd);
			memset(split, 0, sizeof split);
		}


		//�����˳�����
		else if(strcmp(split[0], "exit") == 0)
		{
			exit();
		}

	}
	return 0;
}

//�˵�����
void menu() {
	system("clear");
	cout << "---------------      �����嵥����    --------------" << endl;
	cout << "|                                                 |" << endl;
	cout << "|     pwd       ��ʾ��ǰ����Ŀ¼��·����          |" << endl;
	cout << "|                                                 |" << endl;
	cout << "|     list   �г�ָ��Ŀ¼���е�����Ŀ¼���ļ�     |" << endl;
	cout << "|                                                 |" << endl;
	cout << "|     modifydir	 �ı䵱ǰ����Ŀ¼			   |" << endl;
	cout << "|                                                 |" << endl;
	cout << "|     makedir	     �½�Ŀ¼                      |" << endl;
	cout << "|                                                 |" << endl;
	cout << "|     deldir 	     ɾ��Ŀ¼                      |" << endl;
	cout << "|                                                 |" << endl;
	cout << "|     rename        ������һ���ļ���Ŀ¼          |" << endl;
	cout << "|                                                 |" << endl;
	cout << "|     copy          ����һ���Ѵ��ڵ��ļ�          |" << endl;
	cout << "|                                                 |" << endl;
	cout << "|     exit            �˳�������ͳ���            |" << endl;
	cout << "|                                                 |" << endl;
	cout << "---------------------------------------------------" << endl;
}

//��ʾ��ǰ����Ŀ¼��·����
void pwd()
{
	char show[Long];
	cout << "��ǰ����Ŀ¼��·����:" << endl;
	getcwd(show, Long);
	cout << show << endl << "������" << endl;
}

//�г�ָ��Ŀ¼���е�����Ŀ¼���ļ�
void list()
{
	DIR *d;
	struct dirent *dirent;
	if (strcmp("", split[1]) == 0)//��δָ��Ŀ¼��ʱ���򿪵�ǰ�Ĺ���Ŀ¼
	{
		d = opendir(".");
	}
	else
	{
		d = opendir(split[1]);//ָ����Ŀ¼���󣬻�ȡ���Ʋ�����ʾ
	}
	if (d == NULL)
	{
		cout << "Ŀ¼��ʧ�ܣ���" << endl;
	}
	while ((dirent = readdir(d)) != NULL)//���ζ�ȡĿ¼��Ϣ
	{
		if (dirent->d_name[0] != '.')
		{
			cout << dirent->d_name << " ";
		}
	}
	cout << endl;
	closedir(d);//�ر�Ŀ¼
	cout << "���������" << endl;
}

//�ı䵱ǰ����Ŀ¼
void modifydir()
{
	if (chdir(split[1]) == -1)
	{
		cout << "�������������" << endl;
	}
	else
	{
		cout << "�л�Ŀ¼�ɹ���" << endl;
	}
}

//�½�Ŀ¼
void makedir()
{
	if (mkdir(split[1], 0777) == 0)
	{
		cout << split[1] << "Ŀ¼�½��ɹ�" << endl;
	}
	else
	{
		cout << split[1] << "Ŀ¼�½�ʧ��" << endl;
	}
}

//ɾ��Ŀ¼
void deldir()
{
	if (rmdir(split[1]) == 0)
	{
		cout << "Ŀ¼ɾ���ɹ�" << endl;
	}
	else
	{
		cout << "Ŀ¼ɾ��ʧ��" << endl;
	}
}

//������һ���ļ���Ŀ¼
void rename()
{
	if (rename(split[1], split[2]) == 0)
	{
		cout << "�ɹ�����������" << endl;
	}
	else
	{
		cout << "������ʧ��" << endl;
	}
}

//����һ���Ѵ����ļ�
void copy()
{
	int f1, f2;
	string str = split[2];
	char buffer[Long];
	f1 = open(split[1], O_RDONLY);
	if (f1 == -1)
	{
		cout << "����ʧ��" << endl;
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

//�˳����򲿷�
void exit()
{
	cout << "�˳������������" << endl;
	exit(0);
}