// BinarySearchTree.h

#include <stdio.h>
#include <Windows.h>

struct Eng_Data {
	char eng[128];
	char kor[128];

	int count;
};

typedef Eng_Data ElementType;

typedef struct tagBSTNode
{
	struct tagBSTNode* Left;
	struct tagBSTNode* Right;

	ElementType Data;
} BSTNode;

BSTNode*  BST_CreateNode(ElementType NewData);
void      BST_DestroyNode(BSTNode* Node);
void      BST_DestroyTree(BSTNode* Tree);

BSTNode*  BST_SearchNode(BSTNode* Tree, ElementType Target);
BSTNode*  BST_SearchMinNode(BSTNode* Tree);
void      BST_InsertNode(BSTNode* Tree, BSTNode *Child);
BSTNode*  BST_RemoveNode(BSTNode* Tree, BSTNode* Parent, ElementType Target);
void      BST_InorderPrintTree(BSTNode* Node);




// BinarySearchTree.cpp

#include "BinarySearchTree.h"

BSTNode* BST_CreateNode(ElementType NewData)	//노드생성
{
	BSTNode* NewNode = (BSTNode*)malloc(sizeof(BSTNode));
	NewNode->Left = NULL;
	NewNode->Right = NULL;
	strcpy(NewNode->Data.eng, NewData.eng);
	strcpy(NewNode->Data.kor, NewData.kor);

	NewNode->Data.count = NewData.count;

	return NewNode;
}

void BST_DestroyNode(BSTNode* Node)	//노드 삭제
{
	free(Node);
}

void BST_DestroyTree(BSTNode* Tree)	//트리 삭제
{
	// 구태여 주석을 달자면 프로그램을 종료하거나, 트리를 완전히 삭제하고 싶을 때
	// 트리를 순회하면서 모든 루트를 삭제하는 연산이다.
	if (Tree->Right != NULL)
		BST_DestroyTree(Tree->Right);

	if (Tree->Left != NULL)
		BST_DestroyTree(Tree->Left);

	Tree->Left = NULL;
	Tree->Right = NULL;

	BST_DestroyNode(Tree);
}

BSTNode*  BST_SearchNode(BSTNode* Tree, ElementType Target)
{
	if (Tree == nullptr)
		return nullptr;

	// 타겟을 찾았을 경우 현재 위치를 리턴
	if (!strcmp(Tree->Data.eng,Target.eng)) {
		return Tree;
	}

	else {
		// 현재 위치의 노드 데이터가 타겟의 데이터보다 클 경우
		if (Tree->Data.count > Target.count) {
			// 재귀 함수를 호출하여 트리의 왼쪽 노드를 순회
			BST_SearchNode(Tree->Left, Target);
		}

		// 반대 방향 연산
		else {
			BST_SearchNode(Tree->Right, Target);
		}
	}
}

BSTNode* BST_SearchMinNode(BSTNode* Tree)	//작은수의 노드값 찾기
{
	if (Tree == NULL)
		return NULL;

	if (Tree->Left == NULL)
		return Tree;
	else
		return BST_SearchMinNode(Tree->Left);
}

void BST_InsertNode(BSTNode* Tree, BSTNode *Child) // 노드 삽입
{
	if (Tree == nullptr)
		return;

	// 현재 위치의 노드 데이터가 자식 노드의 데이터보다 작을 경우
	if (Tree->Data.count < Child->Data.count) {
		// 노드의 오른쪽이 단말 노드일 때까지 재귀 함수로 트리의 오른쪽을 순회함.
		if (Tree->Right != nullptr)
			BST_InsertNode(Tree->Right, Child);
		else
			// 오른쪽 노드가 단말 노드일 경우, 단말 노드의 오른쪽에 자식 노드를 삽입
			Tree->Right = Child;
	}

	// 반대 방향 연산
	else {
		if (Tree->Left != nullptr)
			BST_InsertNode(Tree->Left, Child);
		else
			Tree->Left = Child;
	}
}

