/*
 * @Author: CalmCapK
 * @Date: 2022-09-22 03:33:06
 * @LastEditors: CalmCapK
 * @LastEditTime: 2022-09-22 03:33:48
 */
//思路1 长除法
class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        int fl = 1;
        long long nu = numerator;
        long long de = denominator;
        if(nu < 0){
            fl *= -1; 
            nu *= -1;
        }
        if(de < 0){
            fl *= -1; 
            de *= -1;
        }
        map<int, long long>mp;
        vector<int>v;
        long long zhengshu = nu / de;
        long long yushu = nu % de;
        long long cnt = 0;
        long long xunhuan = -1;
        while(yushu!=0){
            yushu *= 10;
            long long xiaoshu = yushu / de;
            if(mp.find(yushu) != mp.end()){
                xunhuan = mp[yushu];
                break;
            }else{
                mp[yushu] = cnt++;
                v.push_back(xiaoshu);
            }
            yushu = yushu % de;
        }
        string s = "";
        if(zhengshu == 0){
            s += '0';
            if(v.size() == 0){
                fl = 1;
            }
        }
        while(zhengshu){
            s += zhengshu % 10 + '0';
            zhengshu /= 10; 
        }
        if(fl == -1){
            s += "-";
        }
        reverse(s.begin(), s.end());
        for(int i = 0; i < v.size(); i++){
            if(i == 0){
                s += ".";
            }
            if(i == xunhuan){
                s += "(";
            }
            s += v[i]+'0';
        }
        if(xunhuan != -1){
            s += ")";
        }
        return s;
    }
};

//思路1 python版
/*
class Solution(object):
    def fractionToDecimal(self, numerator, denominator):
        """
        :type numerator: int
        :type denominator: int
        :rtype: str
        """
        s = ''
        nu = long(numerator)
        de = long(denominator)
        if (nu > 0 and de < 0) or (nu < 0 and de > 0):
            s += '-'
        nu = abs(nu)
        de = abs(de)
        if nu / de == 0 and nu % de == 0:
            return '0'
        zhengshu = nu / de
        yushu = nu % de
        s += str(zhengshu)
        mp = {}
        xunhuan = -1
        cnt = 0
        ans = []
        while yushu != 0 :
            yushu = yushu * 10
            xiaoshu = yushu / de
            if yushu not in mp:
                mp[yushu] = cnt
                cnt+=1
                ans.append(xiaoshu)
            else:
                xunhuan = mp[yushu]
                break
            yushu = yushu % de
        for i in range(len(ans)):
            if i == 0:
                s += '.'
            if i == xunhuan:
                s += '('
            s += str(ans[i])
        if xunhuan != -1:
            s += ')'
        return s
*/