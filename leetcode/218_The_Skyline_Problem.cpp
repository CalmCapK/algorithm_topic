//思路1 扫描线+优先队列
struct Node{
    Node(int x, int h){
        this->x = x;
        this->h = h;
    }
    int x;
    int h;
};
struct cmp{
    bool operator() (Node a, Node b) 
    {
        return a.h < b.h; //大顶堆
    }
};
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        priority_queue<Node, vector<Node>, cmp>pq;
        vector<int>vx;
        int n = buildings.size();
        for(int i = 0; i < n; i++){
            vx.push_back(buildings[i][0]);
            vx.push_back(buildings[i][1]);
        } 
        sort(vx.begin(), vx.end());
        vector<vector<int>>ans;
        int idx = 0;
        for(int i = 0; i < 2*n; i++){
            while(idx < n && buildings[idx][0] <= vx[i]){
                pq.push(Node(buildings[idx][1], buildings[idx][2]));
                idx++;
            }
            while(!pq.empty() && pq.top().x <= vx[i]){ //右边缘不要
                // cout << 'pop ' << pq.top().x << ' ' << pq.top().h << endl; 
                pq.pop();
            }
            // cout << vx[i] << " " << pq.top().x << " " << pq.top().h << endl;
            int mx = pq.empty() ? 0: pq.top().h; 
            if(ans.size() == 0 || mx != ans.back()[1]){ //交叉情况
                // cout << "ans:" << vx[i] << " " << pq.top().h <<endl;
                ans.push_back({vx[i], mx});
            }
        }
        return ans;
    }
};

//思路1 python版 PriorityQueue
from queue import PriorityQueue
class Solution:
    def getSkyline(self, buildings: List[List[int]]) -> List[List[int]]:
        n = len(buildings)
        vx = []
        for i in range(n):
            vx.append(buildings[i][0])
            vx.append(buildings[i][1])
        vx = sorted(vx)
        q = PriorityQueue()
        idx = 0
        ans = []
        for i in range(2*n):
            while idx < n and buildings[idx][0] <= vx[i]:
                q.put((-buildings[idx][2], buildings[idx][1])) 
                idx += 1
            while not q.empty():
                a = q.get()
                # print('pop', i, vx[i], a)
                if a[1] > vx[i]:
                    q.put(a)
                    break
            
            if q.empty():
                mx = 0
            else:
                tmp = q.get()
                mx = -tmp[0]
                q.put(tmp)
                # print(i, vx[i], tmp)
            if len(ans) == 0 or mx != ans[-1][1]:
                ans.append([vx[i], mx])

        return ans

//思路1 python版 heapq
import heapq
class Solution(object):
    def getSkyline(self, buildings):
        """
        :type buildings: List[List[int]]
        :rtype: List[List[int]]
        """
        n = len(buildings)
        vx = []
        for i in range(n):
            vx.append(buildings[i][0])
            vx.append(buildings[i][1])
        vx = sorted(vx)
        q = []
        idx = 0
        ans = []
        for i in range(2*n):
            while idx < n and buildings[idx][0] <= vx[i]:
                heapq.heappush(q, (-buildings[idx][2], buildings[idx][1]))
                idx += 1
            while q:
                a = heapq.heappop(q)
                # print('pop', i, vx[i], a)
                if a[1] > vx[i]:
                    heapq.heappush(q, a)
                    break
            
            if not q:
                mx = 0
            else:
                tmp = heapq.heappop(q)
                mx = -tmp[0]
                heapq.heappush(q, tmp)
                # print(i, vx[i], tmp)
            if len(ans) == 0 or mx != ans[-1][1]:
                ans.append([vx[i], mx])

        return ans

//思路1 python版 class
from queue import PriorityQueue
class Node(object):
    def __init__(self, x, h):
        self.x = x
        self.h = h
        return
 
    def __lt__(self, other):
        return self.h > other.h

class Solution:
    def getSkyline(self, buildings: List[List[int]]) -> List[List[int]]:
        n = len(buildings)
        vx = []
        for i in range(n):
            vx.append(buildings[i][0])
            vx.append(buildings[i][1])
        vx = sorted(vx)
        q = PriorityQueue()
        idx = 0
        ans = []
        for i in range(2*n):
            while idx < n and buildings[idx][0] <= vx[i]:
                q.put(Node(buildings[idx][1], buildings[idx][2])) 
                idx += 1
            while not q.empty():
                a = q.get()
                # print('pop', i, vx[i], a)
                if a.x > vx[i]:
                    q.put(a)
                    break
            
            if q.empty():
                mx = 0
            else:
                tmp = q.get()
                mx = tmp.h
                q.put(tmp)
                # print(i, vx[i], tmp)
            if len(ans) == 0 or mx != ans[-1][1]:
                ans.append([vx[i], mx])

        return ans
