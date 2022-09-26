/*
 * @Author: CalmCapK
 * @Date: 2022-09-22 04:39:23
 * @LastEditors: CalmCapK
 * @LastEditTime: 2022-09-22 04:57:31
 */
//思路1：改造排序函数，字符串拼起来比较
bool cmp(string a, string b){
    string an = a+b;
    string bn = b+a;
    return an > bn;
}
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string>v;
        for(int i = 0; i < nums.size(); i++){
            string s = "";
            if(nums[i] == 0){
                s = "0";
            } 
            while(nums[i]){
                s += nums[i] % 10 + '0';
                nums[i] /= 10;
            }
            reverse(s.begin(), s.end());
            v.push_back(s);
        }
        string ans = "";
        sort(v.begin(), v.end(), cmp);
        for(int j = 0; j < v.size(); j++){
            ans += v[j];
        }
        if(ans.size() > 0 && ans[0] == '0'){
            return "0";
        }
        return ans;
    }
};

//思路1:python版本
/*
def comp(a, b):
        an = a+b
        bn = b+a
        print(an, bn)
        if an > bn:
            return -1
        elif an < bn:
            return 1
        else:
            return 0
class Solution(object):
    def largestNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: str
        """
        ans = []
        for num in nums:
            ans.append(str(num))
        #ans.sort(key=functools.cmp_to_key(lambda x,y: cmp(y+x, x+y)))
        ans.sort(cmp = lambda x,y: cmp(y+x, x+y))
        #ans.sort(key=functools.cmp_to_key(comp))
        #print(ans)
        res = ""
        for a in ans:
            res += a
        if res[0] == '0':
            return "0"
        return res
*/