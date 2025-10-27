// CSC 284
// Unit 7 Assignment 1: Library Management System
// Andrew Dasch

#include "Book.h"
#include "Library.h"
#include <print>

using namespace std;

int main() {
	Library library{};

	// Add books (Move semantics not implemented)
	library.add_book({ "The Hobbit", "J.R.R. Tolkien", "Fantasy", 1937 });
	library.add_book({ "1984", "George Orwell", "Dystopian Fiction", 1949 });
	library.add_book({ "To Kill a Mockingbird", "Harper Lee", "Fiction", 1960 });
	library.add_book({ "The Great Gatsby", "F. Scott Fitzgerald", "Classic Fiction", 1925 });
	library.add_book({ "Pride and Prejudice", "Jane Austen", "Romance", 1813 });
	library.add_book({ "Harry Potter and the Sorcerer's Stone", "J.K. Rowling", "Young Adult", 1997 });
	library.add_book({ "Charlotte's Web", "E.B. White", "Children's", 1952 });
	library.add_book({ "A Brief History of Time", "Stephen Hawking", "Science", 1988 });
	library.add_book({ "The Diary of a Young Girl", "Anne Frank", "Biography", 1947 });
	library.add_book({ "Sapiens: A Brief History of Humankind", "Yuval Noah Harari", "History", 2011 });
	library.add_book({ "Matilda", "Roald Dahl", "Children's", 1988 });
	library.add_book({ "The Lightning Thief", "Rick Riordan", "Young Adult", 2005 });
	library.add_book({ "The Fellowship of the Ring", "J.R.R. Tolkien", "Fantasy", 1954 });
	library.add_book({ "The Two Towers", "J.R.R. Tolkien", "Fantasy", 1954 });
	library.add_book({ "The Return of the King", "J.R.R. Tolkien", "Fantasy", 1955 });
	library.add_book({ "Becoming", "Michelle Obama", "Biography", 2018 });
	library.add_book({ "The Immortal Life of Henrietta Lacks", "Rebecca Skloot", "Science", 2010 });
	library.add_book({ "The Wright Brothers", "David McCullough", "History", 2015 });
	library.add_book({ "Goodnight Moon", "Margaret Wise Brown", "Children's", 1947 });
	library.add_book({ "The Fault in Our Stars", "John Green", "Young Adult", 2012 });
	library.add_book({ "Educated", "Tara Westover", "Memoir", 2018 });

	// Display all books
	library.show_all_books();

	// Find
	println();
	library.find_book("1984");
	library.find_book("Charlotte's Web");
	library.find_book("50 Shades of Gray");

	// Remove
	println();
	library.remove_book("Harry Potter and the Sorcerer's Stone");
	library.remove_book("1984");
	library.remove_book("Fourth Wing");

	// Find by author
	println();
	auto tolkienBooks{ library.get_books_by_author("J.R.R. Tolkien") };
	println("Books by J.R.R. Tolkien:");
	for (auto& book : tolkienBooks)
		book->showBookInfo();

	// Filter by genre
	println("\nScience books:");
	for (auto& book : library.get_books_by_genre("Science"))
		book.showBookInfo();

	println("\nChildren's books:");
	for (auto& book : library.get_books_by_genre("Children's"))
		book.showBookInfo();

	// Filter by year
	println("\nBooks written after 1990:");
	for (auto& book : library.get_books_written_after_year(1990))
		book.showBookInfo();

	// Sort by year
	println("\nBooks by year (ascending):");
	library.sort_by_year();
	library.show_all_books();

	println("\nBooks by year (descending):");
	library.sort_by_year_descending();
	library.show_all_books();

	// Filter by genre and sort by year
	println("\nYA books by year (ascending):");
	library.filter_by_genre_and_sort_by_year("Young Adult");
}
