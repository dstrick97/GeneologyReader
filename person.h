#ifndef PERSON_H
#define PERSON_H

#include<string>
#include <cctype>
using namespace std;

/*****************************************************************
 * PERSON CLASS
 * This class will hold the data neccessary to make up a person
 * including Surname, Given name, Birth date, and Index number
 *****************************************************************/

class Person
{
public:
	string surname;
	string name;
	string bdate;
	string famIndex;

	
	Person() : surname(" "), name(" "), bdate(""), famIndex(""){}

	//friend std::ostream& operator << (std::ostream& out, Person rhs);


	bool operator <= (Person const&rhs) const
	{
		int i = 0;
		string temp1 = surname;
		string temp2 = rhs.surname;

		temp1[0] = tolower(temp1[0]);
		temp2[0] = tolower(temp2[0]);

		if (temp1 == temp2)
		{
			if (name == rhs.name)
			{
				string year;
				int index = bdate.length() - 4;
				for (int i = 0; i < 4 && index < bdate.length(); i++, index++)
				{
					year += bdate[index];
				}

				string RHSyear;
				int RHSindex = rhs.bdate.length() - 4;
				for (int i = 0; i < 4 && RHSindex < rhs.bdate.length(); i++, RHSindex++)
				{
					RHSyear += rhs.bdate[RHSindex];
				}

				if (year <= RHSyear)
					return true;
				else
					return false;
			}
		}
		if (temp1 == temp2)
		{
			while (name[i] == rhs.name[i])
				i++;
			if (name[i] <= rhs.name[i])
				return true;
			else 
				return false;
		}
		
	
		
		while (temp1[i] == temp2[i])
			i++;
		if (temp1[i] <= temp2[i])
			return true;
		else
			return false;
	}

};

/*****************************************************************
 * OVERLOAD OPERATORS
 *****************************************************************/

std::ostream& operator << (std::ostream& out, Person rhs)
{
		
	if (rhs.famIndex == "@I1@")
	{
		out << rhs.name << " " << rhs.surname << ":\n";
	}	
	else
	{
		if (rhs.name != " ")
			out << rhs.name;
		if (rhs.name == " " && rhs.surname != " ")
			out << rhs.surname;
		else if (rhs.surname != " ")
			out << " " << rhs.surname;

		if (rhs.bdate != "")
			out << ", b. " << rhs.bdate;
		if(rhs.famIndex != "@I127@")
			out << endl;
		return out;
	}
}

#endif // PERSON_H