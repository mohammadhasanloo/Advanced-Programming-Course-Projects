#include <iostream>
#include <vector>
#include <exception>

using namespace std;

const int REFRENCE_DELIVERY_DEADLINE = 5;
const int MAGAZINE_DELIVERY_DEADLINE = 2;
const int COMMON_DELIVERY_DEADLINE = 10;
const int STUDENT_MAX_DELIVERY = 2;
const int PROF_MAX_DELIVERY = 5;
const int MAGAZINE_EXTEND_TIME = 0;
const int COMMON_EXTEND_TIME = 2;
const int REFRENCE_EXTEND_TIME = 2;
const int _7000 = 7000;
const int _5000 = 5000;
const int _2000 = 2000;
const int _3000 = 3000;
const int SCALE_MAGAZINE_YEAR = 1390;
const int FIRST_DELAY_REFRENCE_DAYS = 3;
const int FIRST_DELAY_COMMON_DAYS = 7;
const int SECOND_DELAY_COMMON_DAYS = 21;


class books
{
public:
	books(string _title, int _copies);
	string get_title() { return title; }
	string get_available_books();
	bool is_existence_book();
	void change_info_after_borrow();
	virtual void change_info_after_return_document() = 0;
	virtual void change_info_after_time_pass(int days) = 0;
	virtual void change_info_after_extend() = 0;
	virtual int calculate_new_debt() = 0;
protected:
	string title;
	int copies;
};

class magazines :public books
{
public:
	magazines(string _title, int _copies, int _year, int _number);
	void change_info_after_return_document();
	void change_info_after_time_pass(int days) { borrow_days += days; };
	void change_info_after_extend();
	int calculate_new_debt();

private:
	int year;
	int number;
	int borrow_days = 0;
	int extend_time = 0;

};

class refrences :public books
{
public:
	refrences(string _title, int _copies);
	void change_info_after_return_document();
	void change_info_after_time_pass(int days) { borrow_days += days; };
	void change_info_after_extend();
	int calculate_new_debt();

private:
	int borrow_days = 0;
	int extend_time = 0;
};

class common_books :public books
{
public:
	common_books(string _title, int _copies);
	void change_info_after_return_document();
	void change_info_after_time_pass(int days) { borrow_days += days; };
	void change_info_after_extend();
	int calculate_new_debt();

private:
	int borrow_days = 0;
	int extend_time = 0;
};


class members
{
public:
	members(string _name);
	string get_name() { return name; }
	void change_info_after_borrow(books* new_book);
	virtual void add_new_book(books* new_book) = 0;
	void change_info_after_return_document(string remove_book);
	virtual void remove_intended_book(string remove_book) = 0;
	void add_days(int days);
	virtual void change__books_borrow_days(int days) = 0;
	virtual void change_info_after_extend(string curr_book) = 0;
	//virtual int get_total_penalty() = 0;

protected:
	string name;
};

class students :public members
{
public:
	students(string _name, string _student_id);
	void add_new_book(books* new_book);
	void remove_intended_book(string remove_book);
	void change__books_borrow_days(int days);
	void change_info_after_extend(string curr_book);
	//int get_total_penalty();

private:
	string student_id;
	vector <books*> borrow_books;
	int books_num = 0;
	int debt = 0;
};

class professors :public members
{
public:
	professors(string _name);
	void add_new_book(books* new_book);
	void remove_intended_book(string remove_book);
	void change__books_borrow_days(int days);
	void change_info_after_extend(string curr_book);
	//int get_total_penalty();

private:
	vector <books*> borrow_books;
	int books_num = 0;
	int debt = 0;
};


class Library
{
public:
	void add_student_member(string student_id, string student_name);
	void add_prof_member(string prof_name);
	void add_book(string book_title, int copies);
	void add_magazine(string magazine_title, int year, int number, int copies);
	void add_reference(string refrence_title,int copies);
	void borrow(string member_name, string document_title);
	void extend(string member_name, string document_title);
	void return_document(string member_name, string document_title);
	int get_total_penalty(string member_name);
	vector <string> available_titles();
	void time_pass(int days);
	void check_member_errors(string member_name);
	void check_id_error(string student_id);
	void check_docs_errors(string title, int copies);
	void check_decimal_num_errors(int year, int number);
	books* search_intended_book(string document_title);
	members* search_intended_member(string member_name);

private:
	vector <members*> lib_members;
	vector <books*> lib_books;
};


class Command_Handle
{
public:
	void run();

private:
	Library ut_lib;
};



