#pragma once
#include "Major.h"

using namespace std;

namespace StudentRecords
{
	Major::Major(string_view name)
		: m_majorName{ name }
	{}
	void Major::Major::addStudentToMajor()
	{
		m_numStudents++;
	}
	const string Major::Major::getMajorName()
	{
		return m_majorName;
	}
}