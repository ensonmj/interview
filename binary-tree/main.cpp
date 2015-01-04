#include <iostream>
#include <stack>

using namespace std;

struct Node {
    Node(int v=0, Node *l=nullptr, Node *r=nullptr):val(v), left(l), right(r) {}

    int val;
    Node *left;
    Node *right;
};

void preTraversal(Node *p) {
    if(p) {
        cout << p->val << " ";
        preTraversal(p->left);
        preTraversal(p->right);
    }
}

void inTraversal(Node *p) {
    if(p) {
        inTraversal(p->left);
        cout << p->val << " ";
        inTraversal(p->right);
    }
}

void postTraversal(Node *p) {
    if(p) {
        postTraversal(p->left);
        postTraversal(p->right);
        cout << p->val << " ";
    }
}

void preTraversalNonRecur(Node *p) {
    stack<Node *> s;

    while(p || !s.empty()) {
        if(p) {
            cout << p->val << " ";
            s.push(p);
            p = p->left;
        } else {
            p = s.top();
            s.pop();
            p = p->right;
        }
    }
}

void inTraversalNonRecur(Node *p) {
    stack<Node *> s;

    while(p || !s.empty()) {
        if(p) {
            s.push(p);
            p = p->left;
        } else {
            p = s.top();
            s.pop();
            cout << p->val << " ";
            p = p->right;
        }
    }

}

void postTraversalNonRecur(Node *p) {
    stack<Node *> s;
    Node *pre = nullptr;

    while(p || !s.empty()) {
        if(p) {
            s.push(p);
            p = p->left;
        } else if(s.top()->right != pre) {
            p = s.top()->right;
            pre = nullptr;
        } else {
            pre = s.top();
            s.pop();
            cout << pre->val << " ";
        }
    }

}

int main(int argc, char const* argv[]) {
    /*
     *      6            //preorder  6 2 1 4 3 8 10
     *     / \
     *    2   8          //inorder   1 2 3 4 6 8 10
     *   / \   \
     *  1   4   10       //postorder 1 3 4 2 10 8 6
     *     /
     *    3
     */
    Node *head = new Node(6, new Node(2, new Node(1), new Node(4, new Node(3))), new Node(8, nullptr, new Node(10)));

    cout << "Recursive:" << endl;
    preTraversal(head);
    cout << endl;

    inTraversal(head);
    cout << endl;

    postTraversal(head);
    cout << endl;

    cout << "Nonrecursive:" << endl;
    preTraversalNonRecur(head);
    cout << endl;

    inTraversalNonRecur(head);
    cout << endl;

    postTraversalNonRecur(head);
    cout << endl;

    return 0;
}
