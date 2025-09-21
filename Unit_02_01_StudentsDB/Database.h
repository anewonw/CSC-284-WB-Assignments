#pragma once

#include "Student.h"
#include "Major.h"
#include <string>
#include <string_view>
#include <vector>

namespace StudentRecords
{
	class Database
	{
	public:
		Student& addStudent(const int id, std::string_view name, const int age,
			std::string_view major, std::string_view email);
		Student& findID(int id);
		Student& findName(std::string_view name);
		Major& findMajor(string_view query);

		void printAllRecords();

	private:
		std::vector<Student> m_students;
		std::vector<Major> m_majors;
	};
}
