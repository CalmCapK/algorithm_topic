
//思路2 贪心
class Solution {
public:
    bool isMatch(string s, string p) {
        int sn = s.size();
        int pn = p.size();
        int j = 0;
        for(int i = 0, istar = -1, jstar = -1; i < sn;){
            if((j < pn) && (s[i] == p[j] || p[j] == '?')){
                i++;
                j++;
            }else if(j < pn && p[j] == '*'){
                jstar = j; //指向p最后一个*
                j++;
                istar = i; //指向s需要用*的地方
            }else{
                if(jstar != -1){ //不匹配，有*可以用，回退用*
                    istar += 1;
                    i = istar;
                    j = jstar + 1; 
                }else{
                    return false;
                }
            }
        }
        for(; j<pn; j++){
            if(p[j]!='*') return false;
        }
        return true;
    }
};
/*
//思路1：动态规划
class Solution {
public:
    bool dp[2010][2010];
    bool isMatch(string s, string p) {
        int sn = s.size();
        int pn = p.size();
        memset(dp, false, sizeof(dp));
        dp[0][0] = true;
        for(int i = 0; i <= sn; i++){
            for(int j = 1; j <= pn; j++){
                if(i == 0){
                    if(p[j-1] == '*'){
                        dp[i][j] = dp[i][j-1];
                    }
                }else{
                    if(p[j-1] != '*'){ //a = a | a = ?
                        if(s[i-1] == p[j-1] || p[j-1] == '?'){
                            dp[i][j] = dp[i-1][j-1];
                        }else{ //a = b
                            dp[i][j] = false;
                        }
                    }else{
                        //是否使用*
                        if(dp[i-1][j] or dp[i][j-1]){
                            dp[i][j] = true;
                        }
                    }
                }
                
                // cout << i << " " << j << " " << dp[i][j] << endl;
            }
        }
        return dp[sn][pn];
    }
};
*/
/*
//思路2 贪心 python
class Solution(object):
    def isMatch(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """
        sn = len(s)
        pn = len(p)
        j = 0
        i = 0
        istar = -1
        jstar = -1
        while i < sn:
            if (j < pn) and (s[i] == p[j] or p[j] == '?'):
                i+=1
                j+=1
            elif j < pn and p[j] == '*':
                jstar = j
                j += 1
                istar = i
            else:
                if jstar != -1:
                    istar += 1
                    i = istar
                    j = jstar + 1
                else:
                    return False
        while j < pn:
            if p[j] != '*':
                return False
            j += 1
        return True 

*/