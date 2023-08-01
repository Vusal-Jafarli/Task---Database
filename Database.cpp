#include <iostream>
using namespace std;

class Contact
{
	string _name;
	string _surname;
	string _email;
	string _number;

public:
	Contact(string name, string surname, string email, string number)
	{
		set_name(name);
		set_surname(surname);
		set_email(email);
		set_number(number);
	}

	void set_name(string name)
	{
		if (name != "")
		{
			if (name.size() > 3 && name.size() < 50)
			{
				_name = name;
			}
			else
				throw invalid_argument("Name size yanlisdir.");
		}
		else
			throw invalid_argument("Name yanlisdir.");
	}
	void set_surname(string surname)
	{
		if (surname != "")
		{
			if (surname.size() > 3 && surname.size() < 50)
			{
				_surname = surname;
			}
			else
				throw invalid_argument("Surname size yanlisdir.");
		}
		else
			throw invalid_argument("Surname yanlisdir.");
	}
	void set_email(string email)
	{
		if (email != "")
		{
			if (email.size() > 7 && email.size() < 100)
			{
				_email = email;
			}
			else
				throw invalid_argument("Email size yanlisdir.");
		}
		else
			throw invalid_argument("Email yanlisdir.");
	}
	void set_number(string number)
	{
		if (number != "")
		{
			if (number.size() > 7 && number.size() < 100)
			{
				_number = number;
			}
			else
				throw invalid_argument("Number size yanlisdir.");
		}
		else
			throw invalid_argument("Number yanlisdir.");
	}

	string get_name() { return _name; }
	string get_surname() { return _surname; }
	string get_email() { return _email; }
	string get_number() { return _number; }

	friend ostream& operator<<(ostream& os, Contact& con);
};
ostream& operator<<(ostream& os, Contact& con)
{
	os << "Name: " << con.get_name() << endl
		<< "Surname: " << con.get_surname() << endl
		<< "Email: " << con.get_email() << endl
		<< "Number: " << con.get_number() << endl;

	return os;
}




class DataBase
{
	Contact** _contacts;
	int _contact_counts;

public:
	DataBase(Contact** contacts, int contact_counts)
	{
		set_contacts(contacts, contact_counts);
	}

	void AddContact(Contact*& newContact)
	{
		Contact** new_contacts = new Contact * [_contact_counts + 1] {};
		for (size_t i = 0; i < _contact_counts; i++)
		{
			new_contacts[i] = _contacts[i];
		}
		new_contacts[_contact_counts] = newContact;

		delete _contacts;
		_contacts = new_contacts;
		_contact_counts++;
	}
	void DeleteByName(string name)
	{
		Contact** new_contacts = new Contact * [_contact_counts - 1] {};

		size_t i;
		for (i = 0; i < _contact_counts; i++)
		{
			if (_contacts[i]->get_name() == name)
				break;
		}

		for (size_t j = 0; j < i; j++)
			new_contacts[j] = _contacts[j];


		for (size_t j = i + 1; j < _contact_counts; j++)
			new_contacts[j] = _contacts[j - 1];


		delete _contacts;
		_contacts = new_contacts;
		_contact_counts--;



	}
	Contact*& SearchByName(string name)
	{
		for (size_t i = 0; i < _contact_counts; i++)
		{
			if (_contacts[i]->get_name() == name)
				return _contacts[i];
		}
	}

	Contact** get_all_contacts() { return _contacts; }
	int get_contacts_count() { return _contact_counts; }

	void set_contacts(Contact** contacts, int contact_counts)
	{
		Contact** new_contacts = new Contact * [contact_counts] {};

		if (_contacts != nullptr)
		{
			for (size_t i = 0; i < _contact_counts; i++)
				delete _contacts[i];
			delete _contacts;
		}


		for (size_t i = 0; i < contact_counts; i++)
			new_contacts[i] = new Contact(contacts[i]->get_name(), contacts[i]->get_surname(), contacts[i]->get_email(), contacts[i]->get_number());

		_contacts = new_contacts;
		_contact_counts = contact_counts;
	}


	void show() {
		for (size_t i = 0; i < _contact_counts; i++)
			cout << *(_contacts[i]) << endl;

	}
};





void main() {
	Contact* v = new Contact("Vusal", "Ceferli", "jafarlee00@gmail.com", "0708370437");
	Contact* o = new Contact("Orxan", "Memmedli", "orxan1@gmail.com", "0505707050");



	Contact** contacts = new Contact * [2] {v, o};

	DataBase facebook(contacts,2);
	facebook.show();

	cout << endl;
	cout << endl;
	Contact* d = new Contact("Sukur", "Eliyev", "Sukur5@gmail.com", "0705041289");
	Contact* m = new Contact("Memmed", "Quliyev", "Memmed4@gmail.com", "0506985430");

	facebook.AddContact(d);
	facebook.AddContact(m);
	facebook.DeleteByName("Memmed");
	//Contact* l  = facebook.SearchByName("Vusal");
	//cout << *l;


	facebook.show();
	//Contact c = facebook.SearchByName("Vusal");
	//cout << c;
}
//bvc