算法描述：

一、将整个词典的单词分组
    由于每次输入的两个单词长度一致（记为n）， 若它们存在变换词阶，变换词阶里的所有单词的长度也为n. 因此可以将整个词典里的单词，按照单词长度分组，对于长度为n的所有单词，建立一个单独的网络。
    
二、建立网络
    输入：长度为n的单词组
    输出：长度为n的单词组对应的网络
    
    考虑到变换词阶中，相邻单词只相差一个字母，并且两个单词都在词典中。
    如单词data是date的邻居。
    在将要建立的网络中，互为邻居的两个单词有一条边相邻。
    为了快速获取某个单词的邻居，使用这样的方法：
    
    边记录：
    edges[int 修改位编号][string 删掉修改位后的字符串] = [修改位的字符]
    如data有：
    edges[0]["ata"] = ['d',...]
    edges[1]["dta"] = ['a',...]
    edges[2]["dae"] = ['t',...]
    edges[3]["dat"] = ['a',...]
    若要获得单词data的邻居，则获取edges[0]["ata"], edges[1]["dta"], edges[2]["dae"], edges[3]["dat"]的值
    如edges[3]["dat"] = ['e', ...], 表示data存在邻居date.
    获取邻居的时间复杂度为：nlog(n)
    
    这样建立边记录，即可建成网络
    
三、网络搜索
    网络建立后，对于输入的两个单词，使用BFS（广度优先搜索）的方法查找两个单词是否连通。
    若两单词连通，需要输出它们的路径。
    因此在使用BFS时，记录某个单词的上一个节点。
    若找到目标节点，则根据记录从目标点走到出发点，得到完整路径。
    
伪代码：
    //输入单词组，输出边记录
    边记录 BuildNetwork(vector<string> words){
        vector<map<string, set<char> > > edges; // 边记录
        for (words中每一个单词: wordA){
            for (words中每一个单词: wordB){
                if (wordA != wordB and wordA和wordB正好相差一个字母){
                    在edges中添加一条边，该边连接wordA与wordB;
                }
            }
        }
        return edges;
    }
    
    //传入单词word和边记录, 返回word的所有邻居
    vector<string> GetNeibors(word, 边记录 edges){
        vector<string> vs;
        len = word的长度
        for (int i = 0;i < len; ++i){
            string s = word; //删掉第i位后的结果，如word删除第0位的结果为ord
            for (对于edges[i][s]中的每一个元素e){
                string neibor = 构建邻居字符串(i,s,edges[i][s]); // 如e = 'w', i = 0, s = ord时， 可得到单词word
                vs.push_back(neibor);
            }
        }
        return vs;
    }
    
    /*
        传入两个单词，返回路径； 若返回值为空， 则路径不存在
        使用算法：BFS 广度优先搜索
    */
    vector<string> FindPath(string wordA, string wordB, 边记录 edges){
        if (wordA和wordB长度不一致)return vector<string>()；//空路径
        if (wordA == wordB)return vector<string>(wordA); // 两个单词一样
        set<string> vis; // 记录单词是否被访问
        queue<stack<string> > q; // BFS的队列
        q.push(stack<string>(wordA));
        vis.insert(wordA); // 记录wordA
        while (!q.empty()){
            st = 队列q的首元素, 并将该元素出列；
            word = st的栈顶元素
            if (word == wordB){
                //到达目标节点
                //此时从st的栈底到栈顶， 对应变换阶梯的每一个单词
                vector<string> path;
                path.resize(st.size())
                for (int i = st.size() - 1; i >= 0; i--){
                    path[i] = st.top();
                    st.pop();
                }
                return path; // 返回变换阶梯的结果
            }
            for (对于GetNeibors(word, edges)得到的每一个邻居: w){
                //如果w还没被标记， 则加入队列
                if (w not in vis){
                    stack new_st = st;
                    new_st.push(w); // 将邻居加入新的栈
                    q.push(new_st); // 加入队列
                    vis.insert(w); // 记录w
                }
            }
        }
        return vector<string>(); // 没有变换阶梯
    }