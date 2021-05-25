#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h> //for LINE_MAX
#define FIASCO -1
#define SUCCESS 0
//#define LINE_MAX 2048 //для отладки в виндоус
typedef struct node {
	char* value; //строка
	struct node* next; //сосед
} Node;
Node* nodeInit() {
	Node* head = (Node*)malloc(sizeof(Node));
	if (head == NULL) {
		perror("can`t create node");
		return NULL;
	}
	head->next = NULL;
	head->value = NULL;
	return head;
}

Node* addString(char* newLine) {
	Node* newNode = NULL;
	newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) {
		perror("can`t create newNode");
		return NULL;
	}
	newNode->value = (char*)malloc((strlen(newLine) + 1) * sizeof(char));
	if (newNode->value == NULL) {
		perror("can`t create newNode->value");
		return NULL;
	}
	strcpy(newNode->value, newLine);
	//strcpy_s(newNode->value, strlen(newLine) + 1, newLine);
	newNode->next = NULL;
	return(newNode);
}
void freememory(Node* node) {
	if (node == NULL) {
		return;
	}
	Node* nxtNode = NULL;
	while (node != NULL) {
		nxtNode = node->next;
		free(node);
		node = nxtNode;
	}
}

int main() {
	char line[LINE_MAX];
	Node* head = NULL,
		* currentNode = NULL,
		* i = NULL;
	//выделим память
	head = nodeInit();
	if (head == NULL) {
		exit(FIASCO);
	}
	//текущий узел
	currentNode = head;
	//считываем введенные строки
	printf("Enter lines of text. To end entering, put '.' in the start of line.\n");
	while (fgets(line, LINE_MAX, stdin) != NULL) {
		if (line[0] == '.')
			break;

		int i;
		for (i = 0; i < LINE_MAX; i++)
		{
			if (line[i] == '\n')
			{
				line[i] = '\0';
				break;
			}
		}
		currentNode->next = addString(line); //добавим строку в список
		if (currentNode->next == NULL) {
			freememory(currentNode);
			exit(FIASCO);
		}
		currentNode = currentNode->next; //указатель на строку
	}
	int ferr = ferror(stdin); //определение наличия ошибок потока данных
	if (ferr != SUCCESS) {
		perror("detection of data-flow errors");
		freememory(currentNode);
		exit(FIASCO);
	}
	//вывод на экран
	for (i = head->next; i != NULL; i = i->next) {
		puts(i->value);
	}
	i = head->next;
	//чистим память
	freememory(i);

	free(head);
	return SUCCESS;
}