#include<graphics.h>
#include<malloc.h>
#include<windows.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<queue>
#include<iostream>

using std::queue;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

//����
#define LW 40
#define LH 40 
//�ٶ�
#define SLEEPTIME 50

typedef struct snake {
	int xx;
	int yy;
	int h_xx;
	int h_yy;
	struct snake* last;
	struct snake* next;
} Snake;


Snake* head;
Snake* end;
char key = 'd';
char key_temp;
int foodX, foodY;



//void bfs(queue<int*> que, int map[31][31]);

//�����ߵ�����
void createSnakeList() {
	head = (Snake*)malloc(sizeof(Snake));
	end = (Snake*)malloc(sizeof(Snake));
	head->last = NULL;
	head->next = end;
	end->last = head;
	end->next = NULL;
}

//������ͷ
void createSnakeHead(Snake* head, Snake* end) {
	Snake* body1;
	body1 = (Snake*)malloc(sizeof(Snake));
	head->next = body1;
	end->last = body1;
	body1->last = head;
	body1->next = end;
	body1->xx = LW / 2;
	body1->h_xx = LW / 2;
	body1->yy = LH / 2;
	body1->h_yy = LH / 2;
}


//���ڻ�����
void drawSnakeList(Snake* head, Snake* end) {
	Snake* p;
	p = head->next;
	setfillcolor(RGB(205, 38, 38));
	while (p != end) {
		fillrectangle(20 * (p->xx - 1), 20 * (p->yy - 1), 20 * p->xx, 20 * p->yy);
		//fillcircle((p->xx * 20) - 10, (p->yy * 20) - 10, 10); //x,y,r 
		p = p->next;
		setfillcolor(RGB(56, 138, 70));
	}
}

//�����ߵĻ�ͼ����Ҫ���������߻�ͼȻ�󴴽����߻�ͼ
void hideSnakeList(Snake* head, Snake* end) {
	Snake* p;
	p = head->next;
	setfillcolor(RGB(132, 112, 255));
	while (p != end) {
		fillrectangle(20 * (p->xx - 1), 20 * (p->yy - 1), 20 * p->xx, 20 * p->yy);
		//fillcircle(( * 20) - 10, (p->yy * 20) - 10, 10);
		p = p->next;
	}
}

//�����ߵĿ����ƶ�
void snakeMove(Snake* head, Snake* end, bool VR) {
	Snake* p, * q;
	p = head->next;
	q = end->last;
	while (q->last != head) {
		if (VR) {
			q->xx = q->last->xx;
			q->yy = q->last->yy;
		}
		else {
			q->h_xx = q->last->h_xx;
			q->h_yy = q->last->h_yy;
		}

		q = q->last;
	}
	if (key == 'd') {
		if (VR)
			p->xx++;
		else
			p->h_xx++;
	}
	else if (key == 'a')
	{
		if (VR)
			p->xx--;
		else
			p->h_xx--;
	}
	else if (key == 'w') {
		if (VR)
			p->yy--;
		else
			p->h_yy--;
	}
	else if (key == 's') {
		if (VR)
			p->yy++;
		else
			p->h_yy++;
	}

}

//���ڼ������ʳ���Ƿ��ص�
int checkSnakeAndFood(Snake* head, Snake* end) {
	Snake* p;
	p = head->next;
	while (p != end) {
		if (foodX == p->xx && foodY == p->yy)
			return 1;
		p = p->next;
	}
	return 0;
}

//����ʳ��
void drawFood() {
	setfillcolor(RGB(238, 238, 0));
	fillrectangle(20 * (foodX - 1), 20 * (foodY - 1), 20 * foodX, 20 * foodY);
	//fillcircle((foodX * 20) - 10, (foodY * 20) - 10, 10);
}
//����ʳ�����ͨ�������������
void createFood(Snake* head, Snake* end) {

	foodX = rand() % LW + 1;
	//foodX = 30;
	foodY = rand() % LH + 1;
	//foodY = 29.5;
	if (checkSnakeAndFood(head, end)) {
		return createFood(head, end);
	}
	drawFood();
}

