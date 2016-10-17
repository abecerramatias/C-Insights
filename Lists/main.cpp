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
    //assuming that the target is not nullptr and the list is not empty
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

node* circular_insert (node* head, int data){
    auto insertion = new node(data);
    
    if(nullptr == head){
        insertion->next = insertion;
        return insertion;
    }
    
    if(head == head->next){
        head->next = insertion;
        insertion->next = head;
        return insertion;
    }
    
    std::swap(head->data, insertion->data);
    insertion->next = head->next;
    head->next = insertion;
    return head;
}

node* circular_find(node* head, int value){
    auto current = head;
    
    while(nullptr != current && current->data != value){
        current = current->next;
        if(current == head){
            return nullptr;
        }
    }
    
    return current;
}

node* circular_remove(node* head, node* target){
    if(head == head->next){
        delete head;
        return nullptr;
    }
    
    auto next = target->next;
    target->data = next->data;
    target->next = next->next;
    delete next;
    
    return target;
}

void print_list(node* list){
    while(list->next != nullptr){
        cout << list->data << "\n";
        list = list->next;
    }
}

void print_circular_list(node* list){
    node* temp = list;
    do
    {
        cout << temp->data << "\n";
        temp = temp->next;
    }
    while(temp != list);
}

int main(int argc, const char * argv[]) {
    
    node* simple_list = new node(2);
    simple_list = insert(simple_list, 4);
    simple_list = insert(simple_list, 6);
    simple_list = insert(simple_list, 8);
    simple_list = insert(simple_list, 1);
    simple_list = insert(simple_list, 3);
    simple_list = insert(simple_list, 5);
//    print_list(simple_list);
    
    node* sorted_list = new node(2);
    sorted_list = insert_sorted(sorted_list, 4);
    sorted_list = insert_sorted(sorted_list, 6);
    sorted_list = insert_sorted(sorted_list, 8);
    sorted_list = insert_sorted(sorted_list, 1);
    sorted_list = insert_sorted(sorted_list, 3);
    sorted_list = insert_sorted(sorted_list, 5);
//    print_list(sorted_list);
    
    node* circular_list = new node(2);
    circular_list->next = circular_list;
    circular_list = circular_insert(circular_list, 4);
    circular_list = circular_insert(circular_list, 6);
    circular_list = circular_insert(circular_list, 8);
    circular_list = circular_insert(circular_list, 1);
    circular_list = circular_insert(circular_list, 3);
    circular_list = circular_insert(circular_list, 5);
    print_circular_list(circular_list);
    
    node* node_to_remove = circular_find(circular_list, 6);
    circular_list = circular_remove(circular_list, node_to_remove);
    cout << "\n\n";
    print_circular_list(circular_list);
    return 0;
}
