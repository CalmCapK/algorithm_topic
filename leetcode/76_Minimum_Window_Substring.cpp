//思路1 map+滑动窗口
class Solution {
public:
    string minWindow(string s, string t) {
        map<char, int>mp;
        mp.clear();
        map<char, int>cnt;
        cnt.clear();
        int sn = s.size();
        int tn = t.size();
        for(int i = 0; i < sn; i++){
            mp[s[i]] = -1;
        }
        int tt = 0;//t有重复的
        for(int i = 0; i < tn; i++){
            if(cnt.find(t[i]) == cnt.end()){// t含s没有的
                mp[t[i]] = 0;
                cnt[t[i]] = 0;
                tt += 1;
            }
            mp[t[i]] += 1;
        }
        int i=0,j=0;
        int total = 0;
        int ans_i=-1, ans_j = -1;
        while(i < sn && mp[s[i]] == -1){
            i++;
            j++;
        }
        for(; i < sn && j < sn; j++){
            if(mp[s[j]] == -1){
                continue;
            }
            cnt[s[j]] += 1;
            if(cnt[s[j]] == mp[s[j]]){
                total += 1;
            }else if(cnt[s[j]] > mp[s[j]] && s[i] == s[j]){
                while(i < j &&  (mp[s[i]] == -1 || cnt[s[i]] > mp[s[i]])){
                    if(mp[s[i]] != -1){
                        cnt[s[i]]--;
                    }
                    i++;
                }
            }
            if(total == tt){
                if((ans_i == -1 && ans_j == -1) || (ans_j-ans_i+1 > j-i+1)){
                    ans_i = i;
                    ans_j = j;
                }
            }  
        }
        if(ans_i != -1)
            return s.substr(ans_i, ans_j-ans_i+1);
        return "";
    }
};

//思路1： python版
/*
class Solution(object):
    def minWindow(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: str
        """
        dic = {}
        cnt = {}
        for si in s:
            dic[si] = -1
        tt = 0
        for ti in t:
            if ti not in cnt:
                cnt[ti] = 0
                dic[ti] = 0
                tt += 1
            dic[ti] += 1
        i = 0
        j = 0
        sn = len(s)
        tn = len(t)
        total = 0
        ans_i = -1
        ans_j = -1
        while i < sn and dic[s[i]] == -1:
            i += 1
            j += 1
        while i < sn and j < sn:
            if dic[s[j]] == -1:
                j += 1
                continue
            cnt[s[j]] += 1
            if cnt[s[j]] == dic[s[j]]:
                total += 1 
            elif cnt[s[j]] > dic[s[j]] and s[i] == s[j]:
                while i < j and (dic[s[i]] == -1 or cnt[s[i]] > dic[s[i]]):
                    if dic[s[i]] != -1:
                        cnt[s[i]] -= 1
                    i+=1
            if total == tt:
                if ans_i == -1 or ans_j - ans_i + 1 > j - i + 1:
                    ans_i = i
                    ans_j = j
            j += 1
        if ans_i == -1:
            return ""
        return s[ans_i:ans_j+1]
*/