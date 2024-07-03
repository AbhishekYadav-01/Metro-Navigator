class Trip
{
private:
    MetroStation *headStation;
    Trip *prev;

public:
    // Constructor
    Trip(MetroStation *MetroStation, Trip *previousTrip = nullptr)
        : headStation(MetroStation), prev(previousTrip)
    {
    }

    // Getter for headStation
    MetroStation *getHeadStation() const
    {
        return headStation;
    }

    // Getter for prev
    Trip *getPrev() const
    {
        return prev;
    }

    // Setter for prev
    void setPrev(Trip *previousTrip)
    {
        prev = previousTrip;
    }
};
