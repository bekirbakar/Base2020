#include <list>
#include <string>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <boost/program_options.hpp>

#include "environment_parser.h"

static std::string &lTrim(std::string &s)
{
    const auto startPosition = s.find_first_not_of(" \t\r\n\v\f");

    if (std::string::npos != startPosition)
    {
        s = s.substr(startPosition);
    }

    return s;
}

static std::string &tTrim(std::string &s)
{
    const auto endPosition = s.find_last_not_of(" \t\r\n\v\f");

    if (std::string::npos != endPosition)
    {
        s = s.substr(0, endPosition + 1);
    }

    return s;
}

ConfigParser::ConfigParser(const std::string &filename)
{
    parse(filename);
}

Section *ConfigParser::getSection(const std::string &sectionName)
{
    const auto found = std::find_if(sections.begin(),
                                    sections.end(),
                                    [sectionName](const Section &sect)
                                    { return sect.name == sectionName; });

    return found != sections.end() ? &*found : nullptr;
}

std::list<Section> &ConfigParser::getSections()
{
    return sections;
}

std::string ConfigParser::getValue(const std::string &sectionName,
const std::string &keyName)
{
    auto *sect = getSection(sectionName);

    if (sect != nullptr)
    {
        const std::unordered_map<std::string,
        std::string>::const_iterator it = sect->keyValues.find(keyName);

        if (it != sect->keyValues.end())
            return it->second;
    }

    return "";
}

void ConfigParser::parse(const std::string &filename)
{
    Section currentSection;
    std::ifstream fstrm;
    fstrm.open(filename);

    if (!fstrm)
        throw std::invalid_argument(filename + " could not be opened!");

    for (std::string line; std::getline(fstrm, line);)
    {
        if (!line.empty() && (line[0] == ';' || line[0] == '#'))
        {
        }
        else if (line[0] == '[')
        {
            auto end = line.find_first_of(']');
            if (end != std::string::npos)
            {
                if (!currentSection.name.empty())
                {
                    sections.push_back(currentSection);
                    currentSection.name.clear();
                    currentSection.keyValues.clear();
                }

                currentSection.name = line.substr(1, end - 1);
            }
            else
            {
            }
        }
        else if (!line.empty())
        {
            auto end = line.find_first_of("=:");

            if (end != std::string::npos)
            {
                auto name = line.substr(0, end);
                auto value = line.substr(end + 1);
                lTrim(tTrim(name));
                lTrim(tTrim(value));

                currentSection.keyValues[name] = value;
            }
            else
            {
            }
        }
    }

    if (!currentSection.name.empty())
    {
        sections.push_back(currentSection);
        currentSection.name = "";
        currentSection.keyValues.clear();
    }
}

void generate_config_sample(const std::string &filename)
{
    std::ofstream stream;
    stream.open(filename);

    if (stream)
    {
        stream << "[protocol]\nversion = 7   \n\n[user]\nname = Bekir Bakar"
                  "\nemail = b.bakar@outlook.com";
    }
}

void run()
{
    // get_env_options();

    generate_config_sample("system.ini");

    ConfigParser configParser("system.ini");
    auto *const userSection = configParser.getSection("user");

    if (userSection != nullptr)
    {
        std::cout << "section name: " << userSection->name << std::endl;
        std::cout << "email=" << configParser.getValue("user",
        "email") << '\n';
    }
}
