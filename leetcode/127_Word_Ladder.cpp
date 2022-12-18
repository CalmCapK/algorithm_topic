//思路1 最短路，预处理图关系
int mp[5010][5010];
class Solution {
public:
    bool check(string a, string b){
        if(a.size() != b.size()) return false;
        int cnt = 0;
        int n = a.size();
        for(int i = 0; i < n; i++){
            if(a[i] != b[i]){
                if(cnt == 0) cnt+=1;
                else return false;
            }
        }
        return true;
    }
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int n = wordList.size();
        int st = -1;
        int ed = -1;
        // cout << "---" << n << endl;
        for(int i = 0; i < n; i++){
            mp[i][i] = 0;
            if(wordList[i] == beginWord) st = i;
            if(wordList[i] == endWord) ed = i;
            for(int j = i+1; j < n; j++){
                mp[i][j] = 0;
                mp[j][i] = 0;
                //  cout << i << " " << j << endl;
                if(check(wordList[i], wordList[j])){
                    mp[i][j] = 1;
                    mp[j][i] = 1;
                }
            }
        }
        // cout << "---" << endl;
        if(ed == -1){
            return 0;
        }
        queue<pair<int, int> >q;
        while(!q.empty()){
            q.pop();
        }
        int vis[5010];
        memset(vis, 0, sizeof(vis));
        if(st == -1){
            for(int i = 0; i < n; i++){
                if(check(beginWord, wordList[i])){
                    q.push(make_pair(i, 2));
                    vis[i] = 1;
                }
            }
        }else{
            q.push(make_pair(st, 1));
            vis[st] = 1;
        }
        while(!q.empty()){
            pair<int, int> tmp = q.front();
            q.pop();
            if(tmp.first == ed) return tmp.second;
            for(int i = 0; i < n; i++){
                if(mp[tmp.first][i] == 1 && vis[i] == 0){
                    // cout <<  wordList[tmp.first] << " " << wordList[i] << " " << tmp.second+1 << " " << vis[i] << " " << endl;
                    q.push(make_pair(i, tmp.second+1));
                    vis[i] = 1;
                }
            }
        }
        return 0;
    }
};

//思路2 最短路，不预处理图关系
class Solution {
public:
    bool check(string a, string b){
        if(a.size() != b.size()) return false;
        int cnt = 0;
        int n = a.size();
        for(int i = 0; i < n; i++){
            if(a[i] != b[i]){
                if(cnt == 0) cnt+=1;
                else return false;
            }
        }
        return true;
    }
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int n = wordList.size();
        int st = -1;
        int ed = -1;
        for(int i = 0; i < n; i++){
            if(endWord == wordList[i]) ed = i;
            if(beginWord == wordList[i]) st = i;
        }
        if(ed == -1) return 0;

        queue<pair<int, int> >q;
        while(!q.empty()){
            q.pop();
        }
        q.push(make_pair(-1, 1));
        
        int vis[5010];
        memset(vis, 0, sizeof(vis));
        if(st != -1) vis[st] = 1;
        
        while(!q.empty()){
            pair<int, int> tmp = q.front();
            q.pop();
            if(tmp.first == ed) return tmp.second;
            string s = "";
            if(tmp.first == -1){
                s = beginWord;
            }else{
                s = wordList[tmp.first];
            }
            for(int i = 0; i < n; i++){
                if(check(s, wordList[i]) && vis[i] == 0){
                    // cout <<  wordList[tmp.first] << " " << wordList[i] << " " << tmp.second+1 << " " << vis[i] << " " << endl;
                    q.push(make_pair(i, tmp.second+1));
                    vis[i] = 1;
                }
            }
        }
        return 0;
    }
};

//思路3 最短路，枚举字符变化
class Solution {
public:
    map<string, int>mp;
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int n = wordList.size();
        int st = -1;
        int ed = -1;
        mp.clear();
        for(int i = 0; i < n; i++){
            if(endWord == wordList[i]) ed = i;
            if(beginWord == wordList[i]) st = i;
            mp[wordList[i]] = i;
        }
        if(ed == -1) return 0;

        queue<pair<int, int> >q;
        while(!q.empty()){
            q.pop();
        }
        q.push(make_pair(-1, 1));
        
        int vis[5010];
        memset(vis, 0, sizeof(vis));
        if(st != -1) vis[st] = 1;
        
