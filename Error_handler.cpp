
#include "Error_handler.h"



double** Error_check::all_check(int& max_x, int& max_y, double** DH, int& num)
{
	// main error checking member function that calls all the other private error checking functions in

	cout << "Before we start lets check for errors in the data. " << endl;
	cout << "\n.............................................\n";
	DH = valid_DH_values(DH, num);
	cout << "\n.............................................\n";
	DH = repeat_DH_xy(DH, num);
	cout << "\n.............................................\n";
	DH = grid_greater_than_DH(max_x, max_y, DH, num);
	cout << "\n.............................................\n";

	cout << "\nEverything seems in order let's begin." << endl;

	return(DH);

}












double** Error_check::valid_DH_values(double** DH, int num)
{
	/*Checks that all the grade values are valid.*/

	cout << "Checking that all Drill Hole grade values are between 1 and 0 inclusive........." << endl;

	for (int i = 0; i < num; i++)
	{
		
		if (((DH[i][2]) > 1.0) || ((DH[i][2]) < 0.0))
		{
			cout << "Looks like Drill Hole " << i + 1 << " has an invalid grade value." << endl;
			cout << "The co-ordinates are: " << endl;
			cout << "x: " << DH[i][0] << "\ny: " << DH[i][1] << endl;


			string temp;
			do
			{
				cout << "Enter the correct value: " << endl;
				cin >> temp;
				if (valid_double(temp) && (stod(temp) <= 1.0) && (stod(temp) >= 0.0))
				{
					break;
				}
				cout << "Invalid number! Value should be between 1 and 0!" << endl;

			} while (true);


			DH[i][2] = stod(temp); // converts the string to a double and assigns it into the DH array

		}
	}

	cout << "............all Drill Holes valid." << endl;
	// clear memory?
	return (DH);
}





double** Error_check::repeat_DH_xy(double** DH, int& num)
{

	/* Adds the first DH from DH array to the new DH array. Then loops through
	the next DH from the old DH array seeing if it is in the new DH array, if it is then it deletes it and corrects the new number of DH's. */



	double** new_DH = new double* [num]; // creating a temporay Dh for the non repeated DH's
	int new_num = 0; // new number of drill holes

	cout << "\nChecking for any repeated Drill Holes........\n";

	for (int i = 0; i < num; i++)
	{
		double test_x = DH[i][0];
		double test_y = DH[i][1];
		// getting info from one drill hole and then looping through all the drill holes to see if its repeated
		bool is_duplicate = false;


		for (int j = 0; j < new_num; j++)
		{
			if ((fabs(test_x - DH[j][0]) < deci) && (fabs(test_y - DH[j][1]) < deci)) // if the difference between the two x,y values is less that a small value they have the same x and y co-ords.
			{
				cout << "Oh no it looks like you have repeated a Drill Hole." << endl;

				cout << "The co-ordinates to Drill Hole " << i + 1 << " has been repeated" << endl;
				cout << "The co-ordinates are: " << endl;
				cout << "x: " << DH[i][0] << "\ny: " << DH[i][1] << "\nGrade value: " << DH[i][2] << endl;
				cout << "The co-ordinates of the repated Drill Hole " << i + 1 << " are: " << endl;
				cout << "x: " << DH[j][0] << "\ny: " << DH[j][1] << "\nGrade value: " << DH[j][2] << endl;



				cout << "\n\n THE REPEATED DRILL HOLE IS BEING REMOVED\n\n" << endl;

				is_duplicate = true;

				break; // deleted the repeated DH so skips to the next DH in the i loop and as is duplicate is true will not add this DH to the new array.




			}
		}


		if (!is_duplicate)
		{
			// Allocate memory for a new drill hole only when not repeated
			new_DH[new_num] = new double[3];
			new_DH[new_num][0] = DH[i][0]; // assinging the new co-ords and value
			new_DH[new_num][1] = DH[i][1];
			new_DH[new_num][2] = DH[i][2];
			new_num++; // add one to the new number of drill holes
		}


	}

	// clearing the old DH array

	for (int i = 0; i < num; i++)
	{
		delete[] DH[i];
	}
	delete[] DH;

	if(num!=new_num) // if any drill holes have been repeated 
	{
		num = new_num; // update the number of drill holes

		cout << "The corrected Drill holes are as follows: " << endl;
		for (int i = 0; i < new_num; i++) {
			cout << i + 1 << "\t" << new_DH[i][0] << "\t" << new_DH[i][1] << "\t" << new_DH[i][2] << endl;
		}
	}
	else
	{
		cout << ".............there are no repeated Drill Holes" << endl;
	}
	// Update the number of drill holes after removing duplicates
	

	

	return(new_DH);
}



