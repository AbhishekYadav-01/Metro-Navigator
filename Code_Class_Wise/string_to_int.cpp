int string_to_int(const std::string &str) {
    int result = 0;
    for (char c : str) {
        if (c < '0' || c > '9') {
            throw std::invalid_argument("Invalid input string");
        }
        result = result * 10 + (c - '0');
    }
    return result;
}
