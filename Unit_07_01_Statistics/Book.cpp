#include "Book.h"
#include <print>
#include <string_view>

// Constructor
Book::Book(std::string_view title, std::string_view author, std::string_view genre, int year)
	: m_title{ title }
	, m_author{ author }
	, m_genre{ genre }
	, m_year{ year }
{
}

// Print book info
void Book::showBookInfo() const
{
	std::println("{} by {} ({}) [{}]", m_title, m_author, m_year, m_genre);
}

// Accessors
std::string_view Book::getTitle() const
{
	return m_title;
}

std::string_view Book::getAuthor() const
{
	return m_author;
}

std::string_view Book::getGenre() const
{
	return m_genre;
}

int Book::getYear() const
{
	return m_year;
}
