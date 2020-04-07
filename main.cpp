#include <iostream>
#include <string>
#include<vector>


using namespace std;

unsigned int jenkins_one_at_a_time_hash(string key);

pair<string, string> initializePair();

void arrayAdd(vector<string> &hashTable, vector<pair<string, string>> &pairVector);

string
findElement(vector<string> &hashTable, pair<string, string> &myPair);

void linearPunching(int index, vector<string> &hashTable);


int SIZE = 100;

int main() {
    vector<string> hashTable(SIZE);
    vector<pair<string, string>> pairVector;
    initializePair();
    arrayAdd(hashTable, pairVector);
    linearPunching(2, hashTable);
    cout << "n = " << SIZE << endl;
    cout << "Searching for " << pairVector[SIZE / 2].second << " in vector" << endl;
    findElement(hashTable, pairVector[SIZE/2]);
}

unsigned int jenkins_one_at_a_time_hash(string key) {
    int i = 0;
    unsigned int hash = 0;
    while (i != key.length()) {
        hash += key[i++];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

pair<string, string> initializePair() {
    string symboleSet = "abcdefghijklmnop .";
    pair<string, string> myPair;
    for (int i = 0; i <= rand() % 20; i++) {
        myPair.first += symboleSet[rand() % symboleSet.length()];
    }
    for (int i = 0; i <= rand() % 200; i++) {
        myPair.second += symboleSet[rand() % symboleSet.length()];
    }
    return myPair;
}


void arrayAdd(vector<string> &hashTable, vector<pair<string, string>> &pairVector) {
    unsigned int hashKey;
    for (int i = 0; i < SIZE - 1; i++) {
        pairVector.push_back(initializePair());
        hashKey = jenkins_one_at_a_time_hash(pairVector[i].first) % hashTable.size();

        if (!hashTable[hashKey].empty()) {
            if (hashKey == hashTable.size() - 1) hashKey = 0;
            hashKey++;
        }
        hashTable[hashKey] = pairVector[i].second;
    }
}

string
findElement(vector<string> &hashTable, pair<string, string> &myPair) {
    unsigned int hashKey = jenkins_one_at_a_time_hash(myPair.first) % hashTable.size();
    int accesses = 0;
    int comparings = 0;

    if (hashTable[hashKey] != myPair.second) {
        comparings++;
        accesses++;

        if (!hashTable[hashKey].empty()) {
            accesses++;
            if (hashKey == hashTable.size() - 1) {
                hashKey = 0;
            }
            hashKey++;
        }
    }
    comparings++;
    accesses++;
    cout << "Accesses are " << accesses << endl;
    cout << "Comparings are " << comparings << endl;
    return hashTable[hashKey];
}

void linearPunching(int index, vector<string> &hashTable) {
    hashTable.erase(hashTable.begin() + index);
    hashTable[index] = "nothing";
}






