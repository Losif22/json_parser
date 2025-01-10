#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>

//  A structure to hold the parsed JSON data
struct JsonObject {
    std::string name;
    int age;
    std::vector<std::string> skills;
};
 
class JsonParser {
public:
    JsonObject parse(const std::string& jsonString) {
        JsonObject jsonObject;
        size_t pos = 0;
        
        // Extract "name"
        pos = jsonString.find("\"name\":");
        if (pos != std::string::npos) {
            size_t start = jsonString.find('"', pos + 7) + 1;
            size_t end = jsonString.find('"', start);
            jsonObject.name = jsonString.substr(start, end - start);
        }

        // Extract "age"
        pos = jsonString.find("\"age\":");
        if (pos != std::string::npos) {
            size_t start = pos + 6;
            size_t end = jsonString.find(',', start);
            jsonObject.age = std::stoi(jsonString.substr(start, end - start));
        }

        // Extract "skills"
        pos = jsonString.find("\"skills\":");
        if (pos != std::string::npos) {
            size_t start = jsonString.find('[', pos) + 1;
            size_t end = jsonString.find(']', start);
            std::string skillsString = jsonString.substr(start, end - start);
            size_t skillStart = 0, skillEnd = 0;
            while ((skillEnd = skillsString.find('"', skillStart)) != std::string::npos) {
                skillStart = skillEnd + 1;
                skillEnd = skillsString.find('"', skillStart);
                jsonObject.skills.push_back(skillsString.substr(skillStart, skillEnd - skillStart));
                skillStart = skillEnd + 1;
            }
        }
         
        return jsonObject;
    }
};

int main() {
    std::ifstream inputFile("data.json");
    if (!inputFile) {
        std::cout << "Error open file! \n";
        return -1;
    }
    std::ostringstream buffer;
    buffer << inputFile.rdbuf();
    std::string jsonString = buffer.str();
     
    JsonParser parser; 
    JsonObject result = parser.parse(jsonString);

    std::cout << "Name: " << result.name << std::endl;
    std::cout << "Age: " << result.age << std::endl;
    std::cout << "Skills: ";
    for (const auto& skill : result.skills) {
        std::cout << skill << " "; 
    } 
    std::cout << std::endl;
    system("pause>nul");
    return 0;
}