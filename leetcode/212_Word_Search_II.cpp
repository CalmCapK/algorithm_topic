//思路3 dfs+剪枝+删除已匹配单词
class Solution {
public:
    int vis[20][20];
    int d[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool check(int x, int y, int n, int m){
        if(x < 0 || x >= n || y < 0 || y >= m) return false;
        return true;
    }
    unordered_map<string, int>cnt;
    unordered_map<string, int>ws;
    vector<string>ans;
    void dfs(int x, int y, string w, vector<vector<char>>& board){
        if(cnt.find(w) == cnt.end() || cnt[w] == 0){
            return; 
        }
        if(ws.find(w) != ws.end() && ws[w] > 0){
            string pre = "";
            int wl = w.size();
            for(int i = 0; i < wl; i++){
                pre += w[i];
                cnt[pre] -= 1;
            }
            ws[w] = 0;
            ans.push_back(w);
        }
        if(cnt[w] == 0){
            return; 
        }
        for(int i = 0; i < 4; i++){
            int nx = x + d[i][0];
            int ny = y + d[i][1];
            if(check(nx, ny, board.size(), board[0].size()) && vis[nx][ny] == 0){
                vis[nx][ny] = 1;
                dfs(nx, ny, w+board[nx][ny], board);
                vis[nx][ny] = 0;
            }
        } 
    }
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        int wn = words.size();
        int n = board.size();
        int m = board[0].size();
        cnt.clear();
        ws.clear();
        for(int w = 0; w < wn; w++){
            int wl = words[w].size();
            string pre = "";
            for(int i = 0; i < wl; i++){
                pre += words[w][i];
                if(cnt.find(pre) == cnt.end()){
                    cnt[pre] = 0;
                }
                cnt[pre] += 1;
            }
            ws[words[w]] = 1;
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                memset(vis, 0, sizeof(vis));
                vis[i][j] = 1;
                string tmp = "";
                tmp += board[i][j];
                dfs(i, j, tmp, board);
            }
        }
        return ans;
    }
};
//思路3 dfs+剪枝+删除已匹配单词+使用#标注访问情况
class Solution {
public:
    int d[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool check(int x, int y, int n, int m){
        if(x < 0 || x >= n || y < 0 || y >= m) return false;
        return true;
    }
    unordered_map<string, int>cnt;
    unordered_map<string, int>ws;
    vector<string>ans;
    void dfs(int x, int y, string w, vector<vector<char>>& board){
        if(cnt.find(w) == cnt.end() || cnt[w] == 0){
            return; 
        }
        if(ws.find(w) != ws.end() && ws[w] > 0){
            string pre = "";
            int wl = w.size();
            for(int i = 0; i < wl; i++){
                pre += w[i];
                cnt[pre] -= 1;
            }
            ws[w] = 0;
            ans.push_back(w);
        }
        if(cnt[w] == 0){
            return; 
        }
        char ch = board[x][y];
        board[x][y] = '#';
        for(int i = 0; i < 4; i++){
            int nx = x + d[i][0];
            int ny = y + d[i][1];
            if(check(nx, ny, board.size(), board[0].size()) && board[nx][ny] != '#'){
                dfs(nx, ny, w+board[nx][ny], board);
            }
        } 
        board[x][y] = ch;
    }
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        int wn = words.size();
        int n = board.size();
        int m = board[0].size();
        cnt.clear();
        ws.clear();
        for(int w = 0; w < wn; w++){
            int wl = words[w].size();
            string pre = "";
            for(int i = 0; i < wl; i++){
                pre += words[w][i];
                if(cnt.find(pre) == cnt.end()){
                    cnt[pre] = 0;
                }
                cnt[pre] += 1;
            }
            ws[words[w]] = 1;
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                string tmp = "";
                tmp += board[i][j];
                dfs(i, j, tmp, board);
            }
        }
        return ans;
    }
};

//思路4 dfs+剪枝前缀+字典树+删除已匹配单词
struct TrieNode {
    string word;
    unordered_map<char, TrieNode*>child;
    TrieNode(){
        this->word = "";
    }
};
void insertTrie(TrieNode * root, string word){
    TrieNode*node = root;
    for(int i = 0; i < word.size(); i++){
        if(!node->child.count(word[i])){
            node->child[word[i]] = new TrieNode();
        }
        node = node->child[word[i]];
    }
    node->word = word;
}
class Solution {
public:
    int d[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool check(int x, int y, int n, int m){
        if(x < 0 || x >= n || y < 0 || y >= m) return false;
        return true;
    }
    vector<string>ans;
    void dfs(int x, int y, TrieNode* root, vector<vector<char>>& board){
        char ch = board[x][y];
        //剪枝
        if(!root->child.count(ch)){
            return;
        }
        //去重
        TrieNode*nxt = root->child[ch];
        if(nxt->word.size() > 0){
            ans.push_back(nxt->word);
            nxt->word = "";
        }
        //去重又剪枝
        if(nxt->child.empty()){
            root->child.erase(ch);
            return;
        }
        board[x][y] = '#';
        for(int i = 0; i < 4; i++){
            int nx = x + d[i][0];
            int ny = y + d[i][1];
            if(check(nx, ny, board.size(), board[0].size()) && board[nx][ny] != '#'){
                dfs(nx, ny, nxt, board);
            }
        } 
        board[x][y] = ch;
    }
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        int wn = words.size();
        int n = board.size();
        int m = board[0].size();
        TrieNode*root = new TrieNode();
        for(int w = 0; w < wn; w++){
            insertTrie(root, words[w]);
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                dfs(i, j, root, board);
            }
        }
        return ans;
    }
};

//思路4 dfs+剪枝前缀+字典树+删除已匹配单词 python版
class TrieNode(object):
    def __init__(self):
        self.child = {}
        self.word = ""
def insertTrie(root, word):
    node = root
    for i in range(len(word)):
        if word[i] not in node.child:
            node.child[word[i]] = TrieNode()
        node = node.child[word[i]]
    node.word = word
d = [[1, 0], [-1, 0], [0, 1], [0, -1]]
def check(n, m, x, y):
    if x < 0 or y < 0 or x >= n or y >= m:
        return False
    return True

class Solution(object):
    def __init__(self):
        self.ans = []
    def dfs(self, x, y, root, board):
        ch = board[x][y]
        if ch not in root.child:
            return
        nxt =  root.child[ch]
        if len(nxt.word) > 0:
            self.ans.append(nxt.word)
            nxt.word = ""
        if len(nxt.child.keys()) == 0:
            root.child.pop(ch)
            return
        board[x][y] = '#'
        for i in range(4):
            nx = x + d[i][0]
            ny = y + d[i][1]
            if check(len(board), len(board[0]), nx, ny) and board[nx][ny] != '#':
                self.dfs(nx, ny, nxt, board)
        board[x][y] = ch


    def findWords(self, board, words):
        """
        :type board: List[List[str]]
        :type words: List[str]
        :rtype: List[str]
        """
        root = TrieNode()
        for word in words:
            insertTrie(root, word)
        for i in range(len(board)):
            for j in range(len(board[0])):
                self.dfs(i, j, root, board)
        return self.ans