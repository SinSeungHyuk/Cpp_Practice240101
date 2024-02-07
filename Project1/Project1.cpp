// Project1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"


using namespace std;

#define HUNGRY 1 // 가독성+유지보수

/// <summary> 자료형 Byte 크기
/// char (1) , short(2) , int(4), long(4), long long(8)
/// float(4) , double(8)

class Recursive { // 재귀함수
public:
    int Factorial(int n) {
        if (n == 1) return 1;
        return Factorial(n - 1) * n;
    }

    int Fibonacci(int n) {
        if (n == 1 || n == 2) return 1;
        
        return Fibonacci(n - 2) + Fibonacci(n - 1);
    }
};

typedef struct _mySt {
    int a;
    float b;
}mySt;

typedef struct BigSt {
    mySt m;
    char c;
}BigSt;


// 정적 변수
static int n_Static = 1;
// 전역 변수
int n_Global = 2;

int Test() {
    static int i_Static; // Data 영역 
    int num; // Stack 영역

    return 0;
}

int Test(const int* t) {
    t += 2;
    return *t;
}

int main()
{
    int iStatus = HUNGRY;
    Recursive rec;

    //mySt m; // 8바이트. 왜냐면 int형 하나,float형 하나 있으니깐 (당연한사실)
    //m.a = 5;
    //BigSt b{};
    //int num = b.m.a;

    //cout << Add(1,2) << endl;
    //cout << rec.Factorial(10) << endl;
    //cout << rec.Fibonacci(10) << endl;

    // 함수가 사용하는 메모리 영역 : 스택 (데이터,스택,힙)
    // 스택영역에 main함수가 공간을 할당받고 Add를 호출할때 Add(약 8바이트)가
    // 할당받게됨. Add 호출 이후 그 공간은 다시 비워짐
    // 정적,전역변수->데이터 / 동적할당->힙 (운영체제에서 배운 내용)


    // -----------------------------------포인터----------------
    // 포인터 변수 : 주소를 저장하는 변수
    int* pInt = nullptr;
    int i = 100;
    pInt = &i; 
    *pInt = 50; // pInt에 저장된 주소를 따라가서 값을 참조(레퍼런스)
    cout << i << endl; // 50
    
    // 주소의 단위 : Byte
    // 포인터 변수 타입 선언이 가지는 의미 : 그 타입으로만 해석
    // float f = 3.0f;를 pInt에 강제캐스팅으로 넣을 경우 float을 int로 해석하여 출력시 값이 이상하게 나옴

    // 포인터 변수의 크기 : 플랫폼의 크기에 따라 가변적. 요즘은 64비트 os->8바이트
    // 32비트에서 RAM 최대 4기가인 이유 : 한번에 처리 가능한 주소 단위가 4바이트기 때문
    int pSize = sizeof(int*); 
    cout << pSize << endl; // x64 -> 8 byte (64비트에서 8바이트)
    
    pInt += 1; // pInt는 int* 타입이므로 1을 더하면 주소를 4바이트씩 건너뛰게 된다. 
    // char* 포인터였으면 char은 1바이트이므로 1을 더할때 주소에 1바이트씩 더해진다.
    // 배열의 특징
    // 1. 메모리가 연속적으로 이어짐 / 2. 배열의 이름이 배열의 시작주소
    int arr[10] = {}; // 다 0으로 초기화
    *(arr + 1) = 10; // -> arr[1] = 10;
    cout << arr[1] << endl; // 10

    cout << endl;
    // ------------------------------------------- 포인터 문제---------------------
    short sArr[10] = { 1,2,3,4,5,6,7,8,9,10 };
    int* pI = (int*)sArr;
    int iData = *((short*)(pI + 2));
    cout << iData << endl;

    char cArr[2] = { 1,1 };
    short* pS = (short*)cArr;
    iData = *pS;
    cout << iData << endl;

    // -------------------------------- const ---------------------------
    // const -> 상수화 (바뀌지 않는 고정값)
    const int cInt = 100; // stack 영역 안에 100 으로 상수화

    // const 포인터
    int a = 0;
    int b = 1;

    const int* pConstInt = &a;
    //*pConstInt = 100; -> const type* 은 주소는 바꿀 수 있지만 역참조는 못함
    pConstInt = &b;

    // 포인터 const
    int* const pIntConst = &a;
    *pIntConst = 100;
    //pIntConst = &b; type* const 는 주소를 못바꿈
    
    // const 포인터가 사용되는 예시 ***********************************
    // void Test( const int* pI) {} , Test(&a); 
    // 데이터가 큰 파라미터의 경우 스택 영역에 복사,삭제 과정에서 큰 오버헤드 발생
    // 이를 막기위해 포인터 매개변수를 받게됨. 하지만 이는 직접 그 주소에 접근하여
    // 값을 변경할 수 있는 위험이 생김. 보호를 위해 const T*로 접근만하고 수정못하게
    //-------------------------------------------------------------------------------

    // 함수 포인터
    // void Test(int* a, int b) { } 함수를 포인터로 받고 싶을때
    // void TestCall( void(*Func)(int*,int)) , TestCall(Test(&a,b)); 
    // 해당 함수의 반환타입, *함수명, 그 함수의 파라미터를 적어주면 된다.
    //-----------------------------------------------------------------------------
    // 
    // 연결 리스트 (Linked List) 
    // Node ([값,다음주소]) - Node ([값,다음주소]) .. [값+다음주소] 노드끼리 연결
    // +) 중간에 삽입,삭제가 유용
    // -) 인덱스로 한번에 접근가능한 배열에 비해 연결된 주소를 타고가 검색이 느림

    // ==================================== 동적할당=======
    int* pMallocInt = (int*)malloc(4); // 4바이트 메모리 할당
    *pMallocInt = 1; // malloc은 메모리를 동적으로 제공만 해줌. 타입은 사용자가 지정
    free(pMallocInt); // 힙메모리 관리는 사용자가 '직접' (해제)

    // =================================== 가변 배열 =========================
    tArr tArray = {};
    InitArr(&tArray);

    for (int i = 0; i < 10; i++) PushBackArr(&tArray, i);
    for (int i = 0; i < 10; i++) cout << tArray.pInt[i] << ",";

    ReleaseArr(&tArray);

    cout << endl << endl;
    //======================================= class
    CMy c(1);
    c.SetNum(3);
    cout << c.GetNum() << endl; // 3
    CMy* pC = &c;
    pC->SetNum(5);
    cout << c.GetNum() << endl; // 5

    // 레퍼런스 변수 (T& a)
    // 포인터와 유사하지만, 원본을 참조하여 역참조 없이 원본 수정
    int refA = 10;

    int* p = &a;
    *p = 100;

    int& iRef = a; // == int* const pInt;
    iRef = 100; //레퍼런스 변수는 다른 주소가 안들어감. a의 값만 변경

    CArr<int> ca;
    ca.Reallocate(100);
    ca.PushBack(3);
    cout << ca[0] << endl;
    ca[0] = 2;
    cout << ca[0] << endl << endl;

    CLinkedList<int> cl;
    for (int i = 1; i < 10; i++) {
        cl.PushBack(i);
    }
    CLinkedList<int>::iterator clIter22 = cl.begin();
    cl.GetNode(); // 123456789
    cout << endl << endl;

    // ============ namespace
    // using namespace를 사용하면 해당 namespace의 범위를 선언하지 않아도
    // 해당 space의 기능을 사용할 수 있지만 중복되는 이름이 있을 수 있으므로
    // 네임스페이스의 의미를 상실해버릴 수 있음

    list<int> listInt;
    listInt.push_back(10);
    listInt.push_back(20);
    //============================= iterator (inner class, 내부/포함 클래스)
    list<int>::iterator iter = listInt.begin(); // 리스트 첫 '노드' 반환
    int iterData = *iter; // *는 포인터X, 연산자 오버로딩 '노드의 데이터' 반환
    ++iter; // 다음 데이터 반환
    iterData = *iter;
    cout << iterData << endl;
    // listInt.end() -> end iterator는 실제 마지막 노드가 아닌 그보다 뒷 노드

    vector<int> vec;
    vec.push_back(10);
    vector<int>::iterator iterVec = vec.begin();
    vec.push_back(20);
    vec.push_back(30);
    //cout << *iterVec << endl; 벡터가 동적할당하면서 첫 주소가 바뀜
    // iterator 연산자 : ++,-- (전위,후위), ==, !=
    // 
    // *** 생성자를 사용자가 직접 하나라도 만들면 기본 생성자는 생기지 않는다.
    // 복사 생성자 / 대입 연산자
    CMy m1(1);
    CMy m2(m1);
    CMy m3 = m1; // '=' 대입연산자 처럼 보이지만 객체가 생성됨과 동시에 
    // 복사를 하므로 컴파일러상에서는 곧바로 'm3(m1)' 으로 바꿔서 실행한다.

    //==================================== erase
    vector<int> vecInt;
    for (int i = 1; i < 5; i++) vecInt.push_back(i*10);
    for (int i = 0; i < vecInt.size(); i++) cout << vecInt[i] << ",";
    cout << endl;
    //vecInt.erase(vecInt.begin(),++(++vecInt.begin())); //vecInt[1],[2] 삭제
    vector<int>::iterator iVec = vecInt.begin() + 1; // vecInt[1]
    iVec += 1; // *iVec == vecInt[2]
    int n = 1;
    vecInt.erase(vecInt.begin(),iVec); 
    for (int i = 0; i < vecInt.size(); i++) cout << vecInt[i] << ",";

    CLinkedList<int> cll;
    cll.PushBack(200);
    cll.PushBack(300);
    CLinkedList<int>::iterator clIter = cll.begin();
    cll.insert(clIter, 100);
    cll.erase(clIter);
    CLinkedList<int>::iterator afterErase = cll.begin(); // begin 노드가 변경되었으므로 갱신
    cout << *afterErase << endl<<endl; // 100

    // ========================================== 트리 ****************
    // 그래프 vs 트리 -> 계층구조의 유무 
    // 이진트리 -> 각 노드가 자식을 2개 이하로 가진 트리 (꼭 2개x, 이하o)
    // 완전이진트리 -> 각 노드의 자식이 꼭 2개인 완전한 이진트리 (배열구현)
        //-> 힙을 구현할때 사용, 배열에서 인덱스 기준 2i+1,2i+2 가 자식노드
    // 이진 탐색 트리 (Binary Search Tree)
    // 이진탐색(Binary Search)=> [정렬된] 데이터를 반씩 줄이면서 탐색
    // 트리에 들어간 데이터 모양이 한쪽에 치우쳐져 있을 수 있음 (불균형)
    // 실질적으로는 BST 응용한 AVL트리,레드블랙트리(map) 사용

    map<string, int> mp;
    mp.insert(make_pair("c",3));
    mp.insert(make_pair("a",1));
    mp.insert(make_pair( "b",2));

    map<string,int>::iterator mpIter = mp.begin();
    cout << mpIter->second << endl; // insert 과정에서 정렬해 '2번' 출력

    mpIter = mp.find("b"); // 못찾을 경우 end() 반복자 반환
    cout << mpIter->second << endl; // '4번' 출력

    CBST<int, int> bst;
    bst.insert(makePair(3, 3));
    bst.insert(makePair(1, 1));
    bst.insert(makePair(2, 2));
    CBST<int, int>::iterator bstIter = bst.begin();
    cout << bstIter->first << endl; // 1
    bstIter = bst.find(2);
    cout << bstIter->first << endl; // 2

   
    //ACMy acmy;
    CMyChild* cmc = new CMyChild;
    cmc->Print();

    ACMy* cmc2 = new CMyChild2;
    //cmc2->SetNum(5);
    // 
    GasPoweredLandVehicle* gplv = new GasPoweredLandVehicle ;
    cout << gplv->GetWheelCount() << endl<<endl;
    //cout << cmc->GetNum() << endl;
    
    int lam1 = 5;
    int lam2 = 8;
    [=] (int n)->void{
        cout << "= 람다식\n";
        //lam1 = 10; Error! 
    }(10);
    [&](int n)->void {
        cout << "& 람다식\n";
        lam1 += n; 
        lam2 += n;
    }(10);
    cout << "lam1: " << lam1 << endl;
    cout << "lam2: " << lam2 << endl;

    int* pIntA = new int(5);
    int* pIntB = pIntA; // 주소만 받은 얕은 복사
    // ---------------------------------unique_ptr
    //unique_ptr<SPtr> pSptr(new SPtr);
    //unique_ptr<SPtr> pSptr2(new SPtr);
    //pSptr.release();
    //cout << pSptr2->GetNum() << endl;
    //------------------------------- shared_ptr
    shared_ptr<SPtr> pSptr(new SPtr);
    cout << pSptr.use_count() << endl;
    weak_ptr<SPtr> pSptr2(pSptr);
    cout << pSptr.use_count() << endl; 

    cout << "main함수 소멸\n";
}

