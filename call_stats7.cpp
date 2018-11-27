/*
Vy Tran
Lofton Bullard
11/20/16
Description: 
Description: This program implements dynamic arrays that the user has to manually change the size/capacity of the arrays instead of the
compiler. This program is an extension to previous programs reading from a file, processing, and outputting it to a screen.
Using functions that are then called in main. It also includes an introduction to classes. It also introduces friend and operator overloading.

*/

#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>

using namespace std;


class call_record
{
public:
	string firstname;
	string lastname;
	string cell_number;
	int relays;
	int call_length;
	double net_cost;
	double tax_rate;
	double call_tax;
	double total_cost;
};

class call_class
{
public:
	call_class();
	~call_class(); //de-allocates all memory allocate to call_DB by operator new.
	bool is_empty(); //inline implementation
	bool is_full();//inline implementation
	int search(const string key);//returns location if item in listl; otherwise return -1
	void add(); //adds a call record to call_DB
	call_class & operator-(const string key); //removes an item from the list
	void double_size();
	void process();
	friend ostream & operator<<(ostream & out_to_file, call_class & Org); //prints all the elements in the 
																		  //list to the screen.
private:
	int count;
	int size;
	call_record *call_DB;
};




/************************************************************************************************************************************/
//Name: default constructor
//Precondition: the functions for the class call_class has been declared
//Postcondition: default constructor has been called
//Decription: Reads the data file of call information (cell number, relays and call length) into the dynamic array of call record, 
//call_DB. If the count because equal to the size the function double_size is called and the memory allocated to call_DB is doubled.
/************************************************************************************************************************************/
call_class::call_class()
{

	ifstream in;
	in.open("callstats_data.txt");
	count = 0;
	size = 5;
	call_DB = new call_record[size];

	if (in.fail())
	{
		cout << "File does not exist" << endl;
	}
	else
	{
		while (!in.eof())
		{
			if (count == size)
			{
				double_size();
			}
			in >> call_DB[count].firstname;
			in >> call_DB[count].lastname;
			in >> call_DB[count].cell_number;
			in >> call_DB[count].relays;
			in >> call_DB[count].call_length;
			count++;
		}
		in.close();
	}

}

/***********************************************************************************************************************************/
//Name: is_empty
//Precondition:  count has been used and now contains a value based on the elements in the array
//Postcondition: Is_empty has been given its function to return true if count is equals to zero, meaning there is nothing in the 
//array and return false if it contains something
//Decription: returns true if call_DB is empty
/**********************************************************************************************************************************/
bool call_class::is_empty()
{
	return count == 0;
}

/**********************************************************************************************************************************/
//Name: is_full 
//Precondition:  count and size are both in use and contains a value based on the elements within the array
//Postcondition:  Is_full is now set to return true if count and size equals to each other, meaning they are full and it returns false
//if the count and size does not equal to each other meaning it is not full
//Decription: returns true if call_DB is full
/*********************************************************************************************************************************/
bool call_class::is_full()
{
	return count == size;
}

/**********************************************************************************************************************************/
//Name: search
//Precondition:key has been entered by the user which now contains a stirng of numbers
//Postcondition: search now evaluates to see if key is equal to a cell number that already exists in an array  
//Decription: locates key in call_DB if it is there; otherwise -1 is returned
/*********************************************************************************************************************************/
int call_class::search(const string key)
{
	for (int j = 0; j < count; j++)
	{
		if (key == call_DB[j].cell_number)
			return j;  //if you find the cell number that equals to key then return the location 
	}
	return -1;
}

/*********************************************************************************************************************************/
//Name: add
//Precondition: call_DB, count, size, and key all contains values/characters 
//Postcondition: it adds another record that contains firstname, lastname, cell number, relays, and call length into the array 
//Decription: adds the informaton for a call record to call_DB; if call_DB is full, double_size is called to increase the size of call_DB.
/********************************************************************************************************************************/
void call_class::add()
{
	if (is_full())
	{
		double_size();
	}
	//call_DB[count] = key;
	cout << endl << "Enter firstname ";
	cin >> call_DB[count].firstname;
	cout << endl << "Enter lastname ";
	cin >> call_DB[count].lastname;
	cout << endl << "Enter cell number ";
	cin >> call_DB[count].cell_number;
	cout << endl << "Enter relays ";
	cin >> call_DB[count].relays;
	cout << endl << "Enter call length ";
	cout << endl;
	cin >> call_DB[count].call_length;
	count++;
}

/********************************************************************************************************************************/
//Name: operator-
//Precondition:  Search has been given its function to search for values when it is not -1.
//Postcondition: operator- utilizes search to remove an element that has a duplicate copy inside the array
//Decription: remove key from call_DB if it is there.
/*******************************************************************************************************************************/
call_class & call_class::operator-(const string key)
{
	int loc = search(key);
	while (loc != -1)
	{
		for (int m = loc; m < count - 1; m++)
		{
			call_DB[m] = call_DB[m + 1]; //move up and replace
		}
		count--;
		loc = search(key);
	}
	return *this; //we are overloading with chaining so we must return the current object *this
}

/******************************************************************************************************************************/
//Name: double_size
//Precondition:call_DB, count, size all contains values/cahracters
//Postcondition: the array is doubled in size but is a new one that call_DB needs to point to, then call_DB needs to delete 
//its old files 
//Decription: doubles the size (capacity) of call_DB
/******************************************************************************************************************************/
void call_class::double_size()
{
	size *= 2;
	call_record *temp = new call_record[size];

	for (int i = 0; i<count; i++)
	{
		temp[i] = call_DB[i];
	}

	delete[] call_DB;
	call_DB = temp;
}


