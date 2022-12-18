//单调栈+求面积 思路1
class Solution{
public:
    int largestRectangleArea(vector<int>&heights){
        stack<int>st;
        int n = heights.size();
        int al[100010];
        int ar[100010];
        while(!st.empty()){
            st.pop();
        }
        for(int i = 0; i < n; i++){
            while(!st.empty() && heights[st.top()] >= heights[i]){
                st.pop();
            }
            if(st.empty()){
                al[i] = 0;
            }else{
                al[i] = st.top()+1;
            }
            st.push(i);
        }
        while(!st.empty()){
            st.pop();
        }
        for(int i = n-1; i >= 0; i--){
            while(!st.empty() && heights[st.top()] >= heights[i]){
                st.pop();
            }
            if(st.empty()){
                ar[i] = n-1;
            }else{
                ar[i] = st.top()-1;
            }
            st.push(i);
        }
        long long ans = 0;
        for(int i = 0; i < n; i++){
            long long tmp = heights[i]*(ar[i]-al[i]+1);
            ans = max(ans, tmp);
        }
        return ans;
    }
};
//思路2 同时更新
class Solution{
public:
    int largestRectangleArea(vector<int>&heights){
        stack<int>st;
        int n = heights.size();
        int al[100010];
        int ar[100010];
        while(!st.empty()){
            st.pop();
        }
        for(int i = 0; i < n; i++){
            while(!st.empty() && heights[st.top()] >= heights[i]){
                ar[st.top()] = i-1;
                st.pop();
            }
            if(st.empty()){
                al[i] = 0;
            }else{
                al[i] = st.top()+1;
            }
            st.push(i);
        }
        while(!st.empty()){
            ar[st.top()] = n-1;
            st.pop();
        }
        long long ans = 0;
        for(int i = 0; i < n; i++){
            long long tmp = heights[i]*(ar[i]-al[i]+1);
            ans = max(ans, tmp);
        }
        return ans;
    }
};
//思路1 python
class Solution2(object):
    def largestRectangleArea(self, heights):
        """
        :type heights: List[int]
        :rtype: int
        """
        al = []
        ar = []
        n = len(heights)
        st = []
        for i in range(n):
            while len(st) and heights[st[-1]] >= heights[i]:
                st.pop()
            if len(st) == 0:
                al.append(0)
            else:
                al.append(st[-1]+1)
            st.append(i)
        st = []
        for i in range(n-1, -1, -1):
            while len(st) and heights[st[-1]] >= heights[i]:
                st.pop()
            if len(st) == 0:
                ar.append(n-1)
            else:
                ar.append(st[-1]-1)
            st.append(i)
        ar.reverse()
        ans = 0
        for i in range(n):
            #print(i, heights[i], al[i], ar[i])
            ans = max(ans, heights[i]*(ar[i]-al[i]+1));
        return ans

//思路2 python版
class Solution(object):
    def largestRectangleArea(self, heights):
        """
        :type heights: List[int]
        :rtype: int
        """
        n = len(heights)
        al = [0] * n
        ar = [n-1] * n
        st = []
        for i in range(n):
            while len(st) and heights[st[-1]] >= heights[i]:
                ar[st[-1]] = i-1
                st.pop()
            if len(st) == 0:
                al[i] = 0
            else:
                al[i] = st[-1]+1
            st.append(i)
        ans = 0
        for i in range(n):
            #print(i, heights[i], al[i], ar[i])
            ans = max(ans, heights[i]*(ar[i]-al[i]+1));
        return ans