members::members(string _name)
{
	name = _name;
}

students::students(string _name, string _student_id)
	:members(_name)
{
	student_id = _student_id;
}

professors::professors(string _name)
	:members(_name)
{}

books::books(string _title, int _copies)
{
	title = _title;
	copies = _copies;
}

magazines::magazines(string _title, int _copies,int _year, int _number)
	:books(_title, _copies)
{
	year = _year;
	number = _number;
}

refrences::refrences(string _title, int _copies)
	:books(_title, _copies)
{}

common_books::common_books(string _title, int _copies)
	: books(_title, _copies)
{}




void Library::check_member_errors(string member_name)
{
	if(member_name.empty())
		throw runtime_error("name is empty");

	for (int i = 0;i < lib_members.size();i++)
	{
		if (member_name == lib_members[i]->get_name())
			throw runtime_error("repetitious name");
	}
}

void Library::check_id_error(string student_id)
{
	if(student_id.empty())
		throw runtime_error("student_id is empty");
}

void Library::add_student_member(string student_id, string student_name)
{
	check_member_errors(student_name);
	check_id_error(student_id);

	lib_members.push_back(new students(student_name, student_id));
}

void Library::add_prof_member(string prof_name)
{
	check_member_errors(prof_name);

	lib_members.push_back(new professors(prof_name));
}

void Library::check_docs_errors(string title, int copies)
{
	if (title.empty())
		throw runtime_error("title is empty");

	for (int i = 0;i < lib_books.size();i++)
	{
		if (title == lib_books[i]->get_title())
			throw runtime_error("repetitious title");
	}

	if(copies<0)
		throw runtime_error("number of copies must be bigger than -1");
}

void Library::add_book(string book_title, int copies)
{
	check_docs_errors(book_title, copies);

	lib_books.push_back(new common_books(book_title, copies));
}

void Library::add_reference(string refrence_title, int copies)
{
	check_docs_errors(refrence_title, copies);

	lib_books.push_back(new refrences(refrence_title, copies));
}

void Library::check_decimal_num_errors(int year, int number)
{
	if(year<=0)
		throw runtime_error("year number must be bigger than zero!");

	if(number<=0)
		throw runtime_error("number of magazine must be bigger than zero!");
}

void Library::add_magazine(string magazine_title, int year, int number, int copies)
{
	check_docs_errors(magazine_title, copies);
	check_decimal_num_errors(year, number);

	lib_books.push_back(new magazines(magazine_title, copies, year, number));
}

void members::add_days(int days)
{
	change__books_borrow_days(days);
}

void students::change__books_borrow_days(int days)
{
	for (int i = 0;i < borrow_books.size();i++)
		borrow_books[i]->change_info_after_time_pass(days);
}

void professors::change__books_borrow_days(int days)
{
	for (int i = 0;i < borrow_books.size();i++)
		borrow_books[i]->change_info_after_time_pass(days);
}

void Library::time_pass(int days)
{
	if(days<0)
		throw runtime_error("days number must be bigger than -1!");

	for (int i = 0;i < lib_members.size();i++)
		lib_members[i]->add_days(days);
}

string books::get_available_books()
{
	if (copies > 0)
		return title;
	return "";
}

vector <string> Library::available_titles()
{
	vector <string> result;

	for (int i = 0;i < lib_books.size();i++ )
	{
		string available_book=lib_books[i]->get_available_books();
		if (available_book=="")
			continue;
		result.push_back(available_book);
	}
	return result;
}

bool books::is_existence_book()
{
	if (copies > 0)
		return true;
	return false;
}

books* Library::search_intended_book(string document_title)
{
	for (int i = 0;i < lib_books.size();i++)
	{
		if (lib_books[i]->get_title() == document_title)
		{
			if (lib_books[i]->is_existence_book())
				return lib_books[i];
			else
				throw runtime_error("all of this book has been borrowed");
		}
	}
	return nullptr;
}

members* Library::search_intended_member(string member_name)
{
	for (int i = 0;i < lib_members.size();i++)
	{
		if (lib_members[i]->get_name() == member_name)
			return lib_members[i];
	}
	return nullptr;
}

void students::add_new_book(books* new_book)
{
	if (books_num >= STUDENT_MAX_DELIVERY)
		throw runtime_error("This student has more than legal borrow books!");
	borrow_books.push_back(new_book);
	books_num++;
};

