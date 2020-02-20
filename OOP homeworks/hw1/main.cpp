/*  Talha Çomak
	150160726
*/
#include <iostream>
#include <fstream>
#include <vector>
#include "Vector.h"
#include "Polynomial.h"

using namespace std;

ostream& operator<<(ostream& os, Vector& vec){		// << operator overloading for Vector Class
    os << vec.print();
    return os;
}

ostream& operator<<(ostream& os, Polynom& pol){		// << operator overloading for Polynom Class
    os << pol.print();
    return os;
}

void possible_actions(){
	cout<<"Possible Actions:\n";
	cout<<"1. Print Polynomial and Vector lists\n";
	cout<<"2. Do a polynomial operation\n";
	cout<<"3. Do a vector operatoion\n";
	cout<<"4. Help: Print possible actions\n";
	cout<<"0. Exit the program\n\n\n";
}

int main(){
	int vec_size, poly_size, y, z; // y will use for get dimension of Vector, z is use for get elements
	ifstream vec("Vector.txt");
	if(!vec.is_open()){
		cout<<"Vector.txt cannot open!\n";
		return 1;
	}
	vec>>vec_size;

	vector <Vector*> vec_ar; // vector of Vector objects
	for(int i=0; i<vec_size; i++){
		vec>>y;
		int* ar = new int[y];
		for(int j=0; j<y; j++){
			vec>>z;
			ar[j] = z;
		}
		vec_ar.push_back(new Vector(ar, y)); // pushing Vector obejcts into the vector array
	}
	vec.close();

	ifstream poly("Polynomial.txt");
	if(!poly.is_open()){
		cout<<"Polynomial.txt cannot open!\n";
		return 1;
	}
	poly>>poly_size;
	
	vector <Polynom*> poly_ar;  // vector of Vector objects
	for(int i=0; i<poly_size; i++){
		poly>>y;
		int* ar = new int[y+1];
		for(int j=y; j>=0; j--){
			poly>>z;
			ar[j] = z;
		}
		poly_ar.push_back(new Polynom(ar, y)); 	// pushing Polynom obejcts into the vector array
	}
	poly.close();
	
	cout<<"Polynomial and Vector List Program!\n";
	cout<<"Polynomials and Vectors are read from text files!\n\n";
	cout<<"Possible Actions:\n";
	cout<<"1. Print Polynomial and Vector lists\n";
	cout<<"2. Do a polynomial operation\n";
	cout<<"3. Do a vector operatoion\n";
	cout<<"4. Help: Print possible actions\n";
	cout<<"0. Exit the program\n\n\n";
	int action = -1;
	int a, b;
	char c;
	while(action!=0){
		cout<<"Enter an option: ";
		cin>>action;
		while(cin.fail()){ // if user entered a character instead of integer
            cin.clear(); // clear input buffer to restore cin to a usable state
            cin.ignore(1000, '\n'); // ignore last input
            cout << "You can only enter numbers interval [0-4]!\n";
            cout << "Enter an option: ";
            cin >> action;
		}
		switch(action){
			case 0:
				break;
			case 1:
				cout<<"Vectors:\n";
				for(int i=0; i<vec_size; i++){
					cout<<i+1<<". ";
					cout<<*vec_ar[i]<<endl;
				}
				cout<<"\nPolynomials:\n";
				for(int i=0; i<poly_size; i++){
					cout<<i+1<<". "<<poly_ar[i][0]<< endl;
				}
				cout<<endl;
				break;
			case 2:
				cout<<"Which polynomial operation would you like to do?(+:addition, *:multiplication):\n";
				cin>>a>>c>>b;
				if(a<1 || a>poly_size || b<1 || b>poly_size){
					cout<<"Invalid operands!\n";
					break;
				}
				switch(c){
					case '+':{   // Polynomial addition
                        Polynom new_poly = *poly_ar[a-1] + *poly_ar[b-1];
                        cout<<"("<<*poly_ar[a-1]<<") + ("<<*poly_ar[b-1]<<") = "<<new_poly<<endl;
                        break;
					}
					case '*':{	 // Polynomial multiplication
                        Polynom new_poly = *poly_ar[a-1] * *poly_ar[b-1];
                        cout<<"("<<*poly_ar[a-1] <<") * ("<<*poly_ar[b-1]<< ") = "<<new_poly<<endl;
                        break;
					}
					default:
						cout<<"Invalid operation!\n";
						break;
				}
				break;
			case 3:
				cout<<"Which vector operation would you like to do?(+:addition, *:scalar multiplication, .:dot product):\n";
				cin>>a>>c>>b;
				if(a<1 || a>vec_size){
					cout<<"Invalid operands!\n";
					break;
				}
				switch(c){
					case '+':{		// Vector addition
						if(b<1 || b>vec_size){
							cout<<"Invalid operands!\n";
							break;
						}
                        Vector new_vec = *vec_ar[a-1] + *vec_ar[b-1];
                        cout<<*vec_ar[a-1] <<" + "<<*vec_ar[b-1]<< " = " <<new_vec<<endl;
                        break;
					}
					case '*':{		// Vector multiplication by an integer
                        Vector new_vec = *vec_ar[a-1]*b;
                        cout << *vec_ar[a-1] << " * " << b << " = " <<new_vec<<endl;
                        break;
					}
					case '.':{		// Vector dot product (scaler multiplication)
						if(b<1 || b>poly_size){
							cout<<"Invalid operands!\n";
							break;
						}
						if((*vec_ar[a-1]).getter_size() != (*vec_ar[b-1]).getter_size()) cout<<"Invalid operation!\n"; // if sizes of Vectors are not equal
						else cout << *vec_ar[a-1] << " . " << *vec_ar[b-1] << " = " << *vec_ar[a-1] * *vec_ar[b-1] <<endl;
                        break;
					}
					default:
						cout<<"Invalid operation!\n";
						break;
				}
				break;
			case 4:
				possible_actions();
				break;
			default:
				cout<<"Invalid option! Please enter a valid option.\n";
				break;
		}
	}
	poly_ar.clear(); // deleting elements of polynom vector
	vec_ar.clear();  // deleting elements of Vector vector
	return 0;
}
