//思路1 设置为负数
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for(int i = 0; i < n; i++){
            if(nums[i] <= 0){
                nums[i] = n+1;
            }
        }
        for(int i = 0; i < n; i++){
            if(abs(nums[i]) <= n){
                nums[abs(nums[i])-1] = -abs(nums[abs(nums[i])-1]);
            }
        }
        for(int i = 0; i < n; i++){
            if(nums[i] > 0){
                return i+1;
            }
        }
        return n+1;
    }
};

//思路1 python版
/*
class Solution(object):
    def firstMissingPositive(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        for i, num in enumerate(nums):
            if num <= 0:
                nums[i] = len(nums) + 1
        for i, num in enumerate(nums):
            if abs(num) <= len(nums):
                nums[abs(num)-1] = -abs(nums[abs(num)-1])
        for i, num in enumerate(nums):
            if num > 0:
                return i+1
        return len(nums)+1
*/