#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define BACK 0
#define FRONT 1

struct Student
{
	int num;
};
struct NODE
{
	struct Student data;
	struct NODE *next;
};

struct NODE *CreateLink()
{
	struct NODE *head = malloc(sizeof*head);
	if (NULL == head)
	{
		printf("Memory alloction failed!\n");
		exit(-1);
	}
	struct NODE *move = head;
	move->next = NULL;

	int index;
	printf("你想输入几个结点");
	scanf("%d", &index);

	for (int i = 0; i < index; ++i, move = move->next)
	{
		struct NODE *fresh = malloc(sizeof*fresh);
		if (NULL == fresh)
		{
			printf("Memory alloction failed!\n");
			exit(-1);
		}

		move->next = fresh;
		fresh->next = NULL;
	}

	return head;
}
void Init(const struct NODE *head)
{
	struct NODE *move = head->next;

	for (int i = 1; move != NULL; move = move->next, ++i)
	{
		printf("请输入第%d个结点的信息: ", i);
		scanf("%d", &move->data.num);
	}
}
void OutputLink(const struct NODE *head)
{
	struct NODE *move = head->next;

	for (; move != NULL; move = move->next)
	{
		printf("[%d]->", move->data.num);
	}
	printf("[^]\n");
}
void DestroyLink(struct NODE *head)
{
	struct NODE *save = NULL;

	while (head)
	{
		save = head;
		head = head->next;
		free(save);
		save = NULL;
	}
	if (head == NULL)
	{
		printf("链表已销毁!\n");
	}
}

void InsertLink(const struct NODE *head,int flag)
{
	struct NODE *move = (flag == BACK ? head->next : head);

	int index;
	printf("你想在第几个结点之后插入: ");
	scanf("%d", &index);

	for (int i=1; (flag == BACK ? move : move->next) != NULL; ++i, move = move->next)
	{
		if (i == index)
		{
			struct NODE *fresh = malloc(sizeof*fresh);
			if (NULL == fresh)
			{
				printf("Memory alloction failed!\n");
				exit(-1);
			}

			printf("请输入新的结点信息: ");
			scanf("%d", &fresh->data.num);

			fresh->next = move->next;
			move->next = fresh;

			break;
		}
	}
}
void DeleteLink(const struct NODE *head)
{
	struct NODE *move = head;

	int index;
	printf("请输入你想删除的位置: ");
	scanf("%d", &index);

	for (int i = 1; move->next != NULL; move = move->next, ++i)
	{
		if (i == index)
		{
			struct NODE *save = move->next;
			move->next = move->next->next;

			free(save);
			save = NULL;

			break;
		}
	}
}

int main(void)
{
	struct NODE *head = CreateLink();
	Init(head);
	OutputLink(head);
	
	/*InsertLink(head, BACK);
	OutputLink(head);
	InsertLink(head,FRONT);
	OutputLink(head);*/

	/*DeleteLink(head);
	OutputLink(head);*/

	DestroyLink(head);
	system("pause");
	return 0;
}