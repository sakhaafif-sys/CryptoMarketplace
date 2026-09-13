#include "crypto.h"

void createListExchange(ListExchange &LE) {
    LE.first = NULL;
}

void createListCoin(ListCoin &LC) {
    LC.first = NULL;
}

void createListListing(ListListing &LL) {
    LL.first = NULL;
    LL.last = NULL;
}

adrExchange createNodeExchange(string name) {
    adrExchange E = new NodeExchange;
    E->info.name = name;
    E->next = NULL;
    return E;
}

adrCoin createNodeCoin(string code, string name) {
    adrCoin C = new NodeCoin;
    C->info.code = code;
    C->info.name = name;
    C->next = NULL;
    return C;
}

adrListing createNodeListing(adrExchange E, adrCoin C, string pairName) {
    adrListing L = new NodeListing;
    L->exchangePtr = E;
    L->coinPtr = C;
    L->pairName = pairName;
    L->next = NULL;
    L->prev = NULL;
    return L;
}

void insertExchange(ListExchange &LE, adrExchange E) {
    if (LE.first == NULL) {
        LE.first = E;
    } else {
        adrExchange temp = LE.first;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = E;
    }
}

void insertCoin(ListCoin &LC, adrCoin C) {
    if (LC.first == NULL) {
        LC.first = C;
    } else {
        adrCoin temp = LC.first;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = C;
    }
}

void insertListing(ListListing &LL, adrListing L) {
    if (LL.first == NULL) {
        LL.first = L;
        LL.last = L;
    } else {
        LL.last->next = L;
        L->prev = LL.last;
        LL.last = L;
    }
}

void disconnectListing(ListListing &LL, adrListing L) {
    if (L == LL.first && L == LL.last) {
        LL.first = NULL;
        LL.last = NULL;
    } else if (L == LL.first) {
        LL.first = L->next;
        LL.first->prev = NULL;
    } else if (L == LL.last) {
        LL.last = L->prev;
        LL.last->next = NULL;
    } else {
        L->prev->next = L->next;
        L->next->prev = L->prev;
    }
    L->next = NULL;
    L->prev = NULL;
}

void deleteListing(ListListing &LL, adrExchange E, adrCoin C) {
    adrListing L = LL.first;
    bool deleted = false;
    while (L != NULL && deleted == false) {
        if (L->exchangePtr == E && L->coinPtr == C) {
            adrListing temp = L;
            L = L->next;
            disconnectListing(LL, temp);
            delete temp;
            deleted = true;
        } else {
            L = L->next;
        }
    }
}

void deleteExchange(ListExchange &LE, ListListing &LL, string name) {
    adrExchange E = findExchange(LE, name);
    if (E != NULL) {
        adrListing L = LL.first;
        while (L != NULL) {
            adrListing nextL = L->next;
            if (L->exchangePtr == E) {
                disconnectListing(LL, L);
                delete L;
            }
            L = nextL;
        }

        if (E == LE.first) {
            LE.first = E->next;
        } else {
            adrExchange temp = LE.first;
            while (temp->next != E) {
                temp = temp->next;
            }
            temp->next = E->next;
        }
        delete E;
    }
}

void deleteCoin(ListCoin &LC, ListListing &LL, string code) {
    adrCoin C = findCoin(LC, code);
    if (C != NULL) {
        adrListing L = LL.first;
        while (L != NULL) {
            adrListing nextL = L->next;
            if (L->coinPtr == C) {
                disconnectListing(LL, L);
                delete L;
            }
            L = nextL;
        }

        if (C == LC.first) {
            LC.first = C->next;
        } else {
            adrCoin temp = LC.first;
            while (temp->next != C) {
                temp = temp->next;
            }
            temp->next = C->next;
        }
        delete C;
    }
}

adrExchange findExchange(ListExchange LE, string name) {
    adrExchange E = LE.first;
    adrExchange found = NULL;
    while (E != NULL && found == NULL) {
        if (E->info.name == name) {
            found = E;
        } else {
            E = E->next;
        }
    }
    return found;
}

adrCoin findCoin(ListCoin LC, string code) {
    adrCoin C = LC.first;
    adrCoin found = NULL;
    while (C != NULL && found == NULL) {
        if (C->info.code == code) {
            found = C;
        } else {
            C = C->next;
        }
    }
    return found;
}

adrListing findListing(ListListing LL, string eName, string cCode) {
    adrListing L = LL.first;
    adrListing found = NULL;
    while (L != NULL && found == NULL) {
        if (L->exchangePtr->info.name == eName && L->coinPtr->info.code == cCode) {
            found = L;
        } else {
            L = L->next;
        }
    }
    return found;
}

void showAllExchange(ListExchange LE) {
    cout << "=== List Exchanges ===" << endl;
    adrExchange E = LE.first;
    while (E != NULL) {
        cout << "- " << E->info.name << endl;
        E = E->next;
    }
    cout << endl;
}

