#include <iostream>//input output
#include <ctime> //時間函式庫

using namespace std;//空間命名，後面可以不用打std::

class slotMachine {//類似struct
private://只能自己class的能修改內容
	int wheelA;
	int wheelB;
	int wheelC;
	double pullTimes;
	double payOut;
	double moneyInMachine;
	double moneyInPeople;
	double gameCost;
	double moneyPaid;
public://大家都可以用
	slotMachine();
	bool displayMenu(void);
	bool pullHandle(void);
	void spinWheel(int &);
	double calculatePayout();
	void insertCoin(double);
	void displaySpinResults();
	int Random(int, int);
	void displayStatus();
};

int main(void) {
	slotMachine mySlot;//定義mySlot的型態是slotMachine
	cout << "Hellow!" << endl;
	cout << "Welcome to our Slot Machine Game." << endl;
	cout << "Now your status:" << endl;
	cout << endl << "Money in Peoele $" << 150 << endl;
	cout << "Money in Machine $" << 100 << endl;
	cout << "Pulls Left: " << 0 << endl << endl;
	//上面用法跟printf是一樣的，endl類似\n的用法
	bool ok = true;
	while (ok)
	{
		ok = mySlot.displayMenu();
	}
	system("pause");
	return 0;
}

slotMachine::slotMachine()//先把上面定義的private的值設定好
{
	srand((int)time(0));//對時間取亂數
	moneyInMachine = 100;
	moneyInPeople = 150;
	moneyPaid = 0;
	pullTimes = 0;
	payOut = 0;
	wheelA = 0;
	wheelB = 0;
	wheelC = 0;
	gameCost = 2;
}

bool slotMachine::displayMenu(void)//目錄
{
	char choice = 'Z';
	bool continueGame = true;
	if (moneyInMachine == 0)//先判斷機台裡面有沒有錢
	{
		cout << "Congratulations. You hit the jackpot" << endl;
		cout << "That start NEW games!" << endl;
		moneyInMachine = rand() % 200 + 100;
		cout << "We put $" << moneyInMachine << " into the machine" << endl;
		cout << "Good Luck To You" << endl;
	}
	if (moneyInPeople < 2 && pullTimes == 0)//判斷有沒有破產
	{
		displayStatus();
		cout << "Now you are Bankruptcy" << endl;
		cout << "Get out of my store" << endl << endl;
		continueGame = false;
		return continueGame;
	}
	else//沒有破產則開始選擇動作
	{
		cout << "---------------------------------------------------" << endl;
		cout << "\n(E)nd, (P)ull, P(A)Y, (S)tatus :";
		cin >> choice;//輸入你要選擇的
		switch (choice) {
		case 'e':
		case 'E'://結束
			continueGame = false;
			break;
		case 'a':
		case 'A'://投入金額
			int money;
			cout << "\nHow much would you want to put in?\n";
			cin >> money;
			if (money <= moneyInPeople)//投入金額一定要小於等於自身擁有的金額
			{
				if (money % 2 == 0)//我們是 2$ 1次 所以只能投2的倍數 
				{
					cout << "Put $" << money << " into the machine" << endl;
					moneyPaid = money;
					pullTimes += (moneyPaid / gameCost);
					cout << "Now you have " << pullTimes << " Pull times\n" << endl;
					insertCoin(money);
				}
				else
				{
					cout << "Please put even money" << endl;
				}
			}
			else
			{
				cout << "You have no enough money" << endl << endl;
			}
			break;
		case 'p':
		case 'P'://使用拉霸
			if (pullHandle())
			{
				cout << endl;
				pullTimes -= 1;
				displaySpinResults();
				cout << "Payout: $" << calculatePayout() << endl << endl;
			}
			else
			{
				cout << "\nYou have no money in Machine" << endl;
				cout << "Please choice (A) to put money in" << endl << endl;
			}
			break;
		case 'S':
		case 's'://查看目前的狀態
			displayStatus();
			break;
		}
		return continueGame;
	}
}
double slotMachine::calculatePayout()//如果有用到3個一樣的數字，會得到金額
{
	if (wheelA == wheelB  && wheelA == wheelC)
	{
		switch (wheelA)
		{
		case 1:
		case 3:
		case 5://3個1 or 3個3 or 3個5 你會得到機台裡面的金額*0.2 
			payOut = ((moneyInMachine + 1) * 0.2);
			moneyInMachine -= payOut;
			moneyInPeople += payOut;
			cout << "You win!" << endl;
			cout << "Pulls Left: " << pullTimes << endl;
			return payOut;
			break;
		case 2:
		case 4:
		case 6://3個2 or 3個4 or 3個6 你會得到機台裡面的金額*0.4 
			payOut = (moneyInMachine * 0.4);
			moneyInMachine -= payOut;
			moneyInPeople += payOut;
			cout << "You win!" << endl;
			cout << "Pulls Left: " << pullTimes << endl;
			return payOut;
			break;
		case 7://3個7 中大獎 機台裡面的錢全拿
			payOut = (moneyInMachine);
			pullTimes = 0;
			moneyInMachine = 0;
			moneyInPeople += payOut;
			cout << "You win!" << endl;
			cout << "Pulls Left: " << pullTimes << endl;
			return payOut;
			break;
		default:
			return 0;
			break;
		}
	}
	else//都沒有3個一樣的
	{
		cout << "Pulls Left: " << pullTimes << endl;
		cout << "No payout. Try again?\n" << endl;
		return 0;
	}
}


