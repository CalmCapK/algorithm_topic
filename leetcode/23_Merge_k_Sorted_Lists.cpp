/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
//思路6 归并+非递归
class Solution {
public:
    ListNode* merge2lists(ListNode* a, ListNode* b){
        ListNode*head = nullptr;
        ListNode*tail = nullptr;
        while(a && b){
            if(a->val <= b->val){
                if(head == nullptr){
                    head = a;
                    tail = a;
                }else{
                    tail->next = a;
                    tail = tail->next;
                }
                a = a->next;
            }else{
                if(head == nullptr){
                    head = b;
                    tail = b;
                }else{
                    tail->next = b;
                    tail = tail->next;
                }
                b = b->next;
            }
        }
        if(a){
            if(head == nullptr){
                head = a;
                tail = a;
            }else{
                tail->next = a;
            }
        }
        if(b){
            if(head == nullptr){
                head = b;
                tail = b;
            }else{
                tail->next = b;
            }
        }
        return head;
    }
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int n = lists.size();
        int step = 1;
        while(step < n){
            for(int i = 0; i+step < n; i+=step*2){
                // cout << i << " " << i+step << " " << step << " "<< n;
                lists[i] = merge2lists(lists[i], lists[i+step]);
            }
            step *= 2;
        }
        if(n > 0)
            return lists[0];
        return nullptr;
    }
};
/*
//思路5 归并
class Solution {
public:
    ListNode* merge2lists(ListNode* a, ListNode* b){
        ListNode*head = nullptr;
        ListNode*tail = nullptr;
        while(a && b){
            if(a->val <= b->val){
                if(head == nullptr){
                    head = a;
                    tail = a;
                }else{
                    tail->next = a;
                    tail = tail->next;
                }
                a = a->next;
            }else{
                if(head == nullptr){
                    head = b;
                    tail = b;
                }else{
                    tail->next = b;
                    tail = tail->next;
                }
                b = b->next;
            }
        }
        if(a){
            if(head == nullptr){
                head = a;
                tail = a;
            }else{
                tail->next = a;
            }
        }
        if(b){
            if(head == nullptr){
                head = b;
                tail = b;
            }else{
                tail->next = b;
            }
        }
        return head;
    }
    ListNode* merge(vector<ListNode*>& lists, int l, int r){
        if(l > r) return nullptr;
        if(l == r) return lists[l];
        int mid = (l+r)/2;
        return merge2lists(merge(lists, l, mid), merge(lists, mid+1, r));
    }
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return merge(lists, 0, lists.size()-1);
    }
};
*/
//思路4 优先队列
/*
struct cmp{
    bool operator()(ListNode* a, ListNode*b){
        return a->val > b->val;
    }
};
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int n = lists.size();
        priority_queue<ListNode*, vector<ListNode*>, cmp> pq;
        while(!pq.empty()){
            pq.pop();
        }
        for(int i = 0; i < n; i++){
            if(lists[i]!=nullptr)   
                pq.push(lists[i]);
        }
        ListNode* ans_h = nullptr;
        ListNode* ans_t = nullptr;
        while(!pq.empty()){
            ListNode* tmp = pq.top();
            pq.pop();
            if(ans_h == nullptr){
                ans_h = tmp;
                ans_t = tmp;
            }else{
                ans_t->next = tmp;
                ans_t = ans_t->next;
            }
            tmp = tmp->next;
            if(tmp!=nullptr)    
                pq.push(tmp);
        }
        return ans_h;
    }
};
*/
 /*
 //思路2 一个个选
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int n = lists.size();
        ListNode* ans_h = nullptr;
        ListNode* ans_t = nullptr;
        while(true){
            int tmp = -1;
            for(int i = 0; i < n; i++){
                if(lists[i] == nullptr) continue;
                if(tmp == -1){
                    tmp = i;
                }else{
                    if(lists[tmp]->val > lists[i]->val){
                        tmp = i;
                    }
                }
            }
            if(tmp == -1){
                break;
            }
            if(ans_h == nullptr){
                ans_h = lists[tmp];
                ans_t = lists[tmp];
            }else{
                ans_t->next = lists[tmp];
                ans_t = ans_t->next;
            }
            lists[tmp] = lists[tmp]->next;
        }
        return ans_h;
    }
};
*/
 /*
//思路1 一个个选
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* idx[10010];
        int n = lists.size();
        for(int i = 0; i < n; i++){
            idx[i] = lists[i];
        }
        ListNode* ans_h = nullptr;
        ListNode* ans_t = nullptr;
        while(true){
            int tmp = -1;
            for(int i = 0; i < n; i++){
                if(idx[i] == nullptr) continue;
                if(tmp == -1){
                    tmp = i;
                }else{
                    if(idx[tmp]->val > idx[i]->val){
                        tmp = i;
                    }
                }
            }
            if(tmp == -1){
                break;
            }
            if(ans_h == nullptr){
                ans_h = idx[tmp];
                ans_t = idx[tmp];
            }else{
                ans_t->next = idx[tmp];
                ans_t = ans_t->next;
            }
            idx[tmp] = idx[tmp]->next;
        }
        return ans_h;
    }
};
*/

//思路5 归并 python版本
/*
# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def merge2lists(self, a, b):
        head = None
        tail = None
        while a and b:
            if a.val <= b.val:
                if head is None:
                    head = a
                    tail = a
                else:
                    tail.next = a
                    tail = tail.next
                a = a.next
            else:
                if head is None:
                    head = b
                    tail = b
                else:
                    tail.next = b
                    tail = tail.next
                b = b.next
        if a:
            if head is None:
                head = a
                tail = a
            else:
                tail.next = a
        if b:
            if head is None:
                head = b
                tail = b
            else:
                tail.next = b
        return head

    def merge(self, lists, l, r):
        if l > r:
            return None
        elif l == r:
            return lists[l]
        mid = (l+r)/2
        return self.merge2lists(self.merge(lists, l, mid), self.merge(lists, mid+1, r))
    
//思路6： 归并+非递归 python
    def mergeKLists(self, lists):
        """
        :type lists: List[ListNode]
        :rtype: ListNode
        """
        return self.merge(lists, 0, len(lists)-1)

       def mergeKLists(self, lists):
        """
        :type lists: List[ListNode]
        :rtype: ListNode
        """
        n = len(lists)
        step = 1
        while step < n:
            for i in range(0, n-step, step*2):
                lists[i] = self.merge2lists(lists[i], lists[i+step])
            step *= 2
        if n > 0:
            return lists[0]
        return None
*/