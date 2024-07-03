class AVLNode {
private:
    std::string stationName;
    std::vector<MetroStation *> stops;
    AVLNode *left;
    AVLNode *right;
    AVLNode *parent;

public:
    // Constructor
    explicit AVLNode(std::string name) 
        : stationName(std::move(name)), left(nullptr), right(nullptr), parent(nullptr) {}

    // Getter methods
    std::string getstationName() const { return stationName; }
    const std::vector<MetroStation *> &getStops() const { return stops; }
    AVLNode *getLeft() const { return left; }
    AVLNode *getRight() const { return right; }
    AVLNode *getParent() const { return parent; }

    // Setter methods
    void addMetroStation(MetroStation *station) { stops.push_back(station); }
    void setLeft(AVLNode *leftNode) { left = leftNode; }
    void setRight(AVLNode *rightNode) { right = rightNode; }
    void setParent(AVLNode *parentNode) { parent = parentNode; }
};
