#include "ask_usr.h"



double ask_usr::get_power()
{
	/*Promts the user to enter pow variable*/
	string temp;
	cout << "The power in the IDW formula controls the influence of distance. Increasing the power gives more weight to nearby points,"<<
		 " making the interpolation sharper." << endl;

	do
	{
		cout << "Enter Power value (Recommended between 1-2):" << endl;
		cin >> temp;

		if (valid_double(temp) && stod(temp) > 0)// if number is valid then break
		{
			break;
		}
		cout << "Oops, looks like that entry didn't work. Try again: ";


	} while (true);

	double power = stod(temp);


	return(power);
}


int ask_usr::get_num_DH(int x, int y)
{
	/*Prompts the user to enter the number of drill holes and checks that it is less than the total number of grid squares in the block model.*/

	int total_sqr = x * y;
	int num;
	string temp;
	do {
		cout << "How many Drill Holes do you want to enter? " << endl;
		cin >> temp;
		if (valid_int(temp) && stoi(temp) > 0)
		{
			num = stoi(temp);
			if (num < total_sqr)
			{
				break;
			}
			else
			{
				cout << "That won't work. You entered more Drill Holes than squares in your Block Model." << endl;
			}
		}
		else
		{
			cout << "Oops, looks like that entry didn't work. Try again: ";
		}
	} while (true);

	return num;
}


int ask_usr::grid_check(int& grid_x, int& grid_y)
{
	/*Confirms that the user is happy with grid size*/
	do
	{
		grid_size(grid_x, grid_y);
		char Y_N;
		cout << "Your grid dimensions are " << grid_x << "x by " << grid_y << "y" << endl;

		cout << "Is this correct (y/n)?: " << endl;
		cin >> Y_N;

		if (Y_N == 'y' || Y_N == 'Y')
		{
			cout << "\nAmazing! Let's start.\n" << endl;
			break;
		}

		cout << "Oh no, let's try again." << endl;


	} while (true);
	return(0);
}



int ask_usr::grid_size(int& grid_x, int& grid_y) // taking in where the memory of grid x,y is stored and editing it in the member function
{

	/*Promts the user to enter the grid size and checks the input*/

	cout << "Enter the dimensions of your output block model grid. " << endl;
	string temp_x;
	do
	{
		cout << "X value: " << endl;
		cin >> temp_x;

		if (valid_int(temp_x) && stoi(temp_x) > 0)// if number is valid then break
		{
			break;
		}
		cout << "Oops, looks like that entry didn't work. Try again: ";


	} while (true);

	grid_x = stoi(temp_x);


	string temp_y;
	do
	{
		cout << "Y value: " << endl;
		cin >> temp_y;

		if (valid_int(temp_y) && stoi(temp_y) > 0)// if number is valid then break
		{
			break;
		}
		cout << "Oops, looks like that entry didn't work. Try again: ";


	} while (true);

	grid_y = stoi(temp_y);


	return(0);
}

