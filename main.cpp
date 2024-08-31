#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <format>

std::string
trim(const std::string& str)
{
    size_t first = str.find_first_not_of(" \t\"");
    if (first == std::string::npos) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t\"");
    return str.substr(first, (last - first + 1));
}

void 
add_to_map(std::map<std::string, std::string>& config, const std::string& line) 
{

    size_t pos = line.find('=');
    if (pos != std::string::npos)
    {
        std::string key = trim(line.substr(0, pos));
        std::string value = trim(line.substr(pos + 1));
        if (!key.empty())
            config[key] = value;
    }
}

std::map <std::string, std::string>
read_config_file(const std::string& filename) {
    std::map<std::string, std::string> config;

    std::ifstream infile(filename);
    if (!infile.good()) {
        throw std::runtime_error("Cannot open file " + filename);
    }
    std::string line;
    while (std::getline(infile, line))
    {
        //std::cout << line << std::endl;
        add_to_map(config, line);
    }
    return config;
}

void test_load_config(const std::string& fileName) 
{
    try
    {
        std::cout << "Loading config from file " << fileName << std::endl;
        auto config = read_config_file(fileName);
        std::cout << "======== Config ========" << std::endl;
        for (const auto& item : config) {
            std::cout << std::format("'{}' = '{}'\n", item.first, item.second);
        }    
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "================" << std::endl;
}

int main() 
{
    try 
    {
        test_load_config("config.ini");
        test_load_config("config2.ini");
        test_load_config("config3.ini");
        test_load_config("config_missing.ini");
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
