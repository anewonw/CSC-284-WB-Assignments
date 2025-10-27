#include "Library.h"
#include "Book.h"
#include <ranges>
#include <vector>
#include <string>
#include <print>
#include <algorithm>
#include <iterator>
#include <functional>
#include <format>

// Add book to library
void Library::add_book(const Book& book)
{
	m_books.push_back(book);
}

// Find and remove book with remove_if() and erase()
void Library::remove_book(const std::string& title)
{
	auto target{ std::remove_if(begin(m_books), end(m_books),
		[&](const Book& book) {return book.getTitle() == title; }) };

	if (target == end(m_books))
		std::println("\"{}\" not found.", title);
	else {
		std::println("{} removed from library.", title);
		m_books.erase(target, end(m_books));
	}
}


// Find matching title with find_if()
std::vector<Book>::iterator Library::find_book(const std::string& title)
{
	// Traverse vector with iterator, compare titles with lambda expression
	auto it{ std::find_if(begin(m_books), end(m_books),
	[&](const Book& book) { return book.getTitle() == title; }) };

	if (it == end(m_books))
		std::println("\"{}\" not found.", title);
	else
	{
		std::print("Book found: ");
		it->showBookInfo();
	}

	return it;
}

// Return vector of pointers to books by author
// I did it this way in an effort to match the "Implement an iterator-based 
// search function to find books by author" criteria rather than with a filter
std::vector<Book*> Library::get_books_by_author(const std::string& author)
{
	std::vector<Book*> results;
	for (auto it{ begin(m_books) }; it != end(m_books); ++it) {
		if (it->getAuthor() == author)
			results.push_back(&*it);
	}
	return results;
}

// Use iterator to traverse library and display info for all books
void Library::show_all_books() const
{
	for (auto it{ begin(m_books) }; it != end(m_books); ++it) {
		it->showBookInfo();
	}
}

// Sort library by year
void Library::sort_by_year()
{
	std::ranges::sort(m_books, {}, [](const Book& book) { return book.getYear(); });
}

void Library::sort_by_year_descending()
{
	std::ranges::sort(m_books, std::greater{}, [](const Book& book) { return book.getYear(); });
}

// Filter, sort, and display (Some code reuse to demonstrate pipeline.
// Was not sure how to use transform here).
void Library::filter_by_genre_and_sort_by_year(const std::string& genre)
{
	// Get filtered view and convert to victor
	auto filtered{ get_books_by_genre(genre) | std::ranges::to<std::vector>() };

	// Sort filtered vector
	std::ranges::sort(filtered, {}, &Book::getYear);

	// Transform elements to formatted strings and display
	auto display{ filtered
		| std::views::transform([](const Book& book)
		{return std::format("{} by {} ({}) [{}]", book.getTitle(), book.getAuthor(), book.getYear(), book.getGenre()); }) };

	for (const auto& book : display)
		std::println("{}", book);
}

