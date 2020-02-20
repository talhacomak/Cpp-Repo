#include <iostream>

#define MAX_OPERATOR_SIZE 1000

using namespace std;

class Operator {
	int center_x;
	int center_y;
	int op_size;
	public:
	Operator(int x, int y, int size){
		center_x = x;
		center_y = y;
		op_size = size;
	}
	
	void reset(int new_x, int new_y, int new_size){
		center_x = new_x;
		center_y = new_y;
		op_size = new_size;
	}
	void set_x(int new_x){
		center_x = new_x;
	}
	int get_x(){
		return center_x;
	}
	void set_y(int new_y){
		center_y = new_y;
	}
	int get_y(){
		return center_y;
	}
	void set_size(int new_size){
		op_size = new_size;
	}
	int get_size(){
		return op_size;
	}
};

class ArithmeticOperator: public Operator {
	char sign;
	public:
	ArithmeticOperator(int x, int y, int size, char sign): Operator(x, y, size){
        if(sign != 'x' && sign != '/' && sign != '+' && sign != '-') cout << "SIGN parameter is invalid!" << endl;
		else this->sign = sign;
	}
	char get_sign(){
		return sign;
	}
	void print_operator(){
		cout<<"ARITHMETIC_OPERATOR["<<sign<<"], CENTER_LOCATION["<<get_x()+1<<","<<get_y()+1<<"], SIZE["<<get_size()<<"]"<<endl;
	}
};


