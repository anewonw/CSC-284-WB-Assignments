#pragma once

#include "Student.h"
#include "Major.h"
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <print>

namespace StudentRecords
{
	class Database
	{
	public:
		Student& addStudent(int id, std::string_view name, int age,
			std::string_view major, std::string_view email);
		void findID(int id);
		void findName(std::string_view name);

		void printRecord(Student& student) const;
		void printAllRecords() const;
		void printStudentsByMajor() const;

	private:
		void findMajor(std::string_view query);
		std::vector<Student> m_students;
		std::vector<Major> m_majors;
	};
}