BSTNode* BST_RemoveNode(BSTNode* Tree, BSTNode* Parent, ElementType Target)	//노드 삭제
{
	// 요긴하게 쓰일 노드 변수
	BSTNode* node = nullptr;

	if (Tree == nullptr)
		return nullptr;

	// 삭제하고자 하는 노드의 데이터를 찾는 순회 작업
	// 첫번째 인자는 다음 노드 위치, 두번째 인자는 노드의 부모 노드를 가르킬 노드, 세번째 인자는 찾는 타겟의 데이터
	if (Tree->Data.count > Target.count)
		BST_RemoveNode(Tree->Left, Tree, Target);
	else if (Tree->Data.count < Target.count)
		BST_RemoveNode(Tree->Right, Tree, Target);

	else {
		node = Tree;	// 삭제할 노드의 위치 저장

		// 삭제하고자 하는 노드가 단말 노드인 경우
		// 부모 노드의 방향에 따라 삭제 할 자식 노드와 연결을 끊는 작업 수행
		if (Tree->Left == nullptr && Tree->Right == nullptr) {
			if (Parent->Left == Tree) { Parent->Left = nullptr; }
			else { Parent->Right = nullptr; }
		}

		else {
			// 삭제하고자 하는 노드가 2 개의 자식 노드를 가지고 있을 경우
			if (Tree->Left != nullptr && Tree->Right != nullptr) {
				// min 노드는 삭제할 노드의 오른쪽 노드로부터 최소값 즉, 단말 노드를 찾는다.
				BSTNode* min = BST_SearchMinNode(Tree->Right);
				// 삭제할 노드의 데이터에 min 노드의 데이터를 저장한다.
				Tree->Data = min->Data;

				// 삭제할 노드의 오른쪽 노드 위치 저장
				node = Tree->Right;

				// 오른쪽 노드가 단말 노드일 경우
				if (node->Left == nullptr) {
					// 오른쪽 노드와 연결 끊기
					Tree->Right = nullptr;
				}

				// 오른쪽 노드가 자식을 가진 노드일 경우
				while (node->Left != nullptr) {
					// min 단말 노드의 부모 노드를 찾았다면
					if (node->Left == min) {
						// 자식 노드와 연결 끊기
						node->Left = nullptr;
						// 삭제 할 노드 위치 저장
						node = min;
						break;
					}
					// 노드 순회
					else {
						node = node->Left;
					}
				}
			}

			else {
				// 임시 노드
				BSTNode* temp = nullptr;

				// 삭제 할 노드의 왼쪽 자식 노드
				if (Tree->Left != nullptr) {
					// 임시 노드에 저장
					temp = Tree->Left;
				}

				// 반대 방향
				else {
					temp = Tree->Right;
				}

				// 부모 노드의 왼쪽 자식이 삭제 할 노드일 때
				if (Parent->Left == Tree) {
					// 부모 노드의 자식을 임시 노드에 저장된 자식 노드로 바꿈
					// 이로써 삭제할 노드와 부모 노드는 연결이 끊김
					Parent->Left = temp;
				}

				// 반대 방향
				else {
					Parent->Right = temp;
				}
			}
		}
	}

	// 요긴하게 썼던 노드 변수를 리턴함으로써, 삭제 해야 될 노드 위치가 리턴됨
	return node;
}

void BST_InorderPrintTree(BSTNode* Node)	// 트리출력
{
	if (Node == NULL)
		return;

	BST_InorderPrintTree(Node->Left);
	printf("단어 : %s / 뜻 : %s\n", Node->Data.eng, Node->Data.kor);
	BST_InorderPrintTree(Node->Right);
}


// main.cpp

#include "BinarySearchTree.h"
#include <conio.h>

// 트리 변수
BSTNode* Tree = nullptr;
BSTNode* Node = nullptr;

// 트리 데이터 구조체
Eng_Data Data;

// 트리 내에 데이터 순서
int count = 1;

int main() {
	// 루트 노드 더미 데이터
	strcpy(Data.eng, "None");
	strcpy(Data.kor, "None");
	Data.count = 0;

	// 트리 생성
	Tree = BST_CreateNode(Data);

	// 반복문 탈출
	bool flag = false;

	while (1) {
		char num[128];

		system("cls");

		printf("[ 메뉴 ]\n\n1. 입력\n2. 삭제\n3. 탐색 \n0. 종료\n\n입력 : ");
		scanf("%s", num);

		num[1] = '\0';

		switch (atoi(num)) {
		case 1:
			printf("단어 입력 : ");
			scanf("%s", Data.eng);

			printf("의미 입력 : ");
			scanf("%s", Data.kor);

			Node = BST_SearchNode(Tree, Data);
			if (Node != nullptr) {
				printf("이미 같은 단어를 등록 했습니다.\n\n");
			}
			else {
				Data.count = count++;
				BST_InsertNode(Tree, BST_CreateNode(Data));
				printf("정상적으로 등록되었습니다.\n\n");
			}

			printf("아무 키나 입력하세요 . . .\n");
			getch();
			break;

		case 2:
			printf("단어 입력 : ");
			scanf("%s", Data.eng);

			Node = BST_SearchNode(Tree, Data);
			if (Node == nullptr) {
				printf("단어를 찾지 못했습니다.\n\n");
			}
			else {
				Data.count = Node->Data.count;
				Node = BST_RemoveNode(Tree, nullptr, Data);
				printf("%s 단어를 정상적으로 삭제했습니다.\n\n", Data.eng);
			}

			printf("아무 키나 입력하세요 . . .\n");
			getch();
			break;

		case 3:
			printf("단어 입력 : ");
			scanf("%s", Data.eng);

			Node = BST_SearchNode(Tree, Data);
			if (Node == nullptr) {
				printf("단어를 찾지 못했습니다.\n\n");
			}
			else {
				printf("단어 : %s / 의미 : %s\n\n", Node->Data.eng, Node->Data.kor);
			}

			printf("아무 키나 입력하세요 . . .\n");
			getch();
			break;

		case 0:
			printf("\n\n프로그램을 종료합니다 . . .\n");
			flag = true;
			break;

		default:
			continue;
		}

		if (flag) {
			break;
		}
	}

	BST_DestroyTree(Tree);
	system("pause");

	return 0;
}
