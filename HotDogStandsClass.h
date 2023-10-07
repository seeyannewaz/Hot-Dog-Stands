#ifndef HOTDOG_STAND_CLASS_H
#define HOTDOG_STAND_CLASS_H

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class HotDogStandsClass {

private:
    string   identificationStr,
        addressStr;
    float    hotDogPrice;
    unsigned inventoryAmount,
        soldAmount;

public:

    HotDogStandsClass() {
    }

    static unsigned globalSoldCount;

    const string& getIdStr() const
    {
        return identificationStr;
    };

    void          setIdStr(const string& identificationStr)
    {
        this->identificationStr = identificationStr;
    }


    const string& getAddressStr() const
    {
        return addressStr;
    };

    void          setAddressStr(const string& addressStr)
    {
        this->addressStr = addressStr;
    }

    float getPriceFl() const
    {
        return hotDogPrice;
    };

    void  setPriceFl(float hotDogPrice)
    {
        this->hotDogPrice = hotDogPrice;
    }

    unsigned        getSoldAmount() const
    {
        return soldAmount;
    };

    void            setSoldAmount(unsigned soldAmount)
    {
        this->soldAmount = soldAmount;
    }

    unsigned        getInventoryAmount() const
    {
        return inventoryAmount;
    };

    void            setInventoryAmount(unsigned inventoryAmount)
    {
        this->inventoryAmount = inventoryAmount;
    }

    void stockInventoryAmount(unsigned stockCountUns)
    {
        inventoryAmount += stockCountUns;
    }

    void           hotDogsBuy(unsigned count);

};//HotDogStandsClass

#endif