        while(!q.empty()){
            pair<int, int> tmp = q.front();
            q.pop();
            if(tmp.first == ed) return tmp.second;
            string s = "";
            if(tmp.first == -1){
                s = beginWord;
            }else{
                s = wordList[tmp.first];
            }

            int m = s.size();
            for(int i = 0; i < m; i++){
                for(char j = 'a'; j <= 'z'; j++){
                    if(j == s[i]) continue;
                    string ns = s;
                    ns[i] = j;
                    //cout << s << " " << ns << " " <<  tmp.second+1 << " " << mp[ns] << " " << vis[mp[ns]] << endl;
                    if(mp.find(ns) != mp.end() && vis[mp[ns]] == 0){
                        q.push(make_pair(mp[ns], tmp.second+1));
                        vis[mp[ns]] = 1;
                    }
                }
            }
        }
        return 0;
    }
};

//思路4 广度优先搜索+枚举字符变化+合并map和vis和pair
class Solution {
public:
    map<string, int>mp;
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int n = wordList.size();
        int st = -1;
        int ed = -1;
        mp.clear();
        for(int i = 0; i < n; i++){
            if(endWord == wordList[i]) ed = i;
            if(beginWord == wordList[i]) st = i;
            mp[wordList[i]] = 0;
        }
        if(ed == -1) return 0;

        queue<string>q;
        while(!q.empty()){
            q.pop();
        }
        q.push(beginWord);
        mp[beginWord] = 1;
        
        while(!q.empty()){
            string s = q.front();
            q.pop();
            if(s == endWord) return mp[s];
            int m = s.size();
            for(int i = 0; i < m; i++){
                for(char j = 'a'; j <= 'z'; j++){
                    if(j == s[i]) continue;
                    string ns = s;
                    ns[i] = j;
                    //cout << s << " " << ns << " " <<  mp[s] + 1 << endl;
                    if(mp.find(ns) != mp.end() && mp[ns] == 0){
                        q.push(ns);
                        mp[ns] = mp[s] + 1;
                    }
                }
            }
        }
        return 0;
    }
};

//思路5 广度优先搜索+虚拟节点
class Solution {
public:
    map<string, int>mp;
    int cnt = 0;
    vector<vector<int>> edge;
    void addWord(string s){
        if(mp.find(s) == mp.end()){
            mp[s] = cnt++;
            edge.emplace_back();
        }
    }
    void addEdge(string s){
        if(mp.find(s) != mp.end()) return;
        addWord(s);
        int n = s.size();
        for(int i = 0; i < n; i++){
            string ns = s;
            ns[i] = '*';
            addWord(ns);
            edge[mp[s]].push_back(mp[ns]);
            edge[mp[ns]].push_back(mp[s]);
        }
    }
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int n = wordList.size();
        addEdge(beginWord);
        for(int i = 0; i < n; i++){
            addEdge(wordList[i]);
        }
        if(mp.find(endWord) == mp.end()) return 0;
     
        int vis[cnt+10];
        memset(vis, -1, sizeof(vis));
        queue<int>q;
        while(!q.empty()){
            q.pop();
        }
        q.push(mp[beginWord]);
        vis[mp[beginWord]] = 1;
        
        //思路5 广度优先搜索+虚拟节点
        // while(!q.empty()){
        //     int id = q.front();
        //     q.pop();
        //     if(id == mp[endWord]) return vis[id];
        //     for(int i = 0; i < edge[id].size(); i++){
        //         int nx = edge[id][i];
        //         if(vis[nx] != -1) continue;
        //         for(int j = 0; j < edge[nx].size(); j++){
        //             int nxx = edge[nx][j];
        //             if(vis[nxx] == -1){
        //                 q.push(nxx);
        //                 vis[nxx] = vis[id] + 1;
        //             }
        //         }
        //     }
        // }

        //思路6 广度优先搜索+虚拟节点+queue放虚拟节点
        while(!q.empty()){
            int id = q.front();
            q.pop();
            if(id == mp[endWord]) return (vis[id]+1)/2;
            for(int i = 0; i < edge[id].size(); i++){
                int nx = edge[id][i];
                if(vis[nx] == -1){
                    q.push(nx);
                    vis[nx] = vis[id] + 1;
                }
            }
        }
        return 0;
    }
};

//思路7 双向广度优先搜索+虚拟节点+queue放虚拟节点
class Solution {
public:
    map<string, int>mp;
    int cnt = 0;
    vector<vector<int>> edge;
    void addWord(string s){
        if(mp.find(s) == mp.end()){
            mp[s] = cnt++;
            edge.emplace_back();
        }
    }
    void addEdge(string s){
        if(mp.find(s) == mp.end()) return;
        addWord(s);
        int n = s.size();
        for(int i = 0; i < n; i++){
            string ns = s;
            ns[i] = '*';
            addWord(ns);
            edge[mp[s]].push_back(mp[ns]);
            edge[mp[ns]].push_back(mp[s]);
        }
    }
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int n = wordList.size();
        addEdge(beginWord);
        for(int i = 0; i < n; i++){
            addEdge(wordList[i]);
        }
        if(mp.find(endWord) == mp.end()) return 0;
     
