#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <queue>
#include <utility>
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
			queue<string> q; // 队列元素 （单词， 单词的父亲）
			q.push(from);
            map<string, string> rec;
            rec[from] = "";
			
			while(!q.empty()){
				string word = q.front();
                q.pop();
				if (word == to){
					// 到达目标点
                    stack<string> st;
                    while(word.size()){
                        st.push(word);
                        word = rec[word]; // 获取上一个节点
                    }
                    vector<string> path;
                    while(!st.empty()){
                        path.push_back(st.top());
                        st.pop();
                    }
                    return path;
				}
                
                //添加邻居
                for (int i = 0;i < len; ++i){
                    string s;
                    for (int j = 0;j < len; ++j){
                        if (i != j){
                            s += word[j];
                        }
                    }
                    set<char> &se = edges[i][s];
                    for (set<char>::iterator iter = se.begin(); iter != se.end(); ++iter){
                        string neibor;
                        // 构造邻居的单词
                        for (int k = 0;k < len; ++k){
                            if (i == k){
                                neibor += *iter;
                            }else{
                                neibor += word[k];
                            }
                        }
                        if (rec.count(neibor))continue; // 已访问过
                        rec[neibor] = word;
                        q.push(neibor);
                    }
                }
			}
			return vector<string>();
		}
	private:
		void BuildNetwork(vector<string> &vs){
			//若vs为空
			if (vs.empty())return;
			//由于传入单词组的长度一致，因此取第一个即可
			len = vs[0].size();
			edges.resize(len);
			for (int i = 0;i < vs.size(); ++i){
				string &word = vs[i];
				for (int j = 0;j < len;++j){
					string cut; // 删除第j位单词后的结果
					for (int k = 0;k < len;++k){
						if (j == k)continue;
						cut += word[k];
					}
					edges[j][cut].insert(word[j]);
				}
			}
		}
	private:
		int len;
		/*
			边记录
			edges[int 修改位编号][string 删掉修改位后的字符串] = [修改位的字符]
			如data有：
			edges[0]["ata"] = ['d',...]
			edges[1]["dta"] = ['a',...]
			edges[2]["dae"] = ['t',...]
			edges[3]["dat"] = ['a',...]
			若要获得单词data的邻居，则获取edges[0]["ata"], edges[1]["dta"], edges[2]["dae"], edges[3]["dat"]的值
			获取邻居的时间复杂度为：nlog(n)
		*/
		vector<map<string, set<char> > > edges;

};

int main(){
    cout << "读取文件：dictionary-yawl.txt" << endl;
	ifstream fin("dictionary-yawl.txt");
    if (fin.fail()){
        cout << "读取文件失败，请将dictionary-yawl.txt文件放在exe文件所在目录" << endl;
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
    
    cout << "构建网络中，请等待" << endl;
    //构建网络
    vector<WordsNetwork> ns;
    for (int i = 0;i < words.size(); ++i){
        ns.push_back(WordsNetwork(words[i]));
    }
    while(true){
        cout << "请输入两个相同长度的单词：" << endl;
        string wordA, wordB;
        cin >> wordA;
        cin >> wordB;
        if (wordA.size() != wordB.size()){
            cout << "单词长度不匹配" << endl;
        }else{
            vector<string> path = ns[wordA.size()].GetPath(wordA, wordB);
            if (path.empty()){
                cout << "从" << wordA << "到" << wordB << "不存在变换阶梯" << endl;
            }else{
                cout << "变换阶梯为：";
                for (int i = 0;i < path.size(); ++i){
                    cout << path[i] << "    ";
                }
                cout << endl;
            }
        }
    }
	return 0;
}