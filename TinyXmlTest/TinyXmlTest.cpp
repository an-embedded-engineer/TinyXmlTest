#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <vector>
#include <cstdlib>
#include <sstream>

#include "tinyxml2.h"

namespace xml = tinyxml2;


struct XmlData
{
    int int_value;
    double double_value;
    std::string string_value;
    std::vector<int> int_array;

    XmlData()
        : int_value(0)
        , double_value(NAN)
        , string_value()
        , int_array()
    {
    }
};

int main()
{
    std::cout << "Hello World!\n";

    auto file_name = "test.xml";

    std::ifstream ifs(file_name);

    if (ifs.fail())
    {
        std::cerr << "Cannot open : " << file_name << std::endl;

        return -1;
    }

    std::string xml_data((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    std::cout << "[Input XML]" << std::endl;
    std::cout << xml_data << std::endl;

    xml::XMLDocument xml;

    xml.Parse(xml_data.c_str());
    //xml.LoadFile(file_name);

    XmlData data;
    char* e = nullptr;

    auto node_root = xml.FirstChildElement("root");

    auto node_int_value = node_root->FirstChildElement("int_value");
    data.int_value = (int)std::strtol(node_int_value->GetText(), &e, 10);

    auto node_double_value = node_root->FirstChildElement("double_value");
    data.double_value = std::strtod(node_double_value->GetText(), &e);

    auto node_string_value = node_root->FirstChildElement("string_value");
    data.string_value = std::string(node_string_value->GetText());

    auto node_int_array = node_root->FirstChildElement("int_array");
    for (auto node_item = node_int_array->FirstChildElement("item"); node_item != nullptr; node_item = node_item->NextSiblingElement("item"))
    {
        int item_value = (int)std::strtol(node_item->GetText(), &e, 10);

        data.int_array.push_back(item_value);
    }

    std::cout << std::endl;

    std::cout << "[Decoded Data]" << std::endl;
    std::cout << "int_value : " << data.int_value << std::endl;
    std::cout << "double_value : " << data.double_value << std::endl;
    std::cout << "string_value : " << data.string_value << std::endl;
    std::cout << "int_array : " << std::endl;
    for (auto&& item : data.int_array)
    {
        std::cout << "  item : " << item << std::endl;
    }
}