        int vis[cnt+10];
        memset(vis, -1, sizeof(vis));
        vis[mp[beginWord]] = 1;

        queue<int>q;
        while(!q.empty()){
            q.pop();
        }
        q.push(mp[beginWord]);

        int vis_[cnt+10];
        memset(vis_, -1, sizeof(vis_));
        vis_[mp[endWord]] = 1;
        
        queue<int>q_;
        while(!q_.empty()){
            q_.pop();
        }
        q_.push(mp[endWord]);
        
        while(!q.empty() && !q_.empty()){
            int qn = q.size();
            while(qn--){
                int id = q.front();
                q.pop();
                if(vis_[id] != -1) return (vis[id]+vis_[id])/2;
                for(int i = 0; i < edge[id].size(); i++){
                    int nx = edge[id][i];
                    if(vis[nx] == -1){
                        q.push(nx);
                        vis[nx] = vis[id] + 1;
                    }
                }
            }
            qn = q_.size();
            while(qn--){
                int id = q_.front();
                q_.pop();
                if(vis[id] != -1) return (vis[id]+vis_[id])/2;
                for(int i = 0; i < edge[id].size(); i++){
                    int nx = edge[id][i];
                    if(vis_[nx] == -1){
                        q_.push(nx);
                        vis_[nx] = vis_[id] + 1;
                    }
                }
            }
        }
        return 0;
    }
};

//思路6 python版本
class Solution(object):
    
    def __init__(self):
        self.mp = {}
        self.edge = []
        self.cnt = 0

    def addWord(self, s):
        if s not in self.mp:
            self.mp[s] = self.cnt
            self.edge.append([])
            self.cnt += 1

    def addEdge(self, s):
        if s in self.mp: 
            return
        self.addWord(s)
        id1 = self.mp[s]
        w = list(s)
        for i in range(len(s)):
            tmp = w[i]
            w[i] = '*'
            ns = "".join(w)
            self.addWord(ns)
            id2 = self.mp[ns]
            self.edge[id1].append(id2)
            self.edge[id2].append(id1)
            w[i] = tmp

    def ladderLength(self, beginWord, endWord, wordList):
        """
        :type beginWord: str
        :type endWord: str
        :type wordList: List[str]
        :rtype: int
        """
        for w in wordList:
            self.addEdge(w)
        self.addEdge(beginWord)
        if endWord not in self.mp:
            return 0

        vis = [-1] * self.cnt
        vis[self.mp[beginWord]] = 1
        q = collections.deque([self.mp[beginWord]])
        
        while q:
            id = q.popleft()
            if id == self.mp[endWord]: 
                return (vis[id]+1)/2
            for e in self.edge[id]:
                if vis[e] == -1:
                    vis[e] = vis[id] + 1
                    q.append(e)
        return 0



//思路7 python版本
class Solution(object):

    def __init__(self):
        self.mp = {}
        self.edge = []
        self.cnt = 0

    def addWord(self, s):
        if s not in self.mp:
            self.mp[s] = self.cnt
            self.edge.append([])
            self.cnt += 1

    def addEdge(self, s):
        if s in self.mp: 
            return
        self.addWord(s)
        id1 = self.mp[s]
        w = list(s)
        for i in range(len(s)):
            tmp = w[i]
            w[i] = '*'
            ns = "".join(w)
            self.addWord(ns)
            id2 = self.mp[ns]
            self.edge[id1].append(id2)
            self.edge[id2].append(id1)
            w[i] = tmp

    def ladderLength(self, beginWord, endWord, wordList):
        """
        :type beginWord: str
        :type endWord: str
        :type wordList: List[str]
        :rtype: int
        """
        for w in wordList:
            self.addEdge(w)
        self.addEdge(beginWord)
        if endWord not in self.mp:
            return 0

        vis = [-1] * self.cnt
        vis[self.mp[beginWord]] = 1
        q = collections.deque([self.mp[beginWord]])

        vis_ = [-1] * self.cnt
        vis_[self.mp[endWord]] = 1
        q_ = collections.deque([self.mp[endWord]])
        
        while q and q_:
            qn = len(q)
            while qn:
                id = q.popleft()
                if vis_[id] != -1: 
                    return (vis[id]+vis_[id])/2
                for e in self.edge[id]:
                    if vis[e] == -1:
                        vis[e] = vis[id] + 1
                        q.append(e)
                qn -= 1

            qn = len(q_)
            while qn:
                id = q_.popleft()
                if vis[id] != -1: 
                    return (vis[id]+vis_[id])/2
                for e in self.edge[id]:
                    if vis_[e] == -1:
                        vis_[e] = vis_[id] + 1
                        q_.append(e)
                qn -= 1
        return 0