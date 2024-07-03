class Path
{
private:
    std::vector<MetroStation *> stops;
    int totalticketFare;

public:
    // Constructor
    Path() : totalticketFare(0)
    {
    }

    // Getter for stops
    std::vector<MetroStation *> getStops() const
    {
        return stops;
    }

    // Getter for totalticketFare
    int getTotalticketFare() const
    {
        return totalticketFare;
    }

    // Add a stop to the path
    void addStop(MetroStation *stop)
    {
        stops.push_back(stop);
    }

    // Set the total ticket fare
    void setTotalticketFare(int ticketFare)
    {
        totalticketFare = ticketFare;
    }

    // Get the names of the stations in the path
    std::vector<std::string> getPath() const
    {
        std::vector<std::string> ans;
        for (const auto& stop : stops)
        {
            ans.push_back(stop->getstationName());
        }
        return ans;
    }
};
