#include "UI.h"

using namespace std;

UI::UI(Controller* _controller)
{
	this->controller = _controller;
}

void	UI::show_menu() const
{
	cout << "1. Add activity.\n";
	cout << "2. Delete activity.\n";
	cout << "3. Edit activity.\n";
	cout << "4. Display activities.\n";
	cout << "5. Search activity.\n";
	cout << "6. Filter activities.\n";
	cout << "7. Sort activities.\n";
	cout << "8. Exit.\n";
}

string	UI::read_title()
{
	string	title;
	bool	isvalid = false;

	while (!isvalid)
	{
		cout << "Title = ";
		getline(cin, title);
		if (title == "0")
			throw invalid_argument("back argument");
		if (this->controller->isvalid_title(title))
		{
			isvalid = true;
		}
		else
		{
			cout << "Retry...\n";
		}
	}
	return title;
}

string	UI::read_type()
{
	string	type;
	bool	isvalid = false;

	while (!isvalid)
	{
		cout << "Type = ";
		getline(cin, type);
		if (type == "0")
			throw invalid_argument("back argument");
		if (this->controller->isvalid_type(type))
		{
			isvalid = true;
		}
		else
		{
			cout << "Retry...\n";
		}
	}
	return type;
}

string	UI::read_description()
{
	string	description;
	bool	isvalid = false;

	while (!isvalid)
	{
		cout << "Description = ";
		getline(cin, description);
		if (description == "0")
			throw invalid_argument("back argument");
		if (this->controller->isvalid_description(description))
		{
			isvalid = true;
		}
		else
		{
			cout << "Retry...\n";
		}
	}
	return description;
}

int		UI::read_duration()
{
	bool	isvalid = false;
	string	input;

	while (!isvalid)
	{
		cout << "Duration = ";
		getline(cin, input);
		if (input == "0")
			throw invalid_argument("back argument");
		if (this->controller->isvalid_number(input) && !input.empty())
		{
			isvalid = true;
		}
		else
		{
			cout << "Retry...\n";
		}
	}
	return stoi(input);
}

void	UI::add()
{
	string	title, description, type;
	int		duration;

	try
	{
		title = read_title();
	}
	catch (const invalid_argument& e)
	{
		return;
	}

	try
	{
		description = read_description();
	}
	catch (const invalid_argument& e)
	{
		return;
	}

	try
	{
		type = read_type();
	}
	catch (const invalid_argument& e)
	{
		return;
	}
	
	try
	{
		duration = read_duration();
	}
	catch (const invalid_argument& e)
	{
		return;
	}

	try
	{
		this->controller->add(title, description, type, duration);
		cout << "\n" << "Add successful." << "\n\n";
	}
	catch (const invalid_argument& e)
	{
		cout << "\n" << e.what() << "\n\n";
	}
}

void	UI::remove()
{
	string	title;

	try
	{
		title = read_title();
	}
	catch (const invalid_argument& e)
	{
		return;
	}

	try
	{
		this->controller->remove(title);
	}
	catch (const invalid_argument& e)
	{
		cout << "\n" << e.what() << "\n\n";
	}
}

void	UI::edit()
{
	string	title, description, type, duration;

	try
	{
		title = read_title();
	}
	catch (const invalid_argument& e)
	{
		return;
	}

	while (!this->controller->exists(title))
	{
		cout << "Activity does not exist, retry or exit('0').\n";
		try
		{
			title = read_title();
		}
		catch (const invalid_argument& e)
		{
			return;
		}
	}
	cout << "Description = ";
	getline(cin, description);
	cout << "Type = ";
	getline(cin, type);
	cout << "Duration = ";
	getline(cin, duration);
	this->controller->edit(title, description, type, duration);
}

void	UI::display()
{
	DynamicVector<Activity> *list;

	list = this->controller->get_list();
	list->display_once();
}

void	UI::search()
{
	string	title;

	try
	{
		title = read_title();
	}
	catch (const invalid_argument& e)
	{
		return;
	}
	if (this->controller->exists(title))
		cout << this->controller->get_elem(title);
	else
		cout << "The activity does not exist.\n";
}

void	UI::show_menu_filter() const
{
	cout << "0. Back.\n";
	cout << "1. Filter by description.\n";
	cout << "2. Filter by type.\n";
}

void	UI::filter()
{
	string					inputline;
	int						input;
	DynamicVector<Activity> *list;

	input = -1;
	while (input != 0)
	{
		this->show_menu_filter();
		cout << "Input: ";
		getline(cin, inputline);
		if (this->controller->isvalid_number(inputline) && !inputline.empty())
		{
			input = stoi(inputline);
			switch (input)
			{
				case 0: break;
				case 1: 
					try 
					{
						inputline = read_description(); 
					}
					catch (const invalid_argument& e)
					{
						return;
					}
					list = this->controller->get_list_filtered("description", inputline);
					list->display_once();
					break;
				case 2: 
					try 
					{
						inputline = read_type(); 
					}
					catch (const invalid_argument& e)
					{
						return;
					}
					list = this->controller->get_list_filtered("type", inputline);
					list->display_once();
					break;
				default:
					cout << "Invalid input.\n";
					continue;
			}
			break;
		}
		else
		{
			cout << "Invalid input, retry...\n";
		}
	}
}

void	UI::show_menu_sort() const
{
	cout << "0. Back.\n";
	cout << "1. Sort by title.\n";
	cout << "2. Sort by description.\n";
	cout << "3. Sort by type + duration.\n";
}

void	UI::sort()
{
	string					inputline;
	int						input;
	DynamicVector<Activity> *list;

	input = -1;
	while (input != 0)
	{
		this->show_menu_sort();
		cout << "Input: ";
		getline(cin, inputline);
		if (this->controller->isvalid_number(inputline) && !inputline.empty())
		{
			input = stoi(inputline);
			switch (input)
			{
				case 0: break;
				case 1: 
					list = this->controller->get_list_sorted("title");
					list->display_once();
					break;
				case 2: 
					list = this->controller->get_list_sorted("description");
					list->display_once();
					break;
				case 3:
					list = this->controller->get_list_sorted("type+duration");
					list->display_once();
					break;
				default:
					cout << "Invalid input.\n";
					continue;
			}
			break;
		}
		else
		{
			cout << "Invalid input, retry...\n";
		}
	}
}

void	UI::start()
{
	int		input = 0;
	string	inputline;

	this->controller->init();
	while (input != 8)
	{
		this->show_menu();
		cout << "Input: ";
		getline(cin, inputline);
		if (this->controller->isvalid_number(inputline) && !inputline.empty())
		{
			input = stoi(inputline);
			switch (input)
			{
				case 1 : 
					this->add();
					break;
				case 2 : 
					this->remove();
					break;
				case 3 : 
					this->edit();
					break;
				case 4 : 
					this->display();
					break;
				case 5 : 
					this->search();
					break;
				case 6 : 
					this->filter();
					break;
				case 7 : 
					this->sort();
					break;
				case 8 : 
					return;
				default : 
					cout << "\n" << "Invalid input, retry.\n" << "\n";
					break;
			}
		}
		else
		{
			cout << "\n" << "Invalid input, retry.\n" << "\n";
		}
	}
}

UI::~UI()
{
	delete this->controller;
}
