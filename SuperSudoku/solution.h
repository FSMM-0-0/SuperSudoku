#ifndef __SOLUTION_H__
#define __SOLUTION_H__

#define SIZE 10
#define MAXN 1000000

extern char out[MAXN];
extern int out_cnt;

template<class T>
class Queue
{
protected:
	T *element;
	int head, rear;
	int maxSize;
public:
	Queue(int sz = 65) {
		head = rear = 0;
		maxSize = sz;
		element = new T[maxSize];
	}
	~Queue() {
		delete[] element;
	}
	void push(const T& x) {
		element[rear] = x;
		rear = (rear + 1) % maxSize;
	}
	void pop() {
		head = (head + 1) % maxSize;   
	}
	T front() {
		return element[head];
	}
	void makeEmpty() {
		head = rear = 0;
	}
	bool isEmpty() const {
		return (rear == head) ? true : false;
	}
};

class Puzzle
{
private:
	char puzzleboard[SIZE][SIZE];  //���������
	int column[SIZE], row[SIZE], sub[SIZE]; //�жϺϷ�
	int empty_num;  //ʣ��յ����� 
	char *read; //�����뻺��
	int read_cnt;
	class Node {  //�ո�λ��
	private:
	public:
		int r, c, k; //�ո�λ�õ��С��С���
		int maybe[SIZE]; //�ո�λ�ÿ��������
		int maybe_num;  //�ո�λ�ÿ��������������
		Node(int _r, int _c, int _k, int _maybe_num = 0) : r(_r), c(_c), k(_k), maybe_num(_maybe_num){}
		Node() : r(0), c(0), k(0), maybe_num(0){}
	};
	Queue<Node> que;  //�������+����Ψһ��Ŀո����
	void Solution(); //������� 1.Ψһ����� 2.dfs���н�
	void Init();  //��ÿһ��������ȡǰ���г�ʼ��
	bool dfs(int tmp, Node node[]); //dfsÿ���ո���������
	void GetBoard(); //��������������뻺��

public:
	void InitBoard(); //board��ֵ
	void Output(); //������ļ�
	void Read(char *path); //��������ļ�
	Puzzle() : read_cnt(0) {}
};


#endif // !__SOLUTION_H__

