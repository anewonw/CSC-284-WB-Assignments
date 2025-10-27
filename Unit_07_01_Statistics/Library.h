#pragma once
#include "Book.h"
#include <vector>
#include <string>
#include <ranges>

class Library
{
public:
	Library() = default;

	void add_book(const Book& book);
	void remove_book(const std::string& title);
	std::vector<Book>::iterator find_book(const std::string& title);
	std::vector<Book*> get_books_by_author(const std::string& author);
	void show_all_books() const;
	void sort_by_year();
	void sort_by_year_descending();

	// Return view of books filtered by genre with auto
	auto get_books_by_genre(const std::string& genre)
	{
		auto filter{ m_books
			| std::views::filter([&](const Book& book) { return book.getGenre() == genre; }) };

		return filter;
	}

	// Return view of books written after given year with auto
	auto get_books_written_after_year(int year)
	{
		auto filter{ m_books
			| std::views::filter([&](const Book& book) { return book.getYear() > year; }) };

		return filter;
	}

	// Use pipeline of operations to filter, sort, and display books             
	void filter_by_genre_and_sort_by_year(const std::string& genre);

private:
	std::vector<Book> m_books;
};