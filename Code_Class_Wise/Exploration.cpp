class Exploration {
private:
    std::queue<Trip *> trips;

public:
    // Constructor
    Exploration() = default;

    // Getter
    std::queue<Trip *> getTrips() const {
        return trips;
    }

    // Functions
    void enqueue(Trip *trip) {
        trips.push(trip);
    }

    Trip *dequeue() {
        if (trips.empty()) {
            return nullptr;
        }
        Trip *trip = trips.front();
        trips.pop();
        return trip;
    }

    bool isEmpty() const {
        return trips.empty();
    }
};
