// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가

#endif //PCH_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>
#include <vector>
#include <memory>
#include <list>

int Add(int a, int b);

// ===========================Linked list
typedef struct _tagNode {
	int iData; 
	struct _tagNode* pNextNode;
}tNode;

typedef struct _tagList {
	tNode* pHeadNode; // first node
	int iCount; 
}tLinkedList;

void InitList(tLinkedList* pList);
void PushBack(tLinkedList* pList, int iData);
void PushFront(tLinkedList* pList, int iData);
void RealeaseList(tLinkedList* pList);

// ============================ 가변배열
typedef struct tArr {
	int* pInt; // 힙 메모리 영역에서의 시작 주소 = 배열의 시작점
	int iCount;
	int iMaxCount;
}tArr;

void InitArr(tArr* pArr);
void PushBackArr(tArr* pArr, int iData);
void Reallocate(tArr* pArr);
void ReleaseArr(tArr* pArr);

// ========================================== Class
class CMy {
private:
	int num;
public:
	CMy(const CMy& other) { *this = other; };
	CMy() : num(0) {};
	CMy(int n) : num(n) {};
	void SetNum(const int n) { num = n; }
	int GetNum() { return num; }

	// 대입 연산자
	CMy& operator =(const CMy& _Other) { // 레퍼런스 변수
		// const CMy& other -> 매개변수로 객체를 참조받지만 수정 불가
		// 연산이 끝난 후 이 원본을 그대로 반환하므로 반환타입 CMy&
		this->num = _Other.num;

		return *this;
	}
};

// =============================== 클래스 템플릿
template<typename T>
class CArr { // 가변배열 클래스
private:
	T* pArr; // 가변배열의 첫 주소 (배열의 시작점=배열)
	int iCount;
	int iMaxCount;

public:
	CArr();
	void PushBack(const T& iData);
	void Reallocate(int iResizeCount); // resize
	int& operator [](int idx); // int*,int,int&의 차이점 생각해보기
	~CArr();
};

template<typename T>
CArr<T>::CArr()
{
	//pArr = (int*)malloc(sizeof(int) * 2); -> C
	pArr = new T[2]; // -> C++, malloc과 달리 '자료형'을 받아감
	iCount = 0;
	iMaxCount = 2;
}
template<typename T>
void CArr<T>::PushBack(const T& iData)
{
	if (iMaxCount <= iCount) {
		Reallocate(iMaxCount * 2);
	}

	pArr[iCount++] = iData;
}
template<typename T>
void CArr<T>::Reallocate(int iResizeCount)
{
	// 매개변수가 현재 수용량보다 적으면 예외처리
	if (iMaxCount >= iResizeCount) return;

	int* newArr = new T[iResizeCount];

	for (int i = 0; i < iMaxCount; i++) {
		newArr[i] = pArr[i];
	}

	delete[] pArr;
	pArr = newArr;

	iMaxCount = iResizeCount;
}
template<typename T>
int& CArr<T>::operator[](int idx)
{
	return pArr[idx];
}
template<typename T>
CArr<T>::~CArr()
{
	delete[] pArr;
}
// // ===========================연결리스트 클래스 템플릿
template<typename T>
struct LLNode {
	LLNode* pNextNode;
	LLNode* pPrevNode;
	T iData;
	LLNode(const T& data, LLNode<T>* Prev, LLNode<T>* Next) {
		iData = data;
		pPrevNode = Prev;
		pNextNode = Next;
	}
};
template<typename T>
class CLinkedList { 
private:
	LLNode<T>* HeadNode;
	LLNode<T>* TailNode;
	int iCount;
public:
	CLinkedList();
	~CLinkedList();
	void PushBack(const T& iData);
	void PushFront(const T& iData);
	int GetNode();

	class iterator;
	iterator begin();
	iterator end();
	iterator erase(iterator& iter);
	iterator insert(const iterator& iter, const T& data);

	class iterator {
	private:
		CLinkedList<T>* pList;
		LLNode<T>* pNode; // 리스트 반복자는 노드와 리스트의 주소 알아야함
		bool bValid;
	public:
		T& operator* () { return pNode->iData; }
	public :
		iterator() : pList(nullptr), pNode(nullptr), bValid(false) {};
		iterator(CLinkedList* pList, LLNode<T>* pNode) {
			this->pList = pList;
			this->pNode = pNode;
			if (pList != nullptr && pNode != nullptr) {
				bValid = true;
			}
		};

