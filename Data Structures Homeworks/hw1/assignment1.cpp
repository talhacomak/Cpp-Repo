#include <iostream>
#include <cstdio>

using namespace std;

int main(int argc, char **argv) {
    char array[23] = {'\0'};   // this array store the lines of txt files
    int x, y, z, row, col, op = 0;   
    char cha;
    FILE *fptr;
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("File not found.\n");
        return 1;
    }

    int operation[100000][4] = {0};   // this array store the coordinates of center of operators and its size in the grid
	
    fgets(array, 20, fptr);
    sscanf(array, "%d %d", &row, &col); 
    
    if (row<1 || col<1) {
    	cout<<"Grid is not created.";
    	return 1;
	}
    
    char **grid = new char *[row];
    for (int i = 0; i < row; i++) {
        grid[i] = new char[col];
        for (int j = 0; j < col; j++) {
            grid[i][j] = '\0';
        }
    }
    cout << "A grid is created: " << row << " " << col << endl;
    while (!feof(fptr)) {
        fgets(array, 9, fptr);
        if(array[0] == ' ' || array[0] == '\n') continue;
        sscanf(array, "%c %d %d %d", &cha, &x, &y, &z);    // x = row coordinate, y = col coordinate, z = size
        x--;
        y--;
        int a = x, b = y, c = x, d = y, e = x, f = y, g = x, h = y;
        bool check1 = true;    // for cheking borders
        bool check = true;    // for cheking conflicts

        switch (cha) {
            case '/':
                // checking for borders
                if (x + z >= row || y + z >= col || x - z < 0 || y - z < 0) {
                    check1 = false;
                    cout << "BORDER ERROR: Operator " << cha << " with size " << z << " can not be placed on (" << x + 1
                         << "," << y + 1 << ")." << endl;
                }
                // checking for conflict
                if (grid[x][y] != '\0') {
                    cout << "CONFLICT ERROR: Operator " << cha << " with size " << z << " can not be placed on ("
                         << x + 1 << "," << y + 1 << ")." << endl;
                    break;
                }
                for (int i = 0; i < z; i++) {
                    a--;
                    b++;
                    if (a < 0 || b >= col) break;
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
                    if (c >= row || d < 0) break;
                    if (grid[c][d] != '\0') {
                        cout << "CONFLICT ERROR: Operator " << cha << " with size " << z << " can not be placed on ("
                             << x + 1 << "," << y + 1 << ")." << endl;
                        check = false;
                        break;
                    }
                }
                if (!check) break;
                if (!check1) break;

                // denoting the place
                operation[op][0] = 1;
                operation[op][1] = x;
                operation[op][2] = y;
                operation[op][3] = z;
                op++;

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
                break;


            case 'x':
                // checking for borders
                if (x + z >= row || y + z >= col || x - z < 0 || y - z < 0) {
                    check1 = false;
                    cout << "BORDER ERROR: Operator " << cha << " with size " << z << " can not be placed on (" << x + 1
                         << "," << y + 1 << ")." << endl;
                }
                // checking for conflict
                if (grid[x][y] != '\0') {
                    cout << "CONFLICT ERROR: Operator " << cha << " with size " << z << " can not be placed on ("
                         << x + 1 << "," << y + 1 << ")." << endl;
                    break;
                }
                for (int i = 0; i < z; i++) {
                    a++;
                    b++;
                    if (a >= row || b >= col) break;
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
                    if (c >= row || d < 0) break;
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
                    if (e < 0 || f >= col) break;
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
                    if (g < 0 || h < 0) break;
                    if (grid[g][h] != '\0') {
                        cout << "CONFLICT ERROR: Operator " << cha << " with size " << z << " can not be placed on ("
                             << x + 1 << "," << y + 1 << ")." << endl;
                        check = false;
                        break;
                    }
                }
                if (!check) break;
                if (!check1) break;

                // denoting the place
                operation[op][0] = 2;
                operation[op][1] = x;
                operation[op][2] = y;
                operation[op][3] = z;
                op++;

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
                break;


            case '+':
                // checking for borders
                if (x + z >= row || y + z >= col || x - z < 0 || y - z < 0) {
                    check1 = false;
                    cout << "BORDER ERROR: Operator " << cha << " with size " << z << " can not be placed on (" << x + 1
                         << "," << y + 1 << ")." << endl;
                }
                // checking for conflict
                if (grid[x][y] != '\0') {
                    cout << "CONFLICT ERROR: Operator " << cha << " with size " << z << " can not be placed on ("
                         << x + 1 << "," << y + 1 << ")." << endl;
                    break;
                }
                for (int i = 0; i < z; i++) {
                    a++;
                    if (a >= row) break;
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
                    if (d >= col) break;
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
                    if (e < 0) break;
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
                    if (h < 0) break;
                    if (grid[g][h] != '\0') {
                        cout << "CONFLICT ERROR: Operator " << cha << " with size " << z << " can not be placed on ("
                             << x + 1 << "," << y + 1 << ")." << endl;
                        check = false;
                        break;
                    }
                }
                if (!check) break;
                if (!check1) break;

                // denoting the place
                operation[op][0] = 3;
                operation[op][1] = x;
                operation[op][2] = y;
                operation[op][3] = z;
                op++;

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
                break;


            case '-':
                // checking for borders
                if (y + z >= col || y - z < 0 || x < 0 || x >= row) {
                    check1 = false;
                    cout << "BORDER ERROR: Operator " << cha << " with size " << z << " can not be placed on (" << x + 1
                         << "," << y + 1 << ")." << endl;
                }
                // checking for conflict
                if (grid[x][y] != '\0') {
                    cout << "CONFLICT ERROR: Operator " << cha << " with size " << z << " can not be placed on ("
                         << x + 1 << "," << y + 1 << ")." << endl;
                    break;
                }
                for (int i = 0; i < z; i++) {
                    b++;
                    if (b >= col) break;
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
                    if (d < 0) break;
                    if (grid[c][d] != '\0') {
                        cout << "CONFLICT ERROR: Operator " << cha << " with size " << z << " can not be placed on ("
                             << x + 1 << "," << y + 1 << ")." << endl;
                        check = false;
                        break;
                    }
                }
                if (!check) break;
                if (!check1) break;

                // denoting the place
                operation[op][0] = 4;
                operation[op][1] = x;
                operation[op][2] = y;
                operation[op][3] = z;
                op++;

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
                break;

            default :
            	cout << "OPERATOR IS NOT FOUND!" << endl;
                break;
        }
    }


    int op_case;
    char move_case[5];
    FILE *inspt;
    inspt = fopen(argv[2], "r");
    if (inspt == NULL) {
        cout << "File not found.\n";
        return 1;
    }
    while (!feof(inspt)) {
        fgets(array, 10, inspt);
        if(array[0] == ' ' || array[0] == '\n') continue;
        sscanf(array, "%s %d %d %d", move_case, &x, &y, &z);
        x--;
        y--;
        bool find = false;
        int a = x, b = y, c = x, d = y, e = x, f = y, g = x, h = y;
        if (x >= row || x < 0 || y >= col || y < 0) {
            cout << "OUT OF GRID." << endl;
        }
        if (grid[x][y] == '\0') {
            cout << "THERE IS NO OPERATOR." << endl;
            continue;
        } else {
            switch (grid[x][y]) {
                case '/':
                    for (int i = 0;; i++) {
                        if (operation[i][0] == 0) break;
                        if (operation[i][1] == x && operation[i][2] == y) {
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
                                if (operation[i][0] == 0) { // all centers of operators is checked. there is no match.
                                    break;
                                }
                                if (operation[i][1] == a &&
                                    operation[i][2] == b) { // there is a matched operator center
                                    if (operation[i][3] < x - a) {   // this is not the searched operator center
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
                                if (operation[i][0] == 0) break;
                                if (operation[i][1] == c && operation[i][2] == d) {
                                    if (operation[i][3] < c - x) {
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
                        if (operation[i][0] == 0) break;
                        if (operation[i][1] == x && operation[i][2] == y) {
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
                            if (operation[i][0] == 0) break;
                            if (operation[i][1] == a && operation[i][2] == b) {
                                if (operation[i][3] < a - x) {
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
                            if (operation[i][0] == 0) break;
                            if (operation[i][1] == c && operation[i][2] == d) {
                                if (operation[i][3] < x - c) {
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
                            if (operation[i][0] == 0) break;
                            if (operation[i][1] == e && operation[i][2] == f) {
                                if (operation[i][3] < e - x) {
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
                            if (operation[i][0] == 0) break;
                            if (operation[i][1] == g && operation[i][2] == h) {
                                if (operation[i][3] < x - g) {
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
                        if (operation[i][0] == 0) break;
                        if (operation[i][1] == x && operation[i][2] == y) {
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
                            if (operation[i][0] == 0) break;
                            if (operation[i][1] == a && operation[i][2] == b) {
                                if (operation[i][3] < a - x) {
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
                            if (operation[i][0] == 0) break;
                            if (operation[i][1] == c && operation[i][2] == d) {
                                if (operation[i][3] < x - c) {
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
                            if (operation[i][0] == 0) break;
                            if (operation[i][1] == e && operation[i][2] == f) {
                                if (operation[i][3] < f - y) {
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
                            if (operation[i][0] == 0) break;
                            if (operation[i][1] == g && operation[i][2] == h) {
                                if (operation[i][3] < y - h) {
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
                        if (operation[i][0] == 0) break;
                        if (operation[i][1] == x && operation[i][2] == y) {
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
                            if (operation[i][0] == 0) break;
                            if (operation[i][1] == a && operation[i][2] == b) {
                                if (operation[i][3] < b - y) {
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
                            if (operation[i][0] == 0) break;
                            if (operation[i][1] == c && operation[i][2] == d) {
                                if (operation[i][3] < y - d) {
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
            if (!find) continue;

            int j, a0, b0, c0, d0, e0, f0, g0, h0;
            int op_row, op_col;
            bool check = true;
            bool check1 = true;
            int k1 = 0, k2 = 0;

            if (move_case[2] == 'R') {
                a = c = e = g = op_row = operation[op_case][1];
                b = d = f = h = op_col = operation[op_case][2] + z;
                k2 = -z;
            } else if (move_case[2] == 'L') {
                a = c = e = g = op_row = operation[op_case][1];
                b = d = f = h = op_col = operation[op_case][2] - z;
                k2 = z;
            } else if (move_case[2] == 'D') {
                a = c = e = g = op_row = operation[op_case][1] + z;
                b = d = f = h = op_col = operation[op_case][2];
                k1 = -z;
            } else if (move_case[2] == 'U') {
                a = c = e = g = op_row = operation[op_case][1] - z;
                b = d = f = h = op_col = operation[op_case][2];
                k1 = z;
            }
            j = operation[op_case][3];

            switch (operation[op_case][0]) {
                case 1 : //      '/' operator
                    // emptying
                    a0 = c0 = operation[op_case][1];
                    b0 = d0 = operation[op_case][2];
                    grid[a0][b0] = '\0';
                    for (int i = 0; i < operation[op_case][3]; i++) {
                        a0--;
                        b0++;
                        grid[a0][b0] = '\0';
                    }
                    for (int i = 0; i < operation[op_case][3]; i++) {
                        c0++;
                        d0--;
                        grid[c0][d0] = '\0';
                    }

                    // checking for borders
                    if (a + j >= col || b + j >= col || a - j < 0 || b - j < 0) {
                        cout << "BORDER ERROR: " << "/" << " can not be moved from (" << a + 1 + k1 << ","
                             << b + 1 + k2 << ") to (" << a + 1 << "," << b + 1 << ")." << endl;
                        check1 = false;
                    }

                        // checking for conflict
                    else if (grid[a][b] != '\0') {
                        cout << "CONFLICT ERROR: " << "/" << " can not be moved from (" << a + 1 + k1 << ","
                             << b + 1 + k2 << ") to (" << a + 1 << "," << b + 1 << ")." << endl;
                        check = false;
                    }

                    for (int i = 0; i < operation[op_case][3]; i++) {
                        if (!check) break;
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

                    for (int i = 0; i < operation[op_case][3]; i++) {
                        if (!check) break;
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
                        a0 = c0 = operation[op_case][1];
                        b0 = d0 = operation[op_case][2];
                        grid[a0][b0] = '/';
                        for (int i = 0; i < operation[op_case][3]; i++) {
                            a0--;
                            b0++;
                            grid[a0][b0] = '/';
                        }
                        for (int i = 0; i < operation[op_case][3]; i++) {
                            c0++;
                            d0--;
                            grid[c0][d0] = '/';
                        }
                    } else {
                        // moving
                        a = c = e = g = op_row;
                        b = d = f = h = op_col;
                        operation[op_case][1] = op_row;
                        operation[op_case][2] = op_col;

                        grid[a][b] = '/';
                        for (int i = 0; i < operation[op_case][3]; i++) {
                            a--;
                            b++;
                            grid[a][b] = '/';
                        }
                        for (int i = 0; i < operation[op_case][3]; i++) {
                            c++;
                            d--;
                            grid[c][d] = '/';
                        }
                        cout << "SUCCESS: " << grid[c][d] << " moved from (" << op_row + 1 + k1 << ","
                             << op_col + k2 + 1 << ") to (" << op_row + 1 << "," << op_col + 1 << ")." << endl;
                    }
                    break;

                case 2 :  // x operator
                    //emptying
                    a0 = c0 = e0 = g0 = operation[op_case][1];
                    b0 = d0 = f0 = h0 = operation[op_case][2];
                    grid[a0][b0] = '\0';
                    for (int i = 0; i < operation[op_case][3]; i++) {
                        a0++;
                        b0++;
                        grid[a0][b0] = '\0';
                    }
                    for (int i = 0; i < operation[op_case][3]; i++) {
                        c0++;
                        d0--;
                        grid[c0][d0] = '\0';
                    }
                    for (int i = 0; i < operation[op_case][3]; i++) {
                        e0--;
                        f0++;
                        grid[e0][f0] = '\0';
                    }
                    for (int i = 0; i < operation[op_case][3]; i++) {
                        g0--;
                        h0--;
                        grid[g0][h0] = '\0';
                    }

                    // checking for borders
                    if (a + j >= col || b + j >= col || a - j < 0 || b - j < 0) {
                        check1 = false;
                        cout << "BORDER ERROR: " << "x" << " can not be moved from (" << a + 1 + k1 << ","
                             << b + k2 + 1 << ") to (" << a + 1 << "," << b + 1 << ")." << endl;
                    }

                    // checking for conflict
                    if (grid[a][b] != '\0') {
                        cout << "CONFLICT ERROR: " << "x" << " can not be moved from (" << g + 1 + k1 << ","
                             << h + k2 + 1 << ") to (" << g + 1 << "," << h + 1 << ")." << endl;
                        check = false;
                    }

                    for (int i = 0; i < operation[op_case][3]; i++) {
                        if (!check) break;
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

                    for (int i = 0; i < operation[op_case][3]; i++) {
                        if (!check) break;
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

                    for (int i = 0; i < operation[op_case][3]; i++) {
                        if (!check) break;
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

                    for (int i = 0; i < operation[op_case][3]; i++) {
                        if (!check) break;
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
                        a0 = c0 = e0 = g0 = operation[op_case][1];
                        b0 = d0 = f0 = h0 = operation[op_case][2];
                        grid[a0][b0] = 'x';
                        for (int i = 0; i < operation[op_case][3]; i++) {
                            a0++;
                            b0++;
                            grid[a0][b0] = 'x';
                        }
                        for (int i = 0; i < operation[op_case][3]; i++) {
                            c0++;
                            d0--;
                            grid[c0][d0] = 'x';
                        }
                        for (int i = 0; i < operation[op_case][3]; i++) {
                            e0--;
                            f0++;
                            grid[e0][f0] = 'x';
                        }
                        for (int i = 0; i < operation[op_case][3]; i++) {
                            g0--;
                            h0--;
                            grid[g0][h0] = 'x';
                        }
                    } else {
                        // moving
                        a = c = e = g = op_row;
                        b = d = f = h = op_col;
                        operation[op_case][1] = op_row;
                        operation[op_case][2] = op_col;

                        grid[a][b] = 'x';
                        for (int i = 0; i < operation[op_case][3]; i++) {
                            a++;
                            b++;
                            grid[a][b] = 'x';
                        }
                        for (int i = 0; i < operation[op_case][3]; i++) {
                            c++;
                            d--;
                            grid[c][d] = 'x';
                        }
                        for (int i = 0; i < operation[op_case][3]; i++) {
                            e--;
                            f++;
                            grid[e][f] = 'x';
                        }
                        for (int i = 0; i < operation[op_case][3]; i++) {
                            g--;
                            h--;
                            grid[g][h] = 'x';
                        }
                        cout << "SUCCESS: " << grid[g][h] << " moved from (" << op_row + 1 + k1 << ","
                             << op_col + k2 + 1 << ") to (" << op_row + 1 << "," << op_col + 1 << ")." << endl;
                    }

                    break;

                case 3 : // + operator
                    // emptying
                    a0 = c0 = e0 = g0 = operation[op_case][1];
                    b0 = d0 = f0 = h0 = operation[op_case][2];
                    grid[a0][b0] = '\0';
                    for (int i = 0; i < operation[op_case][3]; i++) {
                        a0++;
                        grid[a0][b0] = '\0';
                    }
                    for (int i = 0; i < operation[op_case][3]; i++) {
                        d0++;
                        grid[c0][d0] = '\0';
                    }
                    for (int i = 0; i < operation[op_case][3]; i++) {
                        e0--;
                        grid[e0][f0] = '\0';
                    }
                    for (int i = 0; i < operation[op_case][3]; i++) {
                        h0--;
                        grid[g0][h0] = '\0';
                    }

                    // checking for borders
                    if (a + j >= col || b + j >= col || a - j < 0 || b - j < 0) {
                        check1 = false;
                        cout << "BORDER ERROR: " << "+" << " can not be moved from (" << a + 1 + k1 << ","
                             << b + k2 + 1 << ") to (" << a + 1 << "," << b + 1 << ")." << endl;
                    }

                    // checking for conflict
                    if (grid[a][b] != '\0') {
                        cout << "CONFLICT ERROR: " << "+" << " can not be moved from (" << op_row + 1 + k1 << ","
                             << op_col + k2 + 1 << ") to (" << op_row + 1 << "," << op_col + 1 << ")." << endl;
                        check = false;
                    }

                    for (int i = 0; i < operation[op_case][3]; i++) {
                        if (!check) break;
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

                    for (int i = 0; i < operation[op_case][3]; i++) {
                        if (!check) break;
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

                    for (int i = 0; i < operation[op_case][3]; i++) {
                        if (!check) break;
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

                    for (int i = 0; i < operation[op_case][3]; i++) {
                        if (!check) break;
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
                        a0 = c0 = e0 = g0 = operation[op_case][1];
                        b0 = d0 = f0 = h0 = operation[op_case][2];
                        grid[a0][b0] = '+';
                        for (int i = 0; i < operation[op_case][3]; i++) {
                            a0++;
                            grid[a0][b0] = '+';
                        }
                        for (int i = 0; i < operation[op_case][3]; i++) {
                            d0++;
                            grid[c0][d0] = '+';
                        }
                        for (int i = 0; i < operation[op_case][3]; i++) {
                            e0--;
                            grid[e0][f0] = '+';
                        }
                        for (int i = 0; i < operation[op_case][3]; i++) {
                            h0--;
                            grid[g0][h0] = '+';
                        }
                    } else {
                        // moving
                        a = c = e = g = op_row;
                        b = d = f = h = op_col;
                        operation[op_case][1] = op_row;
                        operation[op_case][2] = op_col;

                        grid[a][b] = '+';
                        for (int i = 0; i < operation[op_case][3]; i++) {
                            a++;
                            grid[a][b] = '+';
                        }
                        for (int i = 0; i < operation[op_case][3]; i++) {
                            d++;
                            grid[c][d] = '+';
                        }
                        for (int i = 0; i < operation[op_case][3]; i++) {
                            e--;
                            grid[e][f] = '+';
                        }
                        for (int i = 0; i < operation[op_case][3]; i++) {
                            h--;
                            grid[g][h] = '+';
                        }
                        cout << "SUCCESS: " << grid[g][h] << " moved from (" << op_row + k1 + 1 << ","
                             << op_col + k2 + 1 << ") to (" << op_row + 1 << "," << op_col + 1 << ")." << endl;
                    }

                    break;

                case 4 : // - operator
                    // emptying
                    a0 = c0 = operation[op_case][1];
                    b0 = d0 = operation[op_case][2];
                    grid[a0][b0] = '\0';
                    for (int i = 0; i < operation[op_case][3]; i++) {
                        b0++;
                        grid[a0][b0] = '\0';
                    }
                    for (int i = 0; i < operation[op_case][3]; i++) {
                        d0--;
                        grid[c0][d0] = '\0';
                    }

                    // checking for borders
                    if (a >= col || b + j >= col || a < 0 || b - j < 0) {
                        check1 = false;
                        cout << "BORDER ERROR: " << "-" << " can not be moved from (" << a + 1 + k1 << ","
                             << b + k2 + 1 << ") to (" << a + 1 << "," << b + 1 << ")." << endl;
                    }

                    // checking for conflict
                    if (grid[a][b] != '\0') {
                        cout << "CONFLICT ERROR: " << "-" << " can not be moved from (" << op_row + k1 + 1 << ","
                             << op_col + k2 + 1 << ") to (" << op_row + 1 << "," << op_col + 1 << ")." << endl;
                        check = false;
                    }
                    for (int i = 0; i < operation[op_case][3]; i++) {
                        if (!check) break;
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

                    for (int i = 0; i < operation[op_case][3]; i++) {
                        if (!check) break;
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
                        a0 = c0 = operation[op_case][1];
                        b0 = d0 = operation[op_case][2];
                        grid[a0][b0] = '-';
                        for (int i = 0; i < operation[op_case][3]; i++) {
                            b0++;
                            grid[a0][b0] = '-';
                        }
                        for (int i = 0; i < operation[op_case][3]; i++) {
                            d0--;
                            grid[c0][d0] = '-';
                        }
                    } else {
                        // moving
                        a = c = e = g = op_row;
                        b = d = f = h = op_col;
                        operation[op_case][1] = op_row;
                        operation[op_case][2] = op_col;
                        grid[a][b] = '-';
                        for (int i = 0; i < operation[op_case][3]; i++) {
                            b++;
                            grid[a][b] = '-';
                        }
                        for (int i = 0; i < operation[op_case][3]; i++) {
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
    }
    return 0;
}