double** Error_check::grid_greater_than_DH(int& max_x, int& max_y, double** DH, int num)
{
	/* checks that the grid size is greater than all the drill hole co - ordinates allowing user to correct either the drill hole or the grid size.*/


	cout << "Checking that your block model dimensions include all the Drill Holes........" << endl;

	for (int i = 0; i < num; i++)
	{
		if ((max_x < DH[i][0]) || (max_y < DH[i][1])) // if the drill hole x or y is outside the grid size
		{
			char temp;
			cout << "Error! Drill Hole " << i + 1 << " is outside the block model domain.";

			cout << "The co-ordinates to Drill Hole " << i + 1 << endl;
			cout << "The co-ordinates are: " << endl;
			cout << "x: " << DH[i][0] << "\ny: " << DH[i][1] << endl;
			

		
			do
			{
				cout << "Do you want to:\n a) Adjust the Drll Hole co-ordinates. \n b) Change grid co-ordinates. \n c) Ignore. " << endl;
				cout << "Enter answer below: " << endl;
				cin >> temp;

				if (temp == 'a')
				{
					adjust_DH(DH, num, i); // option to adjust the drill hole co-ordinates
					
					break;
					
				}
				else if (temp == 'b') // allows user to change the grid size
				{
					cout << "Change grid x from " << max_x << " and change grid y from " << max_y <<endl;
					
					adjust_grid(DH, max_x, max_y); // option to adjust the grid size

					break;
				}

				else if (temp == 'c')
				{
					cout << "Ignoring Drill Hole " << i + 1 << endl;
					break;
				}
				else
				{
					cout << "That didn't work. Ensure you enterd a valid number." << endl;
					
				}
			} while (false);


		}

	}

	cout << "............ Block Model size is valid." << endl;
	return(DH);
	
	// delete after return
}



double ** Error_check::adjust_DH(double** DH, int& num, int i)
{ 
	/*Allows user to correct a drill hole*/

	string temp_x;
	do
	{
		cout << "Change x from " << DH[i][0] << " to " << endl;
		cin >> temp_x;

		if (valid_int(temp_x) && stod(temp_x) > 0)// if number is valid then break
		{
			break;
		}
		cout << "Oops, looks like that entry didnt work. Try again: ";


	} while (true); // repeats until a valid number is entered

	DH[i][0] = stod(temp_x); // assigns the string to the new grid x


	string temp_y;
	do
	{
		cout << "Change y from " << DH[i][1] << " to " << endl;
		cin >> temp_y;

		if (valid_int(temp_y) && stod(temp_y) > 0)// if number is valid then break
		{
			break;
		}
		cout << "Oops, looks like that entry didn't work. Try again: ";


	} while (true); // repeats until a valid number is entered

	DH[i][1] = stod(temp_y); // assigns the string to the new grid y

	return(0);
}



double** Error_check::adjust_grid(double** DH, int& max_x, int& max_y)
{

	/*Allows user to correct the grid size*/

	string temp_x;
	do
	{
		cout << "Enter the new X value:" << endl;
		cin >> temp_x;

		if (valid_int(temp_x) && stoi(temp_x) > 0)// if number is valid then break
		{
			break;
		}
		cout << "Oops, looks like that entry didn't work. Try again: ";


	} while (true); // repeats until a valid number is entered

	max_x = stoi(temp_x); // assigns the string to the new grid x


	string temp_y;
	do
	{
		cout << "Enter the new Y value:" << endl;
		cin >> temp_y;

		if (valid_int(temp_y) && stoi(temp_y) > 0)// if number is valid then break
		{
			break;
		}
		cout << "Oops, looks like that entry didn't work. Try again: ";


	} while (true); // repeats until a valid number is entered

	max_y = stoi(temp_y); // assigns the string to the new grid y



	return(0);
}