void professors::add_new_book(books* new_book)
{
	if (books_num >= PROF_MAX_DELIVERY)
		throw runtime_error("This professor has more than legal borrow books!");
	borrow_books.push_back(new_book);
	books_num++;
};

void members::change_info_after_borrow(books* new_book)
{
	add_new_book(new_book);
}

void books::change_info_after_borrow()
{
	copies--;
}

void Library::borrow(string member_name, string document_title)
{
	books* searched_book = search_intended_book(document_title);

	if(searched_book==nullptr)
		throw runtime_error("intended book didn't found");

	members* searched_member = search_intended_member(member_name);

	if (searched_member == nullptr)
		throw runtime_error("intended member didn't found");



	searched_member->change_info_after_borrow(searched_book);
	searched_book->change_info_after_borrow();

}

int magazines::calculate_new_debt()
{
	int new_debt = 0;
	if (borrow_days <= ((extend_time + 1) * MAGAZINE_DELIVERY_DEADLINE))
		return new_debt;

	int delay_days = borrow_days - (extend_time + 1) * MAGAZINE_DELIVERY_DEADLINE;
	if (year < SCALE_MAGAZINE_YEAR)
		return delay_days * _2000;
	else
		return delay_days * _3000;
}

int common_books::calculate_new_debt()
{
	int new_debt = 0;
	if (borrow_days <= ((extend_time + 1) * COMMON_DELIVERY_DEADLINE))
		return new_debt;
	else
	{
		int delay_days = borrow_days - (extend_time + 1) * COMMON_DELIVERY_DEADLINE;
		if (delay_days <= FIRST_DELAY_COMMON_DAYS)
			return delay_days * _2000;
		else if ((delay_days > FIRST_DELAY_COMMON_DAYS) && (delay_days <= SECOND_DELAY_COMMON_DAYS))
			return (FIRST_DELAY_COMMON_DAYS * _2000) + (delay_days - FIRST_DELAY_REFRENCE_DAYS) * _3000;
		else
			return (FIRST_DELAY_COMMON_DAYS * _2000) + ((SECOND_DELAY_COMMON_DAYS- FIRST_DELAY_COMMON_DAYS) * _3000)
			+ ((delay_days- FIRST_DELAY_COMMON_DAYS- SECOND_DELAY_COMMON_DAYS))*_5000;
	}
}

int refrences::calculate_new_debt()
{
	int new_debt = 0;
	if (borrow_days <= ((extend_time + 1) * REFRENCE_DELIVERY_DEADLINE))
		return new_debt;
	else
	{
		int delay_days = borrow_days - (extend_time + 1) * REFRENCE_DELIVERY_DEADLINE;
		if (delay_days <= FIRST_DELAY_REFRENCE_DAYS)
			return delay_days * _5000;
		else
			return (FIRST_DELAY_REFRENCE_DAYS * _5000) + (delay_days - FIRST_DELAY_REFRENCE_DAYS) * _7000;
	}
}

void students::remove_intended_book(string remove_book)
{
	bool find_curr_book = false;
	for (int i = 0;i < borrow_books.size();i++)
	{
		if (borrow_books[i]->get_title() == remove_book)
		{
			debt += borrow_books[i]->calculate_new_debt();
			borrow_books.erase(borrow_books.begin() + i);
			books_num--;
			find_curr_book = true;
			break;
		}

	}
	if (!find_curr_book)
		throw runtime_error("This student doesn't have this book");
}

void professors::remove_intended_book(string remove_book)
{
	bool find_curr_book = false;
	for (int i = 0;i < borrow_books.size();i++)
	{
		if (borrow_books[i]->get_title() == remove_book)
		{
			borrow_books.erase(borrow_books.begin()+i);
			books_num--;
			find_curr_book = true;
			break;
		}
	}
	if (!find_curr_book)
		throw runtime_error("This professor doesn't have this book");
}

void members::change_info_after_return_document(string remove_book)
{
	remove_intended_book(remove_book);
}

void magazines::change_info_after_return_document()
{
	extend_time = 0;
	borrow_days = 0;
	copies++;
}

void refrences::change_info_after_return_document()
{
	extend_time = 0;
	borrow_days = 0;
	copies++;
}

void common_books::change_info_after_return_document()
{
	extend_time = 0;
	borrow_days = 0;
	copies++;
}

void Library::return_document(string member_name, string document_title)
{
	books* searched_book = search_intended_book(document_title);

	if (searched_book == nullptr)
		throw runtime_error("intended book didn't found");

	members* searched_member = search_intended_member(member_name);

	if (searched_member == nullptr)
		throw runtime_error("intended member didn't found");


	searched_member->change_info_after_return_document(searched_book->get_title());
	searched_book->change_info_after_return_document();
}

