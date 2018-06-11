#include "parse.hpp"
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
    //assert(!d.HasParseError());
    //assert(!d.HasMember("type"));
    int tp = d["type"].GetInt();
    switch (tp) {
        case 0:
            return Ac (d["room"].GetString(), tp, d["switch"].GetInt(),d["temperature"].GetDouble(), d["wind"].GetInt(), (double)0.0);
            break;
        case 1:
            return Ac("", tp, -1, d["temperature"].GetDouble(), -1,0.0);
        default:
            return Ac();
    }
}

const string parser::parse(Ac st)
{
    string send ;

    send = std::string("{\"switch\":") + to_string(st.s) +
    std::string(",\"temperature\":") + to_string(st.tem) +
    std::string(",\"wind\":") + to_string(st.wind) +
    std::string(",\"cost\":") + to_string(st.cost) +
    std::string("}");
    return send;
}


