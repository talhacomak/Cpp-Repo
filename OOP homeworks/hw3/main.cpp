/* @Author
* Student Name: <Talha Çomak>
* Student ID : <150160726>
* Date: <08.05.2019> */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class stock{
	protected:
		double price;
		string name;
		int type;
		
	public:
		stock(double p, string n, int type){
			price = p;
			name = n;
			this->type = type;
		}
		virtual bool is_sufficient(int quantity){
			return true;
		}
		virtual void consume(int quantity){
			return;
		}
		string get_name(){
			return name;
		}
		double get_price(){
			return price;
		}
		int get_type(){
			return type;
		}
		virtual int get_count(){
			return 0;
		}
};

class type1 : public stock{
	int weight;
	public:
	type1(int c, double p, string n, int t) : stock(p, n, t) {
		weight = c; 
	}
	bool is_sufficient(int quantity){
		if(quantity > weight) return false;
		return true;
	}
	void consume(int quantity){
		weight -= quantity;
	}
	int get_count(){
		return weight;
	}
};

class type2 : public stock{
	int number;
	public:
	type2(int c, double p, string n, int t) : stock(p, n, t) {
		number = c;
	}
	bool is_sufficient(int quantity){
		if(quantity > number) return false;
		return true;
	}
	void consume(int quantity){
		number -= quantity;
	}
	int get_count(){
		return number;
	}
};

class type3 : public stock{
	int milliliter;
	public:
	type3(int c, double p, string n, int t) : stock(p, n, t) {
		milliliter = c;
	}
	bool is_sufficient(int quantity){
		if(quantity > milliliter) return false;
		return true;
	}
	void consume(int quantity){
		milliliter-= quantity;
	}
	int get_count(){
		return milliliter;
	}
};

struct ingredients{
	string name;
	int quantity;
};

class menu{
	string menu_name;
	vector <ingredients> ingre;
	double price;
  public:
  	menu(vector <ingredients> in, string name, stock** temp){
  		ingre.insert(ingre.begin(), in.begin(), in.end());
  		menu_name = name;
  		double pri=0;
  		for(int i=0; i<(int)ingre.size(); i++){
  			int j=0;
  			stock** temp2 = temp;
			while(temp2[j] != NULL){
				if(temp2[j]->get_name() == ingre[i].name){
					pri += ingre[i].quantity*temp2[j]->get_price();
					break;
				}
				j++;
			}
			
		}
		price = pri;
	}
	menu(string name, stock** temp2){
  		menu_name = name;
  		stock** temp = temp2;
  		int j = 0;
  		while(temp[j] != NULL){
			if(temp[j]->get_name() == menu_name){
				price = temp[j]->get_price();
				break;
			}
			j++;
		}
	}
	bool is_exist(int quantity, stock** temp){
		if(ingre.size() == 0) {
			stock** temp2 = temp;
			int j = 0;
	  		while(temp2[j] != NULL){
				if(temp2[j]->get_name() == menu_name){
					return temp[j]->is_sufficient(quantity);
				}
				j++;
			}
		}
		vector <int> vec, vec2;
		for(int i=0; i<(int)ingre.size(); i++){
  			int j=0;
  			stock** temp2 = temp;
  			
			while(temp2[j] != NULL){
				if(temp2[j]->get_name() == ingre[i].name){
					vec.push_back(i);
					vec2.push_back(j);
					if(!temp[j]->is_sufficient(quantity*ingre[i].quantity)) return false;
					break;
				}
				j++;
			}
		}
		for(int i=0; i<(int)vec.size(); i++){
			temp[vec2[i]]->consume(quantity*ingre[i].quantity);
		}
		return true;
	}
	double get_price(int quantity){
		return quantity*price;
	}
	string get_name(){
		return menu_name;
	}
};

