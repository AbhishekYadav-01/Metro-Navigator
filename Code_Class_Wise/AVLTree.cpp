// AVLTree class
class AVLTree
{
private:
    AVLNode *root;

public:
    // constructor
    AVLTree()
    {
        root = 0;
    }
    AVLNode *getRoot() const
    {
        return root;
    }

    void setRoot(AVLNode *root)
    {
        this->root = root;
    }

int height(AVLNode *headStation) {
    if (headStation == nullptr) {
        return 0;
    }
    int leftHeight = height(headStation->getLeft());
    int rightHeight = height(headStation->getRight());
    return std::max(leftHeight, rightHeight) + 1;
}


int balanceFactor(AVLNode *headStation) {
    if (headStation == nullptr) {
        return 0;
    }
    int leftHeight = height(headStation->getLeft());
    int rightHeight = height(headStation->getRight());
    return leftHeight - rightHeight;
}


AVLNode *rotateLeft(AVLNode *x) {
    AVLNode *y = x->getRight();
    AVLNode *T2 = y->getLeft();
    AVLNode *x_parent = x->getParent();

    // Perform rotation
    x->setParent(y);
    if (T2 != nullptr) {
        T2->setParent(x);
    }
    y->setLeft(x);
    x->setRight(T2);

    return y;
}


AVLNode *rotateRight(AVLNode *y) {
    AVLNode *x = y->getLeft();
    AVLNode *T2 = x->getRight();
    AVLNode *y_parent = y->getParent();

    // Perform rotation
    y->setParent(x);
    if (T2 != nullptr) {
        T2->setParent(y);
    }
    x->setRight(y);
    y->setLeft(T2);

    return x;
}


int stringCompare(const std::string& s1, const std::string& s2) {
    if (s1 == s2) {
        return 0;
    } else if (s1 < s2) {
        return -1;
    } else {
        return 1;
    }
}


    // inorder traversal
void inOrderTraversal(AVLNode *root) {
    if (root == nullptr) {
        return;
    }
    inOrderTraversal(root->getLeft());
    cout << root->getstationName() << endl;
    inOrderTraversal(root->getRight());
}


    // calculaing lexicographical value
int lex_order(string s1, string s2) {

    int i = 0;
    
    while (i < s1.length() && i < s2.length()) {
        if (int(s1[i]) == int(s2[i])) {
            i++;
            continue;
        } else if (int(s1[i]) < int(s2[i])) {
            return 1;
        } else {
            return 0;
        }
    }
    
    if (s1.length() == s2.length()) {
        return -1;
    } else if (s1.length() < s2.length()) {
        return 1;
    } else {
        return 0;
    }
}


AVLNode* addnode(string &to_add, AVLNode *root, MetroStation *ptr) {
    if (root == nullptr) {
        AVLNode *newNode = new AVLNode(to_add);
        newNode->addMetroStation(ptr);
        return newNode;
    }

    string currentStationName = root->getstationName();

    if (lex_order(to_add, currentStationName) == -1) {
        root->addMetroStation(ptr);
        return root;
    }

    if (lex_order(to_add, currentStationName)) {
        root->setLeft(addnode(to_add, root->getLeft(), ptr));
        root->getLeft()->setParent(root);
    } else {
        root->setRight(addnode(to_add, root->getRight(), ptr));
        root->getRight()->setParent(root);
    }

    int balance = balanceFactor(root);

    if (balance == 2) {
        string leftChildName = root->getLeft()->getstationName();
        if (lex_order(to_add, leftChildName)) {
            return rotateRight(root);
        } else if (!lex_order(to_add, leftChildName)) {
            root->setLeft(rotateLeft(root->getLeft()));
            return rotateRight(root);
        }
    }

    if (balance == -2) {
        string rightChildName = root->getRight()->getstationName();
        if (lex_order(rightChildName, to_add)) {
            return rotateLeft(root);
        } else if (!lex_order(rightChildName, to_add)) {
            root->setRight(rotateRight(root->getRight()));
            return rotateLeft(root);
        }
    }

    return root;
}


void insert(AVLNode *root, MetroStation *MetroStation) {
    string to_add = MetroStation->getstationName();
    AVLNode *newRoot = addnode(to_add, root, MetroStation);
    this->setRoot(newRoot);
}


void populateTree(MetroLine *metroLine) {
    MetroStation *currentStation = metroLine->getHeadStation();
    AVLNode *treeRoot = this->getRoot();
    
    if (treeRoot != nullptr) {
        if (treeRoot->getLeft() == nullptr && treeRoot->getRight() == nullptr) {
            currentStation = currentStation->getnextStation();
        }
    }
    
    if (treeRoot == nullptr) {
        AVLNode *newNode = new AVLNode(currentStation->getstationName());
        newNode->addMetroStation(currentStation);
        this->setRoot(newNode);
        currentStation = currentStation->getnextStation();
    }
    
    while (currentStation != nullptr) {
        insert(this->getRoot(), currentStation);
        currentStation = currentStation->getnextStation();
    }
}


int getTotalNodes(AVLNode *headStation) {
    if (headStation == nullptr) {
        return 0;
    }
    int leftCount = getTotalNodes(headStation->getLeft());
    int rightCount = getTotalNodes(headStation->getRight());
    return leftCount + rightCount + 1;
}


AVLNode *search(AVLNode *headStation, string &stationName) {
    if (headStation == nullptr) {
        return nullptr;
    }

    if (headStation->getstationName() == stationName) {
        return headStation;
    }

    AVLNode *foundNode = search(headStation->getLeft(), stationName);
    if (foundNode != nullptr) {
        return foundNode;
    }

    return search(headStation->getRight(), stationName);
}


    AVLNode *searchStop(string stationName)
    {
        return search(this->getRoot(), stationName);
    }
};
