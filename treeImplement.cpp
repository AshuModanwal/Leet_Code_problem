#include <iostream>
#include <stack>
#include <queue>
using namespace std;
class Node
{
public:
    int data;
    Node *left;
    Node *right;
    Node(int x)
    {
        this->data = x;
        this->left = NULL;
        this->right = NULL;
    }
};

Node *buildTree(Node *root)
{
    // pair<string, int> p;
    cout << "Enter the data: " << endl;
    int data;
    cin >> data;
    root = new Node(data);
    if (data == -1)
        return NULL;
    cout << "Enter data for inserting in left of : " << data << endl;
    root->left = buildTree(root->left);
    cout << "Enter data for inserting in right of : " << data << endl;
    root->right = buildTree(root->right);
    return root;
}
int height(Node *root)
{
    if (root == NULL)
        return 0;
    int l = height(root->left);
    int r = height(root->right);
    int ans = max(l, r) + 1;
    return ans;
}
bool isBalanced(Node *root)
{
    if (root == NULL)
        return true;
    bool l = isBalanced(root->left);
    bool r = isBalanced(root->right);
    bool diff = abs(height(root->left) - height(root->right)) <= 1;
    if (l && r && diff)
        return true;
    return false;
}
pair<bool, int> isBalancedFast(Node *root)
{
    if (root == NULL)
    {
        pair<bool, int> p = make_pair(true, 0);
        return p;
    }
    pair<bool, int> left = isBalancedFast(root->left);
    pair<bool, int> right = isBalancedFast(root->right);
    bool l = left.first;
    bool r = right.first;
    bool diff = abs(right.second - left.second) <= 1;
    pair<bool, int> ans;
    ans.second = max(left.second, right.second) + 1;
    if (l && r && diff)
        ans.first = true;
    else
        ans.first = false;
    return ans;
}
int diameter(Node *root)
{
    if (root == NULL)
        return 0;
    int op1 = diameter(root->left);
    int op2 = diameter(root->right);
    int op3 = height(root->left) + height(root->right) + 1;
    int ans = max(op1, max(op2, op3));
    return ans;
}
pair<int, int> diameterFast(Node *root)
{
    if (root == NULL)
    {
        pair<int, int> p = make_pair(0, 0);
        return p;
    }
    pair<int, int> left = diameterFast(root->left);
    pair<int, int> right = diameterFast(root->right);
    int op1 = left.first;
    int op2 = left.second;
    int op3 = left.second + right.second + 1;
    pair<int, int> ans;
    ans.first = max(op1, max(op2, op3));
    ans.second = max(left.second, right.second) + 1;
    return ans;
}
void levelOrderTraversal(Node *root)
{
    // level order traversal ke liye queue sahi padta hai .
    queue<Node *> q;
    // queue me root push karge
    q.push(root);
    q.push(NULL);
    while (!q.empty())
    {
        Node *temp = q.front();

        q.pop();
        if (temp == NULL) // tree jaise banane ke liye NULL dala hai
        {
            cout << endl;
            if (!q.empty()) // level complete but queue me lower_level bache hai so NULL push karege
                q.push(NULL);
        }
        else
        {
            cout << temp->data << " ";
            if (temp->left)
            { // temp->left me NULL na ho to queue me vo elemnt push kar dege
                q.push(temp->left);
            }
            if (temp->right) // temp->right me NULL na ho to queue me vo elemnt push kar dege
                q.push(temp->right);
        }
    }
}

void preOrder(Node *root)
{
    // base case
    if (root == NULL)
        return;
    cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}
void postOrder(Node *root)
{
    // base case
    if (root == NULL)
        return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->data << " ";
}
void buildFromLevelOrder(Node *&root)
{
    queue<Node *> q;
    cout << "Enter data for root: " << endl;
    int data;
    cin >> data;
    root = new Node(data);
    q.push(root);
    while (!q.empty())
    {
        Node *temp = q.front();
        q.pop();
        cout << "Enter data for left node: " << temp->data << endl;
        int leftData;
        cin >> leftData;
        if (leftData != -1)
        {
            temp->left = new Node(leftData);
            q.push(temp->left);
        }
        cout << "enter data for right Node: " << temp->data << endl;
        int rgData;
        cin >> rgData;
        if (rgData != -1)
        {
            temp->right = new Node(rgData);
            q.push(temp->right);
        }
    }
}
// Node *prev = NULL;
// Node *convertTreeDoubltyList(Node *root{
//     if(root==NULL)
//         return root;
//     Node *head = convertTreeDoubltyList(root->left, prev);
//     if(prev == NULL)
//         head = root;
//     else{
//         root->left = prev;
//         prev->right = root;
//     }
//     prev = root;
//     convertTreeDoubltyList(root->right, prev);
//     return head;

// }
void traverseSpiral(Node *root)
{
    if (root == NULL)
        return;
    queue<Node *> q;
    stack<int> s;
    bool rev = false;
    q.push(root);
    while (!q.empty())
    {
        int cnt = q.size();
        for (int i = 0; i < cnt; i++)
        {
            Node *curr = q.front();
            q.pop();
            if (rev)
                s.push(curr->data);
            else
                cout << curr->data << " ";
            if (curr->left)
                q.push(curr->left);
            if (curr->right)
                q.push(curr->right);
        }
        if (rev)
        {
            while (!s.empty())
            {
                cout << s.top() << " ";
                s.pop();
            }
        }
        rev = !rev;
        cout << endl;
    }
}
bool isValidBST(Node *root)
{
    if (root == NULL)
        return true;
    if (root->left == NULL && root->right == NULL)
        return true;
    int sum = 0;
    if (root->left != NULL)
        sum += root->left->data;
    if (root->right != NULL)
        sum += root->right->data;

    return (root->data < sum && (isValidBST(root->left) && isValidBST(root->right)));
}
int main()
{
    Node *root = NULL;
    // creating the tree
    root = buildTree(root);
    levelOrderTraversal(root);
    cout << "height of tree: " << height(root) << endl;
    cout << "Diameter of Tree in fast way: " << diameterFast(root).first << endl;
    cout << "Diameter of Tree: " << diameter(root) << endl;
    cout << " is Balanced tree: " << isBalancedFast(root).first << endl;

    cout << "Traversing the tree in spiral form: " << endl;
    traverseSpiral(root);
    cout << isValidBST(root);

    // cout<<"In order traversal: "<<endl;
    // inOrder(root);
    // cout<<"Pre order traversal: "<<endl;
    // preOrder(root);
    // cout<<" Post order traversal: "<<endl;
    // postOrder(root);
    // buildFromLevelOrder(root);
    // levelOrderTraversal(root);
    return 0;
}