int main(){
	string input;
	stock* stocks[1000];
	for(int i=0; i<1000; i++){
		stocks[i] = NULL;
	}
	fstream st;
	st.open("stock.txt");
	if(!st.is_open()){
		cerr<<"stock.txt could not open\n";
	}
	int i = 0;
	getline(st, input);
	while(getline(st, input)){
		stringstream ss;
		int type, count;
		double price;
		
		ss<<input;
		string name, surname;
		ss>>name;
		if(input[name.size()+1] < 47 || input[name.size()+1] > 58){
			ss>>surname;
			name += " ";
 			name += surname; 
		}
		ss>>type;
		ss>>count;
		ss>>price;
		switch(type){
			case 1:{
				type1* object = new type1(count, price, name, 1);
				stocks[i] = object;
				break;
			}
			case 2:{
				type2* object = new type2(count, price, name, 2);
				stocks[i] = object;
				break;
			}
			case 3:{
				type3* object = new type3(count, price, name, 3);
				stocks[i] = object;
				break;
			}
			default:{
				break;
			}
		}
		i++;
	}
	st.close();
	
	menu* in_menu[1000];
	for(i=0; i<1000; i++){
		in_menu[i] = NULL;
	}
	i=0;
	ifstream menu_pt("menu.txt");
	if(!menu_pt.is_open()){
		cerr<<"stock.txt could not open\n";
	}
	getline(menu_pt, input);
	while(getline(menu_pt, input)){
		stringstream ss;
		string name, surname;
		ss << input;
		ss >> name;
		if((input[name.size()+1] < 47 || input[name.size()+1] > 58) && input[name.size()+1] != 32 && input[name.size()+1] != 'N'){
			ss>>surname;
			name += " ";
 			name += surname; 
		}
		ss >> surname;
		if(surname[0] == 'N'){
			in_menu[i] = new menu(name, stocks);
			i++;
		}
		else {
			vector <ingredients> in;
			while(surname[surname.size()-1] != input[input.size()-1] || surname[surname.size()-2] != input[input.size()-2] || surname[surname.size()-3] != input[input.size()-3]){
				string x;
				while(surname[surname.size()-1] != ',' && (surname[surname.size()-1] != input[input.size()-1] || surname[surname.size()-2] != input[input.size()-2] || surname[surname.size()-3] != input[input.size()-3])){
					ss>>x;
					surname += " ";
					surname += x;
				}
				stringstream cc;
				cc << surname;
				int k, m, l = 0;
				cc >> k;
				m = k;
				while(m>0){
					m/=10;
					l++;
				}
				string control, result;
				result = surname;
				cc >> control;
				if(control == "gram"){
					result.erase(0, l+6);
				}
				else if(control == "ml"){
					result.erase(0, l+4);
				}
				else{
					result.erase(0, l+1);
				}
				if(surname[surname.size()-1] == ',') result.erase(result.size()-1,1);
				ingredients ingre;
				ingre.name = result;
				ingre.quantity = k;
				in.push_back(ingre);
				ss >> surname;
			}
			in_menu[i] = new menu(in, name, stocks);
			i++;
		}
	}
	menu_pt.close();
	
	ifstream order_pt("order.txt");
	int orders;
	getline(order_pt, input);
	int table = 1;
	while(order_pt>>orders){
		double total=0;
		getline(order_pt, input);
		cout<<"Table"<<table<<" ordered:\n";
		table++;
		for(i=0; i<orders; i++){
			string name;
			getline(order_pt, name);
			stringstream ss;
			ss<< name;
			int quantity, m, l=0;
			ss>>quantity;
			m = quantity;
			while(m>0){
				m/=10;
				l++;
			}
			name.erase(0, l+1);
			int j=0;
			while(in_menu[j] != NULL){
				if(in_menu[j]->get_name() == name){
					if(in_menu[j]->is_exist(quantity, stocks)){
						cout<<quantity<<" "<<name<<" cost: "<<in_menu[j]->get_price(quantity)<<endl;
						total += in_menu[j]->get_price(quantity);
					}
					else{
						cout<< "We don't have enough " << name <<endl;
						
						int h=quantity;
						while(h>0){
							if(in_menu[j]->is_exist(h, stocks)){
								cout<<h<<" "<<name<<" cost: "<<in_menu[j]->get_price(h)<<endl;
								total += in_menu[j]->get_price(h);
								break;
							}
							h--;
						}
					}
					break;
				}
				j++;
			}
		}
		cout<< "Tip is "<< total*15/100 <<endl;
		cout << "Total cost: " << total*123/100 << "TL" <<endl << "**************************"<<endl; 
		getline(order_pt, input);
	}
	order_pt.close();
	
	ofstream ofs("stock.txt");
	ofs<<"Name\tType\tItemCount\tPrice\n";
	for(i=0; stocks[i] != NULL; i++){
		ofs<<stocks[i]->get_name()<<"\t"<<stocks[i]->get_type()<<"\t"<<stocks[i]->get_count()<<"\t"<<stocks[i]->get_price()<<"\n";
	}
	
	return 0;
}
