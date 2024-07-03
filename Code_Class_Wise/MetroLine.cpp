class MetroLine {
private:
    std::string lineName;
    MetroStation* headStation;

public:
    // Constructor
    MetroLine(const std::string& name) {
        lineName = name;
        headStation = nullptr;
    }

    // Getter
    std::string getLineName() const {
        return lineName;
    }

    MetroStation* getHeadStation() const {
        return headStation;
    }

    int getTotalStations() const {
        int count = 0;
        MetroStation* current = headStation;
        while (current != nullptr) {
            count++;
            current = current->getnextStation();
        }
        return count;
    }

    // Populate line from file
    void populateLine(const std::string& filePath) {
        std::ifstream file(filePath);
        std::string line;
        MetroStation* previous = nullptr;

        while (std::getline(file, line)) {
            if (line.empty()) continue;

            std::istringstream stream(line);
            std::vector<std::string> row;
            std::string word;

            while (std::getline(stream, word, ' ')) {
                row.push_back(word);
            }

            std::string stationName = line.substr(0, line.find_last_not_of("0123456789,") + 1);
            stationName.erase(stationName.find_last_not_of(' ') + 1);

            std::string fareStr = row.back();
            fareStr.erase(std::remove(fareStr.begin(), fareStr.end(), ','), fareStr.end());

            int ticketFare = string_to_int(fareStr);
            MetroStation* station = new MetroStation(stationName, this, ticketFare);

            if (previous != nullptr) {
                previous->setnextStation(station);
                station->setpreviousStation(previous);
            } else {
                headStation = station;
            }

            previous = station;
        }
    }

    // Setter
    void setHeadStation(MetroStation* station) {
        headStation = station;
    }

    // Print the line stations
    void printLine() const {
        MetroStation* current = headStation;
        while (current != nullptr) {
            std::cout << current->getstationName() << std::endl;
            current = current->getnextStation();
        }
    }
};
