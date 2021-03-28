/* @Author
* Student Name: Talha Çomak
* Student ID : 150160726 */

#include <iostream>
#include <vector>

using namespace std;


vector <vector <int> > vec;


int minDistance(int dist[], bool sptSet[], int V) {
	int min = INT_MAX;
	int min_index = 0;
	for (int v = 0; v < V; v++) {
		if (sptSet[v] == false && dist[v] <= min) {
			min = dist[v];
			min_index = v;
		}
	}
	return min_index;
}

void dijkstra(int graph[][7], int src, int V) {
	int* dist = new int[V];
	bool* sptSet = new bool[V];

	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	dist[src] = 0;

	for (int count = 0; count < V - 1; count++) {
		int u = minDistance(dist, sptSet, V);
		sptSet[u] = true;
		for (int v = 0; v < V; v++) {
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
				dist[v] = dist[u] + graph[u][v];
				if (dist[u] == 0) {
					vec[v].push_back(v);
				}
				else {
					for (int k = 0; k < (int)vec[u].size(); k++) {
						vec[v].push_back(vec[u][k]);
					}
					vec[v].push_back(v);
				}
			}
		}
	}
}

pair<bool, int> conflictCheckerDest(vector < pair<int, int> > jos, vector < pair<int, int> > lucy) {

	for (int i = 0; i < (int)jos.size() - 1; i++) {
		for (int j = 0; j < (int)lucy.size() - 1; j++) {
			if (jos[i].first == lucy[j].first && jos[i].second == lucy[j].second) return make_pair(true, jos[i].first);
		}
	}
	for (int i = 0; i < (int)lucy.size(); i++) {
		if (jos[(int)jos.size() - 1].first == lucy[i].first && jos[(int)jos.size() - 1].second + 30 >= lucy[i].second && jos[(int)jos.size() - 1].second <= lucy[i].second) return make_pair(true, lucy[i].first);
	}
	for (int i = 0; i < (int)jos.size(); i++) {
		if (lucy[(int)lucy.size() - 1].first == jos[i].first && lucy[(int)lucy.size() - 1].second + 30 >= jos[i].second && lucy[(int)jos.size() - 1].second <= jos[i].second) return make_pair(true, jos[i].first);
	}
	return make_pair(false, 0);
}

pair<bool, int> conflictCheckerRet(vector < pair<int, int> > jos, vector < pair<int, int> > lucy) {

	for (int i = 0; i < (int)lucy.size(); i++) { // find alternative only for lucy
		if (jos[0].first == lucy[i].first && jos[0].second >= lucy[i].second && jos[0].second - 30 <= lucy[i].second) return make_pair(true, jos[0].first);
	}
	for (int i = 0; i < (int)jos.size(); i++) { // find alternative only for joseph
		if (lucy[0].first == jos[i].first && lucy[0].second >= jos[i].second && lucy[0].second - 30 <= jos[i].second) return make_pair(true, lucy[0].first);
	}
	for (int i = 0; i < (int)jos.size() - 1; i++) {
		for (int j = 0; j < (int)lucy.size() - 1; j++) {
			if (jos[i].first == lucy[j].first && jos[i].second == lucy[j].second) return make_pair(true, jos[i].first);
		}
	}
	return make_pair(false, 0);
}


