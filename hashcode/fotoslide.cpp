#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct node
{
    vector <string> vec;
    int order;
    node *next; // pointer to the next node
};

struct list{
    node* head;
    void create(vector <string> v1, vector <string> v2){
        head = NULL;
        node* first = new node;
        node* sec = new node;
        for(int i=0; i<v1.size(); i++){
            first->vec.push_back(v1[i]);
        }
        for(int i=0; i<v2.size(); i++){
            sec->vec.push_back(v2[i]);
        }
        head = first;
        head->next = sec;
        sec->next = NULL;
    };
    void print(){
        node* temp = head;
        int k=0;
        while(temp){
            for(int i=0; i<temp->vec.size(); i++){
                k++;
            }
            temp = temp->next;
        }
        cout<<k;
    }
    bool add(vector <string> input){
        node* temp = head;
        node* temp2 = head->next;
        bool result = false, first_control = false;
        while(temp->next){
            for(int i=0; i<temp->vec.size(); i++){
                for(int j=0; j<input.size(); j++){
                    if(temp->vec[i] == input[j]){
                        first_control = true;
                    }
                }
            }
            if(first_control) {
                for (int i = 0; i < temp2->vec.size(); i++) {
                    for (int j = 0; j < input.size(); j++) {
                        if (temp2->vec[i] == input[j]) {
                            result = true;
                        }
                    }
                }
            }
            if(result) break;
            temp = temp->next;
            if(temp2->next != NULL) temp2 = temp2->next;
        }
        if(result) {
            node *new_node = new node;
            for(int i=0; i<input.size(); i++){
                new_node->vec.push_back(input[i]);
            }
            new_node->next = temp2;
            temp->next = new_node;
        } else{
            for(int i=0; i<temp->vec.size(); i++){
                for(int j=0; j<input.size(); j++){
                    if(temp->vec[i] == input[j]){
                        result = true;
                    }
                }
            }
            if(result) {
                node *new_node = new node;
                for(int i=0; i<input.size(); i++){
                    new_node->vec.push_back(input[i]);
                }
                new_node->next = NULL;
                temp->next = new_node;
            } else{
                temp = head;
                for(int i=0; i<temp->vec.size(); i++){
                    for(int j=0; j<input.size(); j++){
                        if(temp->vec[i] == input[j]){
                            result = true;
                        }
                    }
                }
                if(result) {
                    node *new_node = new node;
                    for(int i=0; i<input.size(); i++){
                        new_node->vec.push_back(input[i]);
                    }
                    new_node->next = head;
                    head = new_node;
                }
            }
        }
        return result;
    }
};

int main(int argc, char** argv){
    ifstream read(argv[1]);
    int row, column, a, b;
    char dir;
    string str;
    vector <vector <string>> vec;

    if(read.is_open()){
        read >> row;
        vec.resize(row);
        for(a = 0; a < row; a++){
            read >> dir;
            read >> column;
            for (b = 0; b < column; b++){
                read >> str;
                vec[a].push_back(str);
            }
        }
    }

    list mylist;
    bool control = false;
    for(int i = 0; i<vec.size(); i++){
        for(int j=i+1; j<vec.size(); j++){
            for(int k=0; k<vec[i].size(); k++){
                for(int m=0; m<vec[j].size(); m++){
                    if(vec[i][k] == vec[j][m]){
                        control = true;
                        mylist.create(vec[i], vec[j]);
                        vec.erase(vec.begin()+j);
                        vec.erase(vec.begin()+i);
                        break;
                    }
                }
                if(control) break;
            }
            if(control) break;
        }
        if(control) break;
    }
    for(int i = 0; i<7; i++){
        for(int j=0; j<vec.size(); j++){
            bool x = mylist.add(vec[j]);
            if(x){
                vec.erase(vec.begin()+j);
                j--;
            }
        }
    }
    mylist.print();
    return 0;
}
