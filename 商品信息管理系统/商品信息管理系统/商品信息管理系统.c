#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>

#define ADMINISTRATOR_KEY "123456"
#define EXIT "exit"
#define FILENAME "Commodities Information.txt"
#define USER_FILENAME "Users information.txt"
#define FRIENDLY_FILENAME "��Ʒ��Ϣ.txt"
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
	char commodities_id[MAX_ID_LEN];//��ƷID
	char commodities_name[MAX_NAME_LEN];//��Ʒ����
	char commodities_price[MAX_PRICE_LEN];//����
	char commodities_discount[MAX_DISCOUNT_LEN];//�ۿ�
	char commodities_amount[MAX_AMOUNT_LEN];//��ʼ����
	char commodities_remain[MAX_REMAIN_LEN];//ʣ������
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
		printf("��ӭʹ����Ʒ��Ϣ����ϵͳ��\n\n");
		printf("����������û�����Ҫ���ע�����̣�������1��\n\n");
		printf("������Ѿ��Ǵ�ϵͳ���û�����Ҫ��ɵ�¼���̣�������2��\n\n");
		printf("����������������ַ��������Զ��˳���ϵͳ��\n\n");

		printf("������ָ�");
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

	printf("��ӭʹ����Ʒ��Ϣ����ϵͳ��\n\n\n");
	while (1)
	{
		printf("�������Ҫע�����˺�(���ã���������0��\n\n");
		printf("�����Ҫ��ʾ������Ʒ����Ϣ��������1��\n\n");
		printf("�����Ҫ�޸�ĳ����Ʒ����Ϣ��������2��\n\n");
		printf("�����Ҫ����ĳ����Ʒ����Ϣ��������3��\n\n");
		printf("�����Ҫɾ��ĳ����Ʒ����Ϣ��������4��\n\n");
		printf("�����Ҫ����ĳ����Ʒ����Ϣ��������5��\n\n");
		printf("�����Ҫ��Ʒ���̲��˳�ϵͳ��������6��\n\n");
		printf("�����Ҫ����Ʒ�۸��������������7��\n\n");
		printf("�����Ҫɾ���������ݣ����ã���������8��\n\n");
		printf("�������Ҫ�˳���¼��������9��\n\n");
		printf("���������������ָ����᲻�����˳�ϵͳ��\n\n");

		printf("������ָ�");
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
		printf("����");
		return;
	}

	while (1)
	{
		user_new_node = calloc(1, sizeof(struct user));

		if (user_new_node == NULL)
		{
			printf("����");
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
			printf("�û����Ѵ��ڣ����������룡\n");
			printf("�������û�����");
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
	printf("����\"exit\"����ǿ���˳��˽��档\n\n");
	printf("���������Ա��Կ��");
	readline(password);
	if (strcmp(password, ADMINISTRATOR_KEY) != 0)
	{
		printf("�������˴���Ĺ���Ա��Կ��\n");
		printf("ע����������ֹ��");
		return;
	}

	if (fopen_s(&users, USER_FILENAME, "a+") != 0)
	{
		printf("����");
		return;
	}

	printf("�����������û�����");
	readline(username);
	if (check_exit(username))
		return;
	while (check_username(username))
		readline(username);
	printf("�������������룺");
	readline(password);
	if (check_exit(password))
		return;
	system("cls");
	printf("��ȷ���������룺");
	readline(confirm_password);
	if (check_exit(confirm_password))
		return;
	while (strcmp(password, confirm_password) != 0)
	{
		system("cls");
		printf("��ȷ���������룺");
		readline(confirm_password);
		if (check_exit(confirm_password))
			return;
	}

	if (strcmp(password, confirm_password) == 0)
	{
		printf("ע��ɹ���");
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
	printf("����\"exit\"��ǿ���˳��˽��档\n\n");

	printf("�������û�����");
	readline(username);
	if (check_exit(username))
		return false;
	for (p = user_first; p != NULL; p = p->next)
	{
		if (strcmp(p->username, username) == 0)
		{
		K:
			printf("���������룺");
			readline(password);
			if (check_exit(password))
				return false;
			if (strcmp(p->password, password) == 0)
			{
				printf("��¼�ɹ���");
				system("pause");
				system("cls");
				return true;
			}
			else
			{
				system("cls");
				printf("����������벻��ȷ��\n\n");
				printf("�����Ҫ�����������룬������1��\n\n");
				printf("��������������룬������2��\n\n");
				printf("����������������ַ��������Զ��˳���ϵͳ��\n\n");
				printf("������ָ�");
				operation = getchar();
				switch (operation)
				{
				case '1':
					system("cls");
					printf("�û�����%s\n", p->username);
					goto K;
					break;
				case '2':
					system("cls");
					printf("���������Ա��Կ��");
					readline(password);
					if (strcmp(password, ADMINISTRATOR_KEY) == 0)
					{
						printf("��������Ϊ��%s\n", p->password);
						printf("���ס�������룬��Ҫй¶��\n");
						system("pause");
						system("cls");
						return true;
						break;
					}
					else
					{
						printf("�������˴���Ĺ���Ա��Կ��\n");
						printf("��¼��������ֹ��");
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
		printf("��������û��������ڣ�\n\n");
		printf("�������Ҫ���������û�����������1��\n\n");
		printf("�������Ҫע���Ϊһ�����û���������2��\n\n");
		printf("����������������ַ��������Զ��˳���ϵͳ��\n\n");
		printf("������ָ�");
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
	printf("����\"exit\"����ǿ���˳��˽��档\n\n");

	printf("�������Ҫע�����˺���\n");
	printf("����ǣ�������Y��������ǣ�������N��");
	readline(password);
	if (check_exit(password))
		return;
	if (strcmp(password, "Y") == 0 || strcmp(password, "y") == 0)
	{
		system("cls");
		printf("�������û�����");
		readline(username);
		if (check_exit(username))
			return;
		for (p = user_first; p != NULL; q = p, p = p->next)
		{
			if (strcmp(username, p->username) == 0)
			{
				printf("���������룺");
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
							printf("����!");
							return;
						}

						for (q = user_first; q != NULL; q = q->next)
						{
							fprintf(users, "%s\n", q->username);
							fprintf(users, "%s\n", q->password);
						}

						fclose(users);
						printf("ע������ɡ�\n");
						printf("��л����ʹ�ã�");
						exit(EXIT_SUCCESS);
					}
					else
					{
						user_first = p->next;
						free(p);
						p = NULL;

						if (fopen_s(&users, USER_FILENAME, "w+") != 0)
						{
							printf("����!");
							return;
						}

						for (q = user_first; q != NULL; q = q->next)
						{
							fprintf(users, "%s\n", q->username);
							fprintf(users, "%s\n", q->password);
						}

						fclose(users);
						printf("ע������ɡ�\n");
						printf("��л����ʹ�ã�");
						exit(EXIT_SUCCESS);
					}
				}
				else
				{
					printf("����������벻��ȷ��\n");
					printf("���Զ�����ע�����̣�\n");
					return;
				}

			}
		}

		if (p == NULL)
		{
			printf("��������û�������ȷ��\n");
			printf("���Զ�����ע�����̣�\n");
			return;
		}
	}
	else if (strcmp(password, "N") == 0 || strcmp(password, "n") == 0)
	{
		printf("�ѽ���ע�����̣�\n");
		return;
	}
	else
	{
		printf("�������������ַ������Զ�Ϊ�����¿�ʼע�����̡�\n");
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
		printf("��ʼ��ʧ�ܣ�");
		return;
	}

	while (ch != EOF)
	{
		new_node = calloc(1, sizeof(struct node));

		if (new_node == NULL)
		{
			printf("����");
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
		printf("��ƷIDΪ��%s\n", p->data.commodities_id);
		printf("��Ʒ����Ϊ��%s\n", p->data.commodities_name);
		printf("��Ʒ����Ϊ��%s\n", p->data.commodities_price);
		printf("��Ʒ�ۿ�Ϊ��%s\n", p->data.commodities_discount);
		printf("��Ʒ��ʼ����Ϊ��%s\n", p->data.commodities_amount);
		printf("��Ʒ���Ϊ��%s\n", p->data.commodities_remain);
		printf("\n");
	}

	printf("�Ƿ���Ҫ���ı��ļ��鿴�������Ҫ��������Y���������Ҫ��������N��");
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
			printf("����");
			while ((buffer = getchar()) != EOF && buffer != '\n');
			return;
		}

		for (p = first; p != NULL; p = p->next)
		{
			fprintf(people, "��ƷIDΪ��%s\n", p->data.commodities_id);
			fprintf(people, "��Ʒ����Ϊ��%s\n", p->data.commodities_name);
			fprintf(people, "��Ʒ����Ϊ��%s\n", p->data.commodities_price);
			fprintf(people, "��Ʒ�ۿ�Ϊ��%s\n", p->data.commodities_discount);
			fprintf(people, "��Ʒ��ʼ����Ϊ��%s\n", p->data.commodities_amount);
			fprintf(people, "��Ʒ���Ϊ��%s\n", p->data.commodities_remain);
			fprintf(people, "\n");
		}

		fclose(people);
		//system("C:/Users/33914/source/repos/�������/�������/��Ʒ��Ϣ.txt");

		if (fopen_s(&people, FRIENDLY_FILENAME, "w+") != 0)
		{
			printf("����");
			while ((buffer = getchar()) != EOF && buffer != '\n');
			return;
		}

		for (p = original; p != NULL; p = p->next)
		{
			fprintf(people, "��ƷIDΪ��%s\n", p->data.commodities_id);
			fprintf(people, "��Ʒ����Ϊ��%s\n", p->data.commodities_name);
			fprintf(people, "��Ʒ����Ϊ��%s\n", p->data.commodities_price);
			fprintf(people, "��Ʒ�ۿ�Ϊ��%s\n", p->data.commodities_discount);
			fprintf(people, "��Ʒ��ʼ����Ϊ��%s\n", p->data.commodities_amount);
			fprintf(people, "��Ʒ���Ϊ��%s\n", p->data.commodities_remain);
			fprintf(people, "\n");
		}

		fclose(people);

		break;
	case 'N':
		return;
		break;
	default:
		printf("�������˴����ָ���������ȷ��ָ�\n");
		printf("������ָ�(Y/N)");
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

	printf("����\"exit\"����ǿ���˳��˽��档\n\n");

	printf("��������޸���Ʒ��ID��");
	readline(target_ID);
	if (check_exit(target_ID))
		return;

	for (p = first; p != NULL; p = p->next)
	{
		if (strcmp(target_ID, p->data.commodities_id) == 0)
		{
			printf("\n");
			printf("����ƷΪ��%s\n", p->data.commodities_name);
			printf("����Ʒ����Ϊ��%s\n", p->data.commodities_price);
			printf("����Ʒ�ۿ�Ϊ��%s\n", p->data.commodities_discount);
			printf("����Ʒ��ʼ����Ϊ��%s\n", p->data.commodities_amount);
			printf("����Ʒ���Ϊ��%s\n", p->data.commodities_remain);
			printf("\n");
			printf("��ע�⣺�ڴ˴�����\"exit\"������ǿ���˳���\n");
			printf("�Ƿ��޸���Ʒ���ƣ������Ҫ��������Y���������Ҫ��������N��");
		A:
			operation = getchar();
			while ((buffer = getchar()) != EOF && buffer != '\n');
			if (operation == '\n')
				operation = getchar();
			operation = toupper(operation);
			switch (operation)
			{
			case 'Y':
				printf("�������µ���Ʒ���ƣ�");
				readline(target_name);
				strcpy_s(p->data.commodities_name, MAX_NAME_LEN, target_name);
				break;
			case 'N':
				break;
			default:
				printf("�������˴����ָ���������ȷ��ָ�\n");
				printf("�Ƿ��޸���Ʒ���ƣ�\n");
				printf("������ָ�(Y/N)");
				goto A;
				break;
			}

			printf("�Ƿ��޸���Ʒ���ۣ������Ҫ��������Y���������Ҫ��������N��");
		B:
			operation = getchar();
			while ((buffer = getchar()) != EOF && buffer != '\n');
			if (operation == '\n')
				operation = getchar();
			operation = toupper(operation);
			switch (operation)
			{
			case 'Y':
				printf("�������µ���Ʒ���ۣ�");
				readline(target_price);
				strcpy_s(p->data.commodities_price, MAX_PRICE_LEN, target_price);
				break;
			case 'N':
				break;
			default:
				printf("�������˴����ָ���������ȷ��ָ�\n");
				printf("�Ƿ��޸���Ʒ���ۣ�\n");
				printf("������ָ�(Y/N)");
				goto B;
				break;
			}

			printf("�Ƿ��޸���Ʒ�ۿۣ������Ҫ��������Y���������Ҫ��������N��");
		C:
			operation = getchar();
			while ((buffer = getchar()) != EOF && buffer != '\n');
			if (operation == '\n')
				operation = getchar();
			operation = toupper(operation);
			switch (operation)
			{
			case 'Y':
				printf("�������µ���Ʒ�ۿۣ�");
				readline(target_discount);
				strcpy_s(p->data.commodities_discount, MAX_DISCOUNT_LEN, target_discount);
				break;
			case 'N':
				break;
			default:
				printf("�������˴����ָ���������ȷ��ָ�\n");
				printf("�Ƿ��޸���Ʒ�ۿۣ�\n");
				printf("������ָ�(Y/N)");
				goto C;
				break;
			}

			printf("�Ƿ��޸���Ʒ��ʼ�����������Ҫ��������Y���������Ҫ��������N��");
		D:
			operation = getchar();
			while ((buffer = getchar()) != EOF && buffer != '\n');
			if (operation == '\n')
				operation = getchar();
			operation = toupper(operation);
			switch (operation)
			{
			case 'Y':
				printf("�������µ���Ʒ��ʼ������");
				readline(target_amount);
				strcpy_s(p->data.commodities_amount, MAX_AMOUNT_LEN, target_amount);
				break;
			case 'N':
				break;
			default:
				printf("�������˴����ָ���������ȷ��ָ�\n");
				printf("�Ƿ��޸���Ʒ��ʼ������\n");
				printf("������ָ�(Y/N)");
				goto D;
				break;
			}

			printf("�Ƿ��޸���Ʒ��棿�����Ҫ��������Y���������Ҫ��������N��");
		E:
			operation = getchar();
			while ((buffer = getchar()) != EOF && buffer != '\n');
			if (operation == '\n')
				operation = getchar();
			operation = toupper(operation);
			switch (operation)
			{
			case 'Y':
				printf("�������µ���Ʒ��棺");
				readline(target_remain);
				strcpy_s(p->data.commodities_remain, MAX_REMAIN_LEN, target_remain);
				break;
			case 'N':
				break;
			default:
				printf("�������˴����ָ���������ȷ��ָ�\n");
				printf("�Ƿ��޸���Ʒ��棿\n");
				printf("������ָ�(Y/N)");
				goto E;
				break;
			}

			break;
		}
	}
	if (p == NULL)
	{
		printf("�������ID�����ڣ�\n");
		printf("�Ƿ���Ҫ����������ƷID�������Ҫ��������Y���������Ҫ��������N��");

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
			printf("�������˴����ָ����Զ��˳���");
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
			printf("�������ظ���ID\n");
			printf("��������ƷID��");
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

	printf("����\"exit\"����ǿ���˳��˽��档\n\n");

	printf("��������ƷID��");
	readline(new_ID);
	while (check_ID(new_ID))
		readline(new_ID);
	if (check_exit(new_ID))
		return;
	printf("��������Ʒ���ƣ�");
	readline(new_name);
	if (check_exit(new_name))
		return;
	printf("��������Ʒ���ۣ�");
	readline(new_price);
	if (check_exit(new_price))
		return;
	printf("��������Ʒ�ۿۣ�");
	readline(new_discount);
	if (check_exit(new_discount))
		return;
	printf("��������Ʒ��ʼ������");
	readline(new_amount);
	if (check_exit(new_amount))
		return;
	printf("��������Ʒ��棺");
	readline(new_remain);
	if (check_exit(new_remain))
		return;

	new_node = calloc(1, sizeof(struct node));
	if (new_node == NULL)
	{
		printf("����");
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

	printf("�Ƿ����������Ʒ��Ϣ������ǣ�������Y��������ǣ�������N��");
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
		printf("�������˴����ָ����������룡\n");
		printf("������ָ�(Y/N)");
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

	printf("�ڴ˴�����\"exit\"����ǿ���˳��˽��档\n");

	printf("��������Ҫɾ������Ʒ��ID��");
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
		printf("�������ID�����ڣ�\n");
		printf("�Ƿ���������ID������ǣ�������Y��������ǣ�������N��");
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
			printf("�������˴����ָ����������룡\n");
			printf("������ָ�");
			goto G;
			break;
		}
	}
	else if (prev == NULL)
	{
		first = cur->next;
		original = first;
		free(cur);
		printf("��ɾ������Ʒ����Ϣ��");
		return;
	}
	else
	{
		prev->next = cur->next;
		free(cur);
		printf("��ɾ������Ʒ����Ϣ��");
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

	printf("����\"exit\"����ǿ���˳��˽��档\n\n");

	printf("��������Ҫ���ҵ���Ʒ��ID��");
	readline(target_ID);

	if (check_exit(target_ID))
		return;

	for (p = first; p != NULL; p = p->next)
	{
		if (strcmp(p->data.commodities_id, target_ID) == 0)
		{
			printf("\n");
			printf("��Ʒ����Ϊ��%s\n", p->data.commodities_name);
			printf("��Ʒ����Ϊ��%s\n", p->data.commodities_price);
			printf("��Ʒ�ۿ�Ϊ��%s\n", p->data.commodities_discount);
			printf("��Ʒ��ʼ����Ϊ��%s\n", p->data.commodities_amount);
			printf("��Ʒ���Ϊ��%s\n", p->data.commodities_remain);
			printf("\n");
			break;
		}
	}

	if (p == NULL)
	{
		printf("�������ID�����ڣ�\n");
		printf("�Ƿ���Ҫ��������ID������ǣ�������Y��������ǣ�������N��");
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
			printf("�������˴����ָ����������룡\n");
			printf("������ָ�(Y/N)");
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
		printf("����");
		return;
	}
	if (fopen_s(&people, FRIENDLY_FILENAME, "w+") != 0)
	{
		printf("����");
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
		fprintf(people, "��ƷIDΪ��%s\n", p->data.commodities_id);
		fprintf(people, "��Ʒ����Ϊ��%s\n", p->data.commodities_name);
		fprintf(people, "��Ʒ����Ϊ��%s\n", p->data.commodities_price);
		fprintf(people, "��Ʒ�ۿ�Ϊ��%s\n", p->data.commodities_discount);
		fprintf(people, "��Ʒ��ʼ����Ϊ��%s\n", p->data.commodities_amount);
		fprintf(people, "��Ʒ���Ϊ��%s\n", p->data.commodities_remain);
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

	printf("������Ϊ��");
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
		printf("����");
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