#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#define P true
#define B false

using namespace std;


class Pokemon{
	int HP;
	int PP;
	vector <int> *Attacks;
	public:
	Pokemon(vector <vector <int> > vec, int hp, int pp){
		HP = hp;
		PP = pp;
		Attacks = new vector <int> [4]; 
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				Attacks[i].push_back(vec[i][j]);
			}
		}
	}
	
	vector <int> *attack(){
		return Attacks;
	}
	
	int power(){
		return PP;
	}
	
	int Healthy(){
		return HP;
	}
};


struct pikachu_node{
	int HP;
	int PP;
};

struct blastoise_node{
	int HP;
	int PP;
};

struct Stats{
	bool turn;
	double prob;
	int level;
	bool isleaf;
};

struct fight{
	fight* up;
	pikachu_node pika;
	blastoise_node blas;
	Stats stats;
	int skill;
	bool efficient;
	void print(){
		cout << "P_HP: " << pika.HP << " P_PP: " << pika.PP << " B_HP: " << blas.HP << " B_PP: "  << blas.PP << " PROB: " << stats.prob << endl;
	}
};

class Graph {
	int V;
	vector <int> *adj;
	vector <int> toPrint;
	vector <int> *reverse;
	vector <fight> elements;
public:
	Graph(int V){
		this->V = V;
		reverse = new vector <int> [V]; 
		adj = new vector <int> [V]; 
	}
	void vertex(int V){
		this->V = V;
	}
	void addEdge(int v, int f){
		reverse[f].push_back(v);
		adj[v].push_back(f);
	}
	fight* give_me_the_element(int node_num){
		return &elements[node_num];
	}
	
	int print(){
		int result = (int)toPrint.size();
		return result;
	}
	
	void add_node(fight f){
		elements.push_back(f);
	}
	
	void prob_correct(int prob){
		int k=(int)elements.size()-1;
		for(int i = k; i>k-prob; i--){
			elements[i].stats.prob /= prob;
		}
	}
	
	void easy_path(int node_num, int level){
		vector <fight> print;
		print.push_back(elements[node_num]);
		double prob = elements[node_num].stats.prob;
		node_num = reverse[node_num][0];
		while(node_num != 0){
			print.push_back(elements[node_num]);
			node_num = reverse[node_num][0];
		}
		bool poke = P;
		string eff;
		string skill;
		for(int i = print.size()-1; i>=0; i--){
			if(poke){
				switch(print[i].skill){
					case 1:
						skill = "Thundershock";
						break;
					case 2:
						skill = "Skull Bash";
						break;
					case 3:
						skill = "Slam";
						break;
					case 4:
						skill = "Skip";
						break;
					default:
						skill = "error";
						break; 
				}
				if(print[i].efficient) eff = "efficient";
				else eff = "inefficient";
				cout<<"Pikachu used "<< skill << ". It's " << eff << ".\n"; 
			} 
			else{
				switch(print[i].skill){
					case 1:
						skill = "Tackle";
						break;
					case 2:
						skill = "Water Gun";
						break;
					case 3:
						skill = "Bite";
						break;
					case 4:
						skill = "Skip";
						break;
					default:
						skill = "error";
						break; 
				}
				if(print[i].efficient) eff = "efficient";
				else eff = "inefficient";
				cout<<"Blastoise used "<< skill << ". It's " << eff << ".\n"; 
			}
			poke = !poke;
		}
		cout<<endl << "Level count: " << level << endl << "Probability: "  << prob << endl;
		
	}
	
	void BFS(int s){
		int size = (int)elements.size();
		bool* discovered = new bool[size];
		for(int i = 0; i < size; i++) 
			discovered[i] = false;
		discovered[s] = true; 
		vector <int> L;
		L.push_back(s);
		
		int i = 0;
		
		while((int)L.size() > i){
			s = L[i]; 
			toPrint.push_back(s); 
	
			for (int j = 0; j < (int)adj[s].size(); ++j){
				int x = adj[s][j];
				if (!discovered[x])
				{
					discovered[x] = true;
					L.push_back(x);
				}
			}
			i+=1;
		}
	}
	void DFS_recur(int v, bool discovered[]){
	    discovered[v] = true; 
	    toPrint.push_back(v);  
	    for (int i = 0; i < (int)adj[v].size(); ++i){
	    	int x = adj[v][i];
	    	if (!discovered[x]) 
	            DFS_recur(x, discovered);
		}
	}
	
	void DFS(int v){
		int size = (int)elements.size();
	    bool *discovered = new bool[size];
	    for (int i = 0; i <size; i++)
	        discovered[i] = false;
	    DFS_recur(v, discovered);
	} 
};


