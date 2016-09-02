#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

//�������г���Ϊn�ĵ���
class WordNetwork{
	public:
		//���볤��Ϊn�ĵ�����
		WordNetwork(vector<string> &vs){
			
		}
	private:
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