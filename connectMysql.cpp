#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#include <mysql.h>
#include <string.h>
#include <iostream>
using namespace std;

MYSQL mysql, *sock;   //����MySQL�ľ�� 
/*
Ŀǰ�ó���ֻ������ָ�������ݿ⣬
�޷���MySQL�Դ��ͻ�������ͨ���������ݿ����ֽ�������
*/

//��ʾ��ǰ���ӵ����ݿ��е�����table
void display()
{
	MYSQL_RES * result; 
	MYSQL_ROW row;
	char *query1="SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = 'wlqing'";
	//��ѯ���еı���  ͬʱ���еı����Ѿ��ڿ���̨����ʾ
	if ( mysql_query(&mysql, query1) != 0 )       
	{ 
		printf("��ѯʧ�ܣ�ԭ����: \n"); 
		fprintf(stderr, " %s\n", mysql_error(&mysql));  
	} 
	else 
	{ 
		if ( (result = mysql_store_result(&mysql)) == NULL ) //�����ѯ�Ľ�� 
		{ 
			printf("��������ʧ�ܣ�ԭ����: \n"); 
			fprintf(stderr, " %s\n", mysql_error(&mysql));  

		} 
		else 
		{ 
			while ( (row = mysql_fetch_row(result)) != NULL ) //��ȡ������е����� 
			{ 
				printf("tableName is %s \n", row[0]);       //��ӡ��ǰ������� 
			} 
			
		} 
	}
}

void select()
{
	display();//��ѯ���еı���  ͬʱ���еı����Ѿ��ڿ���̨����ʾ
	MYSQL_RES * result; 
	MYSQL_ROW row;
	char column[100][100];
	MYSQL_FIELD *fd;
	char sql;
	printf("��������ı���б�������ݲ�ѯ����ʾ��select * from '����':\n ");
	getchar();
	gets(&sql);
	//scanf("%[^;]",&sql);
	//printf("%s \n",&sql);
	if (mysql_query(&mysql, &sql) != 0 )
		{
			printf("��ѯʧ�ܣ�ԭ����: \n"); 
			fprintf(stderr, " %s\n", mysql_error(&mysql)); 
		}
	else
		{
			if ( (result = mysql_store_result(&mysql)) == NULL ) //�����ѯ�Ľ�� 
				{ 
					printf("��������ʧ�ܣ�ԭ����: \n"); 
					fprintf(stderr, " %s\n", mysql_error(&mysql));  

				} 
			else 
				{ 
					int i , j ;
					//printf("���������Ŀ��%s \n",(unsigned long) mysql_num_rows( result ));
					for ( i = 0; fd = mysql_fetch_field( result ); i++ )    // ��ȡ���� 
					{
						strcpy( column[i], fd->name );
					}
					j = mysql_num_fields( result );//�õ��еĸ���
					for ( i = 0; i < j; i++ )     //��ӡ�õ�������
					{
						printf( "%s  ", column[i]);
					}
					printf( "\n" );
					while ( (row = mysql_fetch_row(result)) != NULL ) //��ȡ������е����� 
						{ 
							for ( i = 0; i < j; i++ )
							{
								printf( "%s     ", row[i] );//��ӡ�����ж�Ӧ�ľ������ݣ����ڵ��������޷���MySQL�ͻ�����������
							}
							printf( "\n" );
						} 
					mysql_free_result( result );//��ʱ��ѯ��ɣ��ͷŽ����
				} 
		}
} 

//ͨ������������ڱ��в����¼
void insert()
{
	display();
	char sql;
	printf("��������������sql��䣺\n");
	getchar();
	gets(&sql);

	if (mysql_query(&mysql, &sql) != 0)
	{
		printf("����ʧ�ܣ�ԭ����: \n"); 
		fprintf(stderr, " %s\n", mysql_error(&mysql));
	}
	else
	{
		printf("����ɹ�");
	}
}

//ͨ����������ݶ���Ӧ�ļ�¼�����޸ĸ���
void update()
{
	display();
	char sql;
	printf("��������²�����sql��䣺\n");
	getchar();
	gets(&sql);

	if (mysql_query(&mysql, &sql) != 0)
	{
		printf("�޸�ʧ�ܣ�ԭ����: \n"); 
		fprintf(stderr, " %s\n", mysql_error(&mysql));
	}
	else
	{
		printf("�޸ĳɹ�");
	}
}

//ɾ������ĳ����¼����ɾ�����еļ�¼
void Delete()
{
	display();
	char sql;
	printf("������ɾ��������sql��䣺\n");
	getchar();
	gets(&sql);
	if (mysql_query(&mysql, &sql) != 0)
	{
		printf("ɾ��ʧ�ܣ�ԭ����: \n"); 
		fprintf(stderr, " %s\n", mysql_error(&mysql));
	}
	else
	{
		printf("ɾ���ɹ�");
	}
}
//main������Ҫʵ�ֵĹ���
/*
	1.�������ݿ�
	2.���ӳɹ�֮�����ѡ����棬�ֱ������ɾ�Ĳ�ĺ�����
*/



int main()
{  
	int order;

	char host[20];
	printf("������ip��");
	scanf("%s",host);
	char user[20];
	printf("�������û�����");
	scanf("%s",user);
	char passwd[80];
	printf("���������룺");
	scanf("%s",passwd);
	char db[80];
	printf("���������ݿ⣺");
	scanf("%s",db);
	unsigned int port = 3306;           //����MySQL�ķ������Ķ˿�
	const char * unix_socket = NULL; 
	unsigned long client_flag = 0;      //�������һ��Ϊ0 
	mysql_init(&mysql);                          //����֮ǰ����ʹ�������������ʼ�� 
	if ( (sock = mysql_real_connect(&mysql,host, user, passwd, db, port, unix_socket, client_flag) ) == NULL ) //����MySQL 
	{ 
		printf("����ʧ�ܣ�ԭ����: \n"); 
		fprintf(stderr, " %s\n", mysql_error(&mysql));  
	} 
	//������ӳɹ�����ʾ��Ӧ�Ľ���������ݿ����ϵͳ
	else 
	{ 
		mysql_query( &mysql, "SET NAMES GBK" );   //���ӳɹ������ÿ�����ʾ����
		fprintf(stderr, "����MySQL�ɹ�����\n"); 
		while(1)
		{
			cout<<"========================================================="<<endl;
			cout<<"=+++++++++++++++++++�������ݿ����ϵͳ++++++++++++++++++="<<endl;
			cout<<"---------------------------------------------------------"<<endl;
			cout<<"=\t 1����ѯ\t  2������\t"<<endl;
			cout<<"=\t 3��ɾ��\t  4������\t"<<endl;
			cout<<"=\t        0���˳�     \t"<<endl;
			cout<<"========================================================="<<endl;
			cout<<"������������ţ�";
			cin>>order;
			
			switch (order)
			{
			case 1:
				select();
				break;
			case 2:
				insert();
				break;
			case 3:
				Delete();
				break;
			case 4:
				update();
				break;
			case 0:
				cout<<"�ټ�!";
				return 0;
				break;
			}
		system("pause"); 
		} 
	}
	 system("pause");
} 