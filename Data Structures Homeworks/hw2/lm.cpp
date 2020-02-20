/* @Author
* Student Name: <talha çomak>
* Student ID : <150160726>
* Date: <08.11.2018> */

#include <iostream>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

struct occur_node {   // store the co-occurence chars and their occurences
	char character;
	occur_node *next;
	int occurence;
};

struct vocab_node {  // store the character list and their co-occurences lists
	char character;
	vocab_node *next;
	occur_node *list;
};

struct vocab_list {   // vocabulary list
	vocab_node *head;
	void create(){      // creating the vocabulary list
		head = NULL; 
	}
	
	void print(){    // that function prints the vocabulary list   
		vocab_node* temp = head;
		while(temp){
			if(temp->character == 32){	    // if the character of vocabulary list is space
				cout << "<SP>" << ":" << endl;   // print <SP> :
			}
			else cout<< temp->character << ":" << endl;
			occur_node* temp2 = temp->list;
			while(temp2){
				if(temp2->character == 32){     // if the character of co-occurence list is space
					cout << "\t<" << "<SP>" << "," << temp2->occurence << ">" << endl;     // print <SP> , occurence of co-occur char
				}
				else cout << "\t<" << temp2->character << "," << temp2->occurence << ">" << endl;
				temp2 = temp2->next;
			}
			temp = temp->next;
		}
	}
	
	void add_char(char cha){  // that function adds the characters of given file to the vocabulary list according to alphabetic order
		vocab_node* newnode = new vocab_node; // creating new vocab_node for new character
		newnode->character = cha;
		newnode->next = NULL;
		newnode->list = NULL;
		if(head == NULL){  // if the vocabulary lis is null then the new character becomes the first element of list
			head = newnode;
			return;
		}
		if(cha == head->character) return; // if the new char and the first char are same 
		if(cha < head->character){  // if the new char comes before the old one
			newnode->next = head;	// new character's next pointer becomes head
			head = newnode;			// and head becomes new character's node
			return;
		}
		vocab_node* temp = head;	// creating a temprorary node to search the vocabulary list
		while(temp->next){ 
			if(cha == temp->next->character) return; // if the new char and the next one are same 
			if(cha < temp->next->character){	// if the new char comes before the next one
				newnode->next = temp->next;	  // new charachter's next pointer becomes the next one
				temp->next = newnode;		// and next character's node becomes the new charachter's node  
				return;
			}
			temp = temp->next;		  // temproray node becomes next node
		}
		temp->next = newnode;	// else the new char comes after the last one
	}
	
	void add_occurence(char first, char second){
		// find the first char
		bool found = false;
		if(first == head->character){
			found = true;
		}
		vocab_node* tail = head;
		while(!found && tail->next){
			tail = tail->next;
			if(first == tail->character){
				break;
			}
		}
		// find the second char
		if(tail->list == NULL){  	// if the co-occurence list is null
			tail->list = new occur_node;  // creating new co-occur node
			tail->list->character = second;	// adding the new co-occur char to the co-occurence list
			tail->list->occurence = 1;	// becouse of the new, we assigning one to occurence
			tail->list->next = NULL;
			return;
		}
		if(second == tail->list->character){  // if the co-occurence char already exist
			tail->list->occurence++; 	// increasing the occurence
			return;
		}
		occur_node* tempra = tail->list;
		while(tempra->next){
			if(second == tempra->next->character){	// if the co-occurence char already exist
				tempra->next->occurence++;		// increasing the occurence
				return;
			}
			tempra = tempra->next;
		}
		// if the co-occurence char is not exist 
		tempra->next = new occur_node;		// creating a new occur_node end of the list
		tempra->next->character = second;	// co-occurence char becomes the character of end of list
		tempra->next->occurence = 1;		// becouse of the new, we assigning one to occurence
		tempra->next->next = NULL;
	}
	
	int get_occurence(char x){    // return the occurence of given character from vocabulary list
		int total = 0;
		vocab_node* temp = head;
		while(temp){
			if(x == temp->character){
				occur_node* temp2 = temp->list;
				while(temp2){
					total += temp2->occurence;
					temp2 = temp2->next;
				}
				break;
			}
			temp = temp->next;
		}
		return total;
	}
	
