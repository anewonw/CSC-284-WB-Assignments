#pragma once

#include <iostream>
#include <memory>

class Document
{
public:
	Document(const std::string&, const std::string&);
	~Document();
	void edit(const std::string&);
	void show();

private:
	std::string title;
	std::unique_ptr<std::string> content;
};