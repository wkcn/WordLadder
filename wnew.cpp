#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <queue>
#include <utility>
#include <algorithm>
#include <cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;

string to_lower(string str){
    string res;
    for (int i = 0;i < str.size(); ++i){
        char c = str[i];
        if (c >= 'A' && c <= 'Z')c = c - 'A' + 'a';
        res += c;
    }
    return res;
}

template <typename T>
void Shuffle(vector<T> &vs){
	for (int i = 0;i < vs.size(); ++i){
		int r = rand() % vs.size();
		swap(vs[i], vs[r]);
	}
}

template <typename T>
T gmin(T a, T b){
	return a<b?a:b;
}

//处理所有长度为n的单词
class WordsNetwork{
	public:
        WordsNetwork(){}
		//传入长度为n的单词组
		WordsNetwork(vector<string> &vs){
			//构建网络
			BuildNetwork(vs);
		}
		//传入长度为n的两个单词，返回路径； 若返回值为空， 则路径不存在
		//使用算法， BFS 广度优先搜索
		vector<string> GetPath(string from, string to){
			if (from.size() != len || to.size() != len)return vector<string>(); // 不合法
			if (from == to)return vector<string>(1, from); // 对于同一节点
			if (!sid.count(from) || !sid.count(to))return vector<string>(); // 不存在其中一个单词
			vector<int> rec(sdata.size());
			vector<bool> vis(sdata.size(), false);
			int fid = sid[from];
			int tid = sid[to];
			queue<int> q; // 队列元素
			q.push(fid);
			rec[fid] = -1;
			vis[fid] = true;
			while(!q.empty()){
				int id = q.front();
				q.pop();
				if (id == tid){
					//到达目标点
					stack<string> st;
					while(id != -1){
						st.push(sdata[id]);
						id = rec[id]; // 取上一个节点
					}
					vector<string> path;
                    while(!st.empty()){
                        path.push_back(st.top());
                        st.pop();
                    }
                    return path;
				}
				// 没有达到目标点，添加邻居
				for (int i = 0;i < edges[id].size(); ++i){
					int nid = edges[id][i];
					if (vis[nid])continue;
					vis[nid] = true;
					rec[nid] = id;
					q.push(nid);
				}
			}
			return vector<string>();
		}
		//得到该长度下, 最长词阶级
		//从一个顶点出发，进行BFS，访问所有顶点,取最大路径
		vector<string> GetMaxPath(){
			vector<string> maxPath;
			for (int i = 0;i < sdata.size(); ++i){
				//从i出发				
				vector<bool> vis(sdata.size(), false);
				vis[i] = true;
				queue<pair<int, int> > q;
				q.push(make_pair(i, 0));
				int tid = i;
				int maxDis = 0;
				while(!q.empty()){
					pair<int, int> p;
					p = q.front();
					q.pop();
					int id = p.first;
					int distance = p.second;
					if (distance > maxDis){
						maxDis = distance;
						tid = id;
					}
					for (int i = 0;i < edges[id].size();++i){
						int u = edges[id][i];
						if (!vis[u]){
							vis[u] = true;
							q.push(make_pair(u, distance + 1));
						}
					}
				}
				vector<string> path = GetPath(sdata[i], sdata[tid]);
				if (path.size() > maxPath.size())maxPath = path;
			}
			return maxPath;
		}
		vector<vector<string> > GetPaths(int dis){
			vector<vector<string> > paths;
			vector<int> idList(sdata.size());
			for (int i = 0;i < sdata.size(); ++i){
				idList[i] = i;
			}
			Shuffle(idList);
			for (int w = 0;w < sdata.size(); ++w){
				int i = idList[w];
				//从i出发				
				vector<bool> vis(sdata.size(), false);
				vis[i] = true;
				queue<pair<int, int> > q;
				q.push(make_pair(i, 0));
				int maxDis = 0;
				while(!q.empty()){
					pair<int, int> p;
					p = q.front();
					q.pop();
					int id = p.first;
					int distance = p.second;
					if (distance == dis){
						vector<string> path = GetPath(sdata[i], sdata[id]);
						paths.push_back(path);	
						if (paths.size() > 10)break;
						continue;
					}
					for (int i = 0;i < edges[id].size();++i){
						int u = edges[id][i];
						if (!vis[u]){
							vis[u] = true;
							q.push(make_pair(u, distance + 1));
						}
					}
				}
			}
			return paths;
		}
	private:
		void BuildNetwork(vector<string> &vs){
			//若vs为空
			if (vs.empty())return;
			//记下字符串
			sdata = vs;
			//由于传入单词组的长度一致，因此取第一个即可
			len = vs[0].size();
			str_edges.resize(len);
			for (int i = 0;i < vs.size(); ++i){
				string &word = vs[i];
				sid[word] = i; // 记录id
				for (int j = 0;j < len;++j){
					string cut; // 删除第j位单词后的结果
					for (int k = 0;k < len;++k){
						if (j == k)continue;
						cut += word[k];
					}
					str_edges[j][cut].insert(word[j]);
				}
			}
			//建立id边
			set<pair<int, int> > vis;  // 已经添加边
			edges.resize(vs.size());
			for (int i = 0;i < vs.size(); ++i){
				string &word = vs[i];
				int fid = sid[word];
				for (int j = 0;j < len; ++j){
					//改变第j位
					string s;
					for (int k = 0;k < len; ++k){
						if (j != k)s += word[k];
					}
					set<char> &se = str_edges[j][s];
					//构造邻居
                    for (set<char>::iterator iter = se.begin(); iter != se.end(); ++iter){
						if (*iter == word[j])continue;
						string neibor = word;
						neibor[j] = *iter; // 改变字母
						int tid = sid[neibor];
						//fid -> tid
						if (vis.count(make_pair(fid, tid)) || vis.count(make_pair(tid, fid)))continue; // 已添加
						vis.insert(make_pair(fid, tid)); // 记录
						edges[fid].push_back(tid);
						edges[tid].push_back(fid);
					}
				}
			}
		}
	private:
		int len;
		/*
			边记录
			str_edges[int 修改位编号][string 删掉修改位后的字符串] = [修改位的字符]
			如data有：
			str_edges[0]["ata"] = ['d',...]
			str_edges[1]["dta"] = ['a',...]
			str_edges[2]["dae"] = ['t',...]
			str_edges[3]["dat"] = ['a',...]
			若要获得单词data的邻居，则获取str_edges[0]["ata"], str_edges[1]["dta"], str_edges[2]["dae"], str_edges[3]["dat"]的值
			获取邻居的时间复杂度为：nlog(n)
		*/
		vector<map<string, set<char> > > str_edges;
		map<string, int> sid; // 从string映射到id
		vector<vector<int> > edges; // 边
		vector<string> sdata;
};

