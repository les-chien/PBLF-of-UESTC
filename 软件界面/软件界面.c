#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define GOODS_FILE_NAME "goodsinfo.txt"
#define MAX_ID_LEN 30
#define MAX_NAME_LEN 30
#define MAX_PRICE_LEN 30
#define MAX_DISCOUNT_LEN 30

typedef struct
{
	char goods_id[MAX_ID_LEN];
	char goods_name[MAX_NAME_LEN];
	int goods_price;
	char goods_discount[MAX_DISCOUNT_LEN];
	int goods_amount;
	int goods_remain;
}GoodsInfo;

typedef struct node
{
	GoodsInfo data;
	struct node* next;
}GoodsList;

GoodsList* first = NULL;
GoodsList* new_node = NULL;
int CurrentCnt;

GoodsInfo read_goods_info(GoodsInfo information);
void init_list(GoodsList** p);
void destory_list(GoodsList** p);
void destory_list_and_file(GoodsList** p);
int save_to_file(GoodsList* p);
void output_one_item(GoodsList* p);
void output_all_items(GoodsList* p);
bool insert_item(GoodsList* p, GoodsInfo item, int choice);
bool delete_item(GoodsList* p, char* goods_id);
GoodsList* search_item(GoodsList* p, char* goods_id);
bool change_item(GoodsList* p, char* goods_id, GoodsInfo new_info);
void bubble_sort(GoodsList* p);
int read_line(char str[], int n);
int main0()
{
	GoodsInfo information = { "0", "0", 0, "0", 0, 0 };
	read_goods_info(information);
	GoodsList list;
	list.data = information;
	int get_number = MAX_ID_LEN;
	init_list(&(list.next));
	read_line(information.goods_id, get_number);
	for (;;)
	{
		printf("1.显示所有商品的信息\n");
		printf("2.修改某个商品的信息\n");
		printf("3.插入某个商品的信息\n");
		printf("4.删除某个商品的信息\n");
		printf("5.查找某个商品的信息\n");
		printf("6.商品存盘并退出系统\n");
		printf("7.对商品价格进行排序\n");
		printf("8.(慎用)删除所有内容\n");
		printf("other.不存盘并退出系统");
		scanf_s("%d", &get_number);
		switch (get_number) 
		{
		case 1:
			output_all_items(list.next);
			break;
		case 2:
			change_item(list.next, information.goods_id, list.data);
			break;
		case 3:
			insert_item(list.next, list.data, get_number);
			break;
		case 4:
			delete_item(list.next, information.goods_id);
			break;
		case 5:
			search_item(list.next, information.goods_id);
			break;
		case 6:
			save_to_file(list.next);
			break;
		case 7:
			bubble_sort(list.next);
			break;
		case 8:
			destory_list_and_file(&(list.next));
			break;
		default:
			printf("Illegal number\n");
			return 0;
		}
		printf("\n");
	}
}
GoodsInfo read_goods_info(GoodsInfo information)
{
	printf("商品ID:");
	read_line(information.goods_id, MAX_ID_LEN);
	printf("商品名称：");
	read_line(information.goods_name, MAX_NAME_LEN);
	printf("商品价格：");
	scanf_s("%d", &information.goods_price);
	printf("商品折扣：");
	read_line(information.goods_discount, MAX_DISCOUNT_LEN);
	printf("商品数量：");
	scanf_s("%d", &information.goods_amount);
	printf("商品剩余数量:");
	scanf_s("%d", &information.goods_remain);
	return information;
}
void init_list(GoodsList** L)
{
	int i = 0;
	*L = (GoodsList*)malloc(sizeof(GoodsList));
	if (*L == NULL)
		return;
	GoodsList* hpead = *L;
	GoodsInfo gi;
	FILE* fp;
	if (fopen_s(&fp, "goodsinfo.txt", "a+") != 0)
	{
		printf("Error!");
		return;
	}
	while (fscanf_s(fp, "%s %s %d %s %d %d\n", gi.goods_id, MAX_ID_LEN, gi.goods_name, MAX_NAME_LEN, &gi.goods_price, gi.goods_discount, MAX_DISCOUNT_LEN, &gi.goods_amount, &gi.goods_remain) != EOF)
	{
		GoodsList* cur = (GoodsList*)malloc(sizeof(GoodsList));
		if (cur == NULL)
			continue;

		cur->data = gi;
		hpead->next = cur;
		hpead = hpead->next;
		i++;
	}
	printf("目前有 %d个商品信息 ", i);
}
void destory_list(GoodsList** L)
{
	if (L == NULL || *L == NULL)
		return;
	GoodsList* pre = *L, * p = (*L)->next;
	while (p != NULL)
	{
		free(pre);
		pre = p;
		p = p->next;
	}
	free(pre);
	CurrentCnt = 0;
	*L = NULL;
}
void destory_list_and_file(GoodsList** L)
{
	destory_list(L);
	remove("goodsinfo.txt");
}
int save_to_file(GoodsList* L)
{
	GoodsList* gl;
	gl = L->next;
	int i = 0;
	FILE* fp;
	while (fopen_s(&fp, "goodinfo.txt", "w+") != 0)
	{
		printf("Error!");
		return i;
	}
	while (gl)
	{
		GoodsInfo gi = gl->data;
		fprintf(fp, "%s %s %d %s %d %d\n", gi.goods_id, gi.goods_name, gi.goods_price, gi.goods_discount, gi.goods_amount, gi.goods_remain);
		gl = gl->next;
		i++;
	}
	fclose(fp);
	return i;
}
void output_one_item(GoodsList* p)
{
	printf("%s", p->data.goods_id);
	printf("%s", p->data.goods_name);
	printf("%d", p->data.goods_price);
	printf("%s", p->data.goods_discount);
	printf("%d", p->data.goods_amount);
	printf("%d", p->data.goods_remain);
}
void output_all_items(GoodsList* L)
{
	GoodsList* p = L->next;
	while (p != NULL)
	{
		output_one_item(p);
		p = p->next;
	}
}
bool insert_item(GoodsList* L, GoodsInfo goodsInfo, int choice)
{

	GoodsList* cur, * new_node;
	new_node = (GoodsList*)malloc(sizeof(GoodsList));
	if (new_node == NULL) {
		return false;
	}
	new_node->data = goodsInfo;
	new_node->next = NULL;
	cur = L->next;
	int i = 2;
	switch (choice)
	{
	case 0: //尾插
		if (cur == NULL)
		{
			L->next = new_node;
			CurrentCnt++;
			break;
		}
		else
		{
			while (cur->next)
				cur = cur->next;

		}
		cur->next = new_node;
		CurrentCnt++;
		break;
	case 1: //头插
		if (cur == NULL)
		{
			L->next = new_node;
			CurrentCnt++;
		}
		else
		{
			new_node->next = L->next;
			L->next = new_node;
			CurrentCnt++;
		}
		break;
	default: //任意插
		while (cur)
		{
			if (i == choice)
			{
				new_node->next = cur->next;
				cur->next = new_node;
				CurrentCnt++;
				return true;
			}
			cur = cur->next;
			i++;
		}
		return false;
		break;
	}
	return true;
}
bool delete_item(GoodsList* L, char* goods_id)
{
	GoodsList* pre = L, * p = L->next;
	if (strcmp(goods_id, pre->data.goods_id) == 0) {
		L = p;
		free(pre);
		pre = NULL;
		CurrentCnt--;
		return true;
	}
	else {
		for (; p != NULL && strcmp(goods_id, p->data.goods_id) != 0; pre = pre->next, p = p->next)
			;
		if (p == NULL) {
			printf("该商品不存在。\n");
			return false;
		}
		else {
			pre->next = p->next;
			free(p);
			p = NULL;
			CurrentCnt--;
			return true;
		}
	}
}
GoodsList* search_item(GoodsList* L, char* goods_id)
{
	GoodsList* p;
	p = L->next;
	if (strcmp(L->data.goods_id, goods_id) == 0)
		return L;
	while (p != NULL)
	{
		if (strcmp(p->data.goods_id, goods_id) == 0)
			return p;
		p = p->next;
	}
	printf("Cannot be found.\n");
	return NULL;
}
bool change_item(GoodsList* L, char* goods_id, GoodsInfo new_info)
{
	GoodsList* p1;
	p1 = L;
	p1 = search_item(p1, goods_id);
	if (p1 == NULL)
		return false;
	if (strcmp(p1->data.goods_id, goods_id) == 0)
	{
		p1->data = new_info;
		return true;
	}

	return false;
}
void bubble_sort(GoodsList* L)
{
	GoodsList* p;
	p = L;
	int n, h, j;
	n = 0;
	if (!p)
		return;

	while (p)
	{
		n++;
		p = p->next;
	}
	if (n == 1)
		return;
	for (j = 0; j < n - 1; j++)
	{
		p = L;
		for (h = 0; h < n - 1 - j; h++)
		{
			if (p->data.goods_price > p->next->data.goods_price)
			{
				GoodsInfo temp;
				temp = p->next->data;
				p->next->data = p->data;
				p->data = temp;
			}
			p = p->next;
		}
	}
}
int read_line(char str[], int n)
{
	char ch;
	int i;

	ch = getchar();
	if (ch == '\n')
		ch = getchar();
	for (i = 0; ch != '\n' && i < n; i++)
	{
		str[i] = ch;
		ch = getchar();
	}
	str[i] = '\0';

	return i;
}
