//思路1 双向链表
struct Node{
    Node* before = nullptr;
    Node* after = nullptr;
    int val;
    int key;
};

class LRUCache {
public:
    Node*head;
    Node*tail;
    map<int, Node*>mp;
    int cap;
    int cnt;
    LRUCache(int capacity) {
        cap = capacity;
        cnt = 0;
    }
    
    int get(int key) {
        if(mp.find(key)!=mp.end()){
            Node*node = mp[key];
            if(node->before != nullptr && node->after != nullptr){
                node->before->after = node->after;
                node->after->before = node->before;
                tail->after = node;
                node->before = tail;
                node->after = nullptr;
                tail = node;
            }else if(node->before == nullptr && node->after != nullptr){
                head = node->after;
                head->before = nullptr;
                node->before = tail;
                tail->after = node;
                node->after = nullptr;
                tail = node;
            }
            //Node*p = head;
            //cout << "get: "<< cnt << " : ";;
            // /while(p){
            //    cout << p->key << " " ;
            //    p = p->after;
            //}
            //cout << endl;
            //p = head;
            //cout << "getbefore: " << cnt << " : ";
            //while(p){
           //     if(p->before)
            //        cout << p->before->key << " " ;
             //   p = p->after;
            //}
            //cout << endl;
            return node->val;
        }else{
            return -1;
        }
    }
    
    void put(int key, int value) {
        if(mp.find(key) != mp.end()){
            get(key);
            mp[key]->val = value;
            return;
        }
        Node*node = new Node();
        node->val = value;
        node->key = key;
        mp[key] = node;
        if(cnt == 0){
            head = tail = node;
            cnt++;
        }else if(cnt < cap){
            tail->after = node;
            node->before = tail;
            tail = node;
            cnt++;
        }else{
            mp.erase(head->key);
            tail->after = node;
            node->before = tail;
            tail = node;
            head = head->after;
            head->before = nullptr;
            
        }
        /*Node*p = head;
        cout << "put: " << cnt << " : ";
        while(p){
            cout << p->key << " " ;
            p = p->after;
        }
        cout << endl;
        p = head;
        cout << "putbefore: " << cnt << " : ";
        while(p){
            if(p->before)
                cout << p->before->key << " " ;
            p = p->after;
        }
        cout << endl;*/
    }
};
//思路2 STL实现双向链表
class LRUCache{
public:
    unordered_map<int, list<pair<int, int>>::iterator>mp;
    list<pair<int, int>>l;
    int cap;
    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        if(mp.find(key)!=mp.end()){
            l.splice(l.begin(), l, mp[key]);
            return mp[key]->second;
        }
        return -1;
    }
    
    void put(int key, int value) {
        //if(mp.find(key) != mp.end()){
        //    l.splice(l.begin(), l, mp[key]);
        //    mp[key]->second = value;
        //    return;
        //}
        if(mp.find(key) != mp.end()){
            l.erase(mp[key]);
        }
        l.push_front(make_pair(key, value));
        mp[key] = l.begin();
        if(mp.size() > cap){
            int k = l.rbegin()->first;
            l.pop_back();
            mp.erase(k);
        }
    }
};


//思路1 双向链表 python版
/*
class Node(object):
    def __init__(self, key, value):
        self.before = None
        self.after = None
        self.key = key
        self.value = value

class LRUCache(object):

    def __init__(self, capacity):
        """
        :type capacity: int
        """
        self.head=None
        self.tail=None
        self.mp = {}
        self.cap = capacity
        self.cnt = 0
        
    def get(self, key):
        """
        :type key: int
        :rtype: int
        """
        if key in self.mp.keys():
            if self.mp[key].before and self.mp[key].after:
                self.mp[key].before.after = self.mp[key].after;
                self.mp[key].after.before = self.mp[key].before
                self.tail.after = self.mp[key]
                self.mp[key].before = self.tail
                self.mp[key].after = None
                self.tail = self.mp[key]
            elif self.mp[key].before is None and self.mp[key].after:
                self.head = self.mp[key].after
                self.mp[key].after.before = None
                self.tail.after = self.mp[key]
                self.mp[key].before = self.tail
                self.mp[key].after = None
                self.tail = self.mp[key]
            return self.mp[key].value;
        return -1
        

    def put(self, key, value):
        """
        :type key: int
        :type value: int
        :rtype: None
        """
        if key in self.mp.keys():
            self.get(key)
            self.mp[key].value = value;
            return
        self.mp[key] = Node(key, value)
        if self.cnt == 0:
            self.head = self.mp[key]
            self.tail = self.mp[key]
            self.cnt += 1
        elif self.cnt < self.cap:
            self.tail.after = self.mp[key]
            self.mp[key].before = self.tail
            self.tail = self.mp[key]
            self.cnt += 1
        else:
            self.tail.after = self.mp[key]
            self.mp[key].before = self.tail
            self.tail = self.mp[key]
            self.head = self.head.after
            self.mp.pop(self.head.before.key)
            self.head.before = None
*/
        
