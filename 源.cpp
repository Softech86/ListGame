/*
组员名单：白一非 李航 卢欣冉 朱睿安
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
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
	bool guess(int &rightTot, int &guessTot);
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

bool GameList::guess(int &rightTot, int &guessTot) {
	/* Return if want another round */
	int guessNumber;
	bool guessOut = false;
	rPosition = pick();
	int ans = data[rPosition + 2];
	printf("The value %d, %d form two consecutive elements of a numerical sequence.\nWhat is the next value ? \n", data[rPosition], data[rPosition + 1]);

	for (int guessTime = 5; guessTime > 0; --guessTime) {	
		if (guessTime) {
			printf("Chance remain: %d.\n", guessTime);
		}
		cout << "Guess the next number: ";
		string input;
		stringstream ss;
		cin >> input;
		guessNumber = atoi(input.c_str());
		ss << guessNumber; // ensure the input legal and acceptable
		if (ss.str() != input)
			guessNumber = -1;
		
		++guessTot;
		if (guessNumber == ans) {
			guessOut = true;
			++rightTot;
			printf("Right! Score %.2f\n", 100.0 * rightTot / guessTot);
			break;
		}
		else {
			printf("Wrong! Score %.2f\n", 100.0 * rightTot / guessTot);
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

class Game {
private:
	int listNum, listLen;
	int rightTot = 0, guessTot = 0;
	vector<GameList> GameObjs;
	vector<int*> arga;
	vector<float*> argc;
	int pick();
public:
	Game(int tNum, int tLen, vector<int*> va, vector<float*> vc);
	void play();
};

Game::Game(int tNum, int tLen, vector<int*> va, vector<float*> vc) {
	listNum = tNum;
	listLen = tLen;
	for (int i = 0; i < tNum; ++i) {
		arga.push_back(va[i]);
		argc.push_back(vc[i]);
	}

	for (int i = 0; i < tNum; ++i) {
		GameList G(tLen, arga[i], argc[i]);
		GameObjs.push_back(G);
	}
}

int Game::pick() {
	return rand() % GameObjs.size();
}

void Game::play() {
	while (true) {
		system("cls");
		GameList &gNow = GameObjs[pick()];
		if (!gNow.guess(rightTot, guessTot))
			break;
	}
}

#define NUM 6

int main() {
	int ta[NUM][2] = {
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
	float tc[NUM][4] = {
		{ 1, 1, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 1, 2, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 1 },
		{ 0, 0, -0.5, 1.5 },
	};

	vector<int*> va(ta, ta + NUM);
	vector<float*> vc(tc, tc + NUM);
	srand(int(time(0)));

	Game G(NUM, 8, va, vc);
	G.play();
	//system("pause");
	return 0;
}



