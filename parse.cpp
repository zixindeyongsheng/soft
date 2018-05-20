#include "parse.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <string>
#include <iostream>
using namespace rapidjson;

Ac parser::parse(const char* data)
{
    Document d;
    d.Parse(data);
    std::cout << d["type"].GetInt() << std::endl;
    int tp = d["type"].GetInt();
    switch (tp) {
        case 0:
            return Ac(d["room"].GetString(), tp, d["switch"].GetInt(),
                      d["temperature"].GetDouble(), d["wind"].GetInt());
            break;
        case 1:
            return Ac("", tp, -1, -1.1, -1);
        default:
            return Ac();
    }
}

const char * parser::parse(Ac st)
{
    string send ;

    send = std::string("{\"switch\":") + to_string(st.s) +
    std::string(",\"temperature\":") + to_string(st.tem) +
    std::string(",\"wind\":") + to_string(st.wind) +
    std::string(",\"cost\":") + to_string(st.cost) +
    std::string("}");
    return send.c_str();
}


