#include <stdio.h>

#define MAX_NODE_NUM 10000
#define MAX_CHILD_NUM 2

typedef struct
{
	int parent;
	int child[MAX_CHILD_NUM];
} TreeNode;

TreeNode tree[MAX_NODE_NUM];
int nodeNum;
int edgeNum;
int root;

// ��� ������ŭ -1�� �ʱ�ȭ
void initTree(void)
{
	int i;
	int j;
	for (i = 0; i <= nodeNum; i++)
	{
		tree[i].parent = -1;
		for (j = 0; j < MAX_CHILD_NUM; j++)
		{
			tree[i].child[j] = -1;
		}
	}
}

// ��尪�� -1�� ���(���ܳ��)�� ���� ������ Ž���ϴٰ� �߰�
void addChild(int parent, int child)
{
	int i;
	for (i = 0; i < MAX_CHILD_NUM; i++)
	{
		if (tree[parent].child[i] == -1)
		{
			break;
		}
	}
	tree[parent].child[i] = child;
	tree[child].parent = parent;
}

int getRoot(void)
{
	int i;
	int j;
	for (i = 1; i <= nodeNum; i++)
	{
		if (tree[i].parent == -1)
		{
			return i;
		}
	}
	return -1;
}

//������ȸ
void preOrder(int root)
{
	int i;
	int child;
	printf("%d ", root);

	for (i = 0; i < MAX_CHILD_NUM; i++)
	{
		child = tree[root].child[i];
		if (child != -1)
		{
			preOrder(child);
		}
	}
}

int main(void)
{
	int test_case;
	int T;
	int i;
	int parent;
	int child;

	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case)
	{
		scanf("%d %d", &nodeNum, &edgeNum);

		initTree();

		for (i = 0; i < edgeNum; i++)
		{
			scanf("%d %d", &parent, &child);
			addChild(parent, child);
		}

		root = getRoot();

		printf("#%d ", test_case);
		preOrder(root);
		printf("\n");
	}

	return 0;
}