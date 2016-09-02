#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

int main(){
	ifstream fin("dictionary-yawl.txt");
	string name;
	int i = 0;
	vector<int> vs;
	vs.resize(30);
	set<string> ss;
	while(!fin.eof()){
		fin >> name;
		ss.insert(name);
		vs[name.size()]++;
	}
	int p = 0;
	for (set<string>::iterator iter = ss.begin();iter != ss.end();iter++){
		string v = *iter;
		int y = 0;
		for (int u = 0;u < v.size();++u){
			for (int a = 'A';a <= 'Z';++a){
				string q = v;
				q[u] = a;
				if (ss.count(q)){
					++y;
				}
			}
		}
		if (y > p)p = y;
	}
	cout << p << endl;
	for (int i = 0;i < 30;++i)
		cout << i << ": " << vs[i] << endl;
	return 0;
}