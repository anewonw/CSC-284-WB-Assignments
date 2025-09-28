#include "Document.h"

using namespace std;

// Constructor with message
Document::Document(const string& newTitle, const string& newContent)
	: title(newTitle)
	, content(make_unique<string>(newContent))
{
	cout << "Document \"" << title << "\" created.\n";
}

// Destructor with message
Document::~Document()
{
	cout << "Document \"" << title << "\" destroyed.\n";
}

// Edit content
void Document::edit(const std::string& edit)
{
	*content = edit;
}

// Show title and content
void Document::show()
{
	cout << "Title: " << title
		<< "\nContent: " << *content << endl;
}
