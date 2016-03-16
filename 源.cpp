#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

class GameList {
private:
	vector<int> data;
	int rPosition = 0;
	int pick();
public:
	GameList(int l, int* a, float* c);
	int len();
	void showList();
	bool guess();
};

GameList::GameList(int l, int* a, float* c) {
	/* length: 1 + 1
	 * rule: data[n] = c0 * data[n - 2] + c1 * data[n - 1] + c2 * n + c3 * n * n
	 * begin: a0, a1
	 */
	data.push_back(a[0]);
	data.push_back(a[1]);
	for (int i = 2; i <= l; ++i) {
		int next = c[0] * data[i - 2] + c[1] * data[i - 1] + c[2] * i + c[3] * i * i;
		data.push_back(next);
	}

	//showList();
}

void GameList::showList() {
	cout << len() << endl;
	for (int i = 1; i <= len(); ++i) {
		cout << data[i] << " ";
	}
	cout << endl;
}

int GameList::len() {
	return data.size() - 1;
}

int GameList::pick() {
	return rand() % (len() - 2) + 1;
}

bool GameList::guess() {
	/* Return if want another round */
	int guessNumber;
	bool guessOut = false;
	rPosition = pick();
	int ans = data[rPosition + 2];

	cout << "Here are numbers we offer: ";
	printf("%d %d\n", data[rPosition], data[rPosition + 1]);

	for (int guessTime = 5; guessTime > 0; --guessTime) {
		if (guessTime) {
			printf("Chance remain: %d\n", guessTime);
		}
		cout << "Guess the next number: ";
		cin >> guessNumber;
		if (guessNumber == ans) {
			cout << "Right!\n";
			guessOut = true;
			break;
		}
		else {
			cout << "Wrong!\n";
		}
	}
	if (!guessOut) {
		printf("Answer: %d\n", ans);
	}

	cout << "Wanna another round ? (y / n) ";
	char choice;
	cin >> choice;
	return choice == 'y';
}

int pick(vector<GameList> Obj) {
	return rand() % Obj.size();
}

/*
class GameObjs {
private:

};
*/

#define NUM 6
static int ta[NUM][2] = { 
	{ 0, 1 }, 
	{ 2, 1 },
	{ 0, 1 },
	{ 0, 1 },
	{ 0, 1 },
	{ 0, 1 }
};
/* sequence begins from a1
 * a0 is specially calculated, but shouldn't be part of the sequence
 */
static float tc[NUM][4] = {
	{ 1, 1, 0, 0 },
	{ 1, 1, 0, 0 },
	{ 1, 2, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 1 },
	{ 0, 0, -0.5, 1.5 },
};

void init(vector<int*> &arga, vector<float*> &argc) {
	for (int i = 0; i < NUM; ++i) {
		arga.push_back(ta[i]);
		argc.push_back(tc[i]);
	}
}

int main() {
	srand(int(time(0)));
	vector<GameList> GameObjs; 
	vector<int*> arga;
	vector<float*> argc;

	init(arga, argc);

	for (int i = 0; i < NUM; ++i) {
		GameList G(8, arga[i], argc[i]);
		GameObjs.push_back(G);
	}
	//system("pause");

	while (1) {
		system("cls");
		GameList &gNow = GameObjs[pick(GameObjs)];
		if (!gNow.guess())
			break;
	}

	//system("pause");
	return 0;
}



