//思路1：动态规划分情况讨论
class Solution {
public:
    int dp[40][40];
    bool isMatch(string s, string p) {
        int sn = s.size();
        int pn = p.size();
        memset(dp, false, sizeof(dp));
        dp[0][0] = true;
        for(int i = 0; i <= sn; i++){
            for(int j = 1; j <= pn; j++){
                if(i == 0){
                    if(p[j-1] == '*'){
                        dp[i][j] = dp[i][j-2];
                    }
                }else{
                    if(p[j-1] != '*'){ //a = a | a = .
                        if(s[i-1] == p[j-1] || p[j-1] == '.'){
                            dp[i][j] = dp[i-1][j-1];
                        }else{ //a = b
                            dp[i][j] = false;
                        }
                    }else{
                        if(s[i-1] != p[j-2] && p[j-2] != '.'){ //a = b*
                            dp[i][j] = dp[i][j-2];
                        }else{ //a = a* || a = .*
                            if(dp[i][j-2] || dp[i-1][j]){
                                dp[i][j] = true;
                            }else{
                                dp[i][j] = false;
                            }
                        }
                    }
                }
                
                //cout << i << " " << j << " " << dp[i][j] << endl;
            }
        }
        return dp[sn][pn];
    }
};

//思路1 python版本
/*
class Solution(object):
    def isMatch(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """
        sn = len(s)
        pn = len(p)
        dp = [[False] * (pn + 1) for _ in range(sn + 1)]
        dp[0][0] = True
        for i in range(sn+1):
            for j in range(1, pn+1):
                if i == 0:
                    if p[j-1] == '*':
                        dp[i][j] = dp[i][j-2]
                elif p[j-1] != '*':
                    if s[i-1] == p[j-1] or p[j-1] == '.':
                        dp[i][j] = dp[i-1][j-1]
                    else:
                        dp[i][j] = False
                else:
                    if s[i-1] == p[j-2] or p[j-2] == '.':
                        dp[i][j] = dp[i][j] or dp[i][j-2]
                        dp[i][j] = dp[i][j] or dp[i-1][j]
                    else:
                        dp[i][j] = dp[i][j-2]
                # print(i, j, dp[i][j])
        return dp[sn][pn]
*/