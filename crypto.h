#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>

using namespace std;

struct InfotypeExchange {
    string name;
};

struct InfotypeCoin {
    string code;
    string name;
};

typedef struct NodeExchange* adrExchange;
typedef struct NodeCoin* adrCoin;
typedef struct NodeListing* adrListing;

struct NodeExchange {
    InfotypeExchange info;
    adrExchange next;
};

struct NodeCoin {
    InfotypeCoin info;
    adrCoin next;
};

struct NodeListing {
    adrExchange exchangePtr;
    adrCoin coinPtr;
    string pairName;
    adrListing next;
    adrListing prev;
};

struct ListExchange {
    adrExchange first;
};

struct ListCoin {
    adrCoin first;
};

struct ListListing {
    adrListing first;
    adrListing last;
};

void createListExchange(ListExchange &LE);
void createListCoin(ListCoin &LC);
void createListListing(ListListing &LL);

adrExchange createNodeExchange(string name);
adrCoin createNodeCoin(string code, string name);
adrListing createNodeListing(adrExchange E, adrCoin C, string pairName);

void insertExchange(ListExchange &LE, adrExchange E);
void insertCoin(ListCoin &LC, adrCoin C);
void insertListing(ListListing &LL, adrListing L);

void deleteExchange(ListExchange &LE, ListListing &LL, string name);
void deleteCoin(ListCoin &LC, ListListing &LL, string code);
void deleteListing(ListListing &LL, adrExchange E, adrCoin C);

adrExchange findExchange(ListExchange LE, string name);
adrCoin findCoin(ListCoin LC, string code);
adrListing findListing(ListListing LL, string eName, string cCode);

void showAllExchange(ListExchange LE);
void showAllCoin(ListCoin LC);
void showCoinOfExchange(ListListing LL, string eName);
void showExchangeOfCoin(ListListing LL, string cCode);
void showExchangeWithCoin(ListExchange LE, ListListing LL);
void showCoinWithExchange(ListCoin LC, ListListing LL);

int countCoinOfExchange(ListListing LL, string eName);
int countExchangeOfCoin(ListListing LL, string cCode);
int countCoinNoExchange(ListCoin LC, ListListing LL);
int countExchangeNoCoin(ListExchange LE, ListListing LL);

void editListingExchange(ListListing &LL, adrExchange oldE, adrExchange newE, adrCoin C);
void editListingCoin(ListListing &LL, adrExchange E, adrCoin oldC, adrCoin newC);

void disconnectListing(ListListing &LL, adrListing L);

#endif
