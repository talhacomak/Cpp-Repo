/* @Author
* Student Name: Talha Çomak
* Student ID : 150160726 */

#include <iostream>
#include <vector>
#include <fstream>
#include <climits>

using namespace std;


vector <vector <int> > vec; // using for keeping nodes on the path
							// first indices are ending nodes 

void dijkstra(int** graph, int start, int V) { // graph, starting node and Vertex count
	int* distance = new int[V];		// distance array for calculating path distance between two nodes
	bool* track = new bool[V];		// if the distance is calculated or not

	for (int i = 0; i < V; i++)		// first, all distances are infinite
		distance[i] = INT_MAX, track[i] = false; 

	distance[start] = 0; 	// starting distance is always zero
	int min, min_index;
	for (int i = 0; i < V - 1; i++) {
		min = INT_MAX;
		min_index = 0;
		for (int j = 0; j < V; j++) {  // finding min index
			if (track[j] == false && distance[j] <= min) {
				min = distance[j];
				min_index = j;
			}
		}
		track[min_index] = true;
		for (int j = 0; j < V; j++) {  // finding distances and finding nodes of paths 
			if (!track[j] && graph[min_index][j] && distance[min_index] != INT_MAX && distance[min_index] + graph[min_index][j] < distance[j]) {
				distance[j] = distance[min_index] + graph[min_index][j]; // the distance of node starting node to node j
				if (distance[min_index] == 0) { // if it was zero 
					vec[j].push_back(j);
				}
				else {
					for (int k = 0; k < (int)vec[min_index].size(); k++) {	// adding previous nodes to vector vec
						vec[j].push_back(vec[min_index][k]);
					}
					vec[j].push_back(j);
				}
			}
		}
	}
}

	// this funciton checks if there is a conflict with lucy and joseph when they are going to their destinations
	// two return value, bool one is the conflict station. integer one is the conflicting node. this will using for find the edge
pair<bool, int> conflictCheckerDest(vector < pair<int, int> > jos, vector < pair<int, int> > lucy) {

	for (int i = 0; i < (int)jos.size() - 1; i++) { // searching for all nodes
		for (int j = 0; j < (int)lucy.size() - 1; j++) {
			if (jos[i].first == lucy[j].first && jos[i].second == lucy[j].second) return make_pair(true, jos[i].first);
		}
	}
	for (int i = 0; i < (int)lucy.size(); i++) { // in dest. node waiting 30 min. checking for lucy
		if (jos[(int)jos.size() - 1].first == lucy[i].first && jos[(int)jos.size() - 1].second + 30 >= lucy[i].second && jos[(int)jos.size() - 1].second <= lucy[i].second) return make_pair(true, lucy[i].first);
	}
	for (int i = 0; i < (int)jos.size(); i++) { // in dest. node waiting 30 min. checking for joseph
		if (lucy[(int)lucy.size() - 1].first == jos[i].first && lucy[(int)lucy.size() - 1].second + 30 >= jos[i].second && lucy[(int)jos.size() - 1].second <= jos[i].second) return make_pair(true, jos[i].first);
	}
	return make_pair(false, 0);
}

	// this funciton checks if there is a conflict with lucy and joseph when they are returning back to their hotels
	// two return value, bool one is the conflict station. integer one is the conflicting node. this will using for find the edge
pair<bool, int> conflictCheckerRet(vector < pair<int, int> > jos, vector < pair<int, int> > lucy) {		

	for (int i = 0; i < (int)lucy.size(); i++) { // if true find alternative only for lucy
		if (jos[0].first == lucy[i].first && jos[0].second >= lucy[i].second && jos[0].second - 30 <= lucy[i].second) return make_pair(true, jos[0].first);
	}
	for (int i = 0; i < (int)jos.size(); i++) { // if true find alternative only for joseph
		if (lucy[0].first == jos[i].first && lucy[0].second >= jos[i].second && lucy[0].second - 30 <= jos[i].second) return make_pair(true, lucy[0].first);
	}
	for (int i = 0; i < (int)jos.size() - 1; i++) { // searching for all nodes
		for (int j = 0; j < (int)lucy.size() - 1; j++) {
			if (jos[i].first == lucy[j].first && jos[i].second == lucy[j].second) return make_pair(true, jos[i].first);
		}
	}
	return make_pair(false, 0);
}


