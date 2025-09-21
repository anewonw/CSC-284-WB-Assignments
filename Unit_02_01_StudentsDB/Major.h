#pragma once

#pragma once

#include "Student.h"
#include "Database.h"
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
		const std::string getMajorName();

	private:
		const std::string m_majorName;
		int m_numStudents{ 1 };
	};
}