int Add(int a, int b) {
    return a + b;
}

// ==================================== 연결리스트
void InitList(tLinkedList* pList)
{
    pList->pHeadNode = nullptr;
    pList->iCount = 0;
}

void PushBack(tLinkedList* pList, int iData)
{
    // 영구적으로 노드를 남기기 위해 malloc으로 동적으로 생성
    tNode* pNode = (tNode*)malloc(sizeof(tNode)); 

    pNode->iData = iData;
    pNode->pNextNode = nullptr; // 이 노드가 마지막이므로 다음 노드가 없음

    if (pList->pHeadNode == nullptr) {
        pList->pHeadNode = pNode; // 헤드노드가 없을때
    }
    else {
        // 마지막 노드를 찾아서 그곳에 이 노드의 주소를 넣어줌
        tNode* CurrentNode = pList->pHeadNode;
        while (CurrentNode->pNextNode) {
            // 헤더노드부터 시작해서 다음노드가 null이 될때까지
            // 넥스트노드를 이 노드로 계속 업데이트해줌
            CurrentNode->pNextNode = pNode;
        }
    }
    pList->iCount++;
}

void PushFront(tLinkedList* pList, int iData)
{
    tNode* pNode = (tNode*)malloc(sizeof(tNode));

    pNode->iData = iData;

    if (!pList->pHeadNode) {
        pList->pHeadNode = pNode;
    }
    else {
        tNode* pNext = pList->pHeadNode;
        pList->pHeadNode = pNode;
        pNode->pNextNode = pNext;
    }
    pList->iCount++;
}

