#pragma once

#include "Major.h"
#include <string>
#include <string_view>

namespace StudentRecords
{
	class Student
	{
	public:
		Student(const int id, std::string_view name, const int age,
			Major& major, std::string_view email);

		void setName(std::string_view name);
		const std::string& getName() const;

		//void setMajor(Major& major);
		//Major& getMajor() const;

		//void setEmail(std::string_view email);
		//const std::string& getEmail() const;

		//void setAge(const int age);
		//int getAge() const;

		void setID(const int id);
		int getID()const;

	private:
		int m_id;
		int m_age;
		std::string m_name;
		Major& m_major;
		std::string m_email;
	};
}