		friend class CLinkedList;
	};
};
template<typename T>
CLinkedList<T>::CLinkedList()
{
	HeadNode = nullptr;
	TailNode = nullptr;
	iCount = 0;
}
template<typename T>
CLinkedList<T>::~CLinkedList()
{
	LLNode<T>* CurrentNode = HeadNode;
	while (CurrentNode != nullptr) {
		LLNode<T>* pNext = CurrentNode->pNextNode;
		delete(CurrentNode);
		CurrentNode = pNext;
	}
}
template<typename T>
void CLinkedList<T>::PushBack(const T& iData)
{
	LLNode<T>* pNewNode = new LLNode<T>(iData,nullptr,nullptr);

	if (HeadNode == nullptr) {
		HeadNode = pNewNode;
		TailNode = pNewNode; // 첫 노드이자 마지막 노드
	}
	else {
		// 이 리스트에서 마지막 노드인 TailNode를 사용
		TailNode->pNextNode = pNewNode;
		pNewNode->pPrevNode = TailNode;
		// 기존의 마지막 노드를 추가할 노드로 갱신
		TailNode = pNewNode;
	}
	iCount++;
}
template<typename T>
void CLinkedList<T>::PushFront(const T& iData)
{
	// 새로 생성된 노드가 헤더가 됨. 그뜻은 이 노드의 다음 노드가 기존의 헤드
	LLNode<T>* pNewNode = new LLNode<T>(iData, nullptr, HeadNode);

	HeadNode->pPrevNode = pNewNode; // 지금 헤드의 이전 노드를 새 노드로
	HeadNode = pNewNode;

	iCount++;
}
template<typename T>
int CLinkedList<T>::GetNode()
{
	LLNode<T>* CurrentNode = HeadNode;
	while (CurrentNode != NULL) {
		std::cout << CurrentNode->iData;
		CurrentNode = CurrentNode->pNextNode;
	}
	return 0;
}

template<typename T>
inline typename CLinkedList<T>::iterator CLinkedList<T>::begin()
{
	return iterator(this, HeadNode);
}

template<typename T>
inline typename CLinkedList<T>::iterator CLinkedList<T>::end()
{
	return iterator(this, nullptr);
}

template<typename T>
inline typename CLinkedList<T>::iterator CLinkedList<T>::erase(iterator& iter)
{
	LLNode<T>* deleteNode = iter.pNode;

	if (iter.pNode == HeadNode) {
		HeadNode = iter.pNode->pNextNode;
	}
	else {
			iter.pNode->pNextNode->pPrevNode = iter.pNode->pPrevNode;
	iter.pNode->pPrevNode->pNextNode = iter.pNode->pNextNode;
	}

	delete(deleteNode);

	return iterator(this, HeadNode);
}

template<typename T>
inline typename CLinkedList<T>::iterator CLinkedList<T>::insert(const iterator& iter, const T& data)
{
	// 리스트에 삽입할 노드
	LLNode<T>* newNode = new LLNode<T>(data, nullptr, nullptr);

	// iterator가 헤드노드일 경우
	if (iter.pNode == HeadNode) {
		iter.pNode->pPrevNode = newNode;
		newNode->pNextNode = iter.pNode;
		HeadNode = newNode;
	}

	// iterator가 가리키는 노드의 이전 노드로 가서 생성한 노드 삽입
	iter.pNode->pPrevNode->pNextNode = newNode;
	newNode->pPrevNode = iter.pNode->pPrevNode;
	iter.pNode->pPrevNode = newNode;
	newNode->pNextNode = iter.pNode;

	++iCount;

	return iterator(this, newNode);
}


// ========================================= BST

enum class NODE_TYPE {
	PARENT, // 0 
	LCHILD, // 1
	RCHILD, // 2
	END,    // 3
};

template<typename T1, typename T2>
struct pair {
	T1 first;
	T2 second;
};

template<typename T1,typename T2> 
pair<T1, T2> makePair(const T1& first, const T2& second) {
	return pair<T1,T2>{first, second};
}

template<typename T1, typename T2>
struct tBSTNode {
	// pair data, 부모노드, 자식노드
	pair<T1,T2> _pair;

	tBSTNode* arrNode[(int)NODE_TYPE::END]; // size 4 array

public:
	tBSTNode() : pair(), arrNode{} {};
	tBSTNode(const pair<T1, T2>& p, tBSTNode* pN, tBSTNode* l, tBSTNode* r) :
		_pair(p), arrNode{ pN,l,r } {};

	bool isLeaf() { // 자식노드 있는지 판별
		if (nullptr == arrNode[(int)NODE_TYPE::LCHILD] &&
			nullptr == arrNode[(int)NODE_TYPE::RCHILD]) {
			return true;
		} return false;
	}
	bool isFull() { // 자식노드가 두개인지
		if (arrNode[(int)NODE_TYPE::RCHILD] &&
			arrNode[(int)NODE_TYPE::LCHILD])
			return true;
		return false;
	}
	bool isLeftChild() {
		if (arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] == this)
			return true;
		return false;
	}
	bool isRightChild() {
		if (arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::RCHILD] == this)
			return true;
		return false;
	}
};