//����Ƿ�Ե�ʳ��
int checkSnakeEatFood(Snake* head, Snake* end, bool VR) {
	Snake* p;
	p = head->next;
	if (VR) {
		if (p->xx == foodX && p->yy == foodY)
			return 1;
	}
	else {
		if (p->h_xx == foodX && p->h_yy == foodY)
			return 1;
	}

	return 0;
}



int resData[LH + 1][LW + 1] = { 0 };
//0Ϊײǽ
int checkSnakeAndWall(Snake* head, Snake* end) {
	Snake* p;
	p = head->next;
	if (p->xx <= 0 || p->xx > LW || p->yy <= 0 || p->yy > LH) {
		for (int y = 0; y <= LH; ++y) {
			for (int x = 0; x <= LW; ++x) {
				cout << resData[y][x] << " ";
			}
			cout << endl;
		}
		cout << head->next->xx << " " << head->next->yy << "ײǽ" << endl;
		return 0;
	}
	return 1;
}

//���ڼ�ⰴ�µ���ʲô����Ȼ����м��̿����ַ��ı仯
void checkKey(char key_t) {
	if (key_t == '\0')
		return;
	if (key_t == 'a' && key != 'd') {
		key = key_t;
	}
	else if (key_t == 'd' && key != 'a') {
		key = key_t;
	}
	else if (key_t == 'w' && key != 's')
	{
		key = key_t;
	}
	else if (key_t == 's' && key != 'w') {
		key = key_t;
	}
}

//���ڳ�ʼ��������
void initVitualSnake() {

	Snake* p = head->next;
	while (p != end) {
		p->h_xx = p->xx;
		p->h_yy = p->yy;
		p = p->next;
	}

}


//�����������ʵ��AI�㷨
char bfs(int startX, int startY, int endX, int endY, bool VR) {

	queue<int*> que;
	int map[LH + 1][LW + 1] = { 0 };




	Snake* p = head->next;

	while (p != end) {
		//cout << p->h_xx << "     " << p->h_yy << endl;
		if (VR)
			map[p->yy][p->xx] = -1;
		else
			map[p->h_yy][p->h_xx] = -1;
		p = p->next;
	}


	//��ʳ��λ�ñ�עΪ1����������뵽������
	que.push(new int[2] {startX, startY});
	//cout << foodX << "   " << foodY << endl;
	map[startY][startX] = 1;



	//����BFS�㷨Ѱ��·��
	while (true) {

		bool sw = false;

		if (que.size() == 0)
			break;

		int front_x = que.front()[0];
		int front_y = que.front()[1];

		int next[4][2] = {
			{front_x,front_y - 1},
			{front_x,front_y + 1},
			{front_x - 1,front_y},
			{front_x + 1,front_y}
		};

		for (int i = 0; i < 4; ++i) {

			if (next[i][0] <= 0 || next[i][0] > LW || next[i][1] <= 0 || next[i][1] > LH)
				continue;

			if (next[i][1] == startX && next[i][0] == startY)
				continue;

			if (next[i][1] == endY && next[i][0] == endX) {
				map[endY][endX] = map[front_y][front_x] + 1;
				sw = true;
				//if (resfoodx != foodX && resfoody != foodY) {

					//printf("\n\n\n");
				//}
				break;
				//continue;
			}

			if (map[next[i][1]][next[i][0]] == -1)
				continue;

			if (map[next[i][1]][next[i][0]] != 0)
				continue;

			map[next[i][1]][next[i][0]] = map[front_y][front_x] + 1;
			que.push(new int[2] {next[i][0], next[i][1]});


		}
		delete que.front();
		que.pop();
		if (sw)
			break;
	}

	for (int y = 0; y <= LH; ++y) {
		for (int x = 0; x <= LW; ++x) {
			resData[y][x] = map[y][x];
		}
		//cout << endl;
	}

	//תΪ��������ķ����
	int next[4][2] = {
			{endX,endY - 1},
			{endX,endY + 1},
			{endX - 1,endY},
			{endX + 1,endY}
	};
	for (int i = 0; i < 4; ++i) {
		if (map[endY][endX] != map[next[i][1]][next[i][0]] + 1)
			continue;
		if (next[i][0] <= 0 || next[i][0] > LW || next[i][1] <= 0 || next[i][1] > LH)
			continue;

		if (i == 0) {
			return 'w';
		}
		if (i == 1) {
			return 's';
		}
		if (i == 2) {
			return 'a';
		}
		if (i == 3) {
			return 'd';
		}

	}
	return '\0';

}

