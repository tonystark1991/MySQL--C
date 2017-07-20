#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#include <mysql.h>
#include <string.h>
#include <iostream>
using namespace std;

MYSQL mysql, *sock;   //声明MySQL的句柄 
/*
目前该程序只能连接指定的数据库，
无法像MySQL自带客户端那样通过输入数据库名字进行连接
*/

//显示当前连接的数据库中的所有table
void display()
{
	MYSQL_RES * result; 
	MYSQL_ROW row;
	char *query1="SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = 'wlqing'";
	//查询所有的表名  同时所有的表名已经在控制台上显示
	if ( mysql_query(&mysql, query1) != 0 )       
	{ 
		printf("查询失败，原因是: \n"); 
		fprintf(stderr, " %s\n", mysql_error(&mysql));  
	} 
	else 
	{ 
		if ( (result = mysql_store_result(&mysql)) == NULL ) //保存查询的结果 
		{ 
			printf("保存结果集失败，原因是: \n"); 
			fprintf(stderr, " %s\n", mysql_error(&mysql));  

		} 
		else 
		{ 
			while ( (row = mysql_fetch_row(result)) != NULL ) //读取结果集中的数据 
			{ 
				printf("tableName is %s \n", row[0]);       //打印当前表的名字 
			} 
			
		} 
	}
}

void select()
{
	display();//查询所有的表名  同时所有的表名已经在控制台上显示
	MYSQL_RES * result; 
	MYSQL_ROW row;
	char column[100][100];
	MYSQL_FIELD *fd;
	char sql;
	printf("根据上面的表格列表进行数据查询，提示：select * from '表名':\n ");
	getchar();
	gets(&sql);
	//scanf("%[^;]",&sql);
	//printf("%s \n",&sql);
	if (mysql_query(&mysql, &sql) != 0 )
		{
			printf("查询失败，原因是: \n"); 
			fprintf(stderr, " %s\n", mysql_error(&mysql)); 
		}
	else
		{
			if ( (result = mysql_store_result(&mysql)) == NULL ) //保存查询的结果 
				{ 
					printf("保存结果集失败，原因是: \n"); 
					fprintf(stderr, " %s\n", mysql_error(&mysql));  

				} 
			else 
				{ 
					int i , j ;
					//printf("结果集的数目：%s \n",(unsigned long) mysql_num_rows( result ));
					for ( i = 0; fd = mysql_fetch_field( result ); i++ )    // 获取列名 
					{
						strcpy( column[i], fd->name );
					}
					j = mysql_num_fields( result );//得到列的个数
					for ( i = 0; i < j; i++ )     //打印得到的列名
					{
						printf( "%s  ", column[i]);
					}
					printf( "\n" );
					while ( (row = mysql_fetch_row(result)) != NULL ) //读取结果集中的数据 
						{ 
							for ( i = 0; i < j; i++ )
							{
								printf( "%s     ", row[i] );//打印各个列对应的具体数据，存在的问题是无法像MySQL客户端那样对齐
							}
							printf( "\n" );
						} 
					mysql_free_result( result );//此时查询完成，释放结果集
				} 
		}
} 

//通过输入的内容在表中插入记录
void insert()
{
	display();
	char sql;
	printf("请输入插入操作的sql语句：\n");
	getchar();
	gets(&sql);

	if (mysql_query(&mysql, &sql) != 0)
	{
		printf("插入失败，原因是: \n"); 
		fprintf(stderr, " %s\n", mysql_error(&mysql));
	}
	else
	{
		printf("插入成功");
	}
}

//通过输入的内容对相应的记录进行修改更新
void update()
{
	display();
	char sql;
	printf("请输入更新操作的sql语句：\n");
	getchar();
	gets(&sql);

	if (mysql_query(&mysql, &sql) != 0)
	{
		printf("修改失败，原因是: \n"); 
		fprintf(stderr, " %s\n", mysql_error(&mysql));
	}
	else
	{
		printf("修改成功");
	}
}

//删除表中某条记录，或删除所有的记录
void Delete()
{
	display();
	char sql;
	printf("请输入删除操作的sql语句：\n");
	getchar();
	gets(&sql);
	if (mysql_query(&mysql, &sql) != 0)
	{
		printf("删除失败，原因是: \n"); 
		fprintf(stderr, " %s\n", mysql_error(&mysql));
	}
	else
	{
		printf("删除成功");
	}
}
//main函数想要实现的功能
/*
	1.连接数据库
	2.连接成功之后出现选择界面，分别进入增删改查的函数中
*/



int main()
{  
	int order;

	char host[20];
	printf("请输入ip：");
	scanf("%s",host);
	char user[20];
	printf("请输入用户名：");
	scanf("%s",user);
	char passwd[80];
	printf("请输入密码：");
	scanf("%s",passwd);
	char db[80];
	printf("请输入数据库：");
	scanf("%s",db);
	unsigned int port = 3306;           //这是MySQL的服务器的端口
	const char * unix_socket = NULL; 
	unsigned long client_flag = 0;      //这个参数一般为0 
	mysql_init(&mysql);                          //连接之前必须使用这个函数来初始化 
	if ( (sock = mysql_real_connect(&mysql,host, user, passwd, db, port, unix_socket, client_flag) ) == NULL ) //连接MySQL 
	{ 
		printf("连接失败，原因是: \n"); 
		fprintf(stderr, " %s\n", mysql_error(&mysql));  
	} 
	//如果连接成功则显示相应的界面进入数据库管理系统
	else 
	{ 
		mysql_query( &mysql, "SET NAMES GBK" );   //连接成功，设置可以显示中文
		fprintf(stderr, "连接MySQL成功！！\n"); 
		while(1)
		{
			cout<<"========================================================="<<endl;
			cout<<"=+++++++++++++++++++简易数据库管理系统++++++++++++++++++="<<endl;
			cout<<"---------------------------------------------------------"<<endl;
			cout<<"=\t 1、查询\t  2、插入\t"<<endl;
			cout<<"=\t 3、删除\t  4、更新\t"<<endl;
			cout<<"=\t        0、退出     \t"<<endl;
			cout<<"========================================================="<<endl;
			cout<<"请输入命令序号：";
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
				cout<<"再见!";
				return 0;
				break;
			}
		system("pause"); 
		} 
	}
	 system("pause");
} 