	int get_union_occurence (char first, char sec){  // return the union occurence of given characters from occur_nodes of vocab_list
		int co_occur = 0;
		vocab_node* temp = head;
		while(temp){
			if(first == temp->character){
				occur_node* temp2 = temp->list;
				while(temp2){
					if(sec == temp2->character){
						co_occur = temp2->occurence;
						return co_occur;
					}
					temp2 = temp2->next;
				}
			}
			temp = temp->next;
		}
		return co_occur;
	}
};

struct language_model {
	vocab_list* vocabularylist;
	void readData (const char *filename){ // create, add_char, add_occurence
		vocabularylist = new vocab_list;	
		vocabularylist->create();		// creating the new vocabulary list
		ifstream pt(filename);
		if(!pt.is_open()){
			cout<< filename <<" file not found." <<endl;
			return;
		}
		char x, y;
		list <char> li;
		while(pt.get(x)){	// get a character from file
			if(x<32 || (x>90 && x<97) || x>122 ) continue;	// if the character is not the wanted char, continue to end of the loop
			if(x>31 && x<65){		// if the char is punctation or space,
				li.push_back(x);	// add the list which named li
				continue;			// then continue to end of the loop
			}
			if(x<91 && x>64) x += 32;		// if the char is uppercase letter, turn it the lowercase one
			vocabularylist->add_char(x);	// add the char to vocabulary list
		}
		
		vocab_node* temp;
		temp = vocabularylist->head;
		while(temp->next){
			temp = temp->next;
		}

		if(!li.empty()){    // if there is any punctation or space char in the li;
			li.sort();		// sort the chars in order to use unique 
			li.unique();	// delete the non-single characters
			vector <char> vec;
			vec.insert(vec.begin(), li.begin(), li.end());
			for(int i = 0; i<vec.size(); i++){		// and we can add that chars into the vocabulary list
				vocab_node* new_node = new vocab_node;
				new_node->character = vec[i];
				new_node->list = NULL;
				new_node->next = NULL;
				temp->next = new_node;
				temp = new_node;
			}
		}
		// in order to find characters occuring together 
		pt.clear();  // clear the stream
		pt.seekg(0); // rewind begining of stream
		
		pt.get(x);
		while( x<32 || (x>90 && x<97) || x>122 ){ // if the character is not the wanted char, continue to the loop while finding it
			pt.get(x);
		}
		
		if(x<91 && x>64) x += 32;	// if the char is uppercase letter, turn it the lowercase one
		
		while(pt.get(y)){
			if( y<32 || (y>90 && y<97) || y>122 ){ // if the character is not the wanted char
				while(pt.get(x)){           // continue to the loop while finding it
					if( x<32 || (x>90 && x<97) || x>122 ) continue;  // if the character is not the wanted char, continue to the loop while finding it
					if(x<91 && x>64) x += 32;  // if the char is uppercase letter, turn it the lowercase one
					break;
				}
				continue;
			}
			if(y<91 && y>64) y += 32;  // if the char is uppercase letter, turn it the lowercase one
			vocabularylist->add_occurence(x, y);
			x = y;
		}
	}
	
	double calculateProbability (char first, char sec){  // returns calculated probability of given two characters
		double a, b;
		if(first == 60) first = 32;  // if the first char is <SP>
		if(first == 60) first = 32;	 // if the sec char is <SP>
		a = vocabularylist->get_occurence(first);
		b = vocabularylist->get_union_occurence(first, sec);
		return b/a;
	}
};


int main(int argc, char** argv){
	language_model ptr;  // creating the language model
	if(!argv[1]){
		cout<<"No Parameter!";
		return 1;
	}
	ptr.readData(argv[1]);  // send the filename to readData function of language model
	if(argv[2] && argv[3]){ // if there are extra chars
		if(argv[2][0] == 34){
			if(argv[2][1]){
				if(argv[3][0] == 34){
					if(argv[3][1]){
						cout << ptr.calculateProbability(argv[2][1], argv[3][1]) << endl;
					}
					else cout << ptr.calculateProbability(argv[2][1], '"') << endl;
				}
			}
			else{
				if(argv[3][0] ==  34){
					if(argv[3][1]){
						cout << ptr.calculateProbability(argv[2][0], argv[3][1]) << endl;
					}
					else cout << ptr.calculateProbability(argv[2][0], '"') << endl;
				}
			}
		}
		else cout << ptr.calculateProbability(argv[2][0], argv[3][0]) << endl; // send them to the calculateProbability function of the language model
	}
	else ptr.vocabularylist->print();	// print the vocabulary list of language model
	return 0;
}
