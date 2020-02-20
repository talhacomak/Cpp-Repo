#include <iostream> 
#include <sstream> 
#include <vector>
#include <fstream>
using namespace std; 

struct node{ // node of the minHeap
	int value; 		// time of Event
	string name;	// name of Event
	string state;	// start or end
};

void swap(node *x, node *y){	// swapping two node
	node temp = *x;
	*x = *y;
	*y = temp;
}

class minHeap {
	vector <node*> heap;	// store the heap
	int count;	// number of elements of heap vector
public:
	minHeap(){	// initialize
		count = 0;
	}
	int parent(int i){ 	// parent of a node
		return (i-1)/2;
	}
	int left(int i){ 	// left child of a node
		return (2*i + 1);
	}
	int right(int i){	// right child of a node
		return (2*i + 2);
	}
	int get_count(){	// gives the number of elements in the heap
		return count;
	}
	
	node* extractMin(){		// gives the root (min. element in the heap) and heapify process
		if (count <= 0){
			return NULL;
		}
		if (count == 1){
			count--;
			return heap[0];
		}
		node* root = heap[0];
		heap[0] = heap[count-1];
		count--;
		minHeapify(0);
		return root;
	}
	
	void minHeapify(int i){		// process of heap sort
		int l = left(i);
		int r = right(i);
		int smallest = i;
		if (l < count && heap[l]->value < heap[i]->value)
			smallest = l;
		if (r < count && heap[r]->value < heap[smallest]->value)
			smallest = r;
		if (smallest != i){
			swap(heap[i], heap[smallest]);
			minHeapify(smallest);
		}
	}

	void insertNode(string name, int value, string state) {		// inserts given node to heap according to min. heap
		node* newnode = new node;
		newnode->name = name;
		newnode->value = value;
		newnode->state = state;
		count++;
		int i = count - 1;
		heap.push_back(newnode);
		while (i != 0 && heap[parent(i)]->value > heap[i]->value){ 
			swap(heap[i], heap[parent(i)]);
			i = parent(i);
		}
	}
};

int main(int argv, char* argc[]){

	minHeap heap;
	
	if(argv == 1){	// if there is no arguments
		cout << "Enter a parameter!";
		return 1;
	}
	ifstream array(argc[1]);
	if (!array.is_open()) {		// if the file not found 
		cout << argc[1] << " cannot open!\n" << endl;
		return 1;
	}
	string str; 
	int start, end;
	string name;
	int max = 0;
	while (!array.eof()){	// reading the file
		getline(array, str);	// line by line reading
		stringstream ss;
		ss<<str;
		if(ss.str() == "" || ss.str() == " ") continue; // if there is a reduntant line
		ss>>name;
		ss>>start;
		ss>>end;
		ss.str(std::string());
		if(end > max){ 	// finding the max. elemenent in the heap
			max = end;
		}
		heap.insertNode(name, start, "STARTED");	// start of the event is inserting to heap
		heap.insertNode(name, end, "ENDED");	// end of the event is inserting the heap
	}
	if(heap.get_count() == 0){		// if no event found in the file
		cout<< "No Event Found!";
		return 1;
	}
	
	node* n;
	int previous = -1;
	n = heap.extractMin(); // first element
	for (int i=1; i <= max; i++){	// time loop 1 to max. end time int the heap
		if (n->value == i) {	// if the time is equal to event time
			cout<< "TIME "<<i<< ": "<< n->name << " " << n->state<<endl;
			previous = n->value;	// storing the time
			n = heap.extractMin();	// getting next element
			if(n != NULL && previous == n->value) i--;	// if the next element is exist and time of event is equal to current time, time will not increase
		}
		else{
			cout<< "TIME "<<i<< ": NO EVENT"<<endl;
		}
		if(i == max) cout<< "TIME "<< i <<": NO MORE EVENTS, SCHEDULER EXITS";
 	}
	return 0;
}
