#include<iostream>
#include<vector>
using namespace std;

//带有结点深度信息的层次遍历
vector<vector<int>> levelOrder(TreeNode* root) {
        if(root==nullptr) return {};
        vector<vector<int>> ans;

        queue<TreeNode*> q;
        q.push(root);
       
        while(!q.empty())
        {
            int s=q.size();
            ans.push_back(vector<int>());
            for(int j=0;j<s;j++)
            {
                TreeNode* node=q.front();
                q.pop();
                ans.back().push_back(node->val);
                if(node->left!=nullptr) q.push(node->left);
                if(node->right!=nullptr) q.push(node->right);
            }
        }
    return ans;
   }
