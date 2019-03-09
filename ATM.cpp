#include <iostream>
#include <string.h>
#include <stdlib.h>

using  namespace std;

class USER;
class ATM;

class USER
{
private:
	char account[20];
	char name[10];
	char id[19];
	char key[7];
	float amount;
public:
	friend class ATM;
	USER(char Account[], char Name[], char ID[], char Key[], float Amount);
	void setAccount(char Account[]);
	void setName(char Name[]);
	void setID(char ID[]);
	void setKey(char Key[]);
	void setAmount(float Amount);
	char* getAccount();
	char* getName();
	char* getID();
	char* getKey();
	float getAmount();
};

class ATM
{
private:
	int time;
	USER& us;
public:
	ATM(USER& u):us(u){};
	void loginSystem();
	bool checkInfo(char Account[],char Key[]);
	void showInfo();
	void lockCard();
	void mainMenu();
	void choice();
	void viewBalance();
	void withdrawCash();
	void transferCash();
	void changeKeys();
	void Exit();
};

int main()
{
	USER user1("1234567891011121314","Jessica","123456789101112131","123456",10000);
	ATM a(user1);
	a.loginSystem();
	return 0;
}

USER::USER(char Account[], char Name[], char ID[], char Key[], float Amount)
{
	strcpy(account, Account);
	strcpy(name, Name);
	strcpy(id, ID);
	strcpy(key, Key);
	amount = Amount;
}

void USER::setAccount(char Account[])
{
	strcpy(account,Account);
}

void USER::setName(char Name[])
{
	strcpy(name,Name);
}

void USER::setID(char ID[])
{
	strcpy(id,ID);
}

void USER::setKey(char Key[])
{
	strcpy(key,Key);
}

void USER::setAmount(float Amount)
{
	amount = Amount;
}

char* USER::getAccount()
{
	return account;
}

char* USER::getName()
{
	return name;
}

char* USER::getID()
{
	return id;
}

char* USER::getKey()
{
	return key;
}

float USER::getAmount()
{
	return amount;
}

void ATM::loginSystem()
{
	int time = 0;
	char account[20];
	char name[10];
	char id[19];
	char key[7];
	char ch;
	float amount;
	cout << "********************************��ӭʹ��ATM��***********************************" << endl;
	do
	{
		cout << "���������Ŀ��ţ�" << endl;
		cin >> account;
		cout << endl << "��������������:" << endl;
		cin >> key;
		cout << endl;
		if(!checkInfo(account,key))
		{
			cout << endl << "�Բ������Ŀ��Ż�������������������" << endl;
			cout << "********************************************************************************" << endl;
			time ++;
		}
		else
		{	
			showInfo();
			mainMenu();
		}
	}while(time < 3);
	lockCard();
}

bool ATM::checkInfo(char Account[],char Key[])
{
	if(!strcmp(Account, us.getAccount()) && !strcmp(Key, us.getKey()))
		return true;
	else 
		return false;
}

void ATM::showInfo()
{
	cout << "********************************************************************************" << endl;
	cout <<"���ĸ�����Ϣ����:"<< endl;
	cout <<"���ţ�" << us.getAccount() << endl;
	cout << "����:" << us.getName() << endl;
	cout << "���֤�ţ�" << us.getID() << endl << endl;
	cout << "********************************************************************************" << endl;
}
void ATM::lockCard()
{
	cout << "�Բ�������������������Ѵ����Σ����Ŀ��ѱ�û�գ�" << endl;
	exit(1);
}

void ATM::mainMenu()
{
	cout << "********************************************************************************" << endl;
	cout << "��Ϣȷ���������鿴���˵�������ز�����" << endl;
	cout << "���˵���                  " << endl;
	cout << "            1 - ��ѯ���" << endl;
	cout << "            2 - ȡ��         " << endl;
	cout << "            3 - ת��         " << endl;
	cout << "            4 - �޸�����" << endl;
	cout << "            5 - �˿�         " << endl << endl;
	cout << "********************************************************************************" << endl;
	
	choice();
}

