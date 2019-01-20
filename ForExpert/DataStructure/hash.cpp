#include<stdio.h>
#include<string.h>
#include<memory.h>

#define MAX_KEY 64
#define MAX_DATA 128
#define MAX_TABLE 4096

typedef struct {
	char key[MAX_KEY + 1];
	char data[MAX_DATA + 1];
}Hash;

Hash tb[MAX_TABLE];

unsigned long hash(const char *str) {
	unsigned long hash = 5381;
	int c;

	while (c = *str++) {
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}

	return hash % MAX_TABLE;
}

int find(const char *key, char *data) {
	unsigned long h = hash(key);
	int cnt = MAX_TABLE;

	while (tb[h].key[0] != 0 && cnt--) {
		if (strcmp(tb[h].key, key) == 0) {
			strcpy(data, tb[h].data);
			return 1;
		}

		h = (h + 1) % MAX_TABLE;

	}
	return 0;
}

int add(const char *key, char *data) {
	unsigned long h = hash(key);

	while (tb[h].key[0] != 0) {
		//collision case
		
		//same case
		if (strcmp(tb[h].key, key) == 0) {
			return 0;
		}

		//open addressing
		h = (h + 1) % MAX_TABLE;
	}
	printf("�������� �Է�");
	strcpy(tb[h].key, key);
	strcpy(tb[h].data, data);
	return 1;
}

int main() {
	int T, N, Q;

	//test case
	printf("input testcase");
	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++) {
		//0���� ���� �ʱ�ȭ
		memset(tb, 0, sizeof(tb));

		//input data Ƚ��
		printf("num of input data?");
		scanf("%d", &N);
		char k[MAX_KEY + 1];
		char d[MAX_DATA + 1];

		for (int i = 0; i < N; i++) {
			//printf("!!");
			scanf( "%s %s\n", k, d);
			//printf("%s %s\n", k, d);
			add(k, d);
		}

		printf("#%d\n", test_case);

		//query Ƚ��
		scanf("%d", &Q);

		for (int i = 0; i < Q; i++) {
			char k[MAX_KEY + 1];
			char d[MAX_DATA + 1];

			scanf("%s\n", &k);

			if (find(k, d)) {
				printf("%s\n", d);
			}
			else {
				printf("404 NOT FOUND\n");
			}
		}
	}
	return 0;
}