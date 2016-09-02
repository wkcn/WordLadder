#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <utility>
using namespace std;

//处理所有长度为n的单词
class WordNetwork{
	public:
		//传入长度为n的单词组
		WordNetwork(vector<string> &vs){
			//构建网络
			BuildNetwork(vs);
		}
		//传入长度为n的两个单词，返回路径； 若返回值为空， 则路径不存在
		//使用算法， BFS 广度优先搜索
		vector<string> GetPath(string from, string to){
			if (from.size() == len || to.size() == len)return vector<string>(); // 不合法
			if (from == to)return vector<string>(from); // 对于同一节点
			set<string> vis; // 已访问节点
			queue<pair<string, string> > q; // 队列元素 （单词， 单词的父亲）
			q.push(make_pair(from, ""));
			vis.insert(from);
			
			while(!q.empty()){
				pair<string, string> p = q.front();
				q.pop();
				string word = p.first();
				string parent = p.second();
				if (word == to){
					// 到达目标点
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
	ifstream fin("dictionary-yawl.txt");
	while(!fin.eof()){
		string word;
		fin >> word;
	}
	return 0;
}