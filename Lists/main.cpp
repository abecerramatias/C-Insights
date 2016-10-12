//
//  main.cpp
//  Lists
//
//  Created by Alberto Becerra on 10/8/16.
//  Copyright © 2016 Alberto Becerra. All rights reserved.
//

#include <iostream>
using namespace std;

struct node {
    node* next;
    int data;
    explicit node(int data):node(nullptr, data){}
    node(node* head, int data):next(head), data(data){}
};

node* insert(node* head, int data){
    return new node(head, data);
}

node* insert_sorted(node* head, int data){
    if (nullptr == head || data <= head->data){
        return new node(head, data);
    }
    
    auto current = head;
    while(nullptr != current->next && (current->next->data < data)){
        current = current->next;
    }
    
    if(nullptr == current->next){
        current->next = new node(data);
    } else {
        current->next = new node(current->next, data);
    }
    return head;
}

node* find(node* head, int value){
    while(nullptr != head && head->data != value){
        head = head->next;
    }
    
    return head;
}

node* remove(node* head, node* target){
    if(head == target){
        head = head->next;
        delete target;
        return head;
    }
    
    auto temp = head;
    while(nullptr != temp->next && target != temp->next){
        temp = temp->next;
    }
    
    if(target == temp->next){
        temp->next = temp->next->next;
        delete target;
    }
    
    return head;    
}

void print_list(node* list){
    while(list->next != nullptr){
        cout << list->data << "\n";
        list = list->next;
    }
}

int main(int argc, const char * argv[]) {
    
    node* simple_list = new node(2);
    simple_list = insert(simple_list, 4);
    simple_list = insert(simple_list, 6);
    simple_list = insert(simple_list, 8);
    simple_list = insert(simple_list, 1);
    simple_list = insert(simple_list, 3);
    simple_list = insert(simple_list, 5);
    //print_list(simple_list);
    
    node* sorted_list = new node(2);
    sorted_list = insert_sorted(sorted_list, 4);
    sorted_list = insert_sorted(sorted_list, 6);
    sorted_list = insert_sorted(sorted_list, 8);
    node* to_remove = sorted_list;
    sorted_list = insert_sorted(sorted_list, 1);
    sorted_list = insert_sorted(sorted_list, 3);
    sorted_list = insert_sorted(sorted_list, 5);
    print_list(sorted_list);
    node* updated_list = remove(sorted_list, to_remove);
    cout << "\n\n";
    print_list(updated_list);
    return 0;
}
