//思路1：保存正负数
class Solution1 {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        bool p = false;
        bool f = false;
        bool z = false;
        int pn, fn;
        int mx = nums[0];
        for(int i = 0; i < n; i++){
            if(nums[i] > 0){
                if(!p){
                    pn = nums[i];
                    p = true;
                }else{
                    pn = pn * nums[i];
                }
                if(f){
                    fn = fn * nums[i];
                }
            }else if(nums[i] < 0){
                bool nf = false, np = false;
                int nfn, npn;
                if(p){
                    nfn = pn * nums[i];
                    nf = true;
                }else{
                    nfn = nums[i];
                    nf = true;
                }
                if(f){
                    npn = fn * nums[i];
                    np = true;
                }
                f = nf;
                p = np;
                pn = npn;
                fn = nfn;
            }else{
                z = true;
                f = false;
                p = false;
            }
            if(f){
                mx = max(mx, fn);
            }
            if(p){
                mx = max(mx, pn);
            }
            if(z){
                mx = max(mx, 0);
            }
        }
        return mx;
    }
};

//思路2：保存最大最小值
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int mx = nums[0], mi = nums[0], ans = nums[0];
        for(int i = 1; i < n; i++){
            int tmx=mx, tmi=mi;
            mx = max(tmx*nums[i], max(tmi*nums[i], nums[i]));
            mi = min(tmx*nums[i], min(tmi*nums[i], nums[i]));
            ans = max(ans, max(mx, mi));
            //cout << ans << " " << mx << " " << mi << endl;
        }
        return ans;
    }
};

//思路2：python版本
/*
class Solution(object):
    def maxProduct(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        mx = mi = ans = nums[0]
        n = len(nums)
        for i in nums[1:]:
            tmx = mx
            tmi = mi
            mx = max(i, max(tmx*i, tmi*i))
            mi = min(i, min(tmx*i, tmi*i))
            ans = max(ans, mx)
        return ans
*/