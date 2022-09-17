
//思路3: 指针，从上到下
bool search_zhizhen2(TreeNode* root, TreeNode* mi, TreeNode* mx){
    if(root==nullptr){
        return true;
    }
    if((mi!=nullptr && mi->val >= root->val) || (mx!=nullptr && mx->val <= root->val))
        return false;
    return search_zhizhen2(root->left, mi, root) && search_zhizhen2(root->right, root, mx);
}
//思路2: 指针，不需要判断null情况
bool search_zhizhen(TreeNode* root, TreeNode*& mi, TreeNode*& mx){
    if(root==nullptr){
        mi = nullptr;
        mx = nullptr;
        return true;
    }
    TreeNode * lmi;
    TreeNode * lmx;
    TreeNode * rmi;
    TreeNode * rmx;
    if(!search_zhizhen(root->left, lmi, lmx) || !search_zhizhen(root->right, rmi, rmx)){
        return false;
    }
    if((lmx!=nullptr && lmx->val >= root->val) || (rmi!=nullptr && rmi->val <= root->val)){
        return false;
    }
    if(lmi != nullptr){
        mi = lmi;
    }
    else{
        mi = root;   
    }
    if(rmx != nullptr){
        mx = rmx;    
    }else{
        mx = root;
    }
    return true;
}
//思路1: 需要判断null情况
bool search(TreeNode* root, int& mi, int& mx){
    if(root->left==nullptr and root->right==nullptr){
        mi = root->val;
        mx = root->val;
        return true;
    }
    int lfmi = root->val;
    int lfmx = root->val;
    if(root->left!=nullptr){
        if(!search(root->left, lfmi, lfmx)){
            return false;
        }
        if(lfmx >= root->val){
            return false;
        }
    }
    int rimx = root->val;
    int rimi = root->val;
    if(root->right!=nullptr){
        if(!search(root->right, rimi, rimx)){
            return false;
        }
        if(rimi <= root->val){
            return false;
        }
    }
    //cout << root->val << " " << lfmi << " " << lfmx << " " << rimi << " " << rimx << endl;
    mi = lfmi;
    mx = rimx;
    return true;
}


class Solution {
public:
    bool isValidBST(TreeNode* root) {
        /*if(root == nullptr){
            return true;
        }
        int mi, mx;
        return search(root, mi, mx);
        */
        //TreeNode* mi, *mx;
        //return search_zhizhen(root, mi, mx);
        return search_zhizhen2(root, nullptr, nullptr);
    }
};


/*
#思路3 python版本
def search(root, mi, mx):
    if root is None:
        return True
    if (mi and mi.val >= root.val) or (mx and mx.val <= root.val):
        return False
    #print(root, mi, mx)
    return search(root.left, mi, root) and search(root.right, root, mx)

class Solution(object):
    def isValidBST(self, root):
        """
        :type root: TreeNode
        :rtype: bool
        """
        return search(root, None, None)
*/