template <typename T1, typename T2> // pair<T1, T2>
class CBST {
private:
	tBSTNode<T1,T2>* pRoot;
	int iCount;
public:
	CBST() : pRoot(nullptr), iCount(0) {};

	void insert(const pair<T1, T2>& pair);
	//tBSTNode<T1, T2>* GetInOrderSuccessor(tBSTNode<T1, T2>* pNode);
	tBSTNode<T1, T2>* GetInOrderPredecessor(tBSTNode<T1, T2>* pNode);

	class iterator;
	iterator begin();
	iterator end();
	iterator find(const T1& key);
	iterator erase(const iterator& _iter);

	class iterator {
	private:
		CBST* pBST;
		tBSTNode<T1, T2>* pNode;
	public:
		iterator() : pBST(nullptr), pNode(nullptr) {};
		iterator(CBST* _pBST, tBSTNode<T1, T2>* _pNode) :
			pBST(_pBST), pNode(_pNode) {};

		bool operator ==(const iterator& other) {
			if (other.pBST == pBST && other.pNode == pNode) return true;
			else false;
		}
		bool operator !=(const iterator& other) {
			if (other.pBST == pBST && other.pNode == pNode) return false;
			else true;
		}
		const pair<T1, T2>& operator *() {
			return pNode->_pair;
		}
		const pair<T1, T2>* operator ->() {
			return &pNode->_pair;
		}
		friend class CBST<T1, T2>;
	};
};

template<typename T1, typename T2>
inline void CBST<T1, T2>::insert(const pair<T1, T2>& pair)
{
	tBSTNode<T1,T2>* newNode = new tBSTNode<T1, T2>(pair, nullptr,nullptr,nullptr);

	if (pRoot == nullptr) {
		pRoot = newNode;
	}
	else {
		tBSTNode<T1, T2>* pNode = pRoot;
		NODE_TYPE node_type = NODE_TYPE::END;

		while (true) {
			if (pNode->_pair.first < newNode->_pair.first) {
				node_type = NODE_TYPE::RCHILD;
			}
			else if (pNode->_pair.first > newNode->_pair.first) {
				node_type = NODE_TYPE::LCHILD;
			}
			else { std::cout << "값은 Key값은 들어올 수 없습니다."; break; }

			if (pNode->arrNode[(int)node_type] == nullptr) {
				pNode->arrNode[(int)node_type] = newNode;
				newNode->arrNode[(int)NODE_TYPE::PARENT] = pNode;
				break;
			}
			else {
				pNode = pNode->arrNode[(int)node_type];
			}
		}
	}

	iCount++;
}
//
//template<typename T1, typename T2>
//inline tBSTNode<T1, T2>* CBST<T1, T2>::GetInOrderSuccessor(tBSTNode<T1, T2>* pNode)
//{
//	tBSTNode<T1, T2>* pSuccessor = nullptr;
//	// 1. 오른쪽 자식이 있을 경우, 오른쪽으로 간 후 왼쪽 자식 없을때까지
//	if (pNode->arrNode[(int)NODE_TYPE::RCHILD] != nullptr) {
//		pSuccessor = pNode->arrNode[(int)NODE_TYPE::RCHILD];
//		while (pSuccessor->arrNode[(int)NODE_TYPE::LCHILD]) {
//			pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::LCHILD];
//		}
//	}
//
//	// 2. 자신이 왼쪽자식일때까지 위 부모노드로 계속 올라감
//	else {
//		if (pNode->arrNode[(int)NODE_TYPE::PARENT] == nullptr) return nullptr;
//
//		while (pSuccessor->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] != pSuccessor) {
//			pNode
//		}
//	}
//
//	return pSuccessor;
//}

template<typename T1, typename T2>
inline tBSTNode<T1, T2>* CBST<T1, T2>::GetInOrderPredecessor(tBSTNode<T1, T2>* pNode)
{
	return nullptr;
}

template<typename T1, typename T2>
inline typename CBST<T1,T2>::iterator CBST<T1, T2>::begin()
{
	tBSTNode<T1, T2>* pNode = pRoot;

	while (pNode->arrNode[(int)NODE_TYPE::LCHILD]) { // 왼쪽 자식이 있으면
		pNode = pNode->arrNode[(int)NODE_TYPE::LCHILD];
	}

	return iterator(this, pNode);
}

