#include"Journal.h"

using namespace std;

void Journal::Pause()
{
    m_out.close();
}

void Journal::Continue()
{
    m_out.open(m_path);
}

void Journal::AddRow(const std::string& name)
{
    if (m_nameMapping.count(name))return;

    m_names.push_back(name);
    uint64_t size = m_names.size();
    m_values.resize(size);
    m_nameMapping[name] = size - 1;
}

void Journal::PrintHeader()
{
    string buf = "";
    for (auto& item : m_names)buf += item + ",";
    buf.back() = '\n';
    m_out << buf;

#ifdef ENABLE_TRACE
    cout << "PrintfHeader: buf = \"" << buf << "\"\n";
#endif
}

Journal::Journal() {}

Journal::~Journal()
{
    m_out.close();
}

Journal& Journal::Path(const std::string& path)
{
    m_path = path;
    // TODO: вставьте здесь оператор return
    return *this;
}

Journal& Journal::Start(const std::vector<std::string>& rows)
{
    m_out.open(m_path);
    if (!m_out.is_open())
    {
        std::cout << "ERROR! JORNAL IS NOT OPEN!" << std::endl;
        return *this;
    }

    m_recordCounter = 0;
    AddRow("ID");
    for (auto& row : rows) AddRow(row);

    PrintHeader();

#ifdef ENABLE_TRACE
    cout << "Journal started at <<" << m_path << "\n";
    for (auto& item : m_nameMapping)cout << item.first, cout << ", " << item.second << endl;
    printf("m_values.size() = %d\n", m_values.size());
#endif

    m_started = true;

    // TODO: вставьте здесь оператор return
    return *this;
}

Journal& Journal::Set(const std::string& row, const std::string& value)
{
    if (!m_started)return *this;
    if (!m_nameMapping.count(row))return *this;
    // TODO: вставьте здесь оператор return
    return Set(m_nameMapping[row], value);
}

Journal& Journal::Set(const uint64_t& row, const std::string& value)
{
#ifdef ENABLE_TRACE
    cout << "Set by id:" << "row<" << row << "> value <" << value << ">\n";
#endif

    if (!m_started)return *this;
    if (row < 0)return *this;
    if (row >= m_values.size())return *this;

    m_values[row] = value;

    // TODO: вставьте здесь оператор return
    return *this;
}

Journal& Journal::Print()
{
    if (!m_started)return *this;

    Set(0, to_string(m_recordCounter));
    m_recordCounter++;

    string outbuf;
    for (auto& item : m_values)outbuf += item + ",";
    outbuf.back() = '\n';
    m_out << outbuf;

    for (auto& item : m_values)item = "";

#ifdef ENABLE_TRACE
    cout << outbuf;
#endif

    // TODO: вставьте здесь оператор return
    return *this;
}

Journal& Journal::End()
{
    m_out.close();
    m_values.clear();
    m_nameMapping.clear();
    // TODO: вставьте здесь оператор return
    return *this;
}