class OperatorGrid{
	int grid_rows;
	int grid_cols;
	char **grid;
	int num_operators;
	ArithmeticOperator *operators[MAX_OPERATOR_SIZE];
	public:
	OperatorGrid(int rows, int cols){
		grid_rows = rows;
		grid_cols = cols;
		grid = new char*[rows];
		for(int i=0; i<rows; i++){
			grid[i] = new char[cols];
			for(int j=0; j<cols; j++){
				grid[i][j] = '\0';
			}
		}
		num_operators = 0;
		for(int i=0; i<MAX_OPERATOR_SIZE; i++){
			operators[i] = NULL;
		}
	}
	~OperatorGrid(){
		cout<<"DESTRUCTOR: GIVE BACK["<<grid_rows<<","<<grid_cols<<"] chars.\n";
		cout<<"DESTRUCTOR: GIVE BACK["<<num_operators<<"] Operators.\n";
		for(int i=0; i<grid_rows; i++){
			delete [] grid[i];
		}
		delete [] grid;
		for(int i=0; i<MAX_OPERATOR_SIZE; i++){
			delete [] operators[i];
		}
	}
	bool place_operator (ArithmeticOperator *op){
		int x = op->get_x();
		int y = op->get_y();
		int z = op->get_size();
		char cha = op->get_sign();
		x--;
        y--;
        int a = x, b = y, c = x, d = y, e = x, f = y, g = x, h = y;
        bool check1 = true;    // for cheking borders
        bool check = true;    // for cheking conflicts
        bool is_placed = false; // for cheking placed
        switch (cha) {
            case '/':
                // checking for borders
                if (x + z >= grid_rows || y + z >= grid_cols || x - z < 0 || y - z < 0) {
                    check1 = false;
                    cout << "BORDER ERROR: Operator " << cha << " with size " << z << " can not be placed on (" << x + 1
                         << "," << y + 1 << ")." << endl;
                }
                // checking for conflict
                if (x >= 0 && x < grid_rows && y >= 0 && y < grid_cols){
                    if(grid[x][y] != '\0') {
                        cout << "CONFLICT ERROR: Operator " << cha << " with size " << z << " can not be placed on ("
                         << x + 1 << "," << y + 1 << ")." << endl;
                        break;
                    }
                }
                for (int i = 0; i < z; i++) {
                    a--;
                    b++;
                    if (a >= grid_rows || b >= grid_cols || a<0 || b<0) break;
                    if (grid[a][b] != '\0') {
                        cout << "CONFLICT ERROR: Operator " << cha << " with size " << z << " can not be placed on ("
                             << x + 1 << "," << y + 1 << ")." << endl;
                        check = false;
                        break;
                    }
                }
                if (!check) break;
                for (int i = 0; i < z; i++) {
                    c++;
                    d--;
                    if (c >= grid_rows || d >= grid_cols || c<0 || d<0) break;
                    if (grid[c][d] != '\0') {
                        cout << "CONFLICT ERROR: Operator " << cha << " with size " << z << " can not be placed on ("
                             << x + 1 << "," << y + 1 << ")." << endl;
                        check = false;
                        break;
                    }
                }
                if (!check) break;
                if (!check1) break;


                // placing
                a = c = x;
                b = d = y;
                grid[x][y] = '/';
                for (int i = 0; i < z; i++) {
                    a--;
                    b++;
                    grid[a][b] = '/';
                }
                for (int i = 0; i < z; i++) {
                    c++;
                    d--;
                    grid[c][d] = '/';
                }
                cout << "SUCCESS: Operator " << cha << " with size " << z << " is placed on (" << x + 1 << "," << y + 1
                     << ")." << endl;
                is_placed = true;
                break;


            case 'x':
                // checking for borders
                if (x + z >= grid_rows || y + z >= grid_cols || x - z < 0 || y - z < 0) {
                    check1 = false;
                    cout << "BORDER ERROR: Operator " << cha << " with size " << z << " can not be placed on (" << x + 1
                         << "," << y + 1 << ")." << endl;
                }
                // checking for conflict
                if (x >= 0 && x < grid_rows && y >= 0 && y < grid_cols){
                    if (grid[x][y] != '\0') {
                        cout << "CONFLICT ERROR: Operator " << cha << " with size " << z << " can not be placed on ("
                         << x + 1 << "," << y + 1 << ")." << endl;
                        break;
                    }
                }
                for (int i = 0; i < z; i++) {
                    a++;
                    b++;
                    if (a >= grid_rows || b >= grid_cols || a<0 || b<0) break;
                    if (grid[a][b] != '\0') {
                        cout << "CONFLICT ERROR: Operator " << cha << " with size " << z << " can not be placed on ("
                             << x + 1 << "," << y + 1 << ")." << endl;
                        check = false;
                        break;
                    }
                }
                if (!check) break;

                for (int i = 0; i < z; i++) {
                    c++;
                    d--;
                    if (c >= grid_rows || d >= grid_cols || c<0 || d<0) break;
                    if (grid[c][d] != '\0') {
                        cout << "CONFLICT ERROR: Operator " << cha << " with size " << z << " can not be placed on ("
                             << x + 1 << "," << y + 1 << ")." << endl;
                        check = false;
                        break;
                    }
                }
                if (!check) break;
                for (int i = 0; i < z; i++) {
                    e--;
                    f++;
                    if (e >= grid_rows || f >= grid_cols || e<0 || f<0) break;
                    if (grid[e][f] != '\0') {
                        cout << "CONFLICT ERROR: Operator " << cha << " with size " << z << " can not be placed on ("
                             << x + 1 << "," << y + 1 << ")." << endl;
                        check = false;
                        break;
                    }
                }
                if (!check) break;
                for (int i = 0; i < z; i++) {
                    g--;
                    h--;
                    if (g >= grid_rows || h >= grid_cols || g<0 || h<0) break;
                    if (grid[g][h] != '\0') {
                        cout << "CONFLICT ERROR: Operator " << cha << " with size " << z << " can not be placed on ("
                             << x + 1 << "," << y + 1 << ")." << endl;
                        check = false;
                        break;
                    }
                }
                if (!check) break;
                if (!check1) break;


                // placing
                a = c = e = g = x;
                b = d = f = h = y;
                grid[x][y] = 'x';
                for (int i = 0; i < z; i++) {
                    a++;
                    b++;
                    grid[a][b] = 'x';
                }
                for (int i = 0; i < z; i++) {
                    c++;
                    d--;
                    grid[c][d] = 'x';
                }
                for (int i = 0; i < z; i++) {
                    e--;
                    f++;
                    grid[e][f] = 'x';
                }
                for (int i = 0; i < z; i++) {
                    g--;
                    h--;
                    grid[g][h] = 'x';
                }
                cout << "SUCCESS: Operator " << cha << " with size " << z << " is placed on (" << x + 1 << "," << y + 1
                     << ")." << endl;
                is_placed = true;
                break;


            case '+':
                // checking for borders
                if (x + z >= grid_rows || y + z >= grid_cols || x - z < 0 || y - z < 0) {
                    check1 = false;
                    cout << "BORDER ERROR: Operator " << cha << " with size " << z << " can not be placed on (" << x + 1
                         << "," << y + 1 << ")." << endl;
                }
                // checking for conflict
                if (x >= 0 && x < grid_rows && y >= 0 && y < grid_cols){
                    if (grid[x][y] != '\0') {
                        cout << "CONFLICT ERROR: Operator " << cha << " with size " << z << " can not be placed on ("
                             << x + 1 << "," << y + 1 << ")." << endl;
                        break;
                    }
                }
                for (int i = 0; i < z; i++) {
                    a++;
                    if (a >= grid_rows || b >= grid_cols || a<0 || b<0) break;
                    if (grid[a][b] != '\0') {
                        cout << "CONFLICT ERROR: Operator " << cha << " with size " << z << " can not be placed on ("
                             << x + 1 << "," << y + 1 << ")." << endl;
                        check = false;
                        break;
                    }
                }
                if (!check) break;
                for (int i = 0; i < z; i++) {
                    d++;
                    if (c >= grid_rows || d >= grid_cols || c<0 || d<0) break;
                    if (grid[c][d] != '\0') {
                        cout << "CONFLICT ERROR: Operator " << cha << " with size " << z << " can not be placed on ("
                             << x + 1 << "," << y + 1 << ")." << endl;
                        check = false;
                        break;
                    }
                }
                if (!check) break;
                for (int i = 0; i < z; i++) {
                    e--;
                    if (e >= grid_rows || f >= grid_cols || e<0 || f<0) break;
                    if (grid[e][f] != '\0') {
                        cout << "CONFLICT ERROR: Operator " << cha << " with size " << z << " can not be placed on ("
                             << x + 1 << "," << y + 1 << ")." << endl;
                        check = false;
                        break;
                    }
                }
                if (!check) break;
                for (int i = 0; i < z; i++) {
                    h--;
                    if (g >= grid_rows || h >= grid_cols || g<0 || h<0) break;
                    if (grid[g][h] != '\0') {
                        cout << "CONFLICT ERROR: Operator " << cha << " with size " << z << " can not be placed on ("
                             << x + 1 << "," << y + 1 << ")." << endl;
                        check = false;
                        break;
                    }
                }
                if (!check) break;
                if (!check1) break;


                // placing
                a = c = e = g = x;
                b = d = f = h = y;
                grid[x][y] = '+';
                for (int i = 0; i < z; i++) {
                    a++;
                    grid[a][b] = '+';
                }
                for (int i = 0; i < z; i++) {
                    d++;
                    grid[c][d] = '+';
                }
                for (int i = 0; i < z; i++) {
                    e--;
                    grid[e][f] = '+';
                }
                for (int i = 0; i < z; i++) {
                    h--;
                    grid[g][h] = '+';
                }
                cout << "SUCCESS: Operator " << cha << " with size " << z << " is placed on (" << x + 1 << "," << y + 1
                     << ")." << endl;
                is_placed = true;
                break;


            case '-':
                // checking for borders
                if (y + z >= grid_cols || y - z < 0 || x < 0 || x >= grid_rows) {
                    check1 = false;
                    cout << "BORDER ERROR: Operator " << cha << " with size " << z << " can not be placed on (" << x + 1
                         << "," << y + 1 << ")." << endl;
                }
                // checking for conflict
                if (x >= 0 && x < grid_rows && y >= 0 && y < grid_cols){
                    if (grid[x][y] != '\0') {
                        cout << "CONFLICT ERROR: Operator " << cha << " with size " << z << " can not be placed on ("
                             << x + 1 << "," << y + 1 << ")." << endl;
                        break;
                    }
                }
                for (int i = 0; i < z; i++) {
                    b++;
                    if (a >= grid_rows || b >= grid_cols || a<0 || b<0) break;
                    if (grid[a][b] != '\0') {
                        cout << "CONFLICT ERROR: Operator " << cha << " with size " << z << " can not be placed on ("
                             << x + 1 << "," << y + 1 << ")." << endl;
                        check = false;
                        break;
                    }
                }
                if (!check) break;
                for (int i = 0; i < z; i++) {
                    d--;
                    if (c >= grid_rows || d >= grid_cols || c<0 || d<0) break;
                    if (grid[c][d] != '\0') {
                        cout << "CONFLICT ERROR: Operator " << cha << " with size " << z << " can not be placed on ("
                             << x + 1 << "," << y + 1 << ")." << endl;
                        check = false;
                        break;
                    }
                }
                if (!check) break;
                if (!check1) break;


                // placing
                a = c = x;
                b = d = y;
                grid[x][y] = '-';
                for (int i = 0; i < z; i++) {
                    b++;
                    grid[a][b] = '-';
                }
                for (int i = 0; i < z; i++) {
                    d--;
                    grid[c][d] = '-';
                }
                cout << "SUCCESS: Operator " << cha << " with size " << z << " is placed on (" << x + 1 << "," << y + 1
                     << ")." << endl;
                is_placed = true;
                break;

            default :
            	cout << "SIGN parameter is invalid!" << endl;
                break;
        }
        if(is_placed){
        	operators[num_operators] = new ArithmeticOperator(x, y, z, cha);
			num_operators++;
			return true;
		}
		return false;
	}
	bool move_operator (int x, int y, char direction, int move_by){
		x--;
        y--;
        bool check = true;
        bool check1 = true;
        int op_case;
        int z = move_by;
        int col = grid_cols;
        int row = grid_rows;
        bool find = false;
        int a = x, b = y, c = x, d = y, e = x, f = y, g = x, h = y;
        if (x >= row || x < 0 || y >= col || y < 0) {
            cout << "OUT OF GRID." << endl;
        }
        if (grid[x][y] == '\0') {
            cout << "THERE IS NO OPERATOR." << endl;
        } 
		else {
            switch (grid[x][y]) {
                case '/':
                    for (int i = 0;; i++) {
                        if (operators[i] == NULL) break;
                        if (operators[i]->get_x() == x && operators[i]->get_y() == y) {
                            find = true;
                            op_case = i;
                            break;
                        }
                    }
                    if (find) break;

                    while (true) {
                        bool loop = true;
                        a--;
                        b++;
                        if (a < 0 && b >= col) break; // are boundaries appopriate?
                        if (grid[a][b] == '/') { // is the same operator?
                            for (int i = 0;; i++) {    // is there an operator center ?
                                if (operators[i] == NULL) { // all centers of operators is checked. there is no match.
                                    break;
                                }
                                if (operators[i]->get_x() == a &&
                                    operators[i]->get_y() == b) { // there is a matched operator center
                                    if (operators[i]->get_size() < x - a) {   // this is not the searched operator center
                                        loop = false;
                                        break;
                                    } else {  // yes, it is found
                                        find = true;
                                        op_case = i;
                                        break;
                                    }
                                }
                            }
                            if (find) break;
                        } else break;
                        if (!loop) break;
                    }
                    if (find) break;

                    while (true) {
                        bool loop = true;
                        c++;
                        d--;
                        if (c >= row && d < 0) break;
                        if (grid[c][d] == '/') {
                            for (int i = 0;; i++) {
                                if (operators[i] == NULL) break;
                                if (operators[i]->get_x() == c && operators[i]->get_y() == d) {
                                    if (operators[i]->get_size() < c - x) {
                                        loop = false;
                                        break;
                                    } else {
                                        find = true;
                                        op_case = i;
                                        break;
                                    }
                                }
                            }
                        } else break;
                        if (find) break;
                        if (!loop) break;
                    }
                    break;

                case 'x':
                    for (int i = 0;; i++) {
                        if (operators[i] == NULL) break;
                        if (operators[i]->get_x() == x && operators[i]->get_y() == y) {
                            find = true;
                            op_case = i;
                            break;
                        }
                    }
                    if (find) break;

                    while (true) {
                        bool loop = true;
                        a++;
                        b++;
                        if (a >= row || b >= col) break;
                        if (grid[a][b] != 'x') break;
                        for (int i = 0;; i++) {
                            if (operators[i] == NULL) break;
                            if (operators[i]->get_x() == a && operators[i]->get_y() == b) {
                                if (operators[i]->get_size() < a - x) {
                                    loop = false;
                                    break;
                                } else {
                                    find = true;
                                    op_case = i;
                                    break;
                                }
                            }
                        }
                        if (find) break;
                        if (!loop) break;
                    }
                    if (find) break;

                    while (true) {
                        bool loop = true;
                        c--;
                        d--;
                        if (c < 0 || d < 0) break;
                        if (grid[c][d] != 'x') break;
                        for (int i = 0;; i++) {
                            if (operators[i] == NULL) break;
                            if (operators[i]->get_x() == c && operators[i]->get_y() == d) {
                                if (operators[i]->get_size() < x - c) {
                                    loop = false;
                                    break;
                                } else {
                                    find = true;
                                    op_case = i;
                                    break;
                                }
                            }
                        }
                        if (find) break;
                        if (!loop) break;
                    }
                    if (find) break;

                    while (true) {
                        bool loop = true;
                        e++;
                        f--;
                        if (e >= row || f < 0) break;
                        if (grid[e][f] != 'x') break;
                        for (int i = 0;; i++) {
                            if (operators[i] == NULL) break;
                            if (operators[i]->get_x() == e && operators[i]->get_y() == f) {
                                if (operators[i]->get_size() < e - x) {
                                    loop = false;
                                    break;
                                } else {
                                    find = true;
                                    op_case = i;
                                    break;
                                }
                            }
                        }
                        if (find) break;
                        if (!loop) break;
                    }
                    if (find) break;

                    while (true) {
                        bool loop = true;
                        g--;
                        h++;
                        if (g < 0 || h >= col) break;
                        if (grid[g][h] != 'x') break;
                        for (int i = 0;; i++) {
                            if (operators[i] == NULL) break;
                            if (operators[i]->get_x() == g && operators[i]->get_y() == h) {
                                if (operators[i]->get_size() < x - g) {
                                    loop = false;
                                    break;
                                } else {
                                    find = true;
                                    op_case = i;
                                    break;
                                }
                            }
                        }
                        if (find) break;
                        if (!loop) break;
                    }
                    break;

                case '+':
                    for (int i = 0;; i++) {
                        if (operators[i] == NULL) break;
                        if (operators[i]->get_x() == x && operators[i]->get_y() == y) {
                            find = true;
                            op_case = i;
                            break;
                        }
                    }
                    if (find) break;

                    while (true) {
                        bool loop = true;
                        a++;
                        if (a >= row) break;
                        if (grid[a][b] != '+') break;
                        for (int i = 0;; i++) {
                            if (operators[i] == NULL) break;
                            if (operators[i]->get_x() == a && operators[i]->get_y() == b) {
                                if (operators[i]->get_size() < a - x) {
                                    loop = false;
                                    break;
                                } else {
                                    find = true;
                                    op_case = i;
                                    break;
                                }
                            }
                        }
                        if (find) break;
                        if (!loop) break;
                    }
                    if (find) break;

                    while (true) {
                        bool loop = true;
                        c--;
                        if (c < 0) break;
                        if (grid[c][d] != '+') break;
                        for (int i = 0;; i++) {
                            if (operators[i] == NULL) break;
                            if (operators[i]->get_x() == c && operators[i]->get_y() == d) {
                                if (operators[i]->get_size() < x - c) {
                                    loop = false;
                                    break;
                                } else {
                                    find = true;
                                    op_case = i;
                                    break;
                                }
                            }
                        }
                        if (find) break;
                        if (!loop) break;
                    }
                    if (find) break;

                    while (true) {
                        bool loop = true;
                        f++;
                        if (f >= col) break;
                        if (grid[e][f] != '+') break;
                        for (int i = 0;; i++) {
                            if (operators[i] == NULL) break;
                            if (operators[i]->get_x() == e && operators[i]->get_y() == f) {
                                if (operators[i]->get_size() < f - y) {
                                    loop = false;
                                    break;
                                } else {
                                    find = true;
                                    op_case = i;
                                    break;
                                }
                            }
                        }
                        if (find) break;
                        if (!loop) break;
                    }
                    if (find) break;

                    while (true) {
                        bool loop = true;
                        h--;
                        if (h < 0) break;
                        if (grid[g][h] != '+') break;
                        for (int i = 0;; i++) {
                            if (operators[i] == NULL) break;
                            if (operators[i]->get_x() == g && operators[i]->get_y() == h) {
                                if (operators[i]->get_size() < y - h) {
                                    loop = false;
                                    break;
                                } else {
                                    find = true;
                                    op_case = i;
                                    break;
                                }
                            }
                        }
                        if (find) break;
                        if (!loop) break;
                    }
                    break;

                case '-':
                    for (int i = 0;; i++) {
                        if (operators[i] == NULL) break;
                        if (operators[i]->get_x() == x && operators[i]->get_y() == y) {
                            find = true;
                            op_case = i;
                            break;
                        }
                    }
                    if (find) break;

                    while (true) {
                        bool loop = true;
                        b++;
                        if (b >= col) break;
                        if (grid[a][b] != '-') break;
                        for (int i = 0;; i++) {
                            if (operators[i] == NULL) break;
                            if (operators[i]->get_x() == a && operators[i]->get_y() == b) {
                                if (operators[i]->get_size() < b - y) {
                                    loop = false;
                                    break;
                                } else {
                                    find = true;
                                    op_case = i;
                                    break;
                                }
                            }
                        }
                        if (find) break;
                        if (!loop) break;
                    }
                    if (find) break;

                    while (true) {
                        bool loop = true;
                        d--;
                        if (d < 0) break;
                        if (grid[c][d] != '-') break;
                        for (int i = 0;; i++) {
                            if (operators[i] == NULL) break;
                            if (operators[i]->get_x() == c && operators[i]->get_y() == d) {
                                if (operators[i]->get_size() < y - d) {
                                    loop = false;
                                    break;
                                } else {
                                    find = true;
                                    op_case = i;
                                    break;
                                }
                            }
                        }
                        if (find) break;
                        if (!loop) break;
                    }
                    break;
            }

            int j, a0, b0, c0, d0, e0, f0, g0, h0;
            int op_row, op_col;
            int k1 = 0, k2 = 0;

            if (direction == 'R') {
                a = c = e = g = op_row = operators[op_case]->get_x();
                b = d = f = h = op_col = operators[op_case]->get_y() + z;
                k2 = -z;
            } else if (direction == 'L') {
                a = c = e = g = op_row = operators[op_case]->get_x();
                b = d = f = h = op_col = operators[op_case]->get_y() - z;
                k2 = z;
            } else if (direction == 'D') {
                a = c = e = g = op_row = operators[op_case]->get_x() + z;
                b = d = f = h = op_col = operators[op_case]->get_y();
                k1 = -z;
            } else if (direction == 'U') {
                a = c = e = g = op_row = operators[op_case]->get_x() - z;
                b = d = f = h = op_col = operators[op_case]->get_y();
                k1 = z;
            }
            j = operators[op_case]->get_size();
            switch (operators[op_case]->get_sign()) {
                case '/' : //      '/' operator
                    // emptying
                    a0 = c0 = operators[op_case]->get_x();
                    b0 = d0 = operators[op_case]->get_y();
                    grid[a0][b0] = '\0';
                    for (int i = 0; i < operators[op_case]->get_size(); i++) {
                        a0--;
                        b0++;
                        grid[a0][b0] = '\0';
                    }
                    for (int i = 0; i < operators[op_case]->get_size(); i++) {
                        c0++;
                        d0--;
                        grid[c0][d0] = '\0';
                    }

                    // checking for borders
                    if (a + j >= row || b + j >= col || a - j < 0 || b - j < 0) {
                        cout << "BORDER ERROR: " << "/" << " can not be moved from (" << a + 1 + k1 << ","
                             << b + 1 + k2 << ") to (" << a + 1 << "," << b + 1 << ")." << endl;
                        check1 = false;
                    }

                        // checking for conflict
                    if (!(a >= row || b >= col || a < 0 || b < 0)){
                        if(grid[a][b] != '\0') {
                            cout << "CONFLICT ERROR: " << "/" << " can not be moved from (" << a + 1 + k1 << ","
                             << b + 1 + k2 << ") to (" << a + 1 << "," << b + 1 << ")." << endl;
                            check = false;
                        }
                    }

                    for (int i = 0; i < operators[op_case]->get_size(); i++) {
                        if (!check || (a >= row || b >= col || a < 0 || b < 0)) break;
                        a--;
                        b++;
                        if (a < 0 || b >= col) break;
                        if (grid[a][b] != '\0') {
                            cout << "CONFLICT ERROR: " << "/" << " can not be moved from (" << g + 1 + k1 << ","
                                 << h + k2 + 1 << ") to (" << g + 1 << "," << h + 1 << ")." << endl;
                            check = false;
                            break;
                        }
                    }

                    for (int i = 0; i < operators[op_case]->get_size(); i++) {
                        if (!check || (c >= row || d >= col || c < 0 || d < 0)) break;
                        c++;
                        d--;
                        if (c >= row || d < 0) break;
                        if (grid[c][d] != '\0') {
                            cout << "CONFLICT ERROR: " << "/" << " can not be moved from (" << g + 1 + k1 << ","
                                 << h + k2 + 1 << ") to (" << g + 1 << "," << h + 1 << ")." << endl;
                            check = false;
                            break;
                        }
                    }

                    //there was an error so filling back the emptied boxes
                    if (!check || !check1) {
                        a0 = c0 = operators[op_case]->get_x();
                        b0 = d0 = operators[op_case]->get_y();
                        grid[a0][b0] = '/';
                        for (int i = 0; i < operators[op_case]->get_size(); i++) {
                            a0--;
                            b0++;
                            grid[a0][b0] = '/';
                        }
                        for (int i = 0; i < operators[op_case]->get_size(); i++) {
                            c0++;
                            d0--;
                            grid[c0][d0] = '/';
                        }
                    } else {
                        // moving
                        a = c = e = g = op_row;
                        b = d = f = h = op_col;
                        operators[op_case]->set_x(op_row);
                        operators[op_case]->set_y(op_col);

                        grid[a][b] = '/';
                        for (int i = 0; i < operators[op_case]->get_size(); i++) {
                            a--;
                            b++;
                            grid[a][b] = '/';
                        }
                        for (int i = 0; i < operators[op_case]->get_size(); i++) {
                            c++;
                            d--;
                            grid[c][d] = '/';
                        }
                        cout << "SUCCESS: " << grid[c][d] << " moved from (" << op_row + 1 + k1 << ","
                             << op_col + k2 + 1 << ") to (" << op_row + 1 << "," << op_col + 1 << ")." << endl;
                    }
                    break;

                case 'x' :  // x operator
                    //emptying
                    a0 = c0 = e0 = g0 = operators[op_case]->get_x();
                    b0 = d0 = f0 = h0 = operators[op_case]->get_y();
                    grid[a0][b0] = '\0';
                    for (int i = 0; i < operators[op_case]->get_size(); i++) {
                        a0++;
                        b0++;
                        grid[a0][b0] = '\0';
                    }
                    for (int i = 0; i < operators[op_case]->get_size(); i++) {
                        c0++;
                        d0--;
                        grid[c0][d0] = '\0';
                    }
                    for (int i = 0; i < operators[op_case]->get_size(); i++) {
                        e0--;
                        f0++;
                        grid[e0][f0] = '\0';
                    }
                    for (int i = 0; i < operators[op_case]->get_size(); i++) {
                        g0--;
                        h0--;
                        grid[g0][h0] = '\0';
                    }

                    // checking for borders
                    if (a + j >= row || b + j >= col || a - j < 0 || b - j < 0) {
                        check1 = false;
                        cout << "BORDER ERROR: " << "x" << " can not be moved from (" << a + 1 + k1 << ","
                             << b + k2 + 1 << ") to (" << a + 1 << "," << b + 1 << ")." << endl;
                    }

                    // checking for conflict
                    if (!(a >= row || b >= col || a < 0 || b < 0)){
                        if(grid[a][b] != '\0') {
                            cout << "CONFLICT ERROR: " << "x" << " can not be moved from (" << g + 1 + k1 << ","
                             << h + k2 + 1 << ") to (" << g + 1 << "," << h + 1 << ")." << endl;
                            check = false;
                        }
                    }

                    for (int i = 0; i < operators[op_case]->get_size(); i++) {
                        if (!check || (a >= row || b >= col || a < 0 || b < 0)) break;
                        a++;
                        b++;
                        if (a >= row || b >= col) break;
                        if (grid[a][b] != '\0') {
                            cout << "CONFLICT ERROR: " << "x" << " can not be moved from (" << g + 1 + k1 << ","
                                 << h + k2 + 1 << ") to (" << g + 1 << "," << h + 1 << ")." << endl;
                            check = false;
                            break;
                        }
                    }

                    for (int i = 0; i < operators[op_case]->get_size(); i++) {
                        if (!check || (c >= row || d >= col || c < 0 || d < 0)) break;
                        c++;
                        d--;
                        if (c >= row || d < 0) break;
                        if (grid[c][d] != '\0') {
                            cout << "CONFLICT ERROR: " << "x" << " can not be moved from (" << g + k1 + 1 << ","
                                 << h + k2 + 1 << ") to (" << g + 1 << "," << h + 1 << ")." << endl;
                            check = false;
                            break;
                        }
                    }

                    for (int i = 0; i < operators[op_case]->get_size(); i++) {
                        if (!check || (e >= row || f >= col || e < 0 || f < 0)) break;
                        e--;
                        f++;
                        if (e < 0 || f >= col) break;
                        if (grid[e][f] != '\0') {
                            cout << "CONFLICT ERROR: " << "x" << " can not be moved from (" << g + 1 + k1 << ","
                                 << h + k2 + 1 << ") to (" << g + 1 << "," << h + 1 << ")." << endl;
                            check = false;
                            break;
                        }
                    }

                    for (int i = 0; i < operators[op_case]->get_size(); i++) {
                        if (!check || (g >= row || h >= col || g < 0 || h < 0)) break;
                        g--;
                        h--;
                        if (g < 0 || h < 0) break;
                        if (grid[g][h] != '\0') {
                            cout << "CONFLICT ERROR: " << "x" << " can not be moved from (" << op_row + 1 + k1
                                 << "," << op_col + k2 + 1 << ") to (" << op_row + 1 << "," << op_col + 1 << ")."
                                 << endl;
                            check = false;
                            break;
                        }
                    }

                    if (!check || !check1) {
                        // filling back the emptied boxes
                        a0 = c0 = e0 = g0 = operators[op_case]->get_x();
                        b0 = d0 = f0 = h0 = operators[op_case]->get_y();
                        grid[a0][b0] = 'x';
                        for (int i = 0; i < operators[op_case]->get_size(); i++) {
                            a0++;
                            b0++;
                            grid[a0][b0] = 'x';
                        }
                        for (int i = 0; i < operators[op_case]->get_size(); i++) {
                            c0++;
                            d0--;
                            grid[c0][d0] = 'x';
                        }
                        for (int i = 0; i < operators[op_case]->get_size(); i++) {
                            e0--;
                            f0++;
                            grid[e0][f0] = 'x';
                        }
                        for (int i = 0; i < operators[op_case]->get_size(); i++) {
                            g0--;
                            h0--;
                            grid[g0][h0] = 'x';
                        }
                    } else {
                        // moving
                        a = c = e = g = op_row;
                        b = d = f = h = op_col;
                        operators[op_case]->set_x(op_row);
                        operators[op_case]->set_y(op_col);

                        grid[a][b] = 'x';
                        for (int i = 0; i < operators[op_case]->get_size(); i++) {
                            a++;
                            b++;
                            grid[a][b] = 'x';
                        }
                        for (int i = 0; i < operators[op_case]->get_size(); i++) {
                            c++;
                            d--;
                            grid[c][d] = 'x';
                        }
                        for (int i = 0; i < operators[op_case]->get_size(); i++) {
                            e--;
                            f++;
                            grid[e][f] = 'x';
                        }
                        for (int i = 0; i < operators[op_case]->get_size(); i++) {
                            g--;
                            h--;
                            grid[g][h] = 'x';
                        }
                        cout << "SUCCESS: " << grid[g][h] << " moved from (" << op_row + 1 + k1 << ","
                             << op_col + k2 + 1 << ") to (" << op_row + 1 << "," << op_col + 1 << ")." << endl;
                    }

                    break;

                case '+' : // + operator
                    // emptying
                    a0 = c0 = e0 = g0 = operators[op_case]->get_x();
                    b0 = d0 = f0 = h0 = operators[op_case]->get_y();
                    grid[a0][b0] = '\0';
                    for (int i = 0; i < operators[op_case]->get_size(); i++) {
                        a0++;
                        grid[a0][b0] = '\0';
                    }
                    for (int i = 0; i < operators[op_case]->get_size(); i++) {
                        d0++;
                        grid[c0][d0] = '\0';
                    }
                    for (int i = 0; i < operators[op_case]->get_size(); i++) {
                        e0--;
                        grid[e0][f0] = '\0';
                    }
                    for (int i = 0; i < operators[op_case]->get_size(); i++) {
                        h0--;
                        grid[g0][h0] = '\0';
                    }

                    // checking for borders
                    if (a + j >= row || b + j >= col || a - j < 0 || b - j < 0) {
                        check1 = false;
                        cout << "BORDER ERROR: " << "+" << " can not be moved from (" << a + 1 + k1 << ","
                             << b + k2 + 1 << ") to (" << a + 1 << "," << b + 1 << ")." << endl;
                    }

                    // checking for conflict
                    if (!(a >= row || b >= col || a < 0 || b < 0)){
                        if(grid[a][b] != '\0') {
                            cout << "CONFLICT ERROR: " << "+" << " can not be moved from (" << op_row + 1 + k1 << ","
                             << op_col + k2 + 1 << ") to (" << op_row + 1 << "," << op_col + 1 << ")." << endl;
                            check = false;
                        }
                    }

                    for (int i = 0; i < operators[op_case]->get_size(); i++) {
                        if (!check || (a >= row || b >= col || a < 0 || b < 0)) break;
                        a++;
                        if (a >= row) break;
                        if (grid[a][b] != '\0') {
                            cout << "CONFLICT ERROR: " << "+" << " can not be moved from (" << op_row + 1 + k1
                                 << "," << op_col + k2 + 1 << ") to (" << op_row + 1 << "," << op_col + 1 << ")."
                                 << endl;
                            check = false;
                            break;
                        }
                    }

                    for (int i = 0; i < operators[op_case]->get_size(); i++) {
                        if (!check || (c >= row || d >= col || c < 0 || d < 0)) break;
                        d++;
                        if (d >= col) break;
                        if (grid[c][d] != '\0') {
                            cout << "CONFLICT ERROR: " << "+" << " can not be moved from (" << op_row + 1 + k1
                                 << "," << op_col + k2 + 1 << ") to (" << op_row + 1 << "," << op_col + 1 << ")."
                                 << endl;
                            check = false;
                            break;
                        }
                    }

                    for (int i = 0; i < operators[op_case]->get_size(); i++) {
                        if (!check || (e >= row || f >= col || e < 0 || f < 0)) break;
                        e--;
                        if (e < 0) break;
                        if (grid[e][f] != '\0') {
                            cout << "CONFLICT ERROR: " << "+" << " can not be moved from (" << op_row + 1 + k1
                                 << "," << op_col + k2 + 1 << ") to (" << op_row + 1 << "," << op_col + 1 << ")."
                                 << endl;
                            check = false;
                            break;
                        }
                    }

                    for (int i = 0; i < operators[op_case]->get_size(); i++) {
                        if (!check || (g >= row || h >= col || g < 0 || h < 0)) break;
                        h--;
                        if (h < 0) break;
                        if (grid[g][h] != '\0') {
                            cout << "CONFLICT ERROR: " << "+" << " can not be moved from (" << op_row + k1 + 1
                                 << "," << op_col + k2 + 1 << ") to (" << op_row + 1 << "," << op_col + 1 << ")."
                                 << endl;
                            check = false;
                            break;
                        }
                    }

                    // filling back the emptied boxes
                    if (!check || !check1) {
                        a0 = c0 = e0 = g0 = operators[op_case]->get_x();
                        b0 = d0 = f0 = h0 = operators[op_case]->get_y();
                        grid[a0][b0] = '+';
                        for (int i = 0; i < operators[op_case]->get_size(); i++) {
                            a0++;
                            grid[a0][b0] = '+';
                        }
                        for (int i = 0; i < operators[op_case]->get_size(); i++) {
                            d0++;
                            grid[c0][d0] = '+';
                        }
                        for (int i = 0; i < operators[op_case]->get_size(); i++) {
                            e0--;
                            grid[e0][f0] = '+';
                        }
                        for (int i = 0; i < operators[op_case]->get_size(); i++) {
                            h0--;
                            grid[g0][h0] = '+';
                        }
                    } else {
                        // moving
                        a = c = e = g = op_row;
                        b = d = f = h = op_col;
                        operators[op_case]->set_x(op_row);
                        operators[op_case]->set_y(op_col);

                        grid[a][b] = '+';
                        for (int i = 0; i < operators[op_case]->get_size(); i++) {
                            a++;
                            grid[a][b] = '+';
                        }
                        for (int i = 0; i < operators[op_case]->get_size(); i++) {
                            d++;
                            grid[c][d] = '+';
                        }
                        for (int i = 0; i < operators[op_case]->get_size(); i++) {
                            e--;
                            grid[e][f] = '+';
                        }
                        for (int i = 0; i < operators[op_case]->get_size(); i++) {
                            h--;
                            grid[g][h] = '+';
                        }
                        cout << "SUCCESS: " << grid[g][h] << " moved from (" << op_row + k1 + 1 << ","
                             << op_col + k2 + 1 << ") to (" << op_row + 1 << "," << op_col + 1 << ")." << endl;
                    }

                    break;

                case '-' : // - operator
                    // emptying
                    a0 = c0 = operators[op_case]->get_x();
                    b0 = d0 = operators[op_case]->get_y();
                    grid[a0][b0] = '\0';
                    for (int i = 0; i < operators[op_case]->get_size(); i++) {
                        b0++;
                        grid[a0][b0] = '\0';
                    }
                    for (int i = 0; i < operators[op_case]->get_size(); i++) {
                        d0--;
                        grid[c0][d0] = '\0';
                    }

                    // checking for borders
                    if (a >= row || b + j >= col || a < 0 || b - j < 0) {
                        check1 = false;
                        cout << "BORDER ERROR: " << "-" << " can not be moved from (" << a + 1 + k1 << ","
                             << b + k2 + 1 << ") to (" << a + 1 << "," << b + 1 << ")." << endl;
                    }

                    // checking for conflict
                    if (!(a >= row || b >= col || a < 0 || b < 0)){
                        if(grid[a][b] != '\0') {
                            cout << "CONFLICT ERROR: " << "-" << " can not be moved from (" << op_row + k1 + 1 << ","
                             << op_col + k2 + 1 << ") to (" << op_row + 1 << "," << op_col + 1 << ")." << endl;
                            check = false;
                        }
                    }
                    for (int i = 0; i < operators[op_case]->get_size(); i++) {
                        if (!check || (a >= row || b >= col || a < 0 || b < 0)) break;
                        b++;
                        if (b >= col) break;
                        if (grid[a][b] != '\0') {
                            cout << "CONFLICT ERROR: " << "-" << " can not be moved from (" << op_row + 1 + k1
                                 << "," << op_col + k2 + 1 << ") to (" << op_row + 1 << "," << op_col + 1 << ")."
                                 << endl;
                            check = false;
                            break;
                        }
                    }

                    for (int i = 0; i < operators[op_case]->get_size(); i++) {
                        if (!check || (c >= row || d >= col || c < 0 || d < 0)) break;
                        d--;
                        if (d < 0) break;
                        if (grid[c][d] != '\0') {
                            cout << "CONFLICT ERROR: " << "-" << " can not be moved from (" << op_row + 1 + k1
                                 << "," << op_col + k2 + 1 << ") to (" << op_row + 1 << "," << op_col + 1 << ")."
                                 << endl;
                            check = false;
                            break;
                        }
                    }

                    // filling back the emptied places
                    if (!check || !check1) {
                        a0 = c0 = operators[op_case]->get_x();
                        b0 = d0 = operators[op_case]->get_y();
                        grid[a0][b0] = '-';
                        for (int i = 0; i < operators[op_case]->get_size(); i++) {
                            b0++;
                            grid[a0][b0] = '-';
                        }
                        for (int i = 0; i < operators[op_case]->get_size(); i++) {
                            d0--;
                            grid[c0][d0] = '-';
                        }
                    } else {
                        // moving
                        a = c = e = g = op_row;
                        b = d = f = h = op_col;
                        operators[op_case]->set_x(op_row);
                        operators[op_case]->set_y(op_col);
                        grid[a][b] = '-';
                        for (int i = 0; i < operators[op_case]->get_size(); i++) {
                            b++;
                            grid[a][b] = '-';
                        }
                        for (int i = 0; i < operators[op_case]->get_size(); i++) {
                            d--;
                            grid[c][d] = '-';
                        }
                        cout << "SUCCESS: " << grid[c][d] << " moved from (" << op_row + 1 + k1 << ","
                             << op_col + k2 + 1 << ") to (" << op_row + 1 << "," << op_col + 1 << ")." << endl;
                    }

                    break;

                default :
                    cout << "WRONG INSTRUCTION" << endl;
                    break;
            }
        }
        if(check && check1) return true;
        else return false;
	}
	void print_operators(){
		for(int i=0; i<MAX_OPERATOR_SIZE; i++){
			if(operators[i] == NULL) break;
			operators[i]->print_operator();
		}
	}
};
