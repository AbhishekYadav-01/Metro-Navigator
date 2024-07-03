
class PathFinder
{
private:
    AVLTree *tree;
    std::vector<MetroLine *> lines;

public:
    std::string starting_location;

    // Constructor
    PathFinder(AVLTree *avlTree, const std::vector<MetroLine *> &metroLines)
        : tree(avlTree), lines(metroLines)
    {
    }

    // Getter for AVL tree
    AVLTree *getTree() const
    {
        return tree;
    }

    // Getter for metro lines
    const std::vector<MetroLine *> &getLines() const
    {
        return lines;
    }

    // Populate the AVL tree with metro lines
    void createAVLTree()
    {
        for (auto &metroline : lines)
        {
            tree->populateTree(metroline);
        }
    }

// Search path going left
Trip *searchpath_left(std::string start, std::string end, std::vector<std::string> junctions, std::vector<Path *> &paths, Trip *previous_tail)
{
    Trip *tail = nullptr;
    auto stops = tree->searchStop(start)->getStops();
    auto it = stops.begin();
    
    while (it != stops.end())
    {
        auto current = *it;
        tail = nullptr;
        int firstTime = 0;

        for (;;)
        {
            if (!current)
            {
                break;
            }
            Trip *trip = new Trip(current, tail);
            if (firstTime == 0)
            {
                trip->setPrev(previous_tail);
                firstTime = 1;
            }
            tail = trip;
            if (current->getstationName() == end)
            {
                Trip *trip = tail;
                Path *path = new Path();
                while (trip)
                {
                    path->addStop(trip->getHeadStation());
                    trip = trip->getPrev();
                }
                paths.push_back(path);
                return nullptr;
            }
            if (std::find(junctions.begin(), junctions.end(), current->getstationName()) != junctions.end())
            {
                return nullptr;
            }
            auto nextStops = tree->searchStop(current->getstationName())->getStops();
            if (nextStops.size() != 1)
            {
                junctions.push_back(current->getstationName());
                for (auto &nextStop : nextStops)
                {
                    if (nextStop->getnextStation())
                    {
                        searchpath_right(nextStop->getnextStation()->getstationName(), end, junctions, paths, tail);
                    }
                    if (nextStop->getpreviousStation())
                    {
                        searchpath_left(nextStop->getpreviousStation()->getstationName(), end, junctions, paths, tail);
                    }
                }
                return nullptr;
            }
            current = current->getpreviousStation();
        }
        ++it;
    }
    return nullptr;
}


    // Search path going right
   Trip *searchpath_right(std::string start, std::string end, std::vector<std::string> junctions, std::vector<Path *> &paths, Trip *previous_tail)
{
    Trip *tail = nullptr;
    auto stops = tree->searchStop(start)->getStops();
    
    for (auto &current : stops)
    {
        tail = nullptr;
        int firstTime = 0;
        
        while (true)
        {
            if (!current)
            {
                break;
            }
            Trip *trip = new Trip(current, tail);
            if (firstTime == 0)
            {
                trip->setPrev(previous_tail);
                firstTime = 1;
            }
            tail = trip;
            if (current->getstationName() == end)
            {
                Trip *trip = tail;
                Path *path = new Path();
                while (trip)
                {
                    path->addStop(trip->getHeadStation());
                    trip = trip->getPrev();
                }
                paths.push_back(path);
                return nullptr;
            }
            if (std::find(junctions.begin(), junctions.end(), current->getstationName()) != junctions.end())
            {
                return nullptr;
            }
            auto nextStops = tree->searchStop(current->getstationName())->getStops();
            if (nextStops.size() != 1)
            {
                junctions.push_back(current->getstationName());
                for (auto &nextStop : nextStops)
                {
                    if (nextStop->getnextStation())
                    {
                        searchpath_right(nextStop->getnextStation()->getstationName(), end, junctions, paths, tail);
                    }
                    if (nextStop->getpreviousStation())
                    {
                        searchpath_left(nextStop->getpreviousStation()->getstationName(), end, junctions, paths, tail);
                    }
                }
                return nullptr;
            }
            current = current->getnextStation();
        }
    }
    return nullptr;
}


    // Find the shortest path
    Path *findPath(std::string origin, std::string destination)
    {
        std::vector<std::string> junction_v;
        std::vector<std::string> junction_v_2;
        junction_v.push_back(origin);
        starting_location = origin;
        Path *ans = nullptr;
        int ticketFare = 0;
        auto curr = tree->searchStop(origin)->getStops().front();
        std::vector<Path *> possible_path;
        Trip *tail_right = new Trip(curr, nullptr);
        Trip *tail_left = new Trip(curr, nullptr);
        if (curr->getnextStation())
        {
            searchpath_right(curr->getnextStation()->getstationName(), destination, junction_v, possible_path, tail_right);
        }
        if (curr->getpreviousStation())
        {
            searchpath_left(curr->getpreviousStation()->getstationName(), destination, junction_v_2, possible_path, tail_left);
        }
        if (possible_path.empty())
        {
            return new Path();
        }
        int min = INT_MAX;
        for (auto &path : possible_path)
        {
            if (path->getStops().size() < min)
            {
                ans = path;
                min = path->getStops().size();
            }
        }
        auto stops = ans->getStops();
        for (size_t i = 0; i < stops.size() - 1; ++i)
        {
            if (stops[i + 1]->getLine()->getLineName() != stops[i]->getLine()->getLineName())
            {
                auto v1 = tree->searchStop(stops[i]->getstationName())->getStops();
                auto v2 = tree->searchStop(stops[i + 1]->getstationName())->getStops();
                bool found = false;
                for (auto &s1 : v1)
                {
                    if (found)
                    {
                        break;
                    }
                    for (auto &s2 : v2)
                    {
                        if (s1->getLine()->getLineName() == s2->getLine()->getLineName())
                        {
                            if (s1->getnextStation() && s1->getnextStation()->getstationName() == s2->getstationName())
                            {
                                ticketFare += abs(s2->getticketFare() - s1->getticketFare());
                                found = true;
                                break;
                            }
                            if (s1->getpreviousStation() && s1->getpreviousStation()->getstationName() == s2->getstationName())
                            {
                                ticketFare += abs(s2->getticketFare() - s1->getticketFare());
                                found = true;
                                break;
                            }
                        }
                    }
                }
                continue;
            }
            ticketFare += abs(stops[i]->getticketFare() - stops[i + 1]->getticketFare());
        }
        ans->setTotalticketFare(ticketFare);
        return ans;
    }
};

vector<MetroLine *> lines;

