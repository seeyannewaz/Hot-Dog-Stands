#include "HotDogStandsClass.h"
#include <iostream>

using namespace std;

unsigned HotDogStandsClass::globalSoldCount = 0;

void HotDogStandsClass::hotDogsBuy(unsigned count) {
    if (inventoryAmount == 0)
    {
        cout << "*There are not any more hotdogs left to be sold*" << endl << endl;
        return;
    }
    else if (inventoryAmount < count)
    {
        cout << "*We only have " << inventoryAmount << " hotdog";
        cout << (inventoryAmount > 1 ? "s left.*" : "left.*") << endl << endl;
        return;
    }

    inventoryAmount -= count;
    soldAmount += count;
    HotDogStandsClass::globalSoldCount += count;


}