void ATM::choice()
{
	int n;
	cout <<"��������˵����в������������������������ţ�" << endl;
	cin >> n;
	while(n < 0 || n > 5)
	{
		cout << "���������Ų���ȷ������������" << endl;
		choice();
	}
	switch(n)
	{
		case 1:viewBalance();
			   choice();
		break;
		case 2:withdrawCash();
			   choice();
		break;
		case 3:transferCash();
			   choice();
		break;
		case 4:changeKeys();
			   choice();
		break;
		case 5:Exit();
		break;
	}while(true);
}
void ATM::viewBalance()
{
	cout << endl;
	cout << "                    ����  ��   " << us.getAccount() << endl;
	cout << "                    ���  ��   " << us.getAmount() << endl << endl;
	cout << "********************************************************************************" << endl;
}

void ATM::withdrawCash()
{
	float m;
	float money = 0;
	char ch;

	do
	{
		cout << endl << "��������Ҫȡ����Ǯ��" << endl;
		cin >> m;

		while(m <= 0)
		{
			cout << "��������ȷ��ȡ������" << endl;
			cin >> m;
		}

		if(us.getAmount() - m < 0)
		{
			cout << "�Բ����������㣡" << endl;
		}
		else
		{
			money = money + m;
			//ÿ��ȡ�����Ϊ100�����������е��ʺ͵��ս������
			if((int)m % 100 != 0)
			{
				cout << "�Բ�������ȡ�������Ϊ100�ı�������������ȷ��ȡ������" << endl;
				withdrawCash();
			}
			else if(m > 2000)
			{
				cout << "�Բ�������ȡ�����Ѿ������˵��������2000����������ȷ��ȡ������" << endl;
				withdrawCash();
			}
			else if(money > 5000)
			{
				cout << "�Բ�������ȡ�����Ѿ������˵��������5000��" << endl;
			}
			else
			{
				cout << endl << "�����ɹ������Ժ򣡣�" << endl;
				us.setAmount(us.getAmount() - m);
			}
		}

		cout << "������Yȷ����Ǯ��N����ȡǮ��" << endl;
		cin >> ch;
		if(ch == 'Y' || ch == 'y')
		{
			cout << "********************************************************************************" << endl;
			choice();
		}
	}while(ch == 'N' || ch == 'n');
}

void ATM::transferCash()
{
	char account1[20];
	char account2[20];
	float money;

	//ת���ʺ�����������ȷ��
	cout << endl << "����������ת�������ʺţ�" << endl;
	cin >> account1;
	if(!strcmp(us.getAccount(), account1))
	{
		cout << endl << "����������Լ����˺ţ����������룡" << endl << endl;
		transferCash();
		mainMenu();
	}

	cout << endl << "����ȷ��һ������ת�������ʺţ�" << endl;
	cin >> account2;
	if(!strcmp(account1,account2))
	{
		cout << endl << "������������ʺ�ȷ�ϳɹ�������������ת���Ľ�" << endl;
		cin >> money;
		while(us.getAmount() - money < 0)
		{
			cout << endl << "������Ľ����������������������룺" << endl;
			cin >> money;
		}
		us.setAmount(us.getAmount() - money);
		cout << endl << "���Ĳ����ɹ������ѳɹ���" << account1 << "ת����" << money << endl << endl;
		cout << "********************************************************************************" << endl;
	}
	else 
	{
		cout << endl << "������������ʺŲ�һ�£������²�����" << endl;
		transferCash();
	}
}

void ATM::changeKeys()
{
	char key[7];
	char Nkey1[7];
	char Nkey2[7];
	strcpy(key,us.getKey());

	char ch;
	cout << endl << "�����������룺";
	cin >> Nkey1;

	while(!strcmp(key,Nkey1))
	{
		cout << "����������������������ͬ������������:";
		cin >> Nkey1;
	}
	
	cout << "���ٴ����������룺";
	cin >> Nkey2;	

	if(!strcmp(Nkey1, Nkey2))
	{
		us.setKey(Nkey1);
		cout <<"�����޸ĳɹ���" << endl << endl;
		mainMenu();
	}
	else 
	{
		cout << "����������������벻һ�£������²�����" << endl;
		changeKeys();
	}
}

void ATM::Exit()
{
	cout << endl << endl << "��ȡ�����Ŀ�����л����ʹ�ã���ӭ���´�������" << endl;
	cout << "********************************************************************************" << endl;
	exit(0);
}


