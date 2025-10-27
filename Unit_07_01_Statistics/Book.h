#pragma once
#include <string_view>
#include <string>

class Book
{
public:
	Book(std::string_view title, std::string_view author, std::string_view genre,
		int year);

	void showBookInfo() const;
	std::string_view getTitle() const;
	std::string_view getAuthor() const;
	std::string_view getGenre() const;
	int getYear() const;

private:
	std::string m_title;
	std::string m_author;
	std::string m_genre;
	int m_year;
};