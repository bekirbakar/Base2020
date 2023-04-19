#ifndef ENVIRONMENT_PARSER_H
#define ENVIRONMENT_PARSER_H

#include <list>
#include <string>
#include <unordered_map>

extern void getEnvironmentOptions();

struct Section
{
    std::string name;
    std::unordered_map<std::string, std::string> keyValues;
};

class ConfigParser
{
public:
    explicit ConfigParser(const std::string &filename);
    Section *getSection(const std::string &sectionName);
    std::list<Section> &getSections();
    std::string getValue(const std::string &sectionName,
    const std::string &keyName);

private:
    void parse(const std::string &filename);
    std::list<Section> sections;
};

#endif // !ENVIRONMENT_PARSER_H