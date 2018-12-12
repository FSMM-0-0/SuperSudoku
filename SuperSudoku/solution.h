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
	char puzzleboard[SIZE][SIZE];  //数独求解盘
	int column[SIZE], row[SIZE], sub[SIZE]; //判断合法
	int empty_num;  //剩余空的数量 
	char *read; //求解读入缓存
	int read_cnt;
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
	void Solution(); //数独求解 1.唯一解填充 2.dfs可行解
	void Init();  //对每一盘数独读取前进行初始化
	bool dfs(int tmp, Node node[]); //dfs每个空格可以填的数
	void GetBoard(); //将求解后的数独输入缓存

public:
	void InitBoard(); //board赋值
	void Output(); //输出到文件
	void Read(char *path); //读入求解文件
	Puzzle() : read_cnt(0) {}
};


#endif // !__SOLUTION_H__

