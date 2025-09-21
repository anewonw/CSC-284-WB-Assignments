#include "Database.h"
#include <stdexcept>

using namespace std;

namespace StudentRecords {

	// Create new Student object and add to m_students vector
	Student& Database::addStudent(const int id, std::string_view name, const int age,
		std::string_view major, std::string_view email)
	{
		// Use existing major or create new one
		Student newStudent{ id, name, age, findMajor(major), email };

		m_students.push_back(newStudent);

		return m_students.back();
	}

	Student& Database::findID(int id)
	{
		for (auto& student : m_students) {
			if (student.getID() == id) {
				return student;
			}
		}
		throw logic_error{ "No record found." };
	}

	Student& Database::findName(string_view name)
	{
		for (auto& student : m_students) {
			if (student.getName() == name) {
				return student;
			}
		}
		throw logic_error{ "No record found." };
	}

	void Database::printAllRecords()
	{
	}

	Major& Database::findMajor(string_view query)
	{
		for (auto& major : m_majors) {
			if (query == major.getMajorName()) {
				major.addStudentToMajor();
				return major;
			}
			m_majors.push_back(Major(query));
			return m_majors.back();
		}
	}
}
