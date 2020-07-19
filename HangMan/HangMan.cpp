#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<conio.h>
#include<Windows.h>
#include<vector>
#include<fstream>
using namespace std;

//콘솔 내부의 특정 위치로 커서를 이동시키는 함수
void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//keyboard 입력
int GetKeyDown() {
	if (_kbhit() != 0) { //입력이 들어오면
		return _getch(); //입력된 값 반환
	}
	return 0;
}

//콘솔 세팅
void SetConsoleView() {
	system("mode con:cols=50 lines=20"); //화면 크기
	system("title [HangManGame] by. Leekyoeun"); //게임 이름
}

//시작화면 draw
void DrawReadyGame() {
	system("cls");
	gotoxy(5, 2);
	cout << "============================";
	gotoxy(5, 3);
	cout << "============================";
	gotoxy(5, 4);
	cout << "=============================";
	gotoxy(6, 6);
	cout << "시작하려면 's'를 눌러주세요";
	gotoxy(6, 7);
	cout << "종료하려면 'q'를 눌러주세요";
	gotoxy(9, 14);
	cout << "by. Leekyoeun" << endl;
}

//게임화면 draw
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
	cout << "메인화면 'qq'" << endl;
}

//사전을 세팅하는 함수
void SetDictionary(vector < string>& strArr) {

	static const int INIT_NUM = 4;
	static const string str[INIT_NUM] = { "apple","banana","code","program" };
	ifstream readFromFile("words.txt"); //words.txt 파일을 읽기 전용으로 오픈
	if (!readFromFile.is_open()) { //is_open이 되지 않는다는 것은 파일이 존재하지 않는다는 뜻
		ofstream writeFileToFile("words.txt");//쓰기 전용으로 words.txt 파일을 오픈
		for (int i = 0; i < INIT_NUM; ++i) { //샘플 단언들을 format에 맞게 words.txt 파일에 입력
			string tmp = str[i];
			if (i != INIT_NUM - 1){
				tmp+="\n";
			}
			writeFileToFile.write(tmp.c_str(), tmp.size()); //파일에 쓰는 함수
			strArr.push_back(str[i]); //단어장에 단어를 넣는다.
		}
		writeFileToFile.close(); //쓰기 전용파일 닫기
		return;
	}
	//여기로 왔다는 것은 읽기 전용으로 파일오픈이 되어있다는 뜻
	while (!readFromFile.eof()) { //파일 끝까지
		string tmp;
		getline(readFromFile, tmp); //한줄씩 읽어서
		strArr.push_back(tmp); //단어장에 단어 넣기
	}
	readFromFile.close(); //읽기 전용파일 닫기
	return;
}

//시작화면 기능
bool ReayGame() {
	DrawReadyGame(); //시작화면 그리기
	while (true) {
		int key = GetKeyDown();//키가 들어오면
		if (key == 's' || key == 'S') { //s=start
			return true;
		}
		else if (key == 'q' || key == 'Q') { //q는 끝
			break;
		}
	}
	return false;
}

//게임 시작 함수
void StartGame() {
	int score = 0;
	vector<string>pastWord; //입력한 영단어 저장
	vector<string> strArr; //맞출 단어장
	SetDictionary(strArr); //파일로부터 읽어옴

	while (true) { //하나의 탄을 표현하는 루프

		//1 play
		int num = 0;
		srand((unsigned int)time(NULL)); //랜덤 함수
		num = rand() % static_cast<int>(strArr.size()); //단어장 내에 랜덤한 단어 선택

		string strQuestion;
		const string strOriginal = strArr[num]; //단어가 맞는지 정답확인용으로 저장
		const int originLen = static_cast<int>(strOriginal.length());

		//init
		for (int i = 0; i < originLen; ++i) {
			strQuestion += "_"; //정답 길이만큼 세팅
		}
		int life = originLen + 2; //생명력은 정답 단어 길이+2

		//1 question
		while (true) { //하나의 단어를 맞추는 루프
			DrawStartGame(life, score, pastWord);  //사용단어, 생명력, 점수표기

			//draw question
			gotoxy(5, 5);
			for (int i = 0; i < originLen; ++i) {
				cout << strQuestion[i] << " ";
			}
			cout << endl;

			//input
			gotoxy(9, 12);
			string strInput;
			cin >> strInput;
			if (strInput == "qq") {
				return;
			}
			pastWord.push_back(strInput); //한번 입력한 단어는 pastWord에서 표기

			if (strInput.length() == 1){ //입력받은 스트림의 길이가 1인갱우
				//alphabet
				for (int i = 0; i < originLen; ++i) {
					if (strOriginal[i] == strInput[0]) { //오리지널 단어에 입력한 알파벳이 있는 경우
						strQuestion[i] = strInput[0]; //해당 위치의 "_"를 알파벳이 있는 경우

					}
				}
			}
			else if (strInput.length() > 1) { //입력받은 스트림의 길이가 1보다 큰 경우

				//word
				if (strOriginal == strInput) {
					//score up
					score += 5;
					pastWord.clear();
					break; //하나의 단어를 맞추는 루프를 나가게 되고 다음 턴으로 넘어가게 된다
				}
			}
			//틀리거나, 맞거나 어쨌든 입력이 되면 라이프가 무조건 1개씩 깎입니다.
			life -= 1;
			if (life < 0) {
				score -= 5;
				if (score < 0) {
					score = 0;
				}
				pastWord.clear();
				break;
			}
		}
	}
}

//main 함수
int main(void) {
	SetConsoleView();
	bool isStart = false;
	while (true) {
		isStart = ReayGame();
		if (isStart) {
			StartGame();
		}
		else {
			break;
		}
	}
	return 0;
}