//思路1：遍历完一个连通图才做结论
class Solution {
public:
    int vis[210][210];
    int dir[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
    bool judge(int x, int y, int n, int m){
        if(x < 0 || y < 0 || x >= n || y >= m){
            return false; 
        }
        return true;
    }
    bool dfs(int id, int x, int y, int n, int m, vector<vector<char>>& board){
        vis[x][y] = id;
        bool fl = true;
        for(int i = 0; i < 4; i++){
            int nx = x + dir[i][0];
            int ny = y + dir[i][1];
            if(!judge(nx, ny, n, m)){
                fl = false;
                continue;
            }
            if(board[nx][ny] == 'O' && vis[nx][ny] == 0){   
                if(!dfs(id, nx, ny, n, m, board)){
                    fl = false;
                }
            }
        }
        return fl; 
    }
    void solve(vector<vector<char>>& board) {
        memset(vis, 0, sizeof(vis));
        int n = board.size();
        int m = board[0].size();
        map<int, bool>mp;
        int id = 1;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(board[i][j] == 'O' && vis[i][j] == 0){
                    bool fl = dfs(id, i, j, n, m, board);
                    mp[id] = fl; 
                    id++;
                }
            }
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(board[i][j] == 'O' && mp[vis[i][j]]){
                    board[i][j] = 'X';
                }
            }
        }
    }
};

//思路2 从边界找连通图
class Solution {
public:
    int dir[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
    bool judge(int x, int y, int n, int m){
        if(x < 0 || y < 0 || x >= n || y >= m){
            return false; 
        }
        return true;
    }
    void dfs(int x, int y, int n, int m, vector<vector<char>>& board){
        board[x][y] = 'A';
        for(int i = 0; i < 4; i++){
            int nx = x + dir[i][0];
            int ny = y + dir[i][1];
            if(judge(nx, ny, n, m) && board[nx][ny] == 'O'){   
                dfs(nx, ny, n, m, board);
            }
        }
    }
    void solve(vector<vector<char>>& board) {
        int n = board.size();
        int m = board[0].size();
        for(int i = 0; i < n; i++){
            if(board[i][0] == 'O'){
                dfs(i, 0, n, m, board);
            }
            if(board[i][m-1] == 'O'){
                dfs(i, m-1, n, m, board);
            }
        }
        for(int i = 0; i < m; i++){
            if(board[0][i] == 'O'){
                dfs(0, i, n, m, board);
            }
            if(board[n-1][i] == 'O'){
                dfs(n-1, i, n, m, board);
            }
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(board[i][j] == 'O'){
                    board[i][j] = 'X';
                }
                else if(board[i][j] == 'A'){
                    board[i][j] = 'O';
                }
            }
        }
    }
};

//思路1 python版本
/*
class Solution(object):   
    def judge(self, x, y, n, m):
        if x < 0 or y < 0 or x >= n or y >= m:
            return False
        return True
    
    def dfs(self, id, i, j, n, m, board):
        self.vis[i][j] = id
        fl = True
        self.dir = [[0,1],[1,0],[-1,0],[0,-1]]
        for s in range(len(self.dir)):
            nx = i + self.dir[s][0] 
            ny = j + self.dir[s][1] 
            if not self.judge(nx, ny, n, m):
                fl = False
                continue
            if board[nx][ny] == 'O' and self.vis[nx][ny] == 0:
                if not self.dfs(id, nx, ny, n, m, board):
                    fl = False
        return fl
    def solve(self, board):
        """
        :type board: List[List[str]]
        :rtype: None Do not return anything, modify board in-place instead.
        """
        n = len(board)
        m = len(board[0])
        self.vis = [[0] * m for _ in range(n)]
        id = 1
        mp = {}
        for i in range(n):
            for j in range(m):
                if board[i][j] == 'O' and self.vis[i][j] == 0:      
                    fl = self.dfs(id, i, j, n, m, board)
                    mp[id] = fl
                    id += 1
        for i in range(n):
            for j in range(m):
                if board[i][j] == 'O' and mp[self.vis[i][j]]:
                    board[i][j] = 'X'
                    
*/