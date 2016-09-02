#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <utility>
using namespace std;

//�������г���Ϊn�ĵ���
class WordNetwork{
	public:
		//���볤��Ϊn�ĵ�����
		WordNetwork(vector<string> &vs){
			//��������
			BuildNetwork(vs);
		}
		//���볤��Ϊn���������ʣ�����·���� ������ֵΪ�գ� ��·��������
		//ʹ���㷨�� BFS �����������
		vector<string> GetPath(string from, string to){
			if (from.size() == len || to.size() == len)return vector<string>(); // ���Ϸ�
			if (from == to)return vector<string>(from); // ����ͬһ�ڵ�
			set<string> vis; // �ѷ��ʽڵ�
			queue<pair<string, string> > q; // ����Ԫ�� �����ʣ� ���ʵĸ��ף�
			q.push(make_pair(from, ""));
			vis.insert(from);
			
			while(!q.empty()){
				pair<string, string> p = q.front();
				q.pop();
				string word = p.first();
				string parent = p.second();
				if (word == to){
					// ����Ŀ���
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
	ifstream fin("dictionary-yawl.txt");
	while(!fin.eof()){
		string word;
		fin >> word;
	}
	return 0;
}