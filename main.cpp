
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <sstream>

// We'll use a simple file-based storage system
// Each index will have its own file containing the values
// File name will be the index (with some sanitization if needed)
// Each line in the file will contain one value

class FileStorage {
private:
    std::string getFileName(const std::string& index) {
        // In a real system, we might need to sanitize the index for file names
        // For now, we'll assume the index is safe for use as a filename
        return index;
    }

public:
    void insert(const std::string& index, int value) {
        std::string filename = getFileName(index);
        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {
            file << value << "\n";
            file.close();
        }
    }

    void remove(const std::string& index, int value) {
        std::string filename = getFileName(index);
        std::ifstream file(filename);
        
        if (!file.is_open()) {
            // File doesn't exist, nothing to delete
            return;
        }
        
        // Read all values
        std::vector<int> values;
        int val;
        while (file >> val) {
            if (val != value) {
                values.push_back(val);
            }
        }
        file.close();
        
        // Write back the remaining values
        std::ofstream outfile(filename);
        if (outfile.is_open()) {
            for (int v : values) {
                outfile << v << "\n";
            }
            outfile.close();
        }
        
        // If no values left, remove the file
        if (values.empty()) {
            std::remove(filename.c_str());
        }
    }

    std::vector<int> find(const std::string& index) {
        std::string filename = getFileName(index);
        std::ifstream file(filename);
        std::vector<int> values;
        
        if (!file.is_open()) {
            return values; // Return empty vector (will be treated as null)
        }
        
        int value;
        while (file >> value) {
            values.push_back(value);
        }
        file.close();
        
        // Sort values in ascending order
        std::sort(values.begin(), values.end());
        
        // Remove duplicates (though the problem states same index can't have duplicate values)
        values.erase(std::unique(values.begin(), values.end()), values.end());
        
        return values;
    }
};

int main() {
    FileStorage storage;
    int n;
    std::cin >> n;
    std::cin.ignore(); // Ignore the newline after n
    
    for (int i = 0; i < n; i++) {
        std::string line;
        std::getline(std::cin, line);
        
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        
        if (command == "insert") {
            std::string index;
            int value;
            iss >> index >> value;
            storage.insert(index, value);
        } 
        else if (command == "delete") {
            std::string index;
            int value;
            iss >> index >> value;
            storage.remove(index, value);
        } 
        else if (command == "find") {
            std::string index;
            iss >> index;
            std::vector<int> values = storage.find(index);
            
            if (values.empty()) {
                std::cout << "null" << std::endl;
            } else {
                for (size_t j = 0; j < values.size(); j++) {
                    if (j > 0) std::cout << " ";
                    std::cout << values[j];
                }
                std::cout << std::endl;
            }
        }
    }
    
    return 0;
}