int main() {

	int JosHotel, LucHotel, JosDest, LucDest;

	JosHotel = 0;
	LucHotel = 2;
	JosDest = 5;
	LucDest = 4;
	int node_count = 7;
	vec.resize(node_count);

	int graph[7][7] = { { 0, 4, 8, 0, 0, 0, 0 },
						{ 6, 0, 0, 0, 3, 0, 0 },
						{ 0, 0, 0, 10, 0, 16, 0 },
						{ 0, 5, 0, 0, 0, 0, 7 },
						{ 0, 0, 0, 1, 0, 13, 0 },
						{ 0, 0, 0, 0, 0, 0, 6 },
						{ 0, 0, 2, 0, 0, 0, 0 } };

	
	vector <pair <int, int> > JosephTime;
	vector <pair <int, int> > LucyTime;

	dijkstra(graph, JosHotel, node_count);
	JosephTime.push_back(make_pair(JosHotel, 0));
	int time = graph[JosHotel][vec[JosDest][0]];
	JosephTime.push_back(make_pair(vec[JosDest][0], time));
	for (int j = 1; j < (int)vec[JosDest].size(); j++) {
		time += graph[vec[JosDest][j - 1]][vec[JosDest][j]];
		JosephTime.push_back(make_pair(vec[JosDest][j], time));
	}

	vec.clear();
	vec.resize(node_count);
	dijkstra(graph, LucHotel, node_count);
	LucyTime.push_back(make_pair(LucHotel, 0));
	time = graph[LucHotel][vec[LucDest][0]];
	LucyTime.push_back(make_pair(vec[LucDest][0], time));
	for (int j = 1; j < (int)vec[LucDest].size(); j++) {
		time += graph[vec[LucDest][j - 1]][vec[LucDest][j]];
		LucyTime.push_back(make_pair(vec[LucDest][j], time));
	}

	bool noLucy = false;
	bool noJoseph = false;
	int timeAfterWaitLucy = 0;
	int timeAfterWaitJoseph = 0;
	bool IsJoseph = false;
	bool isConflict = false;
	vector <pair <int, int> > JosephTime2;
	vector <pair <int, int> > LucyTime2;
	pair<bool, int> check = conflictCheckerDest(JosephTime, LucyTime);
	if (check.first) {
		isConflict = true;

		for (int i = 0; i < (int)JosephTime.size(); i++) {
			if (JosephTime[i].first == check.second) {
				graph[JosephTime[i - 1].first][JosephTime[i].first] = 0;
			}
		}
		vec.clear();
		vec.resize(node_count);
		dijkstra(graph, JosHotel, node_count);
		if (vec[JosDest].size() > 0) {
			JosephTime2.push_back(make_pair(JosHotel, 0));
			time = graph[JosHotel][vec[JosDest][0]];
			JosephTime2.push_back(make_pair(vec[JosDest][0], time));
			for (int j = 1; j < (int)vec[JosDest].size(); j++) {
				time += graph[vec[JosDest][j - 1]][vec[JosDest][j]];
				JosephTime2.push_back(make_pair(vec[JosDest][j], time));
			}
		}
		else {
			noJoseph = true;
		}


		for (int i = 0; i < (int)LucyTime.size(); i++) {
			if (LucyTime[i].first == check.second) {
				graph[LucyTime[i - 1].first][LucyTime[i].first] = 0;
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

		//Results
		if (noLucy && noJoseph) {
			cout << "no Possible Solution is found";
			return 0;
		}
		else if (!noLucy && noJoseph) {
			check = conflictCheckerDest(JosephTime, LucyTime2);
			if (check.first) {
				cout << "no Possible Solution is found";
				return 0;
			}
			timeAfterWaitLucy = LucyTime2[(int)LucyTime2.size() - 1].second + 30;
			timeAfterWaitJoseph = JosephTime[(int)JosephTime.size() - 1].second + 30;
			IsJoseph = true;
		}
		else if (noLucy && !noJoseph) {
			check = conflictCheckerDest(JosephTime2, LucyTime);
			if (check.first) {
				cout << "no Possible Solution is found";
				return 0;
			}
			timeAfterWaitJoseph = JosephTime2[(int)JosephTime2.size() - 1].second + 30;
			timeAfterWaitLucy = LucyTime[(int)LucyTime.size() - 1].second + 30;
		}
		else {
			if (JosephTime2[(int)JosephTime2.size() - 1].second + LucyTime[(int)LucyTime.size() - 1].second > JosephTime[(int)JosephTime.size() - 1].second + LucyTime2[(int)LucyTime2.size() - 1].second) {
				check = conflictCheckerDest(JosephTime, LucyTime2);
				if (check.first) {
					cout << "no Possible Solution is found";
					return 0;
				}
				timeAfterWaitLucy = LucyTime2[(int)LucyTime2.size() - 1].second + 30;
				timeAfterWaitJoseph = JosephTime[(int)JosephTime.size() - 1].second + 30;
				IsJoseph = true;
			}
			else {
				check = conflictCheckerDest(JosephTime2, LucyTime);
				if (check.first) {
					cout << "no Possible Solution is found";
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
					graph[JosephTimeRet[i - 1].first][JosephTimeRet[i].first] = 0;
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
					cout << "no Possible Solution is found";
					return 0;
				}
			}
			else {
				cout << "no Possible Solution is found";
				return 0;
			}
		}
		else if (check.second == JosDest) {
			for (int i = 0; i < (int)LucyTimeRet.size(); i++) {
				if (LucyTime[i].first == check.second) {
					graph[LucyTimeRet[i - 1].first][LucyTimeRet[i].first] = 0;
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
					cout << "no Possible Solution is found";
					return 0;
				}
				IsJosephRet = true;
			}
			else {
				cout << "no Possible Solution is found";
				return 0;
			}
		}
		else {
			for (int i = 0; i < (int)JosephTimeRet.size(); i++) {
				if (JosephTimeRet[i].first == check.second) {
					graph[JosephTimeRet[i - 1].first][JosephTimeRet[i].first] = 0;
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
			
			for (int i = 0; i < (int)LucyTimeRet.size(); i++) {
				if (LucyTimeRet[i].first == check.second) {
					graph[LucyTimeRet[i - 1].first][LucyTimeRet[i].first] = 0;
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

			//second check
			if (noLucy && noJoseph) {
				cout << "no Possible Solution is found";
				return 0;
			}
			else if (!noLucy && noJoseph) {
				check = conflictCheckerRet(JosephTimeRet, LucyTimeRet2);
				if (check.first) {
					cout << "no Possible Solution is found";
					return 0;
				}
				IsJosephRet = true;
			}
			else if (noLucy && !noJoseph) {
				check = conflictCheckerDest(JosephTimeRet2, LucyTimeRet);
				if (check.first) {
					cout << "no Possible Solution is found";
					return 0;
				}
			}
			else {
				if (JosephTime2[(int)JosephTime2.size() - 1].second + LucyTimeRet[(int)LucyTimeRet.size() - 1].second > JosephTimeRet[(int)JosephTimeRet.size() - 1].second + LucyTime2[LucyTime2.size() - 1].second) {
					check = conflictCheckerDest(JosephTimeRet, LucyTimeRet2);
					if (check.first) {
						cout << "no Possible Solution is found";
						return 0;
					}
					IsJosephRet = true;
				}
				else {
					check = conflictCheckerDest(JosephTimeRet2, LucyTimeRet);
					if (check.first) {
						cout << "no Possible Solution is found";
						return 0;
					}
				}
			}
		}
	}

	if (!isConflictRet && !isConflict) {
		cout << "Joseph's Path, duration: " << JosephTimeRet[JosephTimeRet.size() - 1].second << endl;
		for (int i = 0; i < JosephTime.size(); i++) {
			cout << "Node: " << JosephTime[i].first << " Time: " << JosephTime[i].second << endl;
		}
		cout << "-- return --" << endl;
		for (int i = 0; i < JosephTimeRet.size(); i++) {
			cout << "Node: " << JosephTimeRet[i].first << " Time: " << JosephTimeRet[i].second << endl;
		}
		cout << "\nLucy's Path, duration: " << LucyTimeRet[LucyTimeRet.size() - 1].second << endl;
		for (int i = 0; i < LucyTime.size(); i++) {
			cout << "Node: " << LucyTime[i].first << " Time: " << LucyTime[i].second << endl;
		}
		cout << "-- return --" << endl;
		for (int i = 0; i < LucyTimeRet.size(); i++) {
			cout << "Node: " << LucyTimeRet[i].first << " Time: " << LucyTimeRet[i].second << endl;
		}
	}
	else if (isConflict && !isConflictRet) {
		if (IsJoseph) {
			cout << "Joseph's Path, duration: " << JosephTimeRet[JosephTimeRet.size() - 1].second << endl;
			for (int i = 0; i < JosephTime.size(); i++) {
				cout << "Node: " << JosephTime[i].first << " Time: " << JosephTime[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < JosephTimeRet.size(); i++) {
				cout << "Node: " << JosephTimeRet[i].first << " Time: " << JosephTimeRet[i].second << endl;
			}
			cout << "\nLucy's Path, duration: " << LucyTimeRet[LucyTimeRet.size() - 1].second << endl;
			for (int i = 0; i < LucyTime2.size(); i++) {
				cout << "Node: " << LucyTime2[i].first << " Time: " << LucyTime2[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < LucyTimeRet.size(); i++) {
				cout << "Node: " << LucyTimeRet[i].first << " Time: " << LucyTimeRet[i].second << endl;
			}
		}
		else {
			cout << "Joseph's Path, duration: " << JosephTimeRet[JosephTimeRet.size() - 1].second << endl;
			for (int i = 0; i < JosephTime2.size(); i++) {
				cout << "Node: " << JosephTime2[i].first << " Time: " << JosephTime2[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < JosephTimeRet.size(); i++) {
				cout << "Node: " << JosephTimeRet[i].first << " Time: " << JosephTimeRet[i].second << endl;
			}
			cout << "\nLucy's Path, duration: " << LucyTimeRet[LucyTimeRet.size() - 1].second << endl;
			for (int i = 0; i < LucyTime.size(); i++) {
				cout << "Node: " << LucyTime[i].first << " Time: " << LucyTime[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < LucyTimeRet.size(); i++) {
				cout << "Node: " << LucyTimeRet[i].first << " Time: " << LucyTimeRet[i].second << endl;
			}
		}
	}
	else if (isConflictRet && !isConflict) {
		if (IsJosephRet) {
			cout << "Joseph's Path, duration: " << JosephTimeRet[JosephTimeRet.size() - 1].second << endl;
			for (int i = 0; i < JosephTime.size(); i++) {
				cout << "Node: " << JosephTime[i].first << " Time: " << JosephTime[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < JosephTimeRet.size(); i++) {
				cout << "Node: " << JosephTimeRet[i].first << " Time: " << JosephTimeRet[i].second << endl;
			}
			cout << "\nLucy's Path, duration: " << LucyTimeRet2[LucyTimeRet2.size() - 1].second << endl;
			for (int i = 0; i < LucyTime.size(); i++) {
				cout << "Node: " << LucyTime[i].first << " Time: " << LucyTime[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < LucyTimeRet2.size(); i++) {
				cout << "Node: " << LucyTimeRet2[i].first << " Time: " << LucyTimeRet2[i].second << endl;
			}
		}
		else {
			cout << "Joseph's Path, duration: " << JosephTimeRet2[JosephTimeRet2.size() - 1].second << endl;
			for (int i = 0; i < JosephTime.size(); i++) {
				cout << "Node: " << JosephTime[i].first << " Time: " << JosephTime[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < JosephTimeRet2.size(); i++) {
				cout << "Node: " << JosephTimeRet2[i].first << " Time: " << JosephTimeRet2[i].second << endl;
			}
			cout << "\nLucy's Path, duration: " << LucyTimeRet[LucyTimeRet.size() - 1].second << endl;
			for (int i = 0; i < LucyTime.size(); i++) {
				cout << "Node: " << LucyTime[i].first << " Time: " << LucyTime[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < LucyTimeRet.size(); i++) {
				cout << "Node: " << LucyTimeRet[i].first << " Time: " << LucyTimeRet[i].second << endl;
			}
		}
	}
	else {
		if (IsJoseph && IsJosephRet) {
			cout << "Joseph's Path, duration: " << JosephTimeRet[JosephTimeRet.size() - 1].second << endl;
			for (int i = 0; i < JosephTime.size(); i++) {
				cout << "Node: " << JosephTime[i].first << " Time: " << JosephTime[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < JosephTimeRet.size(); i++) {
				cout << "Node: " << JosephTimeRet[i].first << " Time: " << JosephTimeRet[i].second << endl;
			}
			cout << "\nLucy's Path, duration: " << LucyTimeRet2[LucyTimeRet2.size() - 1].second << endl;
			for (int i = 0; i < LucyTime2.size(); i++) {
				cout << "Node: " << LucyTime2[i].first << " Time: " << LucyTime2[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < LucyTimeRet2.size(); i++) {
				cout << "Node: " << LucyTimeRet2[i].first << " Time: " << LucyTimeRet2[i].second << endl;
			}
		}
		else if (IsJoseph && !IsJosephRet) {
			cout << "Joseph's Path, duration: " << JosephTimeRet2[JosephTimeRet2.size() - 1].second << endl;
			for (int i = 0; i < JosephTime.size(); i++) {
				cout << "Node: " << JosephTime[i].first << " Time: " << JosephTime[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < JosephTimeRet2.size(); i++) {
				cout << "Node: " << "Node: " << JosephTimeRet2[i].first << " Time: " << JosephTimeRet2[i].second << endl;
			}
			cout << "\nLucy's Path, duration: " << LucyTimeRet[LucyTimeRet.size() - 1].second << endl;
			for (int i = 0; i < LucyTime2.size(); i++) {
				cout << "Node: " << LucyTime2[i].first << " Time: " << LucyTime2[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < LucyTimeRet.size(); i++) {
				cout << "Node: " << LucyTimeRet[i].first << " Time: " << LucyTimeRet[i].second << endl;
			}
		}
		else if (!IsJoseph && IsJosephRet) {
			cout << "Joseph's Path, duration: " << JosephTimeRet[JosephTimeRet.size() - 1].second << endl;
			for (int i = 0; i < JosephTime2.size(); i++) {
				cout << "Node: " << JosephTime2[i].first << " Time: " << JosephTime2[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < JosephTimeRet.size(); i++) {
				cout << "Node: " << JosephTimeRet[i].first << " Time: " << JosephTimeRet[i].second << endl;
			}
			cout << "\nLucy's Path, duration: " << LucyTimeRet2[LucyTimeRet2.size() - 1].second << endl;
			for (int i = 0; i < LucyTime.size(); i++) {
				cout << "Node: " << LucyTime[i].first << " Time: " << LucyTime[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < LucyTimeRet2.size(); i++) {
				cout << "Node: " << LucyTimeRet2[i].first << " Time: " << LucyTimeRet2[i].second << endl;
			}
		}
		else {
			cout << "Joseph's Path, duration: " << JosephTimeRet2[JosephTimeRet2.size() - 1].second << endl;
			for (int i = 0; i < JosephTime2.size(); i++) {
				cout << "Node: " << JosephTime2[i].first << " Time: " << JosephTime2[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < JosephTimeRet2.size(); i++) {
				cout << "Node: " << JosephTimeRet2[i].first << " Time: " << JosephTimeRet2[i].second << endl;
			}
			cout << "\nLucy's Path, duration: " << LucyTimeRet[LucyTimeRet.size() - 1].second << endl;
			for (int i = 0; i < LucyTime.size(); i++) {
				cout << "Node: " << LucyTime[i].first << " Time: " << LucyTime[i].second << endl;
			}
			cout << "-- return --" << endl;
			for (int i = 0; i < LucyTimeRet.size(); i++) {
				cout << "Node: " << LucyTimeRet[i].first << " Time: " << LucyTimeRet[i].second << endl;
			}
		}
	}


	return 0;
}
