#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

//处理所有长度为n的单词
class WordNetwork{
	public:
		//传入长度为n的单词组
		WordNetwork(vector<string> &vs){
			
		}
	private:
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
	ifstream fin("dictionary-yawl.txt");
	while(!fin.eof()){
		string word;
		fin >> word;
	}
	return 0;
}