int main(int argv, char* argc[]) {

	if (argc[1] == NULL) {
		cout << "No parameter!" << endl;
		return 1;
	}

	ifstream file(argc[1]);

	int node_count;
	int JosHotel, LucHotel, JosDest, LucDest;

	file >> node_count;
	file >> JosHotel;
	file >> JosDest;
	file >> LucHotel;
	file >> LucDest;
	int** graph;

	if(node_count > 0) graph = new int* [node_count];
	else {
		cout << "invalid graph size!\n";
		return 1;
	}
	
	//  creating graph
	for (int i = 0; i < node_count; i++) {
		graph[i] = new int[node_count];
		for (int j = 0; j < node_count; j++) {
			graph[i][j] = 0;
		}
	}
	
	// reading graph
	while (!file.eof())
	{
		int i, j, k;
		file >> i;
		file >> j;
		file >> k;
		graph[i][j] = k;
	}
	
	vec.resize(node_count);
	vector <pair <int, int> > JosephTime; // to store the node and time informations of Joseph path
	vector <pair <int, int> > LucyTime;	  // to store the node and time informations of Lucy path

	dijkstra(graph, JosHotel, node_count);	// dijkastra for finding vec, vec is the vector for 
	JosephTime.push_back(make_pair(JosHotel, 0)); // first point with time zero
	int time = graph[JosHotel][vec[JosDest][0]];	// time of the first edge
	JosephTime.push_back(make_pair(vec[JosDest][0], time));
	for (int j = 1; j < (int)vec[JosDest].size(); j++) {	// adding all nodes and their times to the JosephTime vector
		time += graph[vec[JosDest][j - 1]][vec[JosDest][j]];
		JosephTime.push_back(make_pair(vec[JosDest][j], time));
	}
	
	cout<<"vecccc:\n";
	for(int i=0; i<(int)vec.size(); i++){
		for(int j=0; j<(int)vec[i].size(); j++){
			cout<<vec[i][j] << " ";
		}
		cout<<endl;
	}

	vec.clear(); // clearing the vec vector for reuse
	vec.resize(node_count); // resize for reuse
	dijkstra(graph, LucHotel, node_count);		// same processes for Lucy
	LucyTime.push_back(make_pair(LucHotel, 0));
	time = graph[LucHotel][vec[LucDest][0]];
	LucyTime.push_back(make_pair(vec[LucDest][0], time));
	for (int j = 1; j < (int)vec[LucDest].size(); j++) {
		time += graph[vec[LucDest][j - 1]][vec[LucDest][j]];
		LucyTime.push_back(make_pair(vec[LucDest][j], time));
	}

	bool noLucy = false;	// variable for keep information of change of the path for Lucy
	bool noJoseph = false; 	// variable for keep information of change of the path for joseph
	int timeAfterWaitLucy = 0;	// variable for keep time of Lucy after destination
	int timeAfterWaitJoseph = 0; // variable for keep time of Joseph after destination
	bool IsJoseph = false;	// variable for keep path info about Joseph
	bool isConflict = false; // variable for keep path info about Lucy
	int returnback, row, col;	// for the keep the erased path information
	vector <pair <int, int> > JosephTime2;  // for alternative path
	vector <pair <int, int> > LucyTime2;	// for alternative path
	pair<bool, int> check = conflictCheckerDest(JosephTime, LucyTime); // checking whether there is a conflict or not
	if (check.first) {
		isConflict = true;
		for (int i = 0; i < (int)JosephTime.size(); i++) {  // finding conflicting path
			if (JosephTime[i].first == check.second) {
				row = JosephTime[i - 1].first; 		// storing the row
				col = JosephTime[i].first;			// storing the column
				returnback = graph[JosephTime[i - 1].first][JosephTime[i].first];	// stroing the length of the path
				graph[JosephTime[i - 1].first][JosephTime[i].first] = 0;		// deleting the path
				break;
			}
		}
		vec.clear();
		vec.resize(node_count);
		dijkstra(graph, JosHotel, node_count);		// finding alternative path for Joseph
		if (vec[JosDest].size() > 0) {		// if there is an alternative path 
			JosephTime2.push_back(make_pair(JosHotel, 0)); // then store the node and time informaitons into JosephTime2
			time = graph[JosHotel][vec[JosDest][0]];
			JosephTime2.push_back(make_pair(vec[JosDest][0], time));
			for (int j = 1; j < (int)vec[JosDest].size(); j++) {
				time += graph[vec[JosDest][j - 1]][vec[JosDest][j]];
				JosephTime2.push_back(make_pair(vec[JosDest][j], time));
			}
		}
		else {	// there is no alternative path
			noJoseph = true;
		}

		graph[row][col] = returnback;	// adding the deleted path
		for (int i = 0; i < (int)LucyTime.size(); i++) {	// finding alternative path for Lucy then same process
			if (LucyTime[i].first == check.second) {
				row = LucyTime[i - 1].first;
				col = LucyTime[i].first;
				returnback = graph[LucyTime[i - 1].first][LucyTime[i].first];
				graph[LucyTime[i - 1].first][LucyTime[i].first] = 0;
				break;
			}
		}
		vec.clear();
		vec.resize(node_count);
		dijkstra(graph, LucHotel, node_count);
		if (vec[LucDest].size() > 0) {
			LucyTime2.push_back(make_pair(LucHotel, 0));
			time = graph[LucHotel][vec[LucDest][0]];
			LucyTime2.push_back(make_pair(vec[LucDest][0], time));
			for (int j = 1; j < (int)vec[LucDest].size(); j++) {
				time += graph[vec[LucDest][j - 1]][vec[LucDest][j]];
				LucyTime2.push_back(make_pair(vec[LucDest][j], time));
			}
		}
		else {
			noLucy = true;
		}
		graph[row][col] = returnback;

		//Results
		if (noLucy && noJoseph) {
			cout << "No solution!\n";
			return 0;
		}
		else if (!noLucy && noJoseph) { // If there is no solution for Joseph but there is a solution for Lucy
			check = conflictCheckerDest(JosephTime, LucyTime2); // Checking second time
			if (check.first) {
				cout << "No solution!\n";
				return 0;
			}
			timeAfterWaitLucy = LucyTime2[(int)LucyTime2.size() - 1].second + 30;	// If solution is right, then storing the time values
			timeAfterWaitJoseph = JosephTime[(int)JosephTime.size() - 1].second + 30;
			IsJoseph = true;
		}
		else if (noLucy && !noJoseph) { // If there is no solution for Lucy but there is a solution for Joseph
			check = conflictCheckerDest(JosephTime2, LucyTime);  // Checking second time
			if (check.first) {
				cout << "No solution!\n";
				return 0;
			}
			timeAfterWaitJoseph = JosephTime2[(int)JosephTime2.size() - 1].second + 30;
			timeAfterWaitLucy = LucyTime[(int)LucyTime.size() - 1].second + 30;
		}
		else {  // If there are solutions for Lucy and Joseph
				// comparing the times and faster one is selected
			if (JosephTime2[(int)JosephTime2.size() - 1].second + LucyTime[(int)LucyTime.size() - 1].second > JosephTime[(int)JosephTime.size() - 1].second + LucyTime2[(int)LucyTime2.size() - 1].second) {
				check = conflictCheckerDest(JosephTime, LucyTime2);
				if (check.first) {
					cout << "No solution!\n";
					return 0;
				}
				timeAfterWaitLucy = LucyTime2[(int)LucyTime2.size() - 1].second + 30;
				timeAfterWaitJoseph = JosephTime[(int)JosephTime.size() - 1].second + 30;
				IsJoseph = true;
			}
			else {
				check = conflictCheckerDest(JosephTime2, LucyTime);
				if (check.first) {
					cout << "No solution!\n";
					return 0;
				}
				timeAfterWaitJoseph = JosephTime2[(int)JosephTime2.size() - 1].second + 30;
				timeAfterWaitLucy = LucyTime[(int)LucyTime.size() - 1].second + 30;
			}
		}
	}
	else {
		timeAfterWaitJoseph = JosephTime[(int)JosephTime.size() - 1].second + 30;
		timeAfterWaitLucy = LucyTime[(int)LucyTime.size() - 1].second + 30;
	}
	
	// Return
	// Similar process like previous part
	
	bool IsJosephRet = false;
	bool isConflictRet = false;
	vec.clear();
	vec.resize(node_count);

	vector <pair <int, int> > JosephTimeRet;
	vector <pair <int, int> > LucyTimeRet;

	dijkstra(graph, JosDest, node_count);
	JosephTimeRet.push_back(make_pair(JosDest, timeAfterWaitJoseph));
	time = graph[JosDest][vec[JosHotel][0]] + timeAfterWaitJoseph;
	JosephTimeRet.push_back(make_pair(vec[JosHotel][0], time));
	for (int j = 1; j < (int)vec[JosHotel].size(); j++) {
		time += graph[vec[JosHotel][j - 1]][vec[JosHotel][j]];
		JosephTimeRet.push_back(make_pair(vec[JosHotel][j], time));
	}

	vec.clear();
	vec.resize(node_count);
	dijkstra(graph, LucDest, node_count);
	LucyTimeRet.push_back(make_pair(LucDest, timeAfterWaitLucy));
	time = graph[LucDest][vec[LucHotel][0]] + timeAfterWaitLucy;
	LucyTimeRet.push_back(make_pair(vec[LucHotel][0], time));
	for (int j = 1; j < (int)vec[LucHotel].size(); j++) {
		time += graph[vec[LucHotel][j - 1]][vec[LucHotel][j]];
		LucyTimeRet.push_back(make_pair(vec[LucHotel][j], time));
	}

	vector <pair <int, int> > JosephTimeRet2;
	vector <pair <int, int> > LucyTimeRet2;

	check = conflictCheckerRet(JosephTimeRet, LucyTimeRet);
	if (check.first) {
		isConflictRet = true;
		noJoseph = false;
		noLucy = false;
		if (check.second == LucDest) {
			for (int i = 0; i < (int)JosephTimeRet.size(); i++) {
				if (JosephTimeRet[i].first == check.second) {
					row = JosephTimeRet[i - 1].first;
					col = JosephTimeRet[i].first;
					returnback = graph[JosephTimeRet[i - 1].first][JosephTimeRet[i].first];
					graph[JosephTimeRet[i - 1].first][JosephTimeRet[i].first] = 0;
					break;
				}
			}
			vec.clear();
			vec.resize(node_count);
			dijkstra(graph, JosDest, node_count);
			if (vec[JosHotel].size() > 0) {
				JosephTimeRet2.push_back(make_pair(JosDest, timeAfterWaitJoseph));
				time = graph[JosDest][vec[JosHotel][0]] + timeAfterWaitJoseph;
				JosephTimeRet2.push_back(make_pair(vec[JosHotel][0], time));
				for (int j = 1; j < (int)vec[JosHotel].size(); j++) {
					time += graph[vec[JosHotel][j - 1]][vec[JosHotel][j]];
					JosephTimeRet2.push_back(make_pair(vec[JosHotel][j], time));
				}
				check = conflictCheckerRet(JosephTimeRet2, LucyTimeRet);
				if (check.first) {
					cout << "No solution!\n";
					return 0;
				}
			}
			else {
				cout << "No solution!\n";
				return 0;
			}
			graph[row][col] = returnback;
		}
		else if (check.second == JosDest) {
			for (int i = 0; i < (int)LucyTimeRet.size(); i++) {
				if (LucyTime[i].first == check.second) {
					row = LucyTimeRet[i - 1].first;
					col = LucyTimeRet[i].first;
					returnback = graph[LucyTimeRet[i - 1].first][LucyTimeRet[i].first];
					graph[LucyTimeRet[i - 1].first][LucyTimeRet[i].first] = 0;
					break;
				}
			}
			vec.clear();
			vec.resize(node_count);
			dijkstra(graph, LucDest, node_count);

			if (vec[LucHotel].size() > 0) {
				LucyTimeRet2.push_back(make_pair(LucDest, timeAfterWaitLucy));
				time = graph[LucDest][vec[LucHotel][0]] + timeAfterWaitLucy;
				LucyTimeRet2.push_back(make_pair(vec[LucHotel][0], time));
				for (int j = 1; j < (int)vec[JosDest].size(); j++) {
					time += graph[vec[LucHotel][j - 1]][vec[LucHotel][j]];
					LucyTimeRet2.push_back(make_pair(vec[LucHotel][j], time));
				}
				check = conflictCheckerRet(JosephTimeRet, LucyTimeRet2);
				if (check.first) {
					cout << "No solution!\n";
					return 0;
				}
				IsJosephRet = true;
			}
			else {
				cout << "No solution!\n";
				return 0;
			}
			graph[row][col] = returnback;
		}
		else {
			for (int i = 0; i < (int)JosephTimeRet.size(); i++) {
				if (JosephTimeRet[i].first == check.second) {
					row = JosephTimeRet[i - 1].first;
					col = JosephTimeRet[i].first;
					returnback = graph[JosephTimeRet[i - 1].first][JosephTimeRet[i].first];
					graph[JosephTimeRet[i - 1].first][JosephTimeRet[i].first] = 0;
					break;
				}
			}
			vec.clear();
			vec.resize(node_count);
			dijkstra(graph, JosDest, node_count);
			if (vec[JosHotel].size() > 0) {
				JosephTimeRet2.push_back(make_pair(JosDest, timeAfterWaitJoseph));
				time = graph[JosDest][vec[JosHotel][0]] + timeAfterWaitJoseph;
				JosephTimeRet2.push_back(make_pair(vec[JosHotel][0], time));
				for (int j = 1; j < (int)vec[JosHotel].size(); j++) {
					time += graph[vec[JosHotel][j - 1]][vec[JosHotel][j]];
					JosephTimeRet2.push_back(make_pair(vec[JosHotel][j], time));
				}
			}
			else {
				noJoseph = true;
			}
			graph[row][col] = returnback;
			
			for (int i = 0; i < (int)LucyTimeRet.size(); i++) {
				if (LucyTimeRet[i].first == check.second) {
					row = LucyTimeRet[i - 1].first;
					col = LucyTimeRet[i].first;
					returnback = graph[LucyTimeRet[i - 1].first][LucyTimeRet[i].first];
					graph[LucyTimeRet[i - 1].first][LucyTimeRet[i].first] = 0;
					break;
				}
			}
			vec.clear();
			vec.resize(node_count);

			dijkstra(graph, LucDest, node_count);
			if (vec[LucHotel].size() > 0) {
				LucyTimeRet2.push_back(make_pair(LucDest, timeAfterWaitLucy));
				time = graph[LucDest][vec[LucHotel][0]] + timeAfterWaitLucy;
				LucyTimeRet2.push_back(make_pair(vec[LucHotel][0], time));
				for (int j = 1; j < (int)vec[LucHotel].size(); j++) {
					time += graph[vec[LucHotel][j - 1]][vec[LucHotel][j]];
					LucyTimeRet2.push_back(make_pair(vec[LucHotel][j], time));
				}
			}
			else {
				noLucy = true;
			}
			graph[row][col] = returnback;
			
			//second check
			if (noLucy && noJoseph) {
				cout << "No solution!\n";
				return 0;
			}
			else if (!noLucy && noJoseph) {
				check = conflictCheckerRet(JosephTimeRet, LucyTimeRet2);
				if (check.first) {
					cout << "No solution!\n";
					return 0;
				}
				IsJosephRet = true;
			}
			else if (noLucy && !noJoseph) {
				check = conflictCheckerDest(JosephTimeRet2, LucyTimeRet);
				if (check.first) {
					cout << "No solution!\n";
					return 0;
				}
			}
			else {
				if (JosephTime2[(int)JosephTime2.size() - 1].second + LucyTimeRet[(int)LucyTimeRet.size() - 1].second > JosephTimeRet[(int)JosephTimeRet.size() - 1].second + LucyTime2[LucyTime2.size() - 1].second) {
					check = conflictCheckerDest(JosephTimeRet, LucyTimeRet2);
					if (check.first) {
						cout << "No solution!\n";
						return 0;
					}
					IsJosephRet = true;
				}
				else {
					check = conflictCheckerDest(JosephTimeRet2, LucyTimeRet);
					if (check.first) {
						cout << "No solution!\n";
						return 0;
					}
				}
			}
		}
	}
	
	// PRINTING THE RESULTS ACCORDING TO CONDITIONS
	
	if (!isConflictRet && !isConflict) {
		cout << "Joseph's Path, duration: " << JosephTimeRet[JosephTimeRet.size() - 1].second << endl;
		for (int i = 0; i < (int)JosephTime.size(); i++) {
			cout << "Node: " << JosephTime[i].first << " Time: " << JosephTime[i].second << endl;
		}
		cout << "-- return --" << endl;
		for (int i = 0; i < (int)JosephTimeRet.size(); i++) {
			cout << "Node: " << JosephTimeRet[i].first << " Time: " << JosephTimeRet[i].second << endl;
		}
		cout << "\nLucy's Path, duration: " << LucyTimeRet[LucyTimeRet.size() - 1].second << endl;
		for (int i = 0; i < (int)LucyTime.size(); i++) {
			cout << "Node: " << LucyTime[i].first << " Time: " << LucyTime[i].second << endl;
		}
		cout << "-- return --" << endl;
		for (int i = 0; i < (int)LucyTimeRet.size(); i++) {
			cout << "Node: " << LucyTimeRet[i].first << " Time: " << LucyTimeRet[i].second << endl;
		}
	}
	else if (isConflict && !isConflictRet) {
		if (IsJoseph) {
			cout << "Joseph's Path, duration: " << JosephTimeRet[JosephTimeRet.size() - 1].second << endl;
			for (int i = 0; i < (int)JosephTime.size(); i++) {
				cout << "Node: " << JosephTime[i].first << " Time: " << JosephTime[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < (int)JosephTimeRet.size(); i++) {
				cout << "Node: " << JosephTimeRet[i].first << " Time: " << JosephTimeRet[i].second << endl;
			}
			cout << "\nLucy's Path, duration: " << LucyTimeRet[LucyTimeRet.size() - 1].second << endl;
			for (int i = 0; i < (int)LucyTime2.size(); i++) {
				cout << "Node: " << LucyTime2[i].first << " Time: " << LucyTime2[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < (int)LucyTimeRet.size(); i++) {
				cout << "Node: " << LucyTimeRet[i].first << " Time: " << LucyTimeRet[i].second << endl;
			}
		}
		else {
			cout << "Joseph's Path, duration: " << JosephTimeRet[JosephTimeRet.size() - 1].second << endl;
			for (int i = 0; i < (int)JosephTime2.size(); i++) {
				cout << "Node: " << JosephTime2[i].first << " Time: " << JosephTime2[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < (int)JosephTimeRet.size(); i++) {
				cout << "Node: " << JosephTimeRet[i].first << " Time: " << JosephTimeRet[i].second << endl;
			}
			cout << "\nLucy's Path, duration: " << LucyTimeRet[LucyTimeRet.size() - 1].second << endl;
			for (int i = 0; i < (int)LucyTime.size(); i++) {
				cout << "Node: " << LucyTime[i].first << " Time: " << LucyTime[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < (int)LucyTimeRet.size(); i++) {
				cout << "Node: " << LucyTimeRet[i].first << " Time: " << LucyTimeRet[i].second << endl;
			}
		}
	}
	else if (isConflictRet && !isConflict) {
		if (IsJosephRet) {
			cout << "Joseph's Path, duration: " << JosephTimeRet[JosephTimeRet.size() - 1].second << endl;
			for (int i = 0; i < (int)JosephTime.size(); i++) {
				cout << "Node: " << JosephTime[i].first << " Time: " << JosephTime[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < (int)JosephTimeRet.size(); i++) {
				cout << "Node: " << JosephTimeRet[i].first << " Time: " << JosephTimeRet[i].second << endl;
			}
			cout << "\nLucy's Path, duration: " << LucyTimeRet2[LucyTimeRet2.size() - 1].second << endl;
			for (int i = 0; i < (int)LucyTime.size(); i++) {
				cout << "Node: " << LucyTime[i].first << " Time: " << LucyTime[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < (int)LucyTimeRet2.size(); i++) {
				cout << "Node: " << LucyTimeRet2[i].first << " Time: " << LucyTimeRet2[i].second << endl;
			}
		}
		else {
			cout << "Joseph's Path, duration: " << JosephTimeRet2[JosephTimeRet2.size() - 1].second << endl;
			for (int i = 0; i < (int)JosephTime.size(); i++) {
				cout << "Node: " << JosephTime[i].first << " Time: " << JosephTime[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < (int)JosephTimeRet2.size(); i++) {
				cout << "Node: " << JosephTimeRet2[i].first << " Time: " << JosephTimeRet2[i].second << endl;
			}
			cout << "\nLucy's Path, duration: " << LucyTimeRet[LucyTimeRet.size() - 1].second << endl;
			for (int i = 0; i < (int)LucyTime.size(); i++) {
				cout << "Node: " << LucyTime[i].first << " Time: " << LucyTime[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < (int)LucyTimeRet.size(); i++) {
				cout << "Node: " << LucyTimeRet[i].first << " Time: " << LucyTimeRet[i].second << endl;
			}
		}
	}
	else {
		if (IsJoseph && IsJosephRet) {
			cout << "Joseph's Path, duration: " << JosephTimeRet[JosephTimeRet.size() - 1].second << endl;
			for (int i = 0; i < (int)JosephTime.size(); i++) {
				cout << "Node: " << JosephTime[i].first << " Time: " << JosephTime[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < (int)JosephTimeRet.size(); i++) {
				cout << "Node: " << JosephTimeRet[i].first << " Time: " << JosephTimeRet[i].second << endl;
			}
			cout << "\nLucy's Path, duration: " << LucyTimeRet2[LucyTimeRet2.size() - 1].second << endl;
			for (int i = 0; i < (int)LucyTime2.size(); i++) {
				cout << "Node: " << LucyTime2[i].first << " Time: " << LucyTime2[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < (int)LucyTimeRet2.size(); i++) {
				cout << "Node: " << LucyTimeRet2[i].first << " Time: " << LucyTimeRet2[i].second << endl;
			}
		}
		else if (IsJoseph && !IsJosephRet) {
			cout << "Joseph's Path, duration: " << JosephTimeRet2[JosephTimeRet2.size() - 1].second << endl;
			for (int i = 0; i < (int)JosephTime.size(); i++) {
				cout << "Node: " << JosephTime[i].first << " Time: " << JosephTime[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < (int)JosephTimeRet2.size(); i++) {
				cout << "Node: " << "Node: " << JosephTimeRet2[i].first << " Time: " << JosephTimeRet2[i].second << endl;
			}
			cout << "\nLucy's Path, duration: " << LucyTimeRet[LucyTimeRet.size() - 1].second << endl;
			for (int i = 0; i < (int)LucyTime2.size(); i++) {
				cout << "Node: " << LucyTime2[i].first << " Time: " << LucyTime2[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < (int)LucyTimeRet.size(); i++) {
				cout << "Node: " << LucyTimeRet[i].first << " Time: " << LucyTimeRet[i].second << endl;
			}
		}
		else if (!IsJoseph && IsJosephRet) {
			cout << "Joseph's Path, duration: " << JosephTimeRet[JosephTimeRet.size() - 1].second << endl;
			for (int i = 0; i < (int)JosephTime2.size(); i++) {
				cout << "Node: " << JosephTime2[i].first << " Time: " << JosephTime2[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < (int)JosephTimeRet.size(); i++) {
				cout << "Node: " << JosephTimeRet[i].first << " Time: " << JosephTimeRet[i].second << endl;
			}
			cout << "\nLucy's Path, duration: " << LucyTimeRet2[LucyTimeRet2.size() - 1].second << endl;
			for (int i = 0; i < (int)LucyTime.size(); i++) {
				cout << "Node: " << LucyTime[i].first << " Time: " << LucyTime[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < (int)LucyTimeRet2.size(); i++) {
				cout << "Node: " << LucyTimeRet2[i].first << " Time: " << LucyTimeRet2[i].second << endl;
			}
		}
		else {
			cout << "Joseph's Path, duration: " << JosephTimeRet2[JosephTimeRet2.size() - 1].second << endl;
			for (int i = 0; i < (int)JosephTime2.size(); i++) {
				cout << "Node: " << JosephTime2[i].first << " Time: " << JosephTime2[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < (int)JosephTimeRet2.size(); i++) {
				cout << "Node: " << JosephTimeRet2[i].first << " Time: " << JosephTimeRet2[i].second << endl;
			}
			cout << "\nLucy's Path, duration: " << LucyTimeRet[LucyTimeRet.size() - 1].second << endl;
			for (int i = 0; i < (int)LucyTime.size(); i++) {
				cout << "Node: " << LucyTime[i].first << " Time: " << LucyTime[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < (int)LucyTimeRet.size(); i++) {
				cout << "Node: " << LucyTimeRet[i].first << " Time: " << LucyTimeRet[i].second << endl;
			}
		}
	}


	return 0;
}