void magazines::change_info_after_extend()
{
	if (extend_time >= MAGAZINE_EXTEND_TIME)
		throw runtime_error("You can't extend this magazine anymore");
	else if (borrow_days == 0)
		throw runtime_error("You can't extend this magazine at first day");
	else if (borrow_days > (extend_time+1)* MAGAZINE_DELIVERY_DEADLINE)
		throw runtime_error("You can't extend this magazine after deadline");
	else
		extend_time++;
}

void refrences::change_info_after_extend()
{
	if (extend_time >= REFRENCE_EXTEND_TIME)
		throw runtime_error("You can't extend this refrence anymore");
	else if (borrow_days == 0)
		throw runtime_error("You can't extend this refrence at first day");
	else if (borrow_days > (extend_time + 1)* REFRENCE_DELIVERY_DEADLINE)
		throw runtime_error("You can't extend this refrence after deadline");
	else
		extend_time++;
}

void common_books::change_info_after_extend()
{
	if (extend_time >= COMMON_EXTEND_TIME)
		throw runtime_error("You can't extend this common book anymore");
	else if (borrow_days == 0)
		throw runtime_error("You can't extend this common book at first day");
	else if (borrow_days > (extend_time + 1)* COMMON_DELIVERY_DEADLINE)
		throw runtime_error("You can't extend this common book after deadline");
	else
		extend_time++;
}

void students::change_info_after_extend(string curr_book)
{
	bool find_book = false;
	for (int i = 0;i < borrow_books.size();i++)
	{
		if (borrow_books[i]->get_title() == curr_book)
		{
			borrow_books[i]->change_info_after_extend();
			find_book = true;
			break;
		}
	}
	if (!find_book)
		throw runtime_error("This student doesn't have this book");
}

void professors::change_info_after_extend(string curr_book)
{
	bool find_book = false;
	for (int i = 0;i < borrow_books.size();i++)
	{
		if (borrow_books[i]->get_title() == curr_book)
		{
			borrow_books[i]->change_info_after_extend();
			find_book = true;
			break;
		}
	}
	if (!find_book)
		throw runtime_error("This professor doesn't have this book");
}

void Library::extend(string member_name, string document_title)
{
	books* searched_book = search_intended_book(document_title);

	if (searched_book == nullptr)
		throw runtime_error("intended book didn't found");

	members* searched_member = search_intended_member(member_name);

	if (searched_member == nullptr)
		throw runtime_error("intended member didn't found");

	searched_member->change_info_after_extend(searched_book->get_title());
}

/*int students::get_total_penalty()
{

}

int professors::get_total_penalty()
{

}

int Library::get_total_penalty(string member_name)
{
	bool find_book = false;
	int total_penalty = 0;
	for (int i = 0;i < lib_members.size();i++)
	{
		if (lib_members[i]->get_name()== member_name)
		{
			total_penalty = lib_members[i]->get_total_penalty();
			find_book = true;
			break;
		}
	}

	if (!find_book)
		throw runtime_error("Can't find current member!");
}*/

void Command_Handle::run()
{
	try
	{
		//put your testcase here please
		//don't use get_total_penalty please
		Library ut_lib;
		ut_lib.add_student_member("810199999", "Negar");
		ut_lib.add_student_member("810198888", "Naser");
		ut_lib.add_prof_member("Dr. Nagargar");
		ut_lib.add_prof_member("Dr. Naseri");
		ut_lib.add_prof_member("Dr. Naseri");
		ut_lib.add_book("Lean Startup", 1);
		ut_lib.add_magazine("Today News, vol.38, no.3", 1395, 3, 1);
		ut_lib.add_reference("Cambridge Dictionary", 3);
		ut_lib.borrow("Naser", "Lean Startup");
		vector<string> available_docs = ut_lib.available_titles();
		ut_lib.time_pass(10);
		ut_lib.extend("Naser", "Lean Startup");
		ut_lib.time_pass(12);
		ut_lib.return_document("Naser", "Lean Startup");
		ut_lib.borrow("Naser", "Cambridge Dictionary");
		ut_lib.time_pass(8);


	}
	catch (runtime_error& ex)
	{
		cerr << ex.what() << endl;
	}

}

int main()
{
	Command_Handle new_program;
	new_program.run();

	return 0;
}
