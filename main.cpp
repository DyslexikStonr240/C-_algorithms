#include "linked_list.h"

int main(){
    linked_list<int> list;
    for(int i = 0; i < 10; i++){
        list.create_node(i);
    }
    list.insert_node(100, 5);


    list.print();
}
