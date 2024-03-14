#include<iostream>
#include<vector>
#include<unordered_map>
#include<deque>
using namespace std;


struct DoubleDirectList {
    DoubleDirectList* pre;
    DoubleDirectList* next;
    int value;
    int key;
    DoubleDirectList(int key,int value): key(key),value(value) {}
    DoubleDirectList():key(0),value(0) {}
};

class LRUCache {
public:

    unordered_map<int,DoubleDirectList*> hash;
    int len;
    DoubleDirectList* head;
    DoubleDirectList* end;
    int size = 0;
    LRUCache(int capacity) {
        len = capacity;
        head = new DoubleDirectList();
        end = new DoubleDirectList();
        head->next = end;
        end->pre = head;
    }
    
    int get(int key) {
        if(hash.count(key)) {
            DoubleDirectList* temp = hash[key];
            temp->pre->next = temp->next;
            temp->next->pre = temp->pre;
            temp->pre = head;
            temp->next = head->next;
            head->next->pre = temp;
            head->next = temp;
            return temp->value;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if(hash.count(key)) {
            if(hash[key]->value != value) {
                hash[key]->value = value;
                 DoubleDirectList* temp = hash[key];
            temp->pre->next = temp->next;
            temp->next->pre = temp->pre;
            temp->pre = head;
            temp->next = head->next;
            head->next->pre = temp;
            head->next = temp;

                return;
            }
        }else{
            if(size < len) {
                DoubleDirectList* list = new DoubleDirectList(key,value);
                hash[key] = list;
                list->next = head->next;
                head->next->pre = list;
                list->pre = head;
                head->next = list;
                size++;
            }else{
                DoubleDirectList* temp = end->pre;
                temp->pre->next = end;
                end->pre = temp->pre;
                hash.erase(temp->key);

                temp->key = key;
                temp->value = value;
                hash[key] = temp;
                temp->next = head->next;
                head->next->pre = temp;
                temp->pre = head;
                head->next = temp;
            }

        }
    }
};
