#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h> //for LINE_MAX
#define FAILURE -1
#define SUCCESS 0

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
void freeNode(Node* currentNode) {
	free(currentNode->value);
	free(currentNode);
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
		freeNode(node);
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
		exit(FAILURE);
	}
	//текущий узел
	currentNode = head;
	//считываем введенные строки
	printf("Enter lines of text. To end entering, put '.' in the start of line.\n");
	while (fgets(line, LINE_MAX, stdin) != NULL) {
		if (line[0] == '.')
			break;
		currentNode->next = addString(line); //добавим строку в список
		if (currentNode->next == NULL) {
			freememory(currentNode);
			exit(FAILURE);
		}
		currentNode = currentNode->next; //указатель на строку
	}
	int ferr = ferror(stdin); //определение наличия ошибок потока данных
	if (ferr != SUCCESS) {
		perror("detection of data-flow errors");
		freememory(currentNode);
		exit(FAILURE);
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
