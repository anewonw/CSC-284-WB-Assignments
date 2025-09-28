// CSC 284
// Unit 3 Assignment 2: Document Management
// Andrew Dasch

#include <iostream>
#include <memory>

using namespace std;

class Document
{
public:
	// Constructor with message
	Document(const string& newTitle, const string& newContent)
		: title(newTitle)
		, content(make_unique<string>(newContent))
	{
		cout << "Document \"" << title << "\" created.\n";
	}

	// Destructor with message
	~Document()
	{
		cout << "Document \"" << title << "\" destroyed.\n";
	}

	// Edit content
	void edit(const string& edit)
	{
		*content = edit;
	}

	// Show title and content
	void show()
	{
		cout << "Title: " << title
			<< "\nContent: " << *content << endl;
	}

private:
	string title;
	unique_ptr<string> content;
};

unique_ptr<Document> createDocument(const string&, const string&);
shared_ptr<Document> createSharedDocument(const string&, const string&);

int main() {
    cout << "=== Unique_ptr demonstration ===\n";
    unique_ptr<Document> doc1 = createDocument("My Unique Doc", "Initial content");
    doc1->show();

    // Transfer ownership
    unique_ptr<Document> doc2 = move(doc1);
    if (!doc1) {
        cout << "doc1 no longer owns the document\n";
    }
    doc2->edit("Updated content");
    doc2->show();

    cout << "\n=== Shared_ptr demonstration ===\n";
    shared_ptr<Document> sharedDoc = createSharedDocument("Shared Doc", "Shared content");
    {
        shared_ptr<Document> viewer = sharedDoc;  // second owner
        viewer->show();
        viewer->edit("Edited by viewer");
    } // viewer goes out of scope, document still exists

    sharedDoc->show();
    cout << "End of main()\n";

    return 0;
}

// Return smart pointers to Documents
unique_ptr<Document> createDocument(const string& title, const string& content) {
    return make_unique<Document>(title, content);

}
shared_ptr<Document> createSharedDocument(const string& title, const string& content) {
    return make_shared<Document>(title, content);
}
