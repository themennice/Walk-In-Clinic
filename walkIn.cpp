/*
 * WalkIn.cpp
 *
 * Program Description: Terminal Application for Walk-In clinic receptionists that allows to
 *                      add, remove, modify, search for and print patients' data.
 * Program Invariant: Data collection with the following characteristics:
 *                   - Each Patient is unique (no duplicates).
 *                   - The capacity is corresponds to MAX_ELEMENTS
 *                   - CareCard number must only be 10 digits
 *
 * Author:  Denys Dziubii and Xubin Wang
 * Date: January 22, 2019
 */

#include<iostream>
#include"Patient.h"
#include"List.h"

using namespace std;

int main()
{
    List patients; //create a List with 5 Patients

    for(;;) //keep looping until someone exits the program
    {
        // create an acceptable user interface
        cout << endl << "------------------------------------------------" << endl;
        cout << "\033[1;31m Welcome to The Walk-In Clinic Patient System!\033[0m\n" << flush;
        cout << endl << "What would you like to do now?";
        cout << endl << "------------------------------------------------" << endl;
        cout << "To \033[1;35menter\033[0m a new patient into the system:  \033[1;36mEnter 1\033[0m" << endl;
        cout << "To \033[1;32mremove\033[0m patients from the system:      \033[1;34mEnter 2\033[0m" << endl;
        cout << "To \033[1;33msearch\033[0m for an existing patient:       \033[1;36mEnter 3\033[0m" << endl;
        cout << "To \033[1;35mmodify\033[0m a patient's record:            \033[1;34mEnter 4\033[0m" << endl;
        cout << "To \033[1;32mprint\033[0m the list of all patients:       \033[1;36mEnter 5\033[0m" << endl;
        cout << "------------------------------------------------" << endl;
        cout << "To \033[1;33mexit\033[0m the program:                     \033[1;31mEnter 6\033[0m" << endl;
        cout << "------------------------------------------------" << endl;
        cout << "Your choice: \033[1;36m";


        string n; // string variable for user input
        getline(cin >> ws, n); //use getline isntead of cin >>, so that we could store strings and not get errors
        cout << "\033[0m"; //terminate colorful input

        while (n < "1" || n > "6") // if input is out of range, give another chance
        {
            cout << "Wrong input, try again.";
            cout << endl << "Your choice: \033[1;36m";
            getline(cin >> ws, n);
            cout << "\033[0m";
        }

        if(n == "1") // case 1: insert a new Patient
        {
            if (patients.getElementCount() >= 5) // check if list is full
            {
                cout << "\033[2J\033[1;1H"; // clear the screen before proceeding
                cout << "The list is full. Please come back later!" <<endl;
                cout << "Redirecting back to the main menu." <<endl;
                continue; // send to the beginning of the for loop
            }

            string name, phone, email, address, careCard; // initialise Patient details
            do
            {
                cout << "Please Enter The 10-digit Care Card Number:" << endl;
                getline(cin >> ws, careCard);
            }while (careCard.length() != 10); // check if CareCard is 10-digit

            if (patients.duplicate(careCard) == true) // check for duplicates using a newly created function
            {
                cout << "\033[2J\033[1;1H"; // clear the scree
                cout << "The Patient entered is Already in the Line. Duplicate." << endl;
                continue; // send back to the for loop
            }

            // if successful, proceed to recording new patient's information using getline and corresponding setters
            Patient newOne(careCard);
            cout << "Please Enter The Name:" << endl;
            getline(cin, name);
            if(name == "")
                newOne.setName("To be entered");
            else
                newOne.setName(name);

            cout << "Please Enter The Phone Number:" << endl;
            getline(cin, phone);
            if(phone == "")
                newOne.setPhone("To be entered");
            else
                newOne.setPhone(phone);

            cout << "Please Enter The Address:" << endl;
            getline(cin, address);//cin >> address;
            if(address == "")
                newOne.setAddress("To be entered");
            else
                newOne.setAddress(address);

            cout << "Please Enter The Email:" << endl;
            getline(cin, email);
            if(email == "")
                newOne.setEmail("To be entered");
            else
                newOne.setEmail(email);

            patients.insert(newOne); // insert a new Patient into the system, please see the List.cpp for insert implementation
        }

        else if(n == "2") // Case 2: Remove a Patient or remove all patients from the system
        {
            if(patients.getElementCount()== 0) // check if list is empty
            {
                cout << "\033[2J\033[1;1H";
                cout << "The list is empty, nothing to be removed." << endl;
                continue;
            }

            cout << "Would you like to remove one Patient? (y/n)" << endl;// ask if to remove one Patient or more
            string response;
            getline(cin, response);

            if (response == "y" || response == "yes" ||  response == "Yes" ||  response == "YES" ||  response == "Y")
            {
                string careCard;
                do
                {
                    cout << "Please Enter Your Care Card Number with 10 digits" << endl;
                    getline(cin >> ws, careCard);
                }while (careCard.length() != 10);

                if (patients.duplicate(careCard) == false) // call the duplicate function to see if the patient is in the system
            	{   // if returned false, the duplicate doesn't exist, so the patient cannot be searched for.
                	cout << "\033[2J\033[1;1H";
                	cout << "This Patient is not in the system." << endl;
                	continue;
            	}

                Patient toBeRemove(careCard);// after getting Care Card number proceed to removing
                if(patients.remove(toBeRemove))// check if it was removed the patient
                {
                    cout << "\033[2J\033[1;1H";
                    cout << "The Patient was removed successfully." << endl;
                }
                else //otherwise, we went through the list and did not see the needed carecard, so the patient isn't in the system
                {
                    cout << "\033[2J\033[1;1H";
                    cout << "The given patient is not present in the system." << endl;
                }
            }

            // the step needed to remove all Patients, see below
            else if(response == "n" || response == "no" ||  response == "No" ||  response == "NO" ||  response == "N")
            {
                    cout << "If you would like to remove all Patients:\033[1;36mEnter All\033[0m" << endl << "Or press any key to go back to the main menu." << endl;
                    string ans;
                    getline(cin, ans);

                    if (ans=="All")
                    {
                        patients.removeAll(); // call function remove all
                        cout << "\033[2J\033[1;1H";
                        cout << "All Patients were removed successfully." << endl;
                    }
                    else // if any other answer, go back to the beginning of the for loop
                    {
                        cout << "\033[2J\033[1;1H"; // clear the screen
                        cout << "None of the patients were removed. Enter 5 to print the list." << endl;
                        continue;
                    }
            }
            else
            {
                cout << "\033[2J\033[1;1H";
                cout << "Invalid input, going back to the main menu." << endl;
                continue;
            }

        }

        else if(n == "3") // Case 3: search for a given Patient by carecard number
        {
            if(patients.getElementCount()== 0) // check if list is empty
            {
                cout << "\033[2J\033[1;1H";
                cout << "The list is empty, nothing to be searched for." << endl;
                continue;
            }

            string careCard;
            do
            {
                cout << "Please Enter Your Care Card Number with 10 digits" << endl;
                getline(cin >> ws, careCard);
            }while (careCard.length() != 10);// check if it is 10 and store the card number
            cout << endl;

            if (patients.duplicate(careCard) == false) // call the duplicate function to see if the patient is in the system
            {   // if returned false, the duplicate doesn't exist, so the patient cannot be searched for.
                cout << "\033[2J\033[1;1H";
                cout << "This Patient is not in the system." << endl;
                continue;
            }

            Patient toSearch(careCard); // since we know the Patient is in the system, we call the search function to find it
            Patient value = *patients.search(toSearch); // store a pointer to the searched Patient and output it below
            cout << value << "." << endl;

        }

        else if(n == "4") // Case 4: modify Patient's information such as Name, Address, Phone, email, except for CARECARD
        {
            if(patients.getElementCount()== 0) // check if the list is empty
            {
                cout << "\033[2J\033[1;1H";
                cout << "The list is empty, nothing to be modified." << endl;
                continue;
            }

            string careCard;
            do
            {
                cout << "Please Enter Your Care Card Number with 10 digits" << endl;
                getline(cin >> ws, careCard);
            }while (careCard.length() != 10);

            if (patients.duplicate(careCard) == false) // call the duplicate function to see if the patient is in the system
            {   // if returned false, the duplicate doesn't exist, so the patient cannot be searched for.
                cout << "\033[2J\033[1;1H";
                cout << "This Patient is not in the system." << endl;
                continue;
            }
            string change;

            // a label is an address, it comes in handy below, when we want to ask the receptionist if they want to modify anything else
            label: cout << "What Information Would You Like to Modify for the Patient?" << endl;
            cout << "Name, Address, Email or Phone ?" << endl;
            getline(cin, change);

            while(change != "Name" && change != "Address" && change != "Email" && change != "Phone") // added robustness
            {
                cout << "Please Enter Again Correctly" << endl;
                getline(cin, change);
            }

            bool flag = true;
            do
            {
                if(change == "Name") //different cases depending on the desirable value to change
                {
                    string toChange;
                    cout << "Please Enter New Name Correctly" << endl;
                    getline(cin >> ws, toChange);
                    Patient *pat = patients.search(careCard); // use a pointer to the needed patient to modify in the next line
                    pat->setName(toChange);
                    cout << "\033[2J\033[1;1H"; // clear the screen for improved user experience
                    cout << "Name changed successfully!" << endl;
                }
                else if(change == "Address") // similar approach to the one above, similar comments
                {
                    string toChange;
                    cout << "Please Enter New Address Correctly" << endl;
                    getline(cin >> ws, toChange);
                    Patient *pat = patients.search(careCard);
                    pat->setAddress(toChange);
                    cout << "\033[2J\033[1;1H";
                    cout << "Address changed successfully!" << endl;
                }
                else if(change == "Email")
                {
                    string toChange;
                    cout << "Please Enter New Email Correctly" << endl;
                    getline(cin >> ws, toChange);
                    Patient *pat = patients.search(careCard);
                    pat->setEmail(toChange);
                    cout << "\033[2J\033[1;1H";
                    cout << "Email changed successfully!!" << endl;
                }
                else
                {
                    string toChange;
                    cout << "Please Enter New Phone Number Correctly" << endl;
                    getline(cin >> ws, toChange);
                    Patient *pat = patients.search(careCard);
                    pat->setPhone(toChange);
                    cout << "\033[2J\033[1;1H";
                    cout << "Phone Number changed successfully!!" << endl;
                }

                cout << "Would you like to change anthing alse? (y/n)" << endl; // ask if they would like to change anything else within this Patient
                string answer;
                getline(cin >> ws, answer); // record the answer

                if(answer == "y" || answer == "yes" ||  answer == "Yes" ||  answer == "YES" ||  answer == "Y")
                    goto label; // jump to the label mentioned earlier and ask what the user would like to modify again
                else if (answer == "n" || answer == "no" ||  answer == "No" ||  answer == "NO" ||  answer == "N")
                    flag = false;// set flag to false if it is a "no" and thus the loop breaks
                else
                {
                    cout << "\033[2J\033[1;1H";
                    cout << "Couldn't understand your input, going back to the menu." << endl; // case for invalid input
                    flag = false;
                }


            } while(flag);
        }

        else if (n == "5") // Case 5: print out the list of Patients
        {
            cout << endl << "\033[1;36mYour list:\033[0m" << endl;//the numbers and symbols are for color codes to improve use experience
            patients.printList(); // call print list function
        }

        else if (n == "6") // Case 6: the user would like to exit the program
            goto finish; // use another label to jump to the end of the program and terminate it subsequently

        // ask if the user wants to go back to the main menu at the end of each action
        cout << endl << "Would you like to go back to the menu page? (\033[1;32my/n\033[0m)" << endl;
        string answer;
        getline(cin >> ws, answer);
         // perform the action depending on the answer
        if(answer == "y" || answer == "yes" ||  answer == "Yes" ||  answer == "YES" ||  answer == "Y")
        {
            cout << "\033[2J\033[1;1H";
            continue;
        }
         else if (answer == "n" || answer == "no" ||  answer == "No" ||  answer == "NO" ||  answer == "N")
            break;
        else
        {
            cout << "\033[2J\033[1;1H";
            cout << "Couldn't understand your input, going back to the menu." << endl;
            continue;
        }

        cout << endl << endl << endl;
    }

    finish: cout << endl << "\033[1;36mSee you!\033[0m"<< endl << endl; //say bye to the user

    return 0;
}
