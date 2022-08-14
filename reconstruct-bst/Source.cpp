#include <vector>
#include <limits>
#include <iostream>

using namespace std;

// This is an input class. Do not edit.
class BST {
public:
    int value;
    BST* left = nullptr;
    BST* right = nullptr;

    BST(int value) { this->value = value; }
};

struct Treeinfo
{
    int rootIdx;
};

struct Trunk
{
    Trunk* prev;
    string str;

    Trunk(Trunk* prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

BST* reconstructBstFromRange(int lowerBound, int upperBound, vector<int>& preOrderTraversalValues, Treeinfo& currentSubTreeInfo);
BST* reconstructBst(vector<int> preOrderTraversalValues);
void printTree(BST* root, Trunk* prev, bool isLeft);
void showTrunks(Trunk* p);

int main()
{
    vector<int> preOrderTraversalValues = { 10, 4, 2, 1, 5, 17, 19, 18 };

    auto actual = reconstructBst(preOrderTraversalValues);

    printTree(actual, nullptr, false);
    return 0;
}

BST* reconstructBst(vector<int> preOrderTraversalValues) {
    // Write your code here.
    auto treeInfo = Treeinfo{ 0 };
    return reconstructBstFromRange(numeric_limits<int>::min(), numeric_limits<int>::max(), preOrderTraversalValues, treeInfo);
}

BST* reconstructBstFromRange(int lowerBound, int upperBound, vector<int>& preOrderTraversalValues, Treeinfo& currentSubTreeInfo)
{
    if (currentSubTreeInfo.rootIdx == preOrderTraversalValues.size())
        return nullptr;

    int rootValue = preOrderTraversalValues[currentSubTreeInfo.rootIdx];

    if (rootValue < lowerBound || rootValue >= upperBound)return nullptr;

    currentSubTreeInfo.rootIdx++;
    auto leftSubTree = reconstructBstFromRange(lowerBound, rootValue, preOrderTraversalValues, currentSubTreeInfo);
    auto rightSubTree = reconstructBstFromRange(rootValue, upperBound, preOrderTraversalValues, currentSubTreeInfo);

    auto bst = new BST(rootValue);
    bst->left = leftSubTree;
    bst->right = rightSubTree;

    return bst;
}

void showTrunks(Trunk* p)
{
    if (p == nullptr) {
        return;
    }

    showTrunks(p->prev);
    cout << p->str;
}

void printTree(BST* root, Trunk* prev, bool isLeft)
{
    if (root == nullptr) {
        return;
    }

    string prev_str = "    ";
    Trunk* trunk = new Trunk(prev, prev_str);

    printTree(root->right, trunk, true);

    if (!prev) {
        trunk->str = "---";
    }
    else if (isLeft)
    {
        trunk->str = ".---";
        prev_str = "   |";
    }
    else {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << " " << root->value << endl;

    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";

    printTree(root->left, trunk, false);
}