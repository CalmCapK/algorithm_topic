//思路1 二叉树+dfs
int bianli(TreeNode* root, int&ans){
    if(root == nullptr){
        return 0;
    }
    int lans = bianli(root->left, ans);
    int rans = bianli(root->right, ans);
    int ret = max(root->val, max(root->val+lans, root->val+rans));
    ans = max(ans, max(ret, root->val + lans + rans));
    return ret;
}

class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int ans = -999999;
        bianli(root, ans);
        return ans;
    }
};

//思路1：python版
class Solution(object):
    def maxPathSum(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        self.ans = float("-inf")
        self.dfs(root)
        return self.ans

    def dfs(self, root):
        if root is None:
            return 0
        lans = self.dfs(root.left)
        rans = self.dfs(root.right)
        ret = max(root.val, max(root.val+lans, root.val+rans))
        self.ans = max(self.ans, max(ret, root.val+lans+rans))
        # print(root.val, ret, self.ans)
        return ret