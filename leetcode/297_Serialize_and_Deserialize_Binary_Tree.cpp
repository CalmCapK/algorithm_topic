//思路1 先序遍历序列化+list或者queue辅助建树
class Codec {
public:
    void xianxu(TreeNode* root, string &ans){
        if(root == nullptr){
            ans += "NULL,";
            return;
        }
        ans += to_string(root->val) + ',';
        xianxu(root->left, ans);
        xianxu(root->right, ans);
    }
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string ans = "";
        xianxu(root, ans);
        // cout << ans << endl;
        return ans;
    }

    void bulid(TreeNode*&root,list<string>& data){
        if(data.front() =="NULL"){
            data.erase(data.begin());
            return;
        }
        root = new TreeNode(stoi(data.front()));
        data.erase(data.begin());
        bulid(root->left, data);
        bulid(root->right, data);
    }

    void bulid_queue(TreeNode*&root, queue<string>& data){
        if(data.front() =="NULL"){
            data.pop();
            return;
        }
        root = new TreeNode(stoi(data.front()));
        data.pop();
        bulid_queue(root->left, data);
        bulid_queue(root->right, data);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        // list<string>v;
        queue<string>v;
        string tmp = "";
        int n = data.size();
        for(int i = 0; i < n; i++){
            if(data[i] == ','){
                // v.push_back(tmp);
                v.push(tmp);
                tmp = "";
            }else{
                tmp += data[i];
            }
        }
        TreeNode*root = nullptr;
        // bulid(root, v);
        bulid_queue(root, v); 
        return root;
    }
};


//思路1： python版本
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Codec:
    def xianxu(self, root, ans):
        if root is None:
            ans.append("NULL")
            return
        ans.append(str(root.val))
        self.xianxu(root.left, ans)
        self.xianxu(root.right, ans)

    def serialize(self, root):
        """Encodes a tree to a single string.
        
        :type root: TreeNode
        :rtype: str
        """
        ans = []
        self.xianxu(root, ans)
        return ",".join(ans)

    def bulid(self, q):
        tmp = q.popleft()
        if tmp == 'NULL':
            return
        root = TreeNode(tmp)
        root.left = self.bulid(q)
        root.right = self.bulid(q)
        return root

    def deserialize(self, data):
        """Decodes your encoded data to tree.
        
        :type data: str
        :rtype: TreeNode
        """
        q = collections.deque()
        for d in data.split(','):    
            q.append(d)
        root = self.bulid(q)
        return root