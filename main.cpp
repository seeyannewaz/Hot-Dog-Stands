#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

#include "HotDogStandsClass.h"
#include "TransactionsClass.h"

using namespace std;

const string HOTDOG_STANDS_FILE_NAME = "InfoHotDogStands.txt";
const string TRANSACTIONS_FILE_NAME = "InfoHotDogStandsTransactions.txt";
const string GLOBAL_SOLD_FILE_NAME = "InfoGlobalSold.txt";

ostream& operator<<(ostream& leftSideOutputStream, const HotDogStandsClass& hotDogStandObj);
ostream& operator<<(ostream& leftSideOutputStream, const TransactionsClass& transactionsObj);

void CheckFileStreamOpen(const string& fileName, ifstream& inFile);
void ReadInFromGlobalSoldFile(const string& fileName);
void ReadInFromHotDogStandsFile(const string& fileName, HotDogStandsClass*& hotDogStandsAry, unsigned& standsLineCount);
void ReadInFromTransactionsFile(const string& fileName, TransactionsClass*& transactionsAry, unsigned& transactionsLineCount);
void displayStands(HotDogStandsClass* hotDogStandsAry, unsigned totalNoHotDogStandsUns);
unsigned getMatchingHotDogStandIndex(HotDogStandsClass* hotDogStandsAry, unsigned totalNoHotDogStandsUns, TransactionsClass* transactionsAry, unsigned transactionsNoUns);
void processTransactions(HotDogStandsClass*& hotDogStandsAry, unsigned totalNoHotDogStandsUns, TransactionsClass* transactionsAry, unsigned totalNoTransactionsUns);
void UpdateHotDogStandsFile(const string& fileName, HotDogStandsClass* hotDogStandsAry, unsigned totalNoHotDogStandsUns);
void UpdateGlobalSoldFile(const string& fileName);

int main() {
    cout << setprecision(2) << fixed << showpoint;

    HotDogStandsClass* hotDogStandsAry = nullptr;
    unsigned hotDogStandsCountUns;
    TransactionsClass* transactionsAry = nullptr;
    unsigned transactionsCountUns;

    ReadInFromGlobalSoldFile(GLOBAL_SOLD_FILE_NAME);
    ReadInFromHotDogStandsFile(HOTDOG_STANDS_FILE_NAME, hotDogStandsAry, hotDogStandsCountUns);
    ReadInFromTransactionsFile(TRANSACTIONS_FILE_NAME, transactionsAry, transactionsCountUns);

    cout << "Initial states of stands:" << endl;
    cout << "=========================" << endl << endl;
    displayStands(hotDogStandsAry, hotDogStandsCountUns);

    cout << "Process Transactions:" << endl;
    cout << "=====================" << endl << endl;
    processTransactions(hotDogStandsAry, hotDogStandsCountUns, transactionsAry, transactionsCountUns);

    cout << "Final states of stands:" << endl;
    cout << "=======================" << endl << endl;
    displayStands(hotDogStandsAry, hotDogStandsCountUns);

    UpdateHotDogStandsFile(HOTDOG_STANDS_FILE_NAME, hotDogStandsAry, hotDogStandsCountUns);
    UpdateGlobalSoldFile(GLOBAL_SOLD_FILE_NAME);

    cout << "Please press enter key once or twice to end...";
    cin.ignore();
    cin.get();

    return EXIT_SUCCESS;
}

ostream& operator<<(ostream& leftSideOutputStream, const HotDogStandsClass& hotDogStandObj) {
    leftSideOutputStream <<
        "Stand Id   : " + hotDogStandObj.getIdStr() << endl <<
        "Address    : " + hotDogStandObj.getAddressStr() << endl <<
        "Price      : " << hotDogStandObj.getPriceFl() << endl <<
        "Inventory  : " << hotDogStandObj.getInventoryAmount() << endl <<
        "Store Sold : " << hotDogStandObj.getSoldAmount() << " at $" << hotDogStandObj.getPriceFl() << " ea." << endl;

    return leftSideOutputStream;
}

