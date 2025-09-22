#include "Major.h"

using namespace std;

namespace StudentRecords
{
	Major::Major(string_view name)
		: m_majorName{ name }
	{}
	void Major::addStudentToMajor()
	{
		m_numStudents++;
	}
	int Major::getNumStudents() const
	{
		return m_numStudents;
	}
	const string& Major::getMajorName() const
	{
		return m_majorName;
	}
}