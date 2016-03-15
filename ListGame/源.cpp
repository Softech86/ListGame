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
	GameList(int l);
	int len();
	void showList();
	bool guess();
};

GameList::GameList(int l) {
	data.push_back(1);
	data.push_back(1);
	for (int i = 2; i < l; ++i) {
		data.push_back(data[i - 1] + data[i - 2]);
	}
}

void GameList::showList() {
	cout << len() << endl;
	for (int i = 0; i < len(); ++i) {
		cout << data[i] << " ";
	}
	cout << endl;
}

int GameList::len() {
	return data.size();
}

int GameList::pick() {
	return rand() % (len() - 2);
}

bool GameList::guess() {
	//Return if want another round
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

int main() {
	srand(int(time(0)));
	vector<GameList> GameObjs; 
	
	GameList G(10);

	GameObjs.push_back(G);

	while (1) {
		system("cls");
		GameList &gNow = GameObjs[pick(GameObjs)];
		if (!gNow.guess())
			break;
	}

	//system("pause");
	return 0;
}



