//思路1 dfs
class Solution {
public:
    map<string, int>mp;
    vector<string>ret;
    void dfs(int st, int n, string s, string ans){
        // cout << st << " " << s << " " << ans << endl;
        if(st == n){
            ret.push_back(ans);
            return;
        }
        string ns = "";
        for(int i = st; i < n; i++){
            ns += s[i];
            if(mp.find(ns) != mp.end()){
                if(ans == ""){
                    dfs(i+1, n, s, ns);
                }else
                    dfs(i+1, n, s, ans + " " + ns);
            }
        }
    }
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        int m = wordDict.size();
        mp.clear();
        for(int i = 0; i < m; i++){
            mp[wordDict[i]] = 1;
        }
        dfs(0, s.size(), s, "");
        return ret;
    }
};
//思路2 记忆化dfs
class Solution {
public:
    unordered_set<string>mp;
    unordered_map<int, vector<string>> ans;

    void dfs(int st, string s){
        if(ans.count(st)){
            return;
        }
        int n = s.size();
        if(st == n){
            ans[st] = {""};
            return; 
        }
        ans[st] = {};
        string ns = "";
        for(int i = st; i < n; i++){
            ns += s[i];
            if(mp.count(ns)){
                dfs(i+1, s);
                int m = ans[i+1].size();
                for(int j = 0; j < m; j++){
                    if(ans[i+1][j] == ""){
                        ans[st].push_back(ns);    
                    }else{
                        ans[st].push_back(ns + " " + ans[i+1][j]); 
                    }
                    
                }
            }
        }
    }
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        mp.clear();
        mp = unordered_set(wordDict.begin(), wordDict.end());
        dfs(0, s);
        return ans[0];
    }
};

//思路2 python版本
class Solution(object):
    def __init__(self):
        self.ans = {}

    def dfs(self, st, s, wordDict):
        if st in self.ans:
            return
        n = len(s)
        if st == n:
            self.ans[st] = [""]
            return
        self.ans[st] = []
        ns = ""
        for i in range(st, n):
            ns += s[i]
            if ns in wordDict:
                self.dfs(i+1, s, wordDict)
                for a in self.ans[i+1]:
                    if a == "":
                        self.ans[st].append(ns)
                    else:
                        self.ans[st].append(ns + " " + a)

    def wordBreak(self, s, wordDict):
        """
        :type s: str
        :type wordDict: List[str]
        :rtype: List[str]
        """
        self.dfs(0, s, wordDict)
        return self.ans[0]