#pragma once

#include <vector>
#include <string>
#include <string_view>


// Class to keep track of majors and number of students in each
namespace StudentRecords
{
	class Major
	{
	public:
		Major(std::string_view name);

		void addStudentToMajor();
		const std::string& getMajorName() const;
		int getNumStudents() const;

	private:
		std::string m_majorName;
		int m_numStudents{ 1 };
	};
}