#include <iostream>
#include <string>
#include <queue>
#include <sstream>

using namespace std;

int violent_match(string s, string p) {
    int sLen = s.length();
    int pLen = p.length();
    int i = 0, j = 0;
    while (i < sLen && j < pLen) {
        if (s[i] == p[j]) {
            ++i;
            ++j;
        } else {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j == pLen) {
        return i - j;
    } else {
        return -1;
    }
}

void get_next(string p, vector<int>& next) {
    int pLen = p.length();
    next[0] = -1;
    int k = -1, j = 0;
    while (j < pLen - 1) {
        if (k == -1 || p[k] == p[j]) {
            ++k;
            ++j;
            next[j] = k;
        } else {
            k = next[k];
        }
    }
}

int kmp_match(string s, string p) {
    int sLen = s.length();
    int pLen = p.length();
    int i = 0, j = 0;
    vector<int> next(pLen);
    get_next(p, next);
    while (i < sLen && j < pLen) {
        if (j == -1 || s[i] == p[j]) {
            ++i;
            ++j;
        } else {
            j = next[j];
        }
    }
    if (j == pLen) {
        return i - j;
    } else {
        return -1;
    }
}


class TreeNode {
public:
    int val;
    TreeNode *left, *right;
    TreeNode(int val) {
        this->val = val;
        this->left = this->right = NULL;
    }
};

TreeNode* getNextNode(string data, int &index) {
    TreeNode* pTmp;
    if (data[index] == '#') {
        pTmp = NULL;
        ++index;
    } else {
        stringstream ss;
        while (data[index] != ',') {
            ss << data[index++];
        }
        int val;
        ss >> val;
        pTmp = new TreeNode(val);
    }
    ++index;
    return pTmp;
}

string serialize(TreeNode *root) {
    string ret;
    ret.push_back('{');
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* tmp = q.front();
        q.pop();
        if (tmp == NULL) {
            ret.push_back('#');
            ret.push_back(',');
        } else {
            stringstream ss;
            ss << tmp->val;
            ret += ss.str();
            ret += ",";
            q.push(tmp->left);
            q.push(tmp->right);
        }
    }
    ret.replace(ret.end() - 1, ret.end(), "}");
    return ret;
}

TreeNode *deserialize(string data) {
    // write your code here
    int start = 1;
    queue<TreeNode*> q;
    TreeNode* pHead = getNextNode(data, start);
    if (pHead == NULL) {
        return NULL;
    }
    q.push(pHead);

    while (!q.empty()) {
        TreeNode* pNode = q.front();
        q.pop();
        TreeNode* lNode = getNextNode(data, start);
        TreeNode* rNode = getNextNode(data, start);
        pNode->left = lNode;
        pNode->right = rNode;
        if (lNode) {
            q.push(lNode);
        }
        if (rNode) {
            q.push(rNode);
        }
    }
    return pHead;
}

void print(TreeNode* head) {
    queue<TreeNode*> q;
    q.push(head);
    while (!q.empty()) {
        TreeNode* tmp = q.front();
        q.pop();
        if (tmp != NULL) {
            cout << tmp->val << " ";
            q.push(tmp->left);
            q.push(tmp->right);
        }
    }
    cout << endl;
}

void rotateString(string &str,int offset){
    //wirte your code here
    offset = (offset + str.length()) % str.length();
    int cnt = 0;
    char cc = str[0];
    int idx = offset;
    int cycle = 0;
    while (cnt != str.length()) {
        char tmp = str[idx];
        str[idx] = cc;
        cc = tmp;
        if (idx == cycle) {
            ++idx;
            cc = str[idx];
            cycle = idx;
        }
        idx = (idx + offset) % str.length();
        ++cnt;
    }
}

void addRange(TreeNode* root, int k1, int k2, vector<int>& result) {
    if (root->left) {
        addRange(root->left, k1, k2, result);
    }
    if (root->val >= k1 && root->val <= k2) {
        result.push_back(root->val);
    }
    if (root->right) {
        addRange(root->right, k1, k2, result);
    }
}

vector<int> searchRange(TreeNode* root, int k1, int k2) {
    // write your code here
    vector<int> ret;
    addRange(root, k1, k2, ret);
    return ret;
}

void permute_dfs(vector<vector<int>> &ret, vector<int> &list, vector<int> nums, vector<int> &flags) {
    if (list.size() == nums.size()) {
        ret.push_back(list);
        return;
    }
    for (int i = 0; i < nums.size(); ++i) {
        if (flags[i] == 1) {
            continue;
        }
        list.push_back(nums[i]);
        flags[i] = 1;
        permute_dfs(ret, list, nums, flags);
        list.pop_back();
        flags[i] = 0;
    }
}


int main()
{
//    int a;
//    cin >> a;
//    string tmp = "abcdef";
//    cout << tmp << endl;
//    rotateString(tmp, a);
//    cout << tmp << endl;

    TreeNode* a = new TreeNode(20);
    TreeNode* b = new TreeNode(8);
    TreeNode* c = new TreeNode(22);
    TreeNode* d = new TreeNode(4);
    TreeNode* e = new TreeNode(12);

    a->left = b;
    a->right = c;
    b->left = d;
    b->right = e;

    print(a);

    vector<int> ret = searchRange(a, 10, 22);

    for(int num : ret){
        cout << num << endl;
    }
//
//    string ret = serialize(a);
//    cout << ret << endl;
//
//    TreeNode* h = deserialize(ret);
//    print(h);

    return 0;
}