//������̽·
bool pathFinder() {
	initVitualSnake();

	char resDataKey = key;
	char resDataKey_temp = key_temp;
	while (!checkSnakeEatFood(head, end, false)) {


		char foodSearch = bfs(foodX, foodY, head->next->h_xx, head->next->h_yy, false);
		//return foodSearch;
		if (foodSearch == '\0')
			break;
		key_temp = foodSearch;
		checkKey(key_temp);
		snakeMove(head, end, false);
	}
	char snakeEndSearch = bfs(end->last->h_xx, end->last->h_yy, head->next->h_xx, head->next->h_yy, false);
	if (snakeEndSearch != '\0') {
		key = resDataKey;
		key_temp = resDataKey_temp;
		return true;
	}


	return false;
}

//�����
char randMove(bool VR) {
	vector<int> vec;

	int map[LH + 1][LW + 1];

	//��ʼ����ͼ
	for (int i = 0; i < LH + 1; ++i) {
		for (int x = 0; x < LW + 1; ++x) {
			map[i][x] = 0;
		}
	}

	Snake* p = head->next;

	while (p != end) {
		//cout << p->h_xx << "     " << p->h_yy << endl;
		if (VR)
			map[p->yy][p->xx] = -1;
		else
			map[p->h_yy][p->h_xx] = -1;
		p = p->next;
	}


	int head_x = head->next->xx;
	int head_y = head->next->yy;

	int next[4][2] = {
		{head_x,head_y - 1},
		{head_x,head_y + 1},
		{head_x - 1,head_y},
		{head_x + 1,head_y}
	};
	for (int i = 0; i < 4; ++i) {
		if (next[i][0] <= 0 || next[i][0] > LW || next[i][1] <= 0 || next[i][1] > LH)
			continue;

		if (map[next[i][1]][next[i][0]] != 0)
			continue;

		vec.push_back(i);
	}

	if (vec.size()) {
		int randNum = rand() % vec.size();
		if (vec[randNum] == 0)
			return 'w';
		if (vec[randNum] == 1)
			return 's';
		if (vec[randNum] == 2)
			return 'a';
		if (vec[randNum] == 3)
			return 'd';

	}

	return '\0';
}

//AI��������
char AIKey() {

	//ʳ��׷��
	char resKey1 = bfs(foodX, foodY, head->next->xx, head->next->yy, true);
	//β��׷��
	char resKey2 = bfs(end->last->xx, end->last->yy, head->next->xx, head->next->yy, true);
	//���ѡ��
	char resKey3 = randMove(true);

	if (resKey1 != '\0') {

		if (pathFinder()) {
			cout << "����������" << resKey1 << endl;
			return resKey1;
		}
		else {

			if (resKey2 != '\0') {
				cout << "�����߲��ɴʹ��׷β������" << resKey2 << endl;
				return resKey2;
			}
			else {
				cout << "�����߲��ɴ׷β���ɴ�ʹ������������" << resKey1 << endl;
				return resKey1;
			}

		}

	}
	else if (resKey2 != '\0') {
		cout << "׷β������" << resKey2 << endl;
		return resKey2;
	}
	else {

		cout << "���������" << resKey3 << endl;
		return resKey3;
	}
	if (resKey1 == '\0')
		cout << "��·��" << endl;
	return  '\0';
}



void snakeAddBody(Snake* head, Snake* end) {
	Snake* body, * p, * q;
	body = (Snake*)malloc(sizeof(Snake));
	p = end->last;
	body->xx = foodX;
	body->yy = foodY;
	p->next = body;
	end->last = body;
	body->last = p;
	body->next = end;
}

//1Ϊ����
int checkSnakeAndBody(Snake* head, Snake* end) {
	Snake* p, * q;
	p = head->next;
	q = end->last;
	while (q->last != head) {
		if (p->xx == q->xx && p->yy == q->yy) {
			for (int y = 0; y <= LH; ++y) {
				for (int x = 0; x <= LW; ++x) {
					cout << resData[y][x] << " ";
				}
				cout << endl;
			}
			cout << head->next->xx << " " << head->next->yy << "��������" << endl;
			return 1;
		}
		q = q->last;
	}
	return 0;
}

