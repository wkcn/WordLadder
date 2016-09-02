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

//�������г���Ϊn�ĵ���
class WordsNetwork{
	public:
        WordsNetwork(){}
		//���볤��Ϊn�ĵ�����
		WordsNetwork(vector<string> &vs){
			//��������
			BuildNetwork(vs);
		}
		//���볤��Ϊn���������ʣ�����·���� ������ֵΪ�գ� ��·��������
		//ʹ���㷨�� BFS �����������
		vector<string> GetPath(string from, string to){
			if (from.size() != len || to.size() != len)return vector<string>(); // ���Ϸ�
			if (from == to)return vector<string>(1, from); // ����ͬһ�ڵ�
			queue<string> q; // ����Ԫ�� �����ʣ� ���ʵĸ��ף�
			q.push(from);
            map<string, string> rec;
            rec[from] = "";
			
			while(!q.empty()){
				string word = q.front();
                q.pop();
				if (word == to){
					// ����Ŀ���
                    stack<string> st;
                    while(word.size()){
                        st.push(word);
                        word = rec[word]; // ��ȡ��һ���ڵ�
                    }
                    vector<string> path;
                    while(!st.empty()){
                        path.push_back(st.top());
                        st.pop();
                    }
                    return path;
				}
                
                //����ھ�
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
                        // �����ھӵĵ���
                        for (int k = 0;k < len; ++k){
                            if (i == k){
                                neibor += *iter;
                            }else{
                                neibor += word[k];
                            }
                        }
                        if (rec.count(neibor))continue; // �ѷ��ʹ�
                        rec[neibor] = word;
                        q.push(neibor);
                    }
                }
			}
			return vector<string>();
		}
	private:
		void BuildNetwork(vector<string> &vs){
			//��vsΪ��
			if (vs.empty())return;
			//���ڴ��뵥����ĳ���һ�£����ȡ��һ������
			len = vs[0].size();
			edges.resize(len);
			for (int i = 0;i < vs.size(); ++i){
				string &word = vs[i];
				for (int j = 0;j < len;++j){
					string cut; // ɾ����jλ���ʺ�Ľ��
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
			�߼�¼
			edges[int �޸�λ���][string ɾ���޸�λ����ַ���] = [�޸�λ���ַ�]
			��data�У�
			edges[0]["ata"] = ['d',...]
			edges[1]["dta"] = ['a',...]
			edges[2]["dae"] = ['t',...]
			edges[3]["dat"] = ['a',...]
			��Ҫ��õ���data���ھӣ����ȡedges[0]["ata"], edges[1]["dta"], edges[2]["dae"], edges[3]["dat"]��ֵ
			��ȡ�ھӵ�ʱ�临�Ӷ�Ϊ��nlog(n)
		*/
		vector<map<string, set<char> > > edges;

};

int main(){
    cout << "��ȡ�ļ���dictionary-yawl.txt" << endl;
	ifstream fin("dictionary-yawl.txt");
    if (fin.fail()){
        cout << "��ȡ�ļ�ʧ�ܣ��뽫dictionary-yawl.txt�ļ�����exe�ļ�����Ŀ¼" << endl;
        return 0;
    }
    vector<vector<string> > words;
	while(!fin.eof()){
		string word;
		fin >> word;
        int len = word.size();
        if (words.size() <= len)words.resize(len + 1);
        words[len].push_back(to_lower(word)); // תΪСд�������ֵ�
	}
    
    cout << "���������У���ȴ�" << endl;
    //��������
    vector<WordsNetwork> ns;
    for (int i = 0;i < words.size(); ++i){
        ns.push_back(WordsNetwork(words[i]));
    }
    while(true){
        cout << "������������ͬ���ȵĵ��ʣ�" << endl;
        string wordA, wordB;
        cin >> wordA;
        cin >> wordB;
        if (wordA.size() != wordB.size()){
            cout << "���ʳ��Ȳ�ƥ��" << endl;
        }else{
            vector<string> path = ns[wordA.size()].GetPath(wordA, wordB);
            if (path.empty()){
                cout << "��" << wordA << "��" << wordB << "�����ڱ任����" << endl;
            }else{
                cout << "�任����Ϊ��";
                for (int i = 0;i < path.size(); ++i){
                    cout << path[i] << "    ";
                }
                cout << endl;
            }
        }
    }
	return 0;
}