#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    
};

vector<int> postOrder;
vector<int> inOrder;

TreeNode* createTree(int left_post,int right_post,int left_in, int right_in)
{
    if (left_post > right_post || left_in > right_in) return nullptr;
    int in = postOrder[right_post],i;
    TreeNode* root =new TreeNode(in);
    for (i = left_in; i <= right_in; i++)
        if (inOrder[i] == in)
            break;
    int num = i - left_in;
    root->left = createTree(left_post, left_post+num-1, left_in, i - 1);
    root->right = createTree(left_post+num, right_post-1, i + 1, right_in);
    return root;
}

void levelOrder(TreeNode* root,vector<int> &ans)
{
    queue<TreeNode> q;
    q.push(*root);
    while (!q.empty())
    {
        TreeNode node = q.front();
        q.pop();
        ans.push_back(node.val);
        if (node.left != nullptr)
            q.push(*node.left);
        if (node.right != nullptr)
            q.push(*node.right);
    }
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int num;
        cin >> num;
        postOrder.push_back(num);
    }

    for (int i = 0; i < n; i++)
    {
        int num;
        cin >> num;
        inOrder.push_back(num);
    }
    TreeNode* root= createTree(0, postOrder.size() - 1, 0, inOrder.size() - 1);
    vector<int> ans;
    levelOrder(root, ans);
    for (int i = 0; i < ans.size() - 1; i++)
        cout << ans[i] << " ";
    cout << ans[ans.size() - 1];
     
}