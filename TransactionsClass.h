#ifndef TRANSACTIONS_CLASS_CLASS_H
#define TRANSACTIONS_CLASS_CLASS_H

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class TransactionsClass {

private:
	string   standID;
	string   transactionID;
	unsigned transactionArgument;

public:
	const string& getIdentifcationStr() const
	{
		return standID;
	};
	void          setIdentifcationStr(string standID)
	{
		this->standID = standID;
	}

	const string& gettransactionID() const
	{
		return transactionID;
	};
	void          settransactionID(string transactionID)
	{
		this->transactionID = transactionID;
	}

	unsigned gettransactionArgument() const
	{
		return transactionArgument;
	};
	void     settransactionArgument(unsigned transactionArgument)
	{
		this->transactionArgument = transactionArgument;
	}

};

#endif
