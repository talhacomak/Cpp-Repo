#include <iostream>
#include <cstring>

using namespace std;

struct depo{
	char name[10];
	char surname[10];
	depo *next;
};

struct yakit{
	depo* head;
	void cre(){
		head = nullptr;
	}
	
	void al(depo* d1){
		depo* dep = new depo;
		*dep = *d1;
		dep->next = nullptr;
		if(head == nullptr){
			head = dep;
			return;
		}
		if(strcmp(dep->name, head->name) < 0){
			dep->next = head;
			head = dep;
			return;
		}
		depo* temp = head;
		while(temp->next){
			if(strcmp(d1->name, temp->next->name) < 0){
				dep->next = temp->next;
				temp->next = dep;
				return;
			}
			temp = temp->next;
		}
		temp->next = dep;
	}
	void read(int sira){
		depo* tail = head;
		if(sira == 1) {
			cout<<head->name << head->surname <<endl;
			return;
		}
		for(int i=1; i<sira; i++){
			if(!tail->next) {
				cout<<"number "<<sira<<" is not found."<<endl;
				return;
			}
			tail = tail->next;
		}
		cout << tail->name << tail->surname << endl;
	}
	
	void search(depo* d){
		if(!strcmp(d->name, head->name) && !strcmp(d->surname, head->surname)){
			cout<<"record is found."<<endl;
			return;
		}
		depo* tail = head->next;
		while(tail->name){
			if(!strcmp(d->name, tail->name) && !strcmp(d->surname, tail->surname)){
				cout<<"record is found."<<endl;
				return;
			}
			tail = tail->next;
		}
		cout<<"record is not found."<<endl;
	}
	
};

yakit yak;

void print_menu(){
	cout<<"******** MENU ********"<<endl;
	cout<<"Add a record: Press A"<<endl;
	cout<<"Read a record: Press R"<<endl;
	cout<<"Search a record: Press S"<<endl;
	cout<<"Press E for Exit."<<endl;
}
int main() {
	yak.cre();
	bool e = 1;
	while(e){
	print_menu();
	char c;
	cin>>c;
	depo d;
	if(c=='A'){
		cout<<"Enter a record: Name Surname"<<endl;
		cin>>d.name;
		cin>>d.surname;
		yak.al(&d);
	}
	else if(c == 'R'){
		int num;
		cout<<"Enter the record number: "<<endl;
		cin>>num;
		yak.read(num);
	}
	else if(c == 'S'){
		cout<<"Enter a record: Name Surname"<<endl;
		cin>>d.name;
		cin>>d.surname;
		yak.search(&d);
	}
	else if(c == 'E') e = 0;
	else cout<<"invalid value"<<endl;
	}
	return 0;
}