void showAllCoin(ListCoin LC) {
    cout << "=== List Coins ===" << endl;
    adrCoin C = LC.first;
    while (C != NULL) {
        cout << "- " << C->info.code << " (" << C->info.name << ")" << endl;
        C = C->next;
    }
    cout << endl;
}

void showCoinOfExchange(ListListing LL, string eName) {
    cout << "=== Coins on Exchange: " << eName << " ===" << endl;
    adrListing L = LL.first;
    bool found = false;
    while (L != NULL) {
        if (L->exchangePtr->info.name == eName) {
            cout << "- " << L->coinPtr->info.code << " | Pair: " << L->pairName << endl;
            found = true;
        }
        L = L->next;
    }
    if (found == false) cout << "No coins found." << endl;
    cout << endl;
}

void showExchangeOfCoin(ListListing LL, string cCode) {
    cout << "=== Exchanges listing Coin: " << cCode << " ===" << endl;
    adrListing L = LL.first;
    bool found = false;
    while (L != NULL) {
        if (L->coinPtr->info.code == cCode) {
            cout << "- " << L->exchangePtr->info.name << " | Pair: " << L->pairName << endl;
            found = true;
        }
        L = L->next;
    }
    if (found == false) cout << "No exchanges found." << endl;
    cout << endl;
}

void showExchangeWithCoin(ListExchange LE, ListListing LL) {
    cout << "=== All Exchanges and their Coins ===" << endl;
    adrExchange E = LE.first;
    while (E != NULL) {
        cout << "[" << E->info.name << "]" << endl;
        adrListing L = LL.first;
        bool hasCoin = false;
        while (L != NULL) {
            if (L->exchangePtr == E) {
                cout << "   -> " << L->coinPtr->info.code << " (" << L->pairName << ")" << endl;
                hasCoin = true;
            }
            L = L->next;
        }
        if (hasCoin == false) cout << "   -> No listings" << endl;
        E = E->next;
    }
    cout << endl;
}

void showCoinWithExchange(ListCoin LC, ListListing LL) {
    cout << "=== All Coins and their Exchanges ===" << endl;
    adrCoin C = LC.first;
    while (C != NULL) {
        cout << "[" << C->info.code << "]" << endl;
        adrListing L = LL.first;
        bool hasExchange = false;
        while (L != NULL) {
            if (L->coinPtr == C) {
                cout << "   -> " << L->exchangePtr->info.name << " (" << L->pairName << ")" << endl;
                hasExchange = true;
            }
            L = L->next;
        }
        if (hasExchange == false) cout << "   -> Not listed anywhere" << endl;
        C = C->next;
    }
    cout << endl;
}

int countCoinOfExchange(ListListing LL, string eName) {
    int count = 0;
    adrListing L = LL.first;
    while (L != NULL) {
        if (L->exchangePtr->info.name == eName) {
            count++;
        }
        L = L->next;
    }
    return count;
}

int countExchangeOfCoin(ListListing LL, string cCode) {
    int count = 0;
    adrListing L = LL.first;
    while (L != NULL) {
        if (L->coinPtr->info.code == cCode) {
            count++;
        }
        L = L->next;
    }
    return count;
}

int countCoinNoExchange(ListCoin LC, ListListing LL) {
    int count = 0;
    adrCoin C = LC.first;
    while (C != NULL) {
        bool hasExchange = false;
        adrListing L = LL.first;
        while (L != NULL && hasExchange == false) {
            if (L->coinPtr == C) {
                hasExchange = true;
            } else {
                L = L->next;
            }
        }
        if (hasExchange == false) count++;
        C = C->next;
    }
    return count;
}

int countExchangeNoCoin(ListExchange LE, ListListing LL) {
    int count = 0;
    adrExchange E = LE.first;
    while (E != NULL) {
        bool hasCoin = false;
        adrListing L = LL.first;
        while (L != NULL && hasCoin == false) {
            if (L->exchangePtr == E) {
                hasCoin = true;
            } else {
                L = L->next;
            }
        }
        if (hasCoin == false) count++;
        E = E->next;
    }
    return count;
}

void editListingExchange(ListListing &LL, adrExchange oldE, adrExchange newE, adrCoin C) {
    adrListing L = LL.first;
    bool found = false;
    while (L != NULL && found == false) {
        if (L->exchangePtr == oldE && L->coinPtr == C) {
            L->exchangePtr = newE;
            found = true;
        } else {
            L = L->next;
        }
    }
}

void editListingCoin(ListListing &LL, adrExchange E, adrCoin oldC, adrCoin newC) {
    adrListing L = LL.first;
    bool found = false;
    while (L != NULL && found == false) {
        if (L->exchangePtr == E && L->coinPtr == oldC) {
            L->coinPtr = newC;
            found = true;
        } else {
            L = L->next;
        }
    }
}