ostream& operator<<(ostream& leftSideOutputStream, const TransactionsClass& transactionsObj) {
    leftSideOutputStream <<
        "Transaction Stand Id : " + transactionsObj.getIdentifcationStr() << endl <<
        "Transaction Id       : " + transactionsObj.gettransactionID() << endl <<
        "Transaction Argument : " << transactionsObj.gettransactionArgument() << endl;

    return leftSideOutputStream;
}

void CheckFileStreamOpen(const string& fileName, ifstream& inFile) {
    if (inFile.fail()) {
        cout << "File " << fileName << " could not be opened!" << endl;
        cout << endl << "Press the enter key once or twice to continue..." << endl;
        cin.ignore();
        cin.get();
        exit(EXIT_FAILURE);
    }
}

void ReadInFromGlobalSoldFile(const string& fileName) {
    ifstream inFile(fileName);
    CheckFileStreamOpen(fileName, inFile);
    inFile >> HotDogStandsClass::globalSoldCount;
    inFile.close();
}

void ReadInFromHotDogStandsFile(const string& fileName, HotDogStandsClass*& hotDogStandsAry, unsigned& hotDogStandsCountUns) {
    ifstream inFile(fileName);
    CheckFileStreamOpen(fileName, inFile);

    string lineInFileBufferStr;

    // Count the number of lines in the file
    hotDogStandsCountUns = 0;
    while (getline(inFile, lineInFileBufferStr)) {
        ++hotDogStandsCountUns;
    }

    hotDogStandsAry = new HotDogStandsClass[hotDogStandsCountUns];

    inFile.clear();
    inFile.seekg(0, ios::beg);
    string inputStr;
    constexpr char COMMA_DELIMITER_CHAR = ',';

    // for each line read from the file
    for (unsigned lineCount = 0; lineCount < hotDogStandsCountUns; ++lineCount) {
        getline(inFile, lineInFileBufferStr);
        istringstream isStringStream(lineInFileBufferStr);

        // read everything up to the comma delimiter
        getline(isStringStream, inputStr, COMMA_DELIMITER_CHAR);
        hotDogStandsAry[lineCount].setIdStr(inputStr);

        getline(isStringStream, inputStr, COMMA_DELIMITER_CHAR);
        hotDogStandsAry[lineCount].setAddressStr(inputStr);

        getline(isStringStream, inputStr, COMMA_DELIMITER_CHAR);
        hotDogStandsAry[lineCount].setPriceFl(stof(inputStr));

        getline(isStringStream, inputStr, COMMA_DELIMITER_CHAR);
        isStringStream >> inputStr;
        hotDogStandsAry[lineCount].setInventoryAmount(static_cast<unsigned>(stoul(inputStr)));

        getline(isStringStream, inputStr, COMMA_DELIMITER_CHAR);
        isStringStream >> inputStr;
        hotDogStandsAry[lineCount].setSoldAmount(static_cast<unsigned>(stoul(inputStr)));
    }

    inFile.close();
}

void ReadInFromTransactionsFile(const string& fileName, TransactionsClass*& transactionsAry, unsigned& transactionsLineCount) {
    ifstream inFile(fileName);
    CheckFileStreamOpen(fileName, inFile);

    string lineInFileBufferStr;

    // Count the number of lines in the transactions file
    transactionsLineCount = 0;
    while (getline(inFile, lineInFileBufferStr)) {
        ++transactionsLineCount;
    }

    transactionsAry = new TransactionsClass[transactionsLineCount];

    inFile.clear();
    inFile.seekg(0, ios::beg);
    string inputStr;
    constexpr char COMMA_DELIMITER_CHAR = ',';

    for (unsigned lineCount = 0; lineCount < transactionsLineCount; ++lineCount) {
        getline(inFile, lineInFileBufferStr);
        istringstream isStringStream(lineInFileBufferStr);

        getline(isStringStream, inputStr, COMMA_DELIMITER_CHAR);
        transactionsAry[lineCount].setIdentifcationStr(inputStr);

        getline(isStringStream, inputStr, COMMA_DELIMITER_CHAR);
        transactionsAry[lineCount].settransactionID(inputStr);

        getline(isStringStream, inputStr, COMMA_DELIMITER_CHAR);
        transactionsAry[lineCount].settransactionArgument(static_cast<unsigned>(stoul(inputStr)));
    }

    inFile.close();
}