int main(int argv, char* argc[]) {
	vector <vector <int> > pika(4);
	pika[0].push_back(-10);
	pika[0].push_back(100);
	pika[0].push_back(40);
	pika[0].push_back(0);
	pika[1].push_back(-15);
	pika[1].push_back(70);
	pika[1].push_back(50);
	pika[1].push_back(0);
	pika[2].push_back(-20);
	pika[2].push_back(80);
	pika[2].push_back(60);
	pika[2].push_back(0);
	pika[3].push_back(100);
	pika[3].push_back(100);
	pika[3].push_back(0);
	pika[3].push_back(3);
	
	vector <vector <int> > blas(4);
	blas[0].push_back(-10);
	blas[0].push_back(100);
	blas[0].push_back(30);
	blas[0].push_back(0);
	blas[1].push_back(-20);
	blas[1].push_back(100);
	blas[1].push_back(40);
	blas[1].push_back(0);
	blas[2].push_back(-25);
	blas[2].push_back(100);
	blas[2].push_back(60);
	blas[2].push_back(0);
	blas[3].push_back(100);
	blas[3].push_back(100);
	blas[3].push_back(0);
	blas[3].push_back(3);
	
	int pika_HP;
	int blas_HP;
	int max_level;
	int part;
	bool finish;
	bool poke;
	string algo;
	
	if(argc[1] == NULL || argc[2] == NULL) {
		cout << "No parameter!"<<endl;
		return 1;
	}
	
	switch(argc[1][4]){
		case '1':{
			pika_HP = 273;
			blas_HP = 361;
			max_level = atoi(argc[2]);
			part = 1;
			finish = false;
			break;
		}
		case '2':{
			if(argc[3] == NULL) {
				cout << "No parameter!"<<endl;
				return 1;
			}
			
			if(argc[3][0] == 'd'){
				algo = 'd';
			}
			else if(argc[3][0] == 'b'){
				algo = 'b';
			}
			else{
				cout<<"Invalid algorithm!\n"<<endl;
				return 1;
			}
			max_level = atoi(argc[2]);
			pika_HP = 200;
			blas_HP = 200;
			part = 2;
			finish = false;
			break;
		}
		case '3':{ // if you want to increase the HP values the fight will take longer, so if you want that the max_level value might need to be increased.
			max_level = 9;
			pika_HP = 200;
			blas_HP = 200;
			part = 3;
			finish = true;
			if(argc[2][0] == 'p' || argc[2][0] == 'P') poke = P; // for pikhachu
			else if(argc[2][0] == 'b' || argc[2][0] == 'B') poke = B; // for blastoise
			else {
				cout<< "Invalid Pokemon.\n";
				return 1;
			}
			break;
		}
		default:
			cout<<"Invalid part.\n";
			return 1;
			break;
	}
	
	Pokemon Pikachu(pika, pika_HP, 100);
	Pokemon Blastoist(blas, blas_HP, 100);
	
	vector <fight> *graph;
	graph = new vector <fight> [max_level+1];
	
	int node_size;
	if(max_level < 11){ // in my computer if the max_level greater than 12 that results bad alloc error.
		node_size = (int)pow(6.0, max_level);
	}
	else {
		if(max_level == 11) node_size = 23000000;
		if(max_level == 12) node_size = 81000000;
		else node_size = 100000000;
	}
	
	Graph gr(node_size);

	fight f;
	f.pika = {pika_HP,100};
	f.blas = {blas_HP, 100};
	f.stats = {P, 1, 0, 0};
	f.skill = 0;
	
	graph[0].push_back(f);
	gr.add_node(f);
	
	int current_level = 1;
	vector <int> *attack;
	bool turn = P;
	bool game_over_pika = false;
	bool game_over_blas = false;
	int easy = 0;
	
	int last_count = 0;
	int node_count = 1;
	for(int i=1; i<=max_level; i++){
		bool is_leaf;
		if(max_level > current_level) is_leaf = false;
		else is_leaf = true;
		int m = 0;
		for(int k = 0; k < (int)graph[current_level-1].size(); k++){
			if(graph[current_level-1][k].stats.isleaf){
				last_count++;
				continue;
			}
			if(turn == P){ // Pikachu attacks
				attack = Pikachu.attack();
				int prob = 0;
				for(int j =0; j<4; j++){
					f = graph[current_level-1][k];
					if (attack[j][3] <= current_level && -attack[0][0] < Pikachu.power()){
						if(attack[j][1] < 99.999999){
							f.pika.PP = f.pika.PP + attack[j][0];
							f.stats = {P, (((double)attack[j][1])/100)*f.stats.prob, current_level, is_leaf};
							if(f.blas.HP - attack[j][2] <= 0) {
								f.blas.HP = 0;
								f.stats.isleaf = true;
								if(!game_over_pika){
									game_over_pika = true;
									easy = node_count;
								}
							}
							else f.blas.HP = f.blas.HP - attack[j][2];
							f.skill = j+1;
							f.efficient = true;
							if(j==3) f.pika.PP +=100;
							graph[current_level].push_back(f);
							gr.addEdge(last_count, node_count);
							gr.add_node(f);
							node_count++;
							
							f = graph[current_level-1][k];
							f.skill = j+1;
							f.efficient = false;
							f.pika.PP = f.pika.PP + attack[j][0];
							f.stats = {P, (1-((double)attack[j][1])/100)*f.stats.prob, current_level, is_leaf};
							graph[current_level].push_back(f);
							gr.addEdge(last_count, node_count);
							gr.add_node(f);
							node_count++;
						}
						else {
							f.stats = {P, f.stats.prob, current_level, is_leaf};
							if(f.blas.HP - attack[j][2] <= 0) {
								f.blas.HP = 0;
								f.stats.isleaf = true;
								if(!game_over_pika){
									game_over_pika = true;
									easy = node_count;
								}
							}
							else f.blas.HP = f.blas.HP - attack[j][2];
							f.skill = j+1;
							f.efficient = true;
							f.pika.PP = f.pika.PP + attack[j][0];
							if(j==3) f.pika.PP +=100;
							graph[current_level].push_back(f);
							gr.addEdge(last_count, node_count);
							gr.add_node(f);
							node_count++;
						}
						prob++;
					}
				}
				for (; m<(int)graph[current_level].size(); m++){
					graph[current_level][m].stats.prob /= prob; 
				}
				gr.prob_correct(prob);
			}
			else{ // Blastoist attacks
				attack = Blastoist.attack();
				int prob = 0;
				for(int j=0; j<4; j++){
					f = graph[current_level-1][k];
					if (attack[j][3] <= current_level && -attack[0][0] < Blastoist.power()){
						if(attack[j][1] < 99.999999){
							f.blas.PP = f.blas.PP + attack[j][0];
							f.stats = {B, (((double)attack[j][1])/100)*f.stats.prob, current_level, is_leaf};
							if(f.pika.HP - attack[j][2] <= 0) {
								f.pika.HP = 0;
								f.stats.isleaf = true;
								if(!game_over_blas){
									game_over_blas = true;
									easy = node_count;
								}
							}
							else f.pika.HP = f.pika.HP - attack[j][2];
							f.skill = j+1;
							f.efficient = true;
							if(j==3) f.blas.PP +=100;
							graph[current_level].push_back(f);
							gr.addEdge(last_count, node_count);
							gr.add_node(f);
							node_count++;
							
							f = graph[current_level-1][k];
							f.blas.PP = f.blas.PP + attack[j][0];
							f.stats = {B, (1-((double)attack[j][1])/100)*f.stats.prob, current_level, is_leaf};
							f.skill = j+1;
							f.efficient = false;
							gr.addEdge(last_count, node_count);
							gr.add_node(f);
							node_count++;
							graph[current_level].push_back(f);
						}
						else {
							f.blas.PP = f.blas.PP + attack[j][0];
							f.stats = {B, f.stats.prob, current_level, is_leaf};
							if(f.pika.HP - attack[j][2] <= 0) {
								f.pika.HP = 0;
								f.stats.isleaf = true;
								if(!game_over_blas){
									game_over_blas = true;
									easy = node_count;
								}
							}
							else f.pika.HP = f.pika.HP - attack[j][2];
							f.skill = j+1;
							f.efficient = true;
							if(j==3) f.blas.PP +=100;
							gr.addEdge(last_count, node_count);
							gr.add_node(f);
							node_count++;
							graph[current_level].push_back(f);
						}
						prob++;
					}
				}
				for (; m<(int)graph[current_level].size(); m++){
					graph[current_level][m].stats.prob /= prob; 
				}
				gr.prob_correct(prob);
			}
			last_count++;
			if(finish){
				if(poke == P){
					if(game_over_pika) break;
				}
				else {
					if(game_over_blas) break;
				}
			}
		}
		current_level += 1;
		turn = !turn;
		if(finish){
			if(poke == P){
				if(game_over_pika) break;
			}
			else {
				if(game_over_blas) break;
			}
		}
	}
	gr.vertex(node_count);
	switch(part){
		case 1:{
			for(int j=0; j<(int)graph[max_level].size(); j++){
				graph[max_level][j].print();
				cout << endl;
			}
			cout << endl << endl;
			break;
		}
		case 2:{
			if(algo == "b"){
				clock_t start = clock();
				gr.BFS(0);
				cout<< "(BFS) Node count: " << gr.print()<< " Running time: "<<(double)(clock() - start)/CLOCKS_PER_SEC<<endl;
			}
			else{
				clock_t start2 = clock();
				gr.DFS(0);
				cout<< "(DFS) Node count: " << gr.print()<< " Running time: "<<(double)(clock() - start2)/CLOCKS_PER_SEC<<endl;
			}
			break;
		}
		case 3:{
			gr.easy_path(easy, current_level-1);
			break;
		}
		default:
			break;
	}
	
	
	return 0;
}