void TwoWords(vector<WordsNetwork> &ns){
 
	while(true){
		cout << "Please input two words which has SAME LENGTH" << endl;
		string wordA, wordB;
		cin >> wordA;
		cin >> wordB;
		if (wordA.size() != wordB.size()){
			cout << "The length of two words doesn't match" << endl;
		}else{
			vector<string> path = ns[wordA.size()].GetPath(wordA, wordB);
			if (path.empty()){
				cout << "From " << wordA << " to " << wordB << ", it hasn't word ladder" << endl;
			}else{
				cout << "WordLadder is ";
				for (int i = 0;i < path.size(); ++i){
					cout << path[i] << "  ";
				}
				cout << endl;
			}
		}
	}

}

void GetMaxWordLadder(vector<WordsNetwork> &ns){
	cout << "MaxWordLadder: " << endl;
	for (int j = 1; j < ns.size(); ++j){
		vector<string> path = ns[j].GetMaxPath();
		cout << "\t" << j << ": ";
		for (int i = 0;i < path.size(); ++i){
			cout << path[i] << "  ";
		}
		cout << endl;
	}
}

void GetPathsByDis(vector<WordsNetwork> &ns){
	while(1){
		cout << "Please Input wordLen and distance" << endl;
		int len, dis;
		cin >> len >> dis;
		if (len >= ns.size()){
			cout << "wordLen is over maxWordLen" << endl;
			continue;
		}
		vector<vector<string> > paths = ns[len].GetPaths(dis);
		Shuffle(paths);
		for (int j = 1; j < gmin(paths.size(), size_t(10)); ++j){
			cout << "Path " << j << ":";
			vector<string> &path = paths[j];
			for (int i = 0;i < path.size(); ++i){
				cout << path[i] << "  ";
			}
			cout << endl;
		}
	}
}

int main(){
	srand(time(0));
    cout << "Reading dictionary dictionary-yawl.txt" << endl;
	ifstream fin("dictionary-yawl.txt");
    if (fin.fail()){
        cout << "Reading dictionary failed，Please put dictionary-yawl.txt on the path of *.exe" << endl;
        return 0;
    }
    vector<vector<string> > words;
	while(!fin.eof()){
		string word;
		fin >> word;
        int len = word.size();
        if (words.size() <= len)words.resize(len + 1);
        words[len].push_back(to_lower(word)); // 转为小写并加入字典
	}
    
    cout << "Building Network, Please Wait... it may cost five seconds :-(" << endl;
    //构建网络
    vector<WordsNetwork> ns(words.size() + 1);

    for (int i = 1;i < words.size(); ++i){
        ns[i] = WordsNetwork(words[i]);
    }

SELECT_MODE:
	cout << "Please Input a Number:\n\
	1: Input Two Words and Get Word Ladder\n\
	2: Get MaxWordLadder\n\
	3: Get Paths by Distance\n";

	int mode;
	cin >> mode;
	switch(mode){
		case 1:
			TwoWords(ns);
			break;
		case 2:
			GetMaxWordLadder(ns);
			goto SELECT_MODE;
			break;
		case 3:
			GetPathsByDis(ns);
			break;
		default:
			cout << "Error Input"<< endl;
			goto SELECT_MODE;
	}

   	return 0;
}