/******************************************************************************************************************************/
//Name: process
//Precondition:call_DB, count, and all of the elements within call_DB has been given values/characters
//Postcondition: the calculations for net cost, call tax, tax rate, and total cost has been done 
//Decription: calculate the net cost, tax rate, call tax and total cost for every call record in call_DB.
/*****************************************************************************************************************************/
void call_class::process()
{
	for (int l = 0; l < count; l++)
	{

		if (call_DB[l].relays >= 0 && call_DB[l].relays <= 5)
		{
			call_DB[l].tax_rate = 0.01;
		}
		else if (call_DB[l].relays >= 6 && call_DB[l].relays <= 11)
		{
			call_DB[l].tax_rate = 0.03;
		}
		else if (call_DB[l].relays >= 12 && call_DB[l].relays <= 20)
		{
			call_DB[l].tax_rate = 0.05;
		}
		else if (call_DB[l].relays >= 21 && call_DB[l].relays <= 50)
		{
			call_DB[l].tax_rate = 0.08;
		}
		else
		{
			call_DB[l].tax_rate = 0.12;
		}

		call_DB[l].net_cost = call_DB[l].relays / 50.0 * .40 *call_DB[l].call_length;
		call_DB[l].call_tax = call_DB[l].net_cost * call_DB[l].tax_rate;
		call_DB[l].total_cost = call_DB[l].net_cost + call_DB[l].call_tax;
	}
}


/****************************************************************************************************************************/
//Name: operator<<
//Precondition: call_DB, count, and the call_record of call_DB has been calculated/given its values/characters
//Postcondition: every element in the array is print to the screen and the file 
//Decription: Overloading operator<< as a friend function. Prints every field of every call_record in call_DB 
//                   formatted to the screen and a file called "stats7_output.txt".
/***************************************************************************************************************************/
ostream & operator<<(ostream & out, call_class & Org)
{
	int k = 0; 
	for (int i = 0; i < Org.count; i++)
	{

		out.setf(ios::showpoint);
		out.precision(2);
		out.setf(ios::fixed);

		string temp1 = Org.call_DB[i].firstname + " " + Org.call_DB[i].lastname;
		out << setw(20) << temp1 << "\t\t";
		out << Org.call_DB[i].cell_number << "\t";
		out << Org.call_DB[i].relays << "\t";
		out << Org.call_DB[i].call_length << "\t";
		out << Org.call_DB[i].net_cost << "\t";
		out << Org.call_DB[i].tax_rate << "\t";
		out << Org.call_DB[i].call_tax << "\t";
		out << Org.call_DB[i].total_cost << "\n";

	}

	//Put code to OPEN and CLOSE an ofstream and print to the file "stats7_output.txt".
	ofstream out1;
	out1.open("stats7_output.txt");
	out1.setf(ios::showpoint);
	out1.precision(2);
	out1.setf(ios::fixed);
		for (int i = 0; i < Org.count; i++)
		{
			string temp1 = Org.call_DB[i].firstname + " " + Org.call_DB[i].lastname;
			out1 << setw(20) << temp1 << "\t\t";
			out1 << Org.call_DB[i].cell_number << "\t";
			out1 << Org.call_DB[i].relays << "\t";
			out1 << Org.call_DB[i].call_length << "\t";
			out1 << Org.call_DB[i].net_cost << "\t";
			out1 << Org.call_DB[i].tax_rate << "\t";
			out1 << Org.call_DB[i].call_tax << "\t";
			out1 << Org.call_DB[i].total_cost << "\n";
		}
		out1.close();
	
	
	return out;  //must have this statement
}

/****************************************************************************************************************************/
//Name: destructor
//Precondition:  everything has been processed and all functions has been called
//Postcondition: it deallocates all of the memory allocated in call_DB
//Decription: de-allocates all memory allocated to call_DB.  This should be the last function to be called before the program
//            is exited.
/***************************************************************************************************************************/
call_class::~call_class()
{
	delete[] call_DB;
}


//driver to test the functionality of your class.
int main()
{
	//ofstream out1; 
	//out1.open("stats7_output.txt");
	call_class MyClass;
	//int num = 1; 
	int num1 = 0; 

	MyClass.process();
	cout << MyClass;
	string key;
	string user_response = "y";
	MyClass.add();
	MyClass.process();
	cout << MyClass; 
	//out1 << endl << endl << "Results after you added " << num1 << " time" << endl << endl <<  MyClass << endl << endl;
	num1++;
	cout << endl;
	cout << endl << "Enter a cell number to delete ";
	cout << endl << endl;
	cin >> key;
	MyClass - key;
	cout << MyClass;
	//out1 << endl << endl << "After you deleted " << num << " time" << endl << endl <<  MyClass;
	//num++;


	cout << endl << "Would you like to add another call record? " << endl;
	cin >> user_response;
	while (user_response == "y" || user_response == "Y")
	{
		MyClass.add();
		MyClass.process();
		cout << MyClass;
		//out << endl << endl << "Results after you added " << num1 << " times" << endl << endl << MyClass << endl << endl;
		//num1++;

		cout << endl;
		cout << "Enter a cell number to delete \n" << endl;
		cin >> key;
		MyClass - key;
		cout << MyClass; 
		//out << endl << endl << "After you deleted " << num << " times" << endl << endl << MyClass;
		//num++;

		cout << "Would you like to add another call record? ";
		cin >> user_response;
	}
	return 0;
}