template<typename T1, typename T2>
inline typename CBST<T1, T2>::iterator CBST<T1, T2>::end()
{
	return iterator(this, nullptr);
}

template<typename T1, typename T2>
inline typename CBST<T1, T2>::iterator CBST<T1, T2>::find(const T1& key)
{
	tBSTNode<T1, T2>* pNode = pRoot;
	NODE_TYPE node_type = NODE_TYPE::END;

	while (true) {
		if (pNode->_pair.first < key) {
			node_type = NODE_TYPE::RCHILD;
		}
		else if (pNode->_pair.first > key) {
			node_type = NODE_TYPE::LCHILD;
		}
		else break; //iterator(this, pNode); Find! 

		if (pNode->arrNode[(int)node_type] == nullptr) {
			pNode = nullptr;  
			break; //iterator(this, nullptr); Find Fail..
		}
		else {
			pNode = pNode->arrNode[(int)node_type]; // Node Update
		}
	}

	return iterator(this, pNode);
}

template<typename T1, typename T2>
inline typename CBST<T1,T2>::iterator CBST<T1, T2>::erase(const iterator& _iter)
{
	if (_iter.pBST != this) std::cout<<"다른 트리에 접근하였습니다.";

	if (_iter.pNode->isLeaf()) { // 자식이 없을 경우 바로 삭제
		if (_iter.pNode == pRoot) { // 자식이 없는 루트노드일 경우
			delete _iter.pNode;
			pRoot = nullptr;
		}
		else {
			// 부모노드의 곧 삭제되는 자식노드 주소를 null로 설정
			if (_iter.pNode->isLeftChild()) // 만약 왼쪽 자식이라면
				_iter.pNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] = nullptr;
			else
				_iter.pNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::RCHILD] = nullptr;

			delete _iter.pNode;
		}
	}

	else if (_iter.pNode->isFull()) {// 자식이 두개인 노드 삭제

	}

	else { // 자식이 한개인 경우

	}
	--iCount; // 데이터 개수 줄이기

	return iterator();
}

// ============================================ 싱글톤
// 객체의 생성을 1개로 제한, 어디서든 쉽게 접근

// 지역변수
// 전역변수
// 정적변수 (데이터 영역)
// -> 함수/파일/클래스 내에서 선언가능
// -> 클래스 내에서 선언된 정적변수 : 정적 멤버 변수
class CCore {
private:
	//static int iStaic; // 정적멤버 변수 (데이터 영역에 1개만 존재)

public:
	static CCore* Func() { // 정적멤버 함수, 객체없이 호출 가능
		//iStaic = 1; // 정적멤버 변수만 접근가능 (데이터에 1개만 있으므로)
		static CCore instance;
		return &instance;
	}

private:
	CCore();
	~CCore();
};

//int CCore::iStaic = 1; // 데이터 영역에 올리기 위해 초기화 진행

// ============================= 추상 클래스

class ACMy { // 추상 클래스
protected:
	ACMy() { std::cout << "ACMy 생성자\n"; }
	// 순수 가상함수 (몸체 구현 x)
	virtual void SetNum(const int n) = 0;
	virtual int GetNum() const = 0;
};
class ACParent {
private:
	int p;
protected:
	ACParent() { std::cout << "ACParent 생성자\n"; }
	virtual void Print() { std::cout << "ACParent\n"; }
};

class CMyChild : public ACParent, ACMy {
private:
	int i =0;
public:
	CMyChild() { std::cout << "CMyChild 생성자\n"; }
	void Print() { std::cout << "CMyChild\n"; }
	void SetNum(const int n) {
		i = n;
	}
	int GetNum() const {
		return i;
	}
};
class CMyChild2 : public ACMy {
private:
	int i =0;
public:
	void SetNum(const int n) {
		i = n;
	}
	int GetNum() const {
		return i;
	}
};


class Vehicle {
	//...
};
class LandVehicle {
	//...
protected:
	int wheel_count=0;
	virtual int GetWheelCount() const = 0;
};
class FlyVehicle {
	//...
};
class GasPoweredVehicle {
	//...
protected:
	int MAX_GAS=0;
};

class GasPoweredLandVehicle : public LandVehicle, GasPoweredVehicle {
	//...
public:
	GasPoweredLandVehicle() { wheel_count = 4; MAX_GAS = 100; };
	int GetWheelCount() const{ return wheel_count; }
};



// ======================= 스마트 포인터

class SPtr {
public:
	SPtr() { std::cout << "생성자\n"; }
	~SPtr() { std::cout << "소멸자\n"; }
	int GetNum() const { return n; }
private:
	int n = 100;
};