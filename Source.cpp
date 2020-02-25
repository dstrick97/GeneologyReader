/***********************************************************************
* Program:
*    Week 13, Geneology
*    Brother Ercanbrak, CS 235
* Author:
*    Daniel Strickland
* Summary:
*    This program will organize a geneological file. A file will be read
*    in, its contents sorted into alphabetical order, and put into a 
*    separate file. Then the generations will be displayed to the user
************************************************************************/

#include <iostream>          // for CIN and COUT
#include <string>		    //  for strings		
#include <fstream>	       //   for reading files
#include "bnode.h"	      //    for binary nodes
#include "list.h"	     //     for likned list
#include "bst.h"	    //      for binary search tree
#include "stack.h"     //       for stack within bst
#include "person.h"   //		for person class
#include <sstream>   //         for string stream
#include <cstring>  //          for strcmp

using namespace std;

int main(int argc, const char* argv[])
{
	List<BinaryNode<Person> > people;
	char filename[50];
	if (argc == 1)
	{
		cout << "Enter name of file to sort: ";
		cin >> filename;
	}

	else
	{
		strcpy_s(filename, argv[2]);
	}

	ifstream fin(filename);
	if (fin.fail())
	{
		cout << "ERROR: could not read file";
		return 0;
	}
	else
	{
		// if file could not be read, say so and exit.
		// otherwise build list.
		string linefromfile;
		int i = 0;

		while (getline(fin, linefromfile))
		{
			stringstream parser(linefromfile);
			int code;
			string datatype;
			string content;
			string index;
			Person individual = Person();
			if (linefromfile[0] == '0')
			{
				parser >> code >> index >> datatype;
				if (code == 0 && index == "@S1@")
					break;
				if (datatype == "INDI")
				{
					individual.famIndex = index;
					getline(fin, linefromfile);
					parser.clear();					//neccessary to update datetype and code
					parser.str(linefromfile);
					
					parser >> code >> datatype;

					
					while (code >= 1)
						{
						if (datatype == "NAME")
						{
							while (getline(fin, linefromfile))
							{
								parser.clear();
								parser.str(linefromfile);
								parser >> code >> datatype;
								if (code == 2)
								{
									if (datatype == "GIVN")
									{
										parser.ignore(1);
										getline(parser, content);
										individual.name = content;
									}
									else if (datatype == "SURN")
									{
										parser.ignore(1);
										getline(parser, content);
										individual.surname = content;
									}
								}

								else if (code != 2)
									break;
							}

						}
						else if (datatype == "BIRT")
						{
							getline(fin, linefromfile);
							parser.clear();
							parser.str(linefromfile);
							parser >> code >> datatype;
							if (datatype == "DATE")
							{
								parser.ignore(1);
								getline(parser, content);
								individual.bdate = content;
								people.push_back(individual);
								break;
							}
						}

						else
						{
							getline(fin, linefromfile);
							parser.clear();
							parser.str(linefromfile);
							parser >> code >> datatype;
							if (datatype == "FAMS")
							{
								people.push_back(individual);
								break;
							}
						}
					}
				}
				else if (datatype == "FAM")
				{
					string husb = " ";
					string wife = " ";
					string child = " ";

					
					
					while (datatype != "HUSB")
					{
						getline(fin, linefromfile);
						parser.clear();
						parser.str(linefromfile);
						parser >> code >> datatype >> index;
					}
					
					for (int i = 0; i < 2; i++)
					{
						if (datatype == "HUSB")
							husb = index;
						
						else if (datatype == "WIFE")
						{
							wife = index;
							i++;
						}
						else if (datatype == "CHIL")
						{
							child = index;
							break;
						}
						
						getline(fin, linefromfile);
						parser.clear();
						parser.str(linefromfile);
						parser >> code >> datatype >> index;

							
						if (datatype == "WIFE")
							wife = index;
						else if (datatype == "CHIL")
							child = index;
					}
					
						
					
					ListIterator<BinaryNode<Person> > itc = people.begin();
					while (itc.node->data.data.famIndex != child && itc != people.end()) //child it
						++itc;
					
					ListIterator<BinaryNode<Person> > ith = people.begin();	// husband it
					if (husb != " ")
					{
						while (ith.node->data.data.famIndex != husb && ith != people.end())
							++ith;
					}

					ListIterator<BinaryNode<Person> > itw = people.begin();	//wife it
					if (wife != " ")
					{
						while (itw.node->data.data.famIndex != wife && itw != people.end())
							++itw;
					}

					if(husb != " ")
						itc.node->data.pLeft = &ith.node->data;	//cLeft = husband
					
					if(wife != " ")
						itc.node->data.pRight = &itw.node->data; //cRight = wife
				}





			}
		}

		ListIterator<BinaryNode<Person> > it = people.begin();
		BST<Person> sorted;
		while (it != people.end())
		{
			sorted.insert(it.node->data.data);
			++it;
		}

		ofstream fout("sorted.dat");
		
		
		BSTIterator<Person> bstit = sorted.begin();
		for (int i = 0; i < sorted.size(); i++)
		{
			if ((*bstit).name != " ")
				fout << (*bstit).name;
			if ((*bstit).name == " " && (*bstit).surname != " ")
				fout << (*bstit).surname;
			else if ((*bstit).surname != " ")			
				fout << " " << (*bstit).surname;

			if ((*bstit).bdate != "")
				fout << ", b. " << (*bstit).bdate;
			fout << endl;
			++bstit;
		}

		cout << "The Ancestors of ";
		people.head->data.level();
		cout << endl;



	}
	
}