void displayStands(HotDogStandsClass* hotDogStandsAry, unsigned totalNoHotDogStandsUns) {
    for (unsigned displayIndex = 0; displayIndex < totalNoHotDogStandsUns; ++displayIndex) {
        cout << hotDogStandsAry[displayIndex] << endl;
    }

    cout << endl << "Global Sold : " << HotDogStandsClass::globalSoldCount << endl << endl;
    cout << "Please press enter key once or twice to continue...";
    cin.ignore();
    cin.get();
    cout << endl << endl;
}

unsigned getMatchingHotDogStandIndex(HotDogStandsClass* hotDogStandsAry, unsigned totalNoHotDogStandsUns, TransactionsClass* transactionsAry, unsigned transactionsNoUns) {
    for (unsigned seekIndex = 0; seekIndex < totalNoHotDogStandsUns; ++seekIndex) {
        if (hotDogStandsAry[seekIndex].getIdStr() == transactionsAry[transactionsNoUns].getIdentifcationStr()) {
            return seekIndex;
        }
    }
    return 0; // Return a default value if no match is found
}

void processTransaction(TransactionsClass transactionObj, HotDogStandsClass& hotDogStandObj) {
    if (transactionObj.gettransactionID() == "stock inventory") {
        hotDogStandObj.stockInventoryAmount(transactionObj.gettransactionArgument());
    }
    else if (transactionObj.gettransactionID() == "buy") {
        hotDogStandObj.hotDogsBuy(transactionObj.gettransactionArgument());
    }
}

void processTransactions(HotDogStandsClass*& hotDogStandsAry, unsigned totalNoHotDogStandsUns, TransactionsClass* transactionsAry, unsigned totalNoTransactionsUns) {
    for (unsigned transactionNoUns = 0; transactionNoUns < totalNoTransactionsUns; ++transactionNoUns) {
        // Find correct stand
        unsigned hotDogStandIndexUns = getMatchingHotDogStandIndex(hotDogStandsAry, totalNoHotDogStandsUns, transactionsAry, transactionNoUns);
        cout << "-----------------------------" << endl << endl;
        cout << "HotDog Stand Current Status :" << endl << endl;
        cout << hotDogStandsAry[hotDogStandIndexUns] << endl;
        cout << "Transaction: " << endl << endl;
        cout << transactionsAry[transactionNoUns] << endl;
        processTransaction(transactionsAry[transactionNoUns], hotDogStandsAry[hotDogStandIndexUns]);
        cout << "HotDog Stand Status After Transaction :" << endl << endl;
        cout << hotDogStandsAry[hotDogStandIndexUns] << endl << endl;
        cout << "Global Sold : " << HotDogStandsClass::globalSoldCount << endl << endl;
        cout << "Please press enter key once or twice to continue...";
        cin.ignore();
        cin.get();
    }
}

void UpdateHotDogStandsFile(const string& fileName, HotDogStandsClass* hotDogStandsAry, unsigned totalNoHotDogStandsUns) {
    ofstream outFile(fileName);

    for (unsigned writeIndex = 0; writeIndex < totalNoHotDogStandsUns; ++writeIndex) {
        outFile <<
            hotDogStandsAry[writeIndex].getIdStr() << "," <<
            hotDogStandsAry[writeIndex].getAddressStr() << "," <<
            hotDogStandsAry[writeIndex].getPriceFl() << "," <<
            hotDogStandsAry[writeIndex].getInventoryAmount() << "," <<
            hotDogStandsAry[writeIndex].getSoldAmount() << endl;
    }

    outFile.close();
}

void UpdateGlobalSoldFile(const string& fileName) {
    ofstream outFile(fileName);
    outFile << HotDogStandsClass::globalSoldCount << endl;
}
