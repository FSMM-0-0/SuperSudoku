#ifndef __SOLUTION_H__
#define __SOLUTION_H__

#define SIZE 10

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
	int puzzleboard[SIZE][SIZE];  //数独求解盘
	int column[SIZE], row[SIZE], sub[SIZE]; //判断合法
	int empty_num;  //剩余空的数量 
	class Node {  //空格位置
	private:
	public:
		int r, c, k; //空格位置的行、列、宫
		int maybe[SIZE]; //空格位置可以填的数
		int maybe_num;  //空格位置可以填的数的数量
		Node(int _r, int _c, int _k, int _maybe_num = 0) : r(_r), c(_c), k(_k), maybe_num(_maybe_num){}
		Node() : r(0), c(0), k(0), maybe_num(0){}
	};
	Queue<Node> que;  //求解显性+隐性唯一解的空格队列

public:
	void InitBoard(int row, char line[]); //board赋值
	void Init(); 
	void Output(); //输出到文件
	bool Solution(); //数独求解 1.唯一解填充 2.dfs可行解
	bool dfs(int tmp, Node node[]); //dfs每个空格可以填的数
};


#endif // !__SOLUTION_H__

