#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<conio.h>
#include<Windows.h>
#include<vector>
#include<fstream>
using namespace std;

//�ܼ� ������ Ư�� ��ġ�� Ŀ���� �̵���Ű�� �Լ�
void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//keyboard �Է�
int GetKeyDown() {
	if (_kbnhit() != 0) { //�Է��� ������
		return -getch(); //�Էµ� �� ��ȯ
	}
	return 0;
}

//�ܼ� ����
void SetConsoleView() {
	system("mode con:cols=50 lines=20"); //ȭ�� ũ��
	system("title [HangManGame] by. Leekyoeun"); //���� �̸�
}

//����ȭ�� draw
void DrawReadyGame() {
	system("cls");
	gotoxy(5, 2);
	cout << "============================";
	gotoxy(5, 3);
	cout << "============================";
	gotoxy(5, 4);
	cout << "=============================";
	gotoxy(6, 6);
	cout << "�����Ϸ��� 's'�� �����ּ���";
	gotoxy(6, 7);
	cout << "�����Ϸ��� 'q'�� �����ּ���";
	gotoxy(9, 14);
	cout << "by. Leekyoeun" << endl;
}

//����ȭ�� draw
void DrawStartGame(int life, int score, vector < string>& pastWord) {
	system("cls");
	gotoxy(5, 1);
	cout << "life=" << life;
	gotoxy(5, 2);
	cout << "past=";
	for (int i = 0; i < static_cast<int>(pastWord.size()); ++i) {
		cout << pastWord[i] << " ";
	}

	gotoxy(5, 12);
	cout << "input =";
	gotoxy(13, 14);
	cout << "����ȭ�� 'qq'" << endl;
}

//������ �����ϴ� �Լ�
void SetDictionary(vector < string>& strArr) {

	static const int INIT_NUM = 4;
	static const string str[INIT_NUM] = { "apple","banana","code","program" };
	ifstream readFromFile("words.txt"); //words.txt ������ �б� �������� ����
	if (!readFromFile.is_open()) { //is_open�� ���� �ʴ´ٴ� ���� ������ �������� �ʴ´ٴ� ��
		ofstream writeFileToFile("words.txt");//���� �������� words.txt ������ ����
		for (int i = 0; i < INIT_NUM; ++i) { //���� �ܾ���� format�� �°� words.txt ���Ͽ� �Է�
			string tmp = str[i];
			if (i != INIT_NUM - 1){
				tmp+="\n";
			}
			writeFileToFile.write(tmp.c_str(), tmp.size()); //���Ͽ� ���� �Լ�
			strArr.push_back(str[i]); //�ܾ��忡 �ܾ �ִ´�.
		}
		writeFileToFile.close(); //���� �������� �ݱ�
		return;
	}
	//����� �Դٴ� ���� �б� �������� ���Ͽ����� �Ǿ��ִٴ� ��
	while (!readFromFile.eof()) { //���� ������
		string tmp;
		getline(readFromFile, tmp); //���پ� �о
		strArr.push_back(tmp); //�ܾ��忡 �ܾ� �ֱ�
	}
	readFromFile.close(); //�б� �������� �ݱ�
	return;
}

//����ȭ�� ���
bool ReadGame() {
	DrawReadyGame(); //����ȭ�� �׸���
	while (true) {
		int key = GetKeyDown();//Ű�� ������
		if (key == 's' || key == 'S') { //s=start
			return true;
		}
		else if (key == 'q' || key == 'Q') { //q�� ��
			break;
		}
	}
	return false;
}

//���� ���� �Լ�
void STartGame() {
	int score = 0;
	vector<string>pastWord; //�Է��� ���ܾ� ����
	vector<string> strArr; //���� �ܾ���
	SetDictionary(strArr); //���Ϸκ��� �о��

	while (true) { //�ϳ��� ź�� ǥ���ϴ� ����

		//1 play
		int num = 0;
		srand((unsigned int)time(NULL)); //���� �Լ�
		num = rand() % static_cast<int>(strArr.size()); //�ܾ��� ���� ������ �ܾ� ����

		string strQuestion;
		const string strOriginal = strArr[num]; //�ܾ �´��� ����Ȯ�ο����� ����
		const int originLen = static_cast<int>(strOriginal.length());

		//init
		for (int i = 0; i < originLen; ++i) {
			strQuestion += "_"; //���� ���̸�ŭ ����
		}
		int life = originLen + 2; //������� ���� �ܾ� ����+2

		//1 question
		while (true) { //�ϳ��� �ܾ ���ߴ� ����
			DrawStartGame(life, score, pastWord); 

		}
	}
}