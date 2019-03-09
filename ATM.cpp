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
	cout << "********************************欢迎使用ATM机***********************************" << endl;
	do
	{
		cout << "请输入您的卡号：" << endl;
		cin >> account;
		cout << endl << "请输入您的密码:" << endl;
		cin >> key;
		cout << endl;
		if(!checkInfo(account,key))
		{
			cout << endl << "对不起，您的卡号或密码有误，请重新输入" << endl;
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
	cout <<"您的个人信息如下:"<< endl;
	cout <<"卡号：" << us.getAccount() << endl;
	cout << "姓名:" << us.getName() << endl;
	cout << "身份证号：" << us.getID() << endl << endl;
	cout << "********************************************************************************" << endl;
}
void ATM::lockCard()
{
	cout << "对不起，您输入的密码有误已达三次，您的卡已被没收！" << endl;
	exit(1);
}

void ATM::mainMenu()
{
	cout << "********************************************************************************" << endl;
	cout << "信息确认无误后，请查看主菜单进行相关操作！" << endl;
	cout << "主菜单：                  " << endl;
	cout << "            1 - 查询余额" << endl;
	cout << "            2 - 取款         " << endl;
	cout << "            3 - 转账         " << endl;
	cout << "            4 - 修改密码" << endl;
	cout << "            5 - 退卡         " << endl << endl;
	cout << "********************************************************************************" << endl;
	
	choice();
}

void ATM::choice()
{
	int n;
	cout <<"请根据主菜单进行操作！！请输入您想操作的序号：" << endl;
	cin >> n;
	while(n < 0 || n > 5)
	{
		cout << "您输入的序号不正确，请重新输入" << endl;
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
	cout << "                    卡号  ：   " << us.getAccount() << endl;
	cout << "                    余额  ：   " << us.getAmount() << endl << endl;
	cout << "********************************************************************************" << endl;
}

void ATM::withdrawCash()
{
	float m;
	float money = 0;
	char ch;

	do
	{
		cout << endl << "请输入您要取多少钱：" << endl;
		cin >> m;

		while(m <= 0)
		{
			cout << "请输入正确的取款数：" << endl;
			cin >> m;
		}

		if(us.getAmount() - m < 0)
		{
			cout << "对不起，您的余额不足！" << endl;
		}
		else
		{
			money = money + m;
			//每次取款余额为100的整数倍，有单笔和单日金额限制
			if((int)m % 100 != 0)
			{
				cout << "对不起，您的取款金额必须为100的倍数！请输入正确的取款数！" << endl;
				withdrawCash();
			}
			else if(m > 2000)
			{
				cout << "对不起，您的取款金额已经超过了单笔最大金额2000！请输入正确的取款数！" << endl;
				withdrawCash();
			}
			else if(money > 5000)
			{
				cout << "对不起，您的取款金额已经超过了单日最大金额5000！" << endl;
			}
			else
			{
				cout << endl << "操作成功，请稍候！！" << endl;
				us.setAmount(us.getAmount() - m);
			}
		}

		cout << "请输入Y确认收钱！N继续取钱！" << endl;
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

	//转入帐号需两次输入确认
	cout << endl << "请输入您想转的银行帐号：" << endl;
	cin >> account1;
	if(!strcmp(us.getAccount(), account1))
	{
		cout << endl << "您输入的是自己的账号，请重新输入！" << endl << endl;
		transferCash();
		mainMenu();
	}

	cout << endl << "请再确认一遍您想转的银行帐号：" << endl;
	cin >> account2;
	if(!strcmp(account1,account2))
	{
		cout << endl << "您输入的银行帐号确认成功！请输入您想转出的金额：" << endl;
		cin >> money;
		while(us.getAmount() - money < 0)
		{
			cout << endl << "您输入的金额大于了您的余额，请重新输入：" << endl;
			cin >> money;
		}
		us.setAmount(us.getAmount() - money);
		cout << endl << "您的操作成功！您已成功向" << account1 << "转入金额" << money << endl << endl;
		cout << "********************************************************************************" << endl;
	}
	else 
	{
		cout << endl << "您两次输入的帐号不一致，请重新操作！" << endl;
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
	cout << endl << "请输入新密码：";
	cin >> Nkey1;

	while(!strcmp(key,Nkey1))
	{
		cout << "您输入的新密码与旧密码相同，请重新输入:";
		cin >> Nkey1;
	}
	
	cout << "请再次输入新密码：";
	cin >> Nkey2;	

	if(!strcmp(Nkey1, Nkey2))
	{
		us.setKey(Nkey1);
		cout <<"密码修改成功！" << endl << endl;
		mainMenu();
	}
	else 
	{
		cout << "您两次输入的新密码不一致，请重新操作！" << endl;
		changeKeys();
	}
}

void ATM::Exit()
{
	cout << endl << endl << "请取走您的卡，感谢您的使用，欢迎您下次再来！" << endl;
	cout << "********************************************************************************" << endl;
	exit(0);
}