int game() {
	initgraph(LW * 20, LH * 20, SHOWCONSOLE);
	setbkcolor(RGB(132, 112, 255));
	setlinecolor(RGB(132, 112, 255));
	settextstyle(42, 20, _T("����"));
	cleardevice();
	createSnakeList();
	createSnakeHead(head, end);
	drawSnakeList(head, end);
	createFood(head, end);
	drawFood();
	while (true)
	{
		Sleep(SLEEPTIME);

		if (_kbhit()) {
			key_temp = _getch();
		}
		checkKey(key_temp);
		hideSnakeList(head, end);
		snakeMove(head, end, true);
		if (checkSnakeAndWall(head, end) == 0) {
			outtextxy(220, 280, _T("��Ϸ������"));
			system("pause");
			return 0;
		}
		if (checkSnakeAndBody(head, end) == 1) {
			outtextxy(220, 280, _T("��Ϸ������"));
			system("pause");
			return 0;
		}
		if (checkSnakeEatFood(head, end, true) == 1) {
			snakeAddBody(head, end);
		}
		drawSnakeList(head, end);


	}
	return 0;
}

//�����AIģʽ
void gameAI() {
	initgraph(LW * 20, LH * 20, SHOWCONSOLE);
	setbkcolor(RGB(132, 112, 255));
	setlinecolor(RGB(132, 112, 255));
	settextstyle(42, 20, _T("����"));
	cleardevice();
	createSnakeList();
	createSnakeHead(head, end);
	drawSnakeList(head, end);
	createFood(head, end);
	drawFood();
	while (true)
	{
		Sleep(SLEEPTIME);


		//AI��������
		key_temp = AIKey();
		checkKey(key_temp);
		hideSnakeList(head, end);
		snakeMove(head, end, true);

		if (checkSnakeAndWall(head, end) == 0) {
			drawSnakeList(head, end);
			outtextxy(220, 280, _T("��Ϸ������"));
			system("pause");
			return;
		}
		if (checkSnakeAndBody(head, end) == 1) {
			drawSnakeList(head, end);
			outtextxy(220, 280, _T("��Ϸ������"));
			system("pause");
			return;
		}
		if (checkSnakeEatFood(head, end, true) == 1) {
			snakeAddBody(head, end);
			createFood(head, end);
		}

		drawSnakeList(head, end);


	}
}

//�˵�
void menu() {
	initgraph(200, 300, SHOWCONSOLE);
	setbkcolor(RGB(45, 45, 48));
	cleardevice();
	setlinecolor(WHITE);
	settextcolor(WHITE);
	settextstyle(42, 20, _T("����"));
	outtextxy(40, 40, _T("̰����"));
	outtextxy(60, 100, _T("��ʼ"));
	outtextxy(40, 170, _T("AIѰ·"));

	//����
	rectangle(55, 95, 145, 145);
	rectangle(30, 160, 165, 220);


	MOUSEMSG m;
	while (true) {
		m = GetMouseMsg();
		if (m.x > 55 && m.y > 95 && m.x < 145 && m.y < 145) {
			settextcolor(RED);
			setlinecolor(RED);
			outtextxy(60, 100, _T("��ʼ"));

			//����
			rectangle(55, 95, 145, 145);

			if (m.uMsg == WM_LBUTTONDOWN) {
				game();
			}

		}
		else {
			setlinecolor(WHITE);
			settextcolor(WHITE);
			outtextxy(40, 40, _T("̰����"));
			outtextxy(60, 100, _T("��ʼ"));
			//����
			rectangle(55, 95, 145, 145);
		}

		if (m.x > 30 && m.y > 160 && m.x < 165 && m.y < 220) {
			settextcolor(RED);
			setlinecolor(RED);
			outtextxy(40, 170, _T("AIѰ·"));
			//����
			rectangle(30, 220, 165, 160);

			if (m.uMsg == WM_LBUTTONDOWN) {
				gameAI();
			}
		}
		else {
			setlinecolor(WHITE);
			settextcolor(WHITE);
			outtextxy(40, 170, _T("AIѰ·"));
			//����
			rectangle(30, 220, 165, 160);
		}
	}
}


int main() {
	srand((unsigned)(time(NULL)));
	menu();

	//game();
	return 0;
}