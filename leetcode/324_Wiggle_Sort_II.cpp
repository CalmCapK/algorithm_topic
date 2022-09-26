/*
 * @Author: CalmCapK
 * @Date: 2022-09-24 01:58:24
 * @LastEditors: CalmCapK
 * @LastEditTime: 2022-09-24 02:01:43
 */
//思路1 从左往右计算
class Solution2 {
public:
    void wiggleSort(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<int>v;
        if(n % 2 == 0){
            for(int i = 0; i < (n+1)/2; i++){
                v.push_back(nums[i+n/2]);
                v.push_back(nums[i]);
            }
            reverse(v.begin(), v.end());
        }else{
            v.push_back(nums[0]);
            for(int i = 1; i < (n+1)/2; i++){
                v.push_back(nums[i+n/2]);
                v.push_back(nums[i]);
            }
        }
        nums = v;
    }
};
//思路2：从右往左计算
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<int>v;
        for(int i = (n-1)/2, j=n-1; j >= (n+1)/2; i--, j--){
            v.push_back(nums[i]);
            v.push_back(nums[j]);
        }
        if(n % 2 == 1) v.push_back(nums[0]);
        nums = v;
    }
};

//思路2 python版本
class Solution(object):
    def wiggleSort(self, nums):
        """
        :type nums: List[int]
        :rtype: None Do not return anything, modify nums in-place instead.
        """
        ans = sorted(nums)
        n = len(nums)
        j = n-1
        idx = 0
        for i in range((n-1)/2, -1, -1):
            nums[idx] = ans[i]
            idx += 1
            if j > (n-1)/2:
                nums[idx] = ans[j]
                idx += 1
                j -= 1