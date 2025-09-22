#include "Student.h"

using namespace std;

namespace StudentRecords
{
	Student::Student(int id, string_view name, int age,
		string_view major, string_view email)
		: m_id{ id }
		, m_name{ name }
		, m_age{ age }
		, m_major{ major }
		, m_email{ email }
	{
	}

	void Student::setName(string_view name)
	{
		m_name = name;
	}
	const string& Student::getName() const
	{
		return m_name;
	}

	const string& Student::getMajor() const
	{
		return m_major;
	}
	void Student::setEmail(string_view email)
	{
		m_email = email;
	}
	const string& Student::getEmail() const
	{
		return m_email;
	}
	void Student::setAge(const int age)
	{
		m_age = age;
	}
	int Student::getAge() const
	{
		return m_age;
	}
	
	void Student::setID(const int id)
	{
		m_id = id;
	}
	int Student::getID() const
	{
		return m_id;
	}
}