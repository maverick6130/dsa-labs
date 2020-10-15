#include<bits/stdc++.h>
using namespace std;

struct Node {
    char type;
    Node *left, *right;
    int expr;
    Node(char t) : type(t), expr(0)
    ,left(NULL), right(NULL) {};
};

pair<int,int> ops (Node* tree, int init=1) {
    if(tree->type=='e') return pair<int,int> (0,0);
    pair<int,int> l,r;
    if(tree->left->type==tree->type) l = ops (tree->left,0);
    else l = ops (tree->left);
    if(tree->right->type==tree->type) r = ops (tree->right,0);
    else r = ops (tree->right);
    return pair<int,int> (init+l.first+r.first,init+max(l.second,r.second));
}

int ksteps(Node *tree, int k) {
    if(tree->type=='e') return 0;

    int l = ksteps(tree->left,k);
    int r = ksteps(tree->right,k);
    
    if((tree->left->type!=tree->type)&&(tree->right->type!=tree->type)) {
        tree->expr = 1;
        return 1 + l + r;
    }
    
    if((tree->left->type==tree->type)&&(tree->right->type!=tree->type)) {
        if(tree->left->expr<k) {
            tree->expr = tree->left->expr + 1;
            return l + r; 
        }
        tree->expr = 1;
        return 1 + l + r;
    }
    
    if((tree->right->type==tree->type)&&(tree->left->type!=tree->type)) {
        if(tree->right->expr<k) {
            tree->expr = tree->right->expr + 1;
            return r + l; 
        }
        tree->expr = 1;
        return 1 + r + l;
    }

    if (tree->left->expr+tree->right->expr<k) {
        tree->expr = tree->left->expr + tree->right->expr + 1;
        return l+r-1;
    }
    
    if (tree->left->expr<tree->right->expr) {
        if(tree->left->expr<k) {
            tree->expr = tree->left->expr + 1;
            return l + r; 
        }
        tree->expr = 1;
        return 1 + l + r;
    }

    if(tree->right->expr<k) {
        tree->expr = tree->right->expr + 1;
        return l + r; 
    }

    tree->expr = 1;
    return 1 + l + r;

}

int ktime(Node *tree, int k) {
    if(tree->type=='e') return 0;

    int l = ktime(tree->left,k);
    int r = ktime(tree->right,k);
    
    if((tree->left->type!=tree->type)&&(tree->right->type!=tree->type)) {
        tree->expr = 1;
        return 1 + max(l,r);
    }
    
    if((tree->left->type==tree->type)&&(tree->right->type!=tree->type)) {
        if(tree->left->expr<k) {
            if(l<=r) {
                tree->expr = 1;
                return r+1;    
            }
            tree->expr = tree->left->expr + 1;
            return l;
        }
        tree->expr = 1;
        return 1 + max(l,r);
    }
    
    if((tree->right->type==tree->type)&&(tree->left->type!=tree->type)) {
        if(tree->right->expr<k) {
            if(r<=l) {
                tree->expr = 1;
                return l+1;
            }
            tree->expr = tree->right->expr + 1;
            return r; 
        }
        tree->expr = 1;
        return 1 + max(l,r);
    }

    if (tree->left->expr+tree->right->expr<k) {
        if (l<r) {
            tree->expr = tree->right->expr + 1;
            return r;
        }
        if (r<l) {
            tree->expr = tree->left->expr + 1;
            return l;
        }
        tree->expr = tree->left->expr + tree->right->expr + 1;
        return l;
    }
    
    if(l<r) {
        if(tree->right->expr<k) {
            tree->expr = tree->right->expr + 1;
            return r;
        }
        tree->expr = 1;
        return r+1;
    }

    if(r<l) {
        if(tree->left->expr<k) {
            tree->expr = tree->left->expr + 1;
            return l;
        }
        tree->expr = 1;
        return l+1;
    }

    tree->expr = 1;
    return l+1;
}

int main(int argc, char *argv[]) {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string s;
    cin >> s;

    stack <Node*> mktree;
    for(auto x : s) {
        if(x=='e') mktree.push(new Node(x));
        else {
            Node* n = new Node(x);
            n->right = mktree.top();
            mktree.pop();
            n->left = mktree.top();
            mktree.pop();
            mktree.push(n);
        }
    }
    auto tree = mktree.top();

    cout << ops(tree).first << " " << ops(tree).second << endl;

    int t;
    cin >> t;
    while(t--) {
        int k;
        cin >> k;
        cout << ksteps(tree,k-1) << " " << ktime(tree,k-1) << endl;
    }

    return 0;
}