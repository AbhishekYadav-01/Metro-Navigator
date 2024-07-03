class MetroStation {
private:
    std::string stationName;
    MetroStation *nextStation;
    MetroStation *previousStation;
    MetroLine *line;
    int ticketFare;

public:
    // Constructor
    MetroStation(const std::string &name, MetroLine *metroLine, int fare)
        : stationName(name), nextStation(nullptr), previousStation(nullptr), line(metroLine), ticketFare(fare) {}

    // Getters
    std::string getstationName() const {
        return stationName;
    }

    MetroStation *getnextStation() const {
        return nextStation;
    }

    MetroStation *getpreviousStation() const {
        return previousStation;
    }

    MetroLine *getLine() const {
        return line;
    }

    int getticketFare() const {
        return ticketFare;
    }

    // Setters
    void setnextStation(MetroStation *next) {
        nextStation = next;
    }

    void setpreviousStation(MetroStation *prev) {
        previousStation = prev;
    }
};
