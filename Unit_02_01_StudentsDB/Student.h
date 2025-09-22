#pragma once

#include "Major.h"
#include <string>
#include <string_view>

namespace StudentRecords
{
	class Student
	{
	public:
		Student(int id, std::string_view name, int age,
			std::string_view major, std::string_view email);

		void setName(std::string_view name);
		const std::string& getName() const;

		// setMajor not implemented
		const std::string& getMajor() const;

		void setEmail(std::string_view email);
		const std::string& getEmail() const;

		void setAge(const int age);
		int getAge() const;

		void setID(const int id);
		int getID()const;

	private:
		int m_id;
		int m_age;
		std::string m_name;
		std::string m_major;
		std::string m_email;
	};
}