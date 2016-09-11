// this header file is programmed with C++11 standard

#pragma once
#include <vector>
#include <string>

using std::vector;
using std::pair;
using std::make_pair;
using std::string;

enum tag_type {
    para
};

/*Markdown syntax reference (from MD's author website):
 * https://daringfireball.net/projects/markdown/syntax
 */

// Use tree to save structures of Contents and body
struct content_node {
    string heading;
    string target;
    int depth;
    vector<content_node *> contents;

    content_node(string& heading, int depth) : heading(heading), depth(depth) {}

    content_node() : heading(""), target(""), depth(0) {}
};

struct body_node {
    tag_type type;
    string info[3]; // saves displayed content, link, and title
    vector<body_node *> body;

    body_node(tag_type type) : type(type) {}
};

class MDConvert
{
public:
    MDConvert();
    ~MDConvert();

private:
    content_node cnode;
    body_node bnode;
    pair<int, string> space_in_line(const string& line);
    string replace_special_chars(const string& line);
    pair<int, string> header(const string& line);
};

MDConvert::MDConvert() : bnode(para) {
    string s = "";
    cnode = content_node(s, 0);
}

MDConvert::~MDConvert()
{
}

// heading spaces (including tab and ' ') does nothing in MD, so parse them first
// count spaces in a line
// return pair by number of spaces and string without spaces
pair<int, string> MDConvert::space_in_line(const string& line) {
    if (!line.size()) {
        return make_pair(0, string());
    }

    int count_space = 0;
    for (char c : line) {
        if (c == '\t' || c == ' ') {
            ++count_space;
            continue;
        }
        return make_pair(count_space, &c);
    }
    return make_pair(0, string());
}


// handle special chars ('<' and '&' in HTML)
inline string MDConvert::replace_special_chars(const string& line) {
    string string_to_export;
    for (char c : line) {
        switch (c) {
        case '<':
            string_to_export.append("&lt;");
            break;
        case '&':
            string_to_export.append("&amp;");
            break;
        default:
            string_to_export.push_back(c);
        }
    }

    return string_to_export;
}

// TODO: support Setext underlined headers

// handle '#'s
/*
 * input address of a line
 * return a pair of the number of '#' and corresponding title. */
inline pair<int, string> MDConvert::header(const string& line)
{
    int count = 0;
    for (char c : line)
    {
        switch (c)
        {
        case '#':
            ++count;
            break;
        case ' ':
        case '\t':
            break;
        default:
            return make_pair(count, &c);
        }
    }

    return make_pair(0, string());
}

