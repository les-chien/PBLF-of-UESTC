#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>

#define ADMINISTRATOR_KEY "123456"
#define EXIT "exit"
#define FILENAME "Commodities Information.txt"
#define USER_FILENAME "Users information.txt"
#define FRIENDLY_FILENAME "商品信息.txt"
#define MAX_USERNAME_LEN 30
#define MAX_PASSWORD_LEN 30
#define MAX_ID_LEN 30
#define MAX_NAME_LEN 30
#define MAX_PRICE_LEN 30
#define MAX_DISCOUNT_LEN 30
#define MAX_AMOUNT_LEN 30
#define MAX_REMAIN_LEN 30

struct commodity_information
{
	char commodities_id[MAX_ID_LEN];//商品ID
	char commodities_name[MAX_NAME_LEN];//商品名称
	char commodities_price[MAX_PRICE_LEN];//单价
	char commodities_discount[MAX_DISCOUNT_LEN];//折扣
	char commodities_amount[MAX_AMOUNT_LEN];//初始总量
	char commodities_remain[MAX_REMAIN_LEN];//剩余数量
};

struct node
{
	struct commodity_information data;
	struct node* next;
};

struct user
{
	char username[MAX_USERNAME_LEN];
	char password[MAX_PASSWORD_LEN];
	struct user* next;
};

struct node* first = NULL;
struct node* new_node = NULL;
struct node* original;
struct user* user_first = NULL;
struct user* user_new_node = NULL;

