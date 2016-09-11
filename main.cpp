#include <fstream>
#include "mdtransform.hpp"

using std::ofstream;
using std::string;

int main(int argc, char const *argv[]) {
	//load md file
	MDConvert transformer("test.md");

	string table = transformer.getTableOfContents();
	string content = transformer.getContents();

	//ready for HTML head
	string head =
		"<!DOCTYPE html>\
		<html>\
		<head>\
			<meta charset=\"utf-8\">\
			<title>HTML of test.md</title>\
			<link rel=\"stylesheet\" href=\"github-markdown.css\">\
			</head>\
		<body>\
		<article class=\"markdown-body\">\
		";
	
	string end = "</article></body></html>";

	ofstream out;
	out.open("output/index.html");
	out << head + table + content + end;
	out.close();
	return 0;
}