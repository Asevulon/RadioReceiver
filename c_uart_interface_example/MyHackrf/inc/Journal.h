#include<fstream>
#include <cstdint>
#include<vector>
#include<map>
#include<iostream>


class Journal
{
private:
    std::ofstream m_out;

    std::string m_path{};
    bool m_started = false;

    uint64_t m_recordCounter = 0;

    std::map<std::string, uint64_t>m_nameMapping;
    std::vector<std::string> m_values;
    std::vector<std::string>m_names;

protected:
    void AddRow(const std::string& name);
    void PrintHeader();
public:
    Journal();
    ~Journal();

    Journal& Path(const std::string& path);
    Journal& Start(const std::vector<std::string>& rows);
    Journal& Set(const std::string& row, const std::string& value);
    Journal& Set(const uint64_t& row, const std::string& value);
    Journal& Print();
    Journal& End();
};