int readline(char sentence[]);
void user_initialization();
bool check_username(char username[]);
void register_Users();
bool login_in();
void cancel();
void initialization();
void display();
void modify();
bool check_ID(char sentence[]);
bool check_exit(char sentence[]);
void new();
void delete();
void find();
void save();
void sort();
void quicksort(double number[], int low, int high);
int split(double number[], int low, int high);
void delete_all_content();
int main()
{
	char buffer = '\n';
	char operation;
M:
	user_initialization();

	while (1)
	{
		printf("欢迎使用商品信息管理系统！\n\n");
		printf("如果您是新用户，需要完成注册流程，请输入1。\n\n");
		printf("如果您已经是此系统的用户，需要完成登录流程，请输入2。\n\n");
		printf("如果您输入了其它字符，将会自动退出此系统。\n\n");

		printf("请输入指令：");
		operation = getchar();
		switch (operation)
		{
		case '1':
			register_Users();
			break;
		case '2':
			if (login_in())
				goto L;
			break;
		default:
			exit(EXIT_SUCCESS);
		}

		system("pause");
		system("cls");
	}
L:
	initialization();

	printf("欢迎使用商品信息管理系统！\n\n\n");
	while (1)
	{
		printf("如果您需要注销此账号(慎用），请输入0。\n\n");
		printf("如果需要显示所有商品的信息，请输入1。\n\n");
		printf("如果需要修改某个商品的信息，请输入2。\n\n");
		printf("如果需要插入某个商品的信息，请输入3。\n\n");
		printf("如果需要删除某个商品的信息，请输入4。\n\n");
		printf("如果需要查找某个商品的信息，请输入5。\n\n");
		printf("如果需要商品存盘并退出系统，请输入6。\n\n");
		printf("如果需要对商品价格进行排序，请输入7。\n\n");
		printf("如果需要删除所有内容（慎用），请输入8。\n\n");
		printf("如果您需要退出登录，请输入9。\n\n");
		printf("如果您输入了其它指令，将会不存盘退出系统。\n\n");

		printf("请输入指令：");
		operation = getchar();
		printf("\n");
		switch (operation)
		{
		case'0':
			cancel();
			break;
		case'1':
			display();
			break;
		case'2':
			modify();
			break;
		case'3':
			new();
			break;
		case'4':
			delete();
			break;
		case'5':
			find();
			break;
		case'6':
			save();
			exit(EXIT_SUCCESS);
		case'7':
			sort();
			while ((buffer = getchar()) != EOF && buffer != '\n');
			break;
		case'8':
			delete_all_content();
			while ((buffer = getchar()) != EOF && buffer != '\n');
			break;
		case '9':
			system("cls");
			while ((buffer = getchar()) != EOF && buffer != '\n');
			goto M;
			break;
		default:
			exit(EXIT_FAILURE);
		}

		system("pause");
		system("cls");
	}
}
int readline(char sentence[])
{
	char ch;
	int sum = 0;

	ch = getchar();
	if (ch == '\n')
		ch = getchar();
	while (ch != '\n')
	{
		sentence[sum] = ch;
		sum++;
		ch = getchar();
	}
	sentence[sum] = '\0';

	return sum;
}
void user_initialization()
{
	FILE* users;
	char username[MAX_USERNAME_LEN];
	char password[MAX_PASSWORD_LEN];
	char ch;
	int i;

	if (fopen_s(&users, USER_FILENAME, "a+") != 0)
	{
		printf("错误！");
		return;
	}

	while (1)
	{
		user_new_node = calloc(1, sizeof(struct user));

		if (user_new_node == NULL)
		{
			printf("错误！");
			return;
		}

		ch = fgetc(users);
		for (i = 0; ch != '\n'; i++)
		{
			if (ch == EOF)
			{
				free(user_new_node);
				user_new_node = NULL;
				fclose(users);
				return;
			}
			username[i] = ch;
			ch = fgetc(users);
		}
		username[i] = '\0';

		ch = fgetc(users);
		for (i = 0; ch != '\n'; i++)
		{
			password[i] = ch;
			ch = fgetc(users);
		}
		password[i] = '\0';

		strcpy_s(user_new_node->username, MAX_USERNAME_LEN, username);
		strcpy_s(user_new_node->password, MAX_PASSWORD_LEN, password);

		user_new_node->next = user_first;
		user_first = user_new_node;
	}

	fclose(users);
	return;
}
bool check_username(char username[])
{
	struct user* p;

	for (p = user_first; p != NULL; p = p->next)
	{
		if (strcmp(username, p->username) == 0)
		{
			printf("用户名已存在，请重新输入！\n");
			printf("请输入用户名：");
			return true;
			break;
		}
	}

	if (p == NULL)
		return false;
}
void register_Users()
{
	char username[MAX_USERNAME_LEN];
	char password[MAX_PASSWORD_LEN];
	char confirm_password[MAX_PASSWORD_LEN];
	FILE* users;

	system("cls");
	printf("输入\"exit\"可以强制退出此界面。\n\n");
	printf("请输入管理员密钥：");
	readline(password);
	if (strcmp(password, ADMINISTRATOR_KEY) != 0)
	{
		printf("您输入了错误的管理员密钥！\n");
		printf("注册流程已中止。");
		return;
	}

	if (fopen_s(&users, USER_FILENAME, "a+") != 0)
	{
		printf("错误！");
		return;
	}

	printf("请输入您的用户名：");
	readline(username);
	if (check_exit(username))
		return;
	while (check_username(username))
		readline(username);
	printf("请输入您的密码：");
	readline(password);
	if (check_exit(password))
		return;
	system("cls");
	printf("请确认您的密码：");
	readline(confirm_password);
	if (check_exit(confirm_password))
		return;
	while (strcmp(password, confirm_password) != 0)
	{
		system("cls");
		printf("请确认您的密码：");
		readline(confirm_password);
		if (check_exit(confirm_password))
			return;
	}

	if (strcmp(password, confirm_password) == 0)
	{
		printf("注册成功！");
		fprintf(users, "%s\n", username);
		fprintf(users, "%s\n", password);
		fclose(users);
		user_initialization();
		return;
	}

}
bool login_in()
{
	struct user* p;
	char username[MAX_USERNAME_LEN];
	char password[MAX_PASSWORD_LEN];
	char operation;

	system("cls");
	printf("输入\"exit\"可强制退出此界面。\n\n");

	printf("请输入用户名：");
	readline(username);
	if (check_exit(username))
		return false;
	for (p = user_first; p != NULL; p = p->next)
	{
		if (strcmp(p->username, username) == 0)
		{
		K:
			printf("请输入密码：");
			readline(password);
			if (check_exit(password))
				return false;
			if (strcmp(p->password, password) == 0)
			{
				printf("登录成功！");
				system("pause");
				system("cls");
				return true;
			}
			else
			{
				system("cls");
				printf("您输入的密码不正确！\n\n");
				printf("如果您要重新输入密码，请输入1。\n\n");
				printf("如果您忘记了密码，请输入2。\n\n");
				printf("如果您输入了其它字符，将会自动退出此系统。\n\n");
				printf("请输入指令：");
				operation = getchar();
				switch (operation)
				{
				case '1':
					system("cls");
					printf("用户名：%s\n", p->username);
					goto K;
					break;
				case '2':
					system("cls");
					printf("请输入管理员密钥：");
					readline(password);
					if (strcmp(password, ADMINISTRATOR_KEY) == 0)
					{
						printf("您的密码为：%s\n", p->password);
						printf("请记住您的密码，不要泄露。\n");
						system("pause");
						system("cls");
						return true;
						break;
					}
					else
					{
						printf("您输入了错误的管理员密钥！\n");
						printf("登录流程已中止。");
						return false;
						break;
					}
				default:
					exit(EXIT_SUCCESS);
				}
			}
		}
	}

	if (p == NULL)
	{
		system("cls");
		printf("您输入的用户名不存在！\n\n");
		printf("如果您需要重新输入用户名，请输入1。\n\n");
		printf("如果您需要注册成为一名新用户，请输入2。\n\n");
		printf("如果您输入了其它字符，将会自动退出此系统。\n\n");
		printf("请输入指令：");
		operation = getchar();
		switch (operation)
		{
		case '1':
			return login_in();
			break;
		case '2':
			register_Users();
			return false;
			break;
		default:
			exit(EXIT_SUCCESS);
		}
	}
}
void cancel()
{
	FILE* users;
	struct user* p;
	struct user* q = NULL;
	char username[MAX_USERNAME_LEN];
	char password[MAX_PASSWORD_LEN];

	system("cls");
	printf("输入\"exit\"可以强制退出此界面。\n\n");

	printf("您真的需要注销本账号吗？\n");
	printf("如果是，请输入Y；如果不是，请输入N。");
	readline(password);
	if (check_exit(password))
		return;
	if (strcmp(password, "Y") == 0 || strcmp(password, "y") == 0)
	{
		system("cls");
		printf("请输入用户名：");
		readline(username);
		if (check_exit(username))
			return;
		for (p = user_first; p != NULL; q = p, p = p->next)
		{
			if (strcmp(username, p->username) == 0)
			{
				printf("请输入密码：");
				readline(password);
				if (check_exit(password))
					return;
				if (strcmp(password, p->password) == 0)
				{
					if (q != NULL)
					{
						q->next = p->next;
						free(p);
						p = NULL;

						if (fopen_s(&users, USER_FILENAME, "w+") != 0)
						{
							printf("错误!");
							return;
						}

						for (q = user_first; q != NULL; q = q->next)
						{
							fprintf(users, "%s\n", q->username);
							fprintf(users, "%s\n", q->password);
						}

						fclose(users);
						printf("注销已完成。\n");
						printf("感谢您的使用！");
						exit(EXIT_SUCCESS);
					}
					else
					{
						user_first = p->next;
						free(p);
						p = NULL;

						if (fopen_s(&users, USER_FILENAME, "w+") != 0)
						{
							printf("错误!");
							return;
						}

						for (q = user_first; q != NULL; q = q->next)
						{
							fprintf(users, "%s\n", q->username);
							fprintf(users, "%s\n", q->password);
						}

						fclose(users);
						printf("注销已完成。\n");
						printf("感谢您的使用！");
						exit(EXIT_SUCCESS);
					}
				}
				else
				{
					printf("您输入的密码不正确！\n");
					printf("已自动结束注销流程！\n");
					return;
				}

			}
		}

		if (p == NULL)
		{
			printf("您输入的用户名不正确！\n");
			printf("已自动结束注销流程！\n");
			return;
		}
	}
	else if (strcmp(password, "N") == 0 || strcmp(password, "n") == 0)
	{
		printf("已结束注销流程！\n");
		return;
	}
	else
	{
		printf("您输入了其它字符，已自动为您重新开始注销流程。\n");
		system("pause");
		cancel();
	}
}
void initialization()
{
	FILE* fp;
	char ch = 1;
	int i;
	char initialization_ID[MAX_ID_LEN];
	char initialization_name[MAX_NAME_LEN];
	char initialization_price[MAX_PRICE_LEN];
	char initialization_discount[MAX_DISCOUNT_LEN];
	char initialization_amount[MAX_AMOUNT_LEN];
	char initialization_remain[MAX_REMAIN_LEN];

	if (fopen_s(&fp, FILENAME, "a+") != 0)
	{
		printf("初始化失败！");
		return;
	}

	while (ch != EOF)
	{
		new_node = calloc(1, sizeof(struct node));

		if (new_node == NULL)
		{
			printf("错误！");
			return;
		}

		ch = fgetc(fp);
		for (i = 0; ch != '\n'; i++)
		{
			if (ch == EOF)
			{
				free(new_node);
				new_node = NULL;
				fclose(fp);
				return;
			}
			initialization_ID[i] = ch;
			ch = fgetc(fp);
		}
		initialization_ID[i] = '\0';
		strcpy_s(new_node->data.commodities_id, MAX_ID_LEN, initialization_ID);

		ch = fgetc(fp);
		for (i = 0; ch != '\n'; i++)
		{
			initialization_name[i] = ch;
			ch = fgetc(fp);
		}
		initialization_name[i] = '\0';
		strcpy_s(new_node->data.commodities_name, MAX_NAME_LEN, initialization_name);

		ch = fgetc(fp);
		for (i = 0; ch != '\n'; i++)
		{
			initialization_price[i] = ch;
			ch = fgetc(fp);
		}
		initialization_price[i] = '\0';
		strcpy_s(new_node->data.commodities_price, MAX_PRICE_LEN, initialization_price);

		ch = fgetc(fp);
		for (i = 0; ch != '\n'; i++)
		{
			initialization_discount[i] = ch;
			ch = fgetc(fp);
		}
		initialization_discount[i] = '\0';
		strcpy_s(new_node->data.commodities_discount, MAX_DISCOUNT_LEN, initialization_discount);

		ch = fgetc(fp);
		for (i = 0; ch != '\n'; i++)
		{
			initialization_amount[i] = ch;
			ch = fgetc(fp);
		}
		initialization_amount[i] = '\0';
		strcpy_s(new_node->data.commodities_amount, MAX_AMOUNT_LEN, initialization_amount);

		ch = fgetc(fp);
		for (i = 0; ch != '\n'; i++)
		{
			initialization_remain[i] = ch;
			ch = fgetc(fp);
		}
		initialization_remain[i] = '\0';
		strcpy_s(new_node->data.commodities_remain, MAX_REMAIN_LEN, initialization_remain);

		new_node->next = first;
		first = new_node;
	}

	original = first;
	fclose(fp);
	return;
}
void display()
{
	struct node* p;
	char operation;
	char buffer;
	FILE* people;

	while ((buffer = getchar()) != EOF && buffer != '\n');
	system("cls");

	for (p = first; p != NULL; p = p->next)
	{
		printf("商品ID为：%s\n", p->data.commodities_id);
		printf("商品名称为：%s\n", p->data.commodities_name);
		printf("商品单价为：%s\n", p->data.commodities_price);
		printf("商品折扣为：%s\n", p->data.commodities_discount);
		printf("商品初始数量为：%s\n", p->data.commodities_amount);
		printf("商品库存为：%s\n", p->data.commodities_remain);
		printf("\n");
	}

	printf("是否需要打开文本文件查看？如果需要，请输入Y；如果不需要，请输入N。");
J:
	operation = getchar();
	while ((buffer = getchar()) != EOF && buffer != '\n');
	if (operation == '\n')
		operation = getchar();
	operation = toupper(operation);
	switch (operation)
	{
	case 'Y':
		if (fopen_s(&people, FRIENDLY_FILENAME, "w+") != 0)
		{
			printf("错误！");
			while ((buffer = getchar()) != EOF && buffer != '\n');
			return;
		}

		for (p = first; p != NULL; p = p->next)
		{
			fprintf(people, "商品ID为：%s\n", p->data.commodities_id);
			fprintf(people, "商品名称为：%s\n", p->data.commodities_name);
			fprintf(people, "商品单价为：%s\n", p->data.commodities_price);
			fprintf(people, "商品折扣为：%s\n", p->data.commodities_discount);
			fprintf(people, "商品初始数量为：%s\n", p->data.commodities_amount);
			fprintf(people, "商品库存为：%s\n", p->data.commodities_remain);
			fprintf(people, "\n");
		}

		fclose(people);
		//system("C:/Users/33914/source/repos/软件界面/软件界面/商品信息.txt");

		if (fopen_s(&people, FRIENDLY_FILENAME, "w+") != 0)
		{
			printf("错误！");
			while ((buffer = getchar()) != EOF && buffer != '\n');
			return;
		}

		for (p = original; p != NULL; p = p->next)
		{
			fprintf(people, "商品ID为：%s\n", p->data.commodities_id);
			fprintf(people, "商品名称为：%s\n", p->data.commodities_name);
			fprintf(people, "商品单价为：%s\n", p->data.commodities_price);
			fprintf(people, "商品折扣为：%s\n", p->data.commodities_discount);
			fprintf(people, "商品初始数量为：%s\n", p->data.commodities_amount);
			fprintf(people, "商品库存为：%s\n", p->data.commodities_remain);
			fprintf(people, "\n");
		}

		fclose(people);

		break;
	case 'N':
		return;
		break;
	default:
		printf("您输入了错误的指令，请输入正确的指令！\n");
		printf("请输入指令：(Y/N)");
		goto J;
		break;
	}

	return;
}
void modify()
{
	struct node* p;
	char target_ID[MAX_ID_LEN];
	char target_name[MAX_NAME_LEN];
	char target_price[MAX_PRICE_LEN];
	char target_discount[MAX_DISCOUNT_LEN];
	char target_amount[MAX_AMOUNT_LEN];
	char target_remain[MAX_REMAIN_LEN];
	char operation;
	char buffer;

	while ((buffer = getchar()) != EOF && buffer != '\n');
	system("cls");

	printf("输入\"exit\"可以强制退出此界面。\n\n");

	printf("请输入待修改商品的ID：");
	readline(target_ID);
	if (check_exit(target_ID))
		return;

	for (p = first; p != NULL; p = p->next)
	{
		if (strcmp(target_ID, p->data.commodities_id) == 0)
		{
			printf("\n");
			printf("该商品为：%s\n", p->data.commodities_name);
			printf("该商品单价为：%s\n", p->data.commodities_price);
			printf("该商品折扣为：%s\n", p->data.commodities_discount);
			printf("该商品初始数量为：%s\n", p->data.commodities_amount);
			printf("该商品库存为：%s\n", p->data.commodities_remain);
			printf("\n");
			printf("请注意：在此处输入\"exit\"将不会强制退出。\n");
			printf("是否修改商品名称？如果需要，请输入Y；如果不需要，请输入N。");
		A:
			operation = getchar();
			while ((buffer = getchar()) != EOF && buffer != '\n');
			if (operation == '\n')
				operation = getchar();
			operation = toupper(operation);
			switch (operation)
			{
			case 'Y':
				printf("请输入新的商品名称：");
				readline(target_name);
				strcpy_s(p->data.commodities_name, MAX_NAME_LEN, target_name);
				break;
			case 'N':
				break;
			default:
				printf("您输入了错误的指令，请输入正确的指令！\n");
				printf("是否修改商品名称？\n");
				printf("请输入指令：(Y/N)");
				goto A;
				break;
			}

			printf("是否修改商品单价？如果需要，请输入Y；如果不需要，请输入N。");
		B:
			operation = getchar();
			while ((buffer = getchar()) != EOF && buffer != '\n');
			if (operation == '\n')
				operation = getchar();
			operation = toupper(operation);
			switch (operation)
			{
			case 'Y':
				printf("请输入新的商品单价：");
				readline(target_price);
				strcpy_s(p->data.commodities_price, MAX_PRICE_LEN, target_price);
				break;
			case 'N':
				break;
			default:
				printf("您输入了错误的指令，请输入正确的指令！\n");
				printf("是否修改商品单价？\n");
				printf("请输入指令：(Y/N)");
				goto B;
				break;
			}

			printf("是否修改商品折扣？如果需要，请输入Y；如果不需要，请输入N。");
		C:
			operation = getchar();
			while ((buffer = getchar()) != EOF && buffer != '\n');
			if (operation == '\n')
				operation = getchar();
			operation = toupper(operation);
			switch (operation)
			{
			case 'Y':
				printf("请输入新的商品折扣：");
				readline(target_discount);
				strcpy_s(p->data.commodities_discount, MAX_DISCOUNT_LEN, target_discount);
				break;
			case 'N':
				break;
			default:
				printf("您输入了错误的指令，请输入正确的指令！\n");
				printf("是否修改商品折扣？\n");
				printf("请输入指令：(Y/N)");
				goto C;
				break;
			}

			printf("是否修改商品初始数量？如果需要，请输入Y；如果不需要，请输入N。");
		D:
			operation = getchar();
			while ((buffer = getchar()) != EOF && buffer != '\n');
			if (operation == '\n')
				operation = getchar();
			operation = toupper(operation);
			switch (operation)
			{
			case 'Y':
				printf("请输入新的商品初始数量：");
				readline(target_amount);
				strcpy_s(p->data.commodities_amount, MAX_AMOUNT_LEN, target_amount);
				break;
			case 'N':
				break;
			default:
				printf("您输入了错误的指令，请输入正确的指令！\n");
				printf("是否修改商品初始数量？\n");
				printf("请输入指令：(Y/N)");
				goto D;
				break;
			}

			printf("是否修改商品库存？如果需要，请输入Y；如果不需要，请输入N。");
		E:
			operation = getchar();
			while ((buffer = getchar()) != EOF && buffer != '\n');
			if (operation == '\n')
				operation = getchar();
			operation = toupper(operation);
			switch (operation)
			{
			case 'Y':
				printf("请输入新的商品库存：");
				readline(target_remain);
				strcpy_s(p->data.commodities_remain, MAX_REMAIN_LEN, target_remain);
				break;
			case 'N':
				break;
			default:
				printf("您输入了错误的指令，请输入正确的指令！\n");
				printf("是否修改商品库存？\n");
				printf("请输入指令：(Y/N)");
				goto E;
				break;
			}

			break;
		}
	}
	if (p == NULL)
	{
		printf("您输入的ID不存在！\n");
		printf("是否需要重新输入商品ID？如果需要，请输入Y；如果不需要，请输入N。");

		operation = getchar();
		while ((buffer = getchar()) != EOF && buffer != '\n');
		operation = toupper(operation);

		switch (operation)
		{
		case 'Y':
			modify();
			break;
		case 'N':
			return;
			break;
		default:
			printf("您输入了错误的指令，已自动退出。");
			return;
			break;
		}
	}

	return;
}
bool check_ID(char sentence[])
{
	struct node* p;
	for (p = first; p != NULL; p = p->next)
	{
		if (strcmp(p->data.commodities_id, sentence) == 0)
		{
			printf("输入了重复的ID\n");
			printf("请输入商品ID：");
			return true;
		}

	}

	if (p == NULL)
		return false;

	return false;
}
bool check_exit(char sentence[])
{
	if (strcmp(sentence, EXIT) == 0)
		return true;

	return false;
}
void new()
{
	char new_ID[MAX_ID_LEN];
	char new_name[MAX_NAME_LEN];
	char new_price[MAX_PRICE_LEN];
	char new_discount[MAX_DISCOUNT_LEN];
	char new_amount[MAX_AMOUNT_LEN];
	char new_remain[MAX_REMAIN_LEN];
	char operation;
	char buffer;

	while ((buffer = getchar()) != EOF && buffer != '\n');
	system("cls");

	printf("输入\"exit\"可以强制退出此界面。\n\n");

	printf("请输入商品ID：");
	readline(new_ID);
	while (check_ID(new_ID))
		readline(new_ID);
	if (check_exit(new_ID))
		return;
	printf("请输入商品名称：");
	readline(new_name);
	if (check_exit(new_name))
		return;
	printf("请输入商品单价：");
	readline(new_price);
	if (check_exit(new_price))
		return;
	printf("请输入商品折扣：");
	readline(new_discount);
	if (check_exit(new_discount))
		return;
	printf("请输入商品初始数量：");
	readline(new_amount);
	if (check_exit(new_amount))
		return;
	printf("请输入商品库存：");
	readline(new_remain);
	if (check_exit(new_remain))
		return;

	new_node = calloc(1, sizeof(struct node));
	if (new_node == NULL)
	{
		printf("错误！");
		return;
	}

	strcpy_s(new_node->data.commodities_id, MAX_ID_LEN, new_ID);
	strcpy_s(new_node->data.commodities_name, MAX_NAME_LEN, new_name);
	strcpy_s(new_node->data.commodities_price, MAX_PRICE_LEN, new_price);
	strcpy_s(new_node->data.commodities_discount, MAX_DISCOUNT_LEN, new_discount);
	strcpy_s(new_node->data.commodities_amount, MAX_AMOUNT_LEN, new_amount);
	strcpy_s(new_node->data.commodities_remain, MAX_REMAIN_LEN, new_remain);
	new_node->next = first;
	first = new_node;

	printf("是否继续插入商品信息？如果是，请输入Y；如果不是，请输入N。");
F:
	operation = getchar();
	operation = toupper(operation);
	switch (operation)
	{
	case 'Y':
		new();
		break;
	case 'N':
		while ((buffer = getchar()) != EOF && buffer != '\n');
		return;
		break;
	default:
		printf("您输入了错误的指令，请重新输入！\n");
		printf("请输入指令：(Y/N)");
		goto F;
		break;
	}
}
void delete()
{
	char target_ID[MAX_ID_LEN];
	char operation;
	char buffer;
	struct node* cur;
	struct node* prev;

	while ((buffer = getchar()) != EOF && buffer != '\n');
	system("cls");

	printf("在此处输入\"exit\"可以强制退出此界面。\n");

	printf("请输入需要删除的商品的ID：");
	readline(target_ID);

	if (check_exit(target_ID))
		return;

	for (prev = NULL, cur = first; cur != NULL; prev = cur, cur = cur->next)
	{
		if (strcmp(cur->data.commodities_id, target_ID) == 0)
			break;
	}

	if (cur == NULL)
	{
		printf("您输入的ID不存在！\n");
		printf("是否重新输入ID？如果是，请输入Y；如果不是，请输入N。");
	G:
		operation = getchar();
		while ((buffer = getchar()) != EOF && buffer != '\n');
		operation = toupper(operation);
		switch (operation)
		{
		case 'Y':
			delete();
			break;
		case 'N':
			return;
			break;
		default:
			printf("您输入了错误的指令，请重新输入！\n");
			printf("请输入指令：");
			goto G;
			break;
		}
	}
	else if (prev == NULL)
	{
		first = cur->next;
		original = first;
		free(cur);
		printf("已删除此商品的信息。");
		return;
	}
	else
	{
		prev->next = cur->next;
		free(cur);
		printf("已删除此商品的信息。");
		return;
	}

}
void find()
{
	char target_ID[MAX_ID_LEN];
	char operation;
	char buffer;
	struct node* p;

	while ((buffer = getchar()) != EOF && buffer != '\n');
	system("cls");

	printf("输入\"exit\"可以强制退出此界面。\n\n");

	printf("请输入需要查找的商品的ID：");
	readline(target_ID);

	if (check_exit(target_ID))
		return;

	for (p = first; p != NULL; p = p->next)
	{
		if (strcmp(p->data.commodities_id, target_ID) == 0)
		{
			printf("\n");
			printf("商品名称为：%s\n", p->data.commodities_name);
			printf("商品单价为：%s\n", p->data.commodities_price);
			printf("商品折扣为：%s\n", p->data.commodities_discount);
			printf("商品初始数量为：%s\n", p->data.commodities_amount);
			printf("商品库存为：%s\n", p->data.commodities_remain);
			printf("\n");
			break;
		}
	}

	if (p == NULL)
	{
		printf("您输入的ID不存在！\n");
		printf("是否需要重新输入ID？如果是，请输入Y；如果不是，请输入N。");
	I:
		operation = getchar();
		while ((buffer = getchar()) != EOF && buffer != '\n');
		operation = toupper(operation);
		switch (operation)
		{
		case 'Y':
			find();
			break;
		case 'N':
			return;
			break;
		default:
			printf("您输入了错误的指令，请重新输入！\n");
			printf("请输入指令：(Y/N)");
			goto I;
			break;
		}
	}
}
void save()
{
	FILE* fp;
	FILE* people;
	struct node* p;

	if (fopen_s(&fp, FILENAME, "w+") != 0)
	{
		printf("错误！");
		return;
	}
	if (fopen_s(&people, FRIENDLY_FILENAME, "w+") != 0)
	{
		printf("错误！");
		return;
	}

	for (p = first; p != NULL; p = p->next)
	{
		fprintf(fp, "%s\n", p->data.commodities_id);
		fprintf(fp, "%s\n", p->data.commodities_name);
		fprintf(fp, "%s\n", p->data.commodities_price);
		fprintf(fp, "%s\n", p->data.commodities_discount);
		fprintf(fp, "%s\n", p->data.commodities_amount);
		fprintf(fp, "%s\n", p->data.commodities_remain);
	}
	for (p = first; p != NULL; p = p->next)
	{
		fprintf(people, "商品ID为：%s\n", p->data.commodities_id);
		fprintf(people, "商品名称为：%s\n", p->data.commodities_name);
		fprintf(people, "商品单价为：%s\n", p->data.commodities_price);
		fprintf(people, "商品折扣为：%s\n", p->data.commodities_discount);
		fprintf(people, "商品初始数量为：%s\n", p->data.commodities_amount);
		fprintf(people, "商品库存为：%s\n", p->data.commodities_remain);
		fprintf(people, "\n");
	}

	delete_all_content();

	fclose(fp);
	fclose(people);
	return;
}
void sort()
{
	char price[100][MAX_PRICE_LEN];
	double sort_price[100];
	int sum = 0;
	struct node* p;

	system("cls");

	for (p = first; p != NULL; p = p->next)
	{
		strcpy_s(price[sum], MAX_PRICE_LEN, p->data.commodities_price);
		sum++;
	}

	for (int vertical = 0, horizontal = 0, num = 0; vertical < sum; horizontal++)
	{
		if (price[vertical][horizontal] < '0' || price[vertical][horizontal] > '9')
		{
			price[vertical][horizontal] = '\0';
			sort_price[num] = atof(price[vertical]);
			horizontal = 0;
			vertical++;
			num++;
		}
	}

	quicksort(sort_price, 0, sum - 1);

	printf("排序结果为：");
	for (int i = 0; i < sum; i++)
	{
		printf("%lf  ", sort_price[i]);
		if ((i + 1) % 5 == 0)
			printf("\n");
	}

	return;
}
void quicksort(double number[], int low, int high)
{
	int middle;

	if (low >= high)
		return;

	middle = split(number, low, high);

	quicksort(number, low, middle - 1);
	quicksort(number, middle + 1, high);
}
int split(double number[], int low, int high)
{
	double part_element = number[low];

	while (1)
	{
		while (low < high && part_element <= number[high])
			high--;

		if (low >= high)
			break;

		number[low++] = number[high];

		while (low < high && number[low] <= part_element)
			low++;

		if (low >= high)
			break;

		number[high--] = number[low];
	}

	number[high] = part_element;

	return high;
}
void delete_all_content()
{
	struct node* cur = first->next;
	struct node* prev = first;

	if (cur == NULL)
		free(first);
	else if (prev == NULL)
	{
		printf("错误！");
		return;
	}
	else
	{
		while (prev != NULL)
		{
			if (cur != NULL)
			{
				free(prev);
				prev = cur;
				cur = cur->next;
			}
			else
			{
				free(prev);
				prev = NULL;
				break;
			}
		}
	}


	first = NULL;
	new_node = NULL;

	return;
}