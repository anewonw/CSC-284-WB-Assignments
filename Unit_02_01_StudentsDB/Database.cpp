#include "Database.h"
#include <stdexcept>

using namespace std;

namespace StudentRecords {

	// Create new Student object and add to m_students vector
	Student& Database::addStudent(int id, string_view name, int age,
		string_view major, string_view email)
	{
		findMajor(major);
		Student newStudent{ id, name, age, major, email };
		m_students.push_back(newStudent);

		return m_students.back();
	}

	void Database::findID(int id)
	{
		for (auto& student : m_students) {
			if (student.getID() == id) {
				println("\nStudent record found : ");
				printRecord(student);
				return;
			}
		}
		throw logic_error{ "Error - No record found." };
	}

	void Database::findName(string_view name)
	{
		for (auto& student : m_students) {
			if (student.getName() == name) {
				println("\nStudent record found : ");
				printRecord(student);
				return;
			}
		}
		throw logic_error{ "Error - No record found." };
	}
	void Database::printRecord(Student& student) const
	{
		println("\n{:<10}{:<30}{:<10}{:<15}{}", "ID", "Name", "Age", "Major", "Email");
		println("{}", string(80, '-'));
		println("{:<10}{:<30}{:<10}{:<15}{}",
			student.getID(), student.getName(), student.getAge(), student.getMajor(), student.getEmail());
	}

	void Database::printAllRecords() const
	{
		println("\n{:<10}{:<30}{:<10}{:<15}{}", "ID", "Name", "Age", "Major", "Email");
		println("{}", string(80, '-'));
		for (auto& student : m_students) {
			println("{:<10}{:30}{:<10}{:<15}{}",
				student.getID(), student.getName(), student.getAge(), student.getMajor(), student.getEmail());
		}
	}

	void Database::printStudentsByMajor() const
	{
		println("\nStudents by Major: ");
		for (auto& major : m_majors)
			println("{}: {}", major.getMajorName(), major.getNumStudents());
	}

	// Update existing major or create new one
	void Database::findMajor(string_view query)
	{
		for (Major& major : m_majors) {
			if (query == major.getMajorName()) {
				major.addStudentToMajor();
				return;
			}
		}
		m_majors.push_back(query);
	}
}