void RealeaseList(tLinkedList* pList)
{
    tNode* pDeleteNode = pList->pHeadNode;

    for (int i = 0; i < pList->iCount; i++) {
        tNode* pNext = pDeleteNode->pNextNode;
        free(pDeleteNode);
        pDeleteNode = pNext;
    }
}

// ===================================== 가변배열
void InitArr(tArr* pArr)
{
    pArr->pInt = (int*)malloc(sizeof(int) * 2);
    pArr->iCount = 0;
    pArr->iMaxCount = 2;
}

void PushBackArr(tArr* pArr, int iData)
{
    if (pArr->iMaxCount <= pArr->iCount) { // 공간 확인
        Reallocate(pArr);
    }

    // pInt는 힙 영역에 생긴 배열의 시작주소다. 시작주소=배열의 첫 인덱스
    // 따라서 pInt에는 이 가변배열이 들어있고 iCount번째 인덱스가 곧 마지막 인덱스
    pArr->pInt[pArr->iCount++] = iData;
}

void Reallocate(tArr* pArr) // 배열 새로 할당 (동적)
{
    // 1.크기 늘린 새 배열 만들기 2.기존 데이터 복붙 3.기존데이터 해제 4.크기 변경
    int* pNewArr = (int*)malloc(pArr->iMaxCount * 2 * sizeof(int)); // 2배 늘리기

    for (int i = 0; i < pArr->iCount; i++) {
        pNewArr[i] = pArr->pInt[i];
    }

    free(pArr->pInt);
    pArr->pInt = pNewArr;

    pArr->iMaxCount *= 2;
}

void ReleaseArr(tArr* pArr)
{
    free(pArr->pInt);
    pArr->iCount = 0;
    pArr->iMaxCount = 0;
}

// ======================================= class
