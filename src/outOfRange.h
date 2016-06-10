#include <string>

/**
 * @class OutOfRange
 *
 * @brief Class to represent an out of range exception.
 *
 * Thrown whenever an out of range exception occurs.
 * It stores the details of the exception (the value that went out of range,
 * the variable and the line number where the exception occured).
 */
class OutOfRange {
    private:
        int value;
        std::string varName;
        int lineNumber;
    public:
        OutOfRange(int value, int lineNumber, std::string varName);
        std::string getErrorMessage();
};
