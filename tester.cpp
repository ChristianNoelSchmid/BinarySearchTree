/*
 * Christian Schmid
 * CS163 - Data Structures
 * Program IV - tester.h
 * 
 * Definition for Tester class - tests all particular use cases
 * of a BiTree (BST). Also includes helper functions for the Tester.
 * 
 */

#include "tester.h"

// The main test loop
void Tester::test_loop() {

    introduction();
    test_tree();
    goodbye();

}

// Prints the introduction, with directions
void Tester::introduction() {

    using namespace std;
    clear_screen();
    cout << "Welcome to the Binary Tree searcher!\n"
         << "Here, you will test the usage of a Binary Search Tree, which will store\n"
         << "a collection of terms and definitions from the Carrano reading.\n";
    wait_for_enter();
    clear_screen();

    cout << "You will have the options to insert terms into the tree (sorted by name)\n"
         << "retrieve terms from the tree, either singly or by range, and remove elements\n"
         << "from the tree.";
    wait_for_enter();

    cout << "ARE YOU READY???\n\n";
    wait_for_enter();
    clear_screen();
            

}

// The primary tree testing loop: runs insertion, removal,
// and retrieval test loops
void Tester::test_tree() {

    using namespace std;
    bool repeat = true;
    
    while(repeat) {

        clear_screen();
        cout << "Tree height: " << bitree.get_height() << "\n"
             << "Tree is efficient: " << bitree.is_efficient() << "\n"
             << "--\n"
             << "Please choose an option (1-6):\n"
             << "1) Insert a New Term\n"
             << "2) Retrieve and Display Terms\n"
             << "3) Remove Term\n"
             << "4) Display Tree, Inorder\n"
             << "5) Display Tree, Breadth-first\n"
             << "6) Exit Program\n"
             << "--\n"
             << ">> ";

        int answer;
        cin >> answer; cin.ignore(100, '\n');

        if(answer == 1) insertion_loop();
        else if(answer == 2) retrieval_loop();
        else if(answer == 3) removal_loop();

        else if(answer == 4) { bitree.display_all(); wait_for_enter(); }
        else if(answer == 5) { bitree.display_breadth_first(); wait_for_enter(); }

        else repeat = false;

    }

    goodbye();

}

// Prompts User for information on new element to add, repeating
// if desired by User
void Tester::insertion_loop() {

    using namespace std;
    bool repeat = true;
    CharString char_str;
    Term new_term;

    while(repeat) {

        clear_screen();

        // Retrieve all necessary info from User, and
        // store into temp Term variable
        // Name
        cout << "Please enter the name of the new term: ";
        char_str.from_input(); new_term.set_name(char_str);

        // Associated Data Structure
        cout << "Please enter the associated data structure: ";
        char_str.from_input(); new_term.set_data_struct_rel(char_str);

        // Information about Term
        cout << "Finally, enter the information pertaining to the term:\n >>";
        char_str.from_input(); new_term.set_definition(char_str);

        // If insertion is unsuccessful (ie. it already exists) prompt User
        if(!bitree.insert(new_term)) cout << "Term \"" << new_term.get_name() << "\" already exists!\n";
        else cout << "Term \"" << new_term.get_name() << "\" inserted!\n";

        // Ask if User would like to enter again, returning to main loop if not
        cout << "Would you like to enter another term?\n"
             << "Y/N >> ";

        char answer; cin >> answer; cin.ignore(100, '\n');
        if(tolower(answer) != 'y') repeat = false;

    }

}

// Prompts User for a Term to retrieve from the BiTree, displaying either one
// or a range of Terms. Repeats if desired by User
void Tester::retrieval_loop() {

    using namespace std;
    bool repeat = true;

    while(repeat) {

        clear_screen();
        cout << "Would you like to retrieve a single element, or a range of elements?\n"
             << "Please choose an option (1-3):\n"
             << "1) Single\n"
             << "2) Range\n"
             << "3) Go Back\n"
             << "--\n"
             << ">> ";

        int input = 0; cin >> input; cin.ignore(100, '\n');

        // If Single display desired...
        if(input == 1) {

            CharString char_str;

            // Prompt User for Term to be retrieved
            cout << "Please enter the term you wish to retrieve: ";
            char_str.from_input();

            // Display Term. If Term not found, inform User
            if(!bitree.display(char_str))
                cout << "Term \"" << char_str.to_char() << "\" not found!\n";

            wait_for_enter();

        }

        // If range display desired..
        else if(input == 2) {

            CharString lower, upper;

            // Retrieve the lower-bound search and upper-bound search
            cout << "Please enter the lower bound you wish to search with: ";
            lower.from_input();

            cout << "Now enter the upper bound: ";
            upper.from_input();

            // Display the range - if no elements are found within range, inform the User
            if(!bitree.display_range(lower, upper)) 
                cout << "No terms found between \"" << lower.to_char() << "\" and \"" << upper.to_char() << "\"";

            wait_for_enter();

        }

        else repeat = false;

    }  

}

// Prompts User to remove an element from the BiTree,
// repeating if desired
void Tester::removal_loop() {

    using namespace std;
    bool repeat = true;

    CharString char_str;

    while(repeat) {

        clear_screen();

        // Retrieve the desired Term from User
        cout << "Please enter a term you wish to remove: ";
        char_str.from_input();

        // Remove the Term. If the Term is not found, inform the User
        if(!bitree.remove(char_str))
            cout << "Term \"" << char_str.to_char() << "\" not found!\n";

        // If Term was found, inform the User it has been removed
        else 
            cout << "Term \"" << char_str.to_char() << "\" removed!\n";
        
        wait_for_enter();

        // Ask if User would like to remove another term
        cout << "Would you like to remove another term?\nY/N >> ";
        char answer; cin >> answer; cin.ignore(100, '\n');

        if(tolower(answer) != 'y') repeat = false;

    } 

}

// Prints goodbye to the User
void Tester::goodbye() {

    clear_screen();
    std::cout << "Thanks, so much, for using the Binary Search Tree Program #4!\n"
              << "Please have a good day now!\n";

}

// Waits for User to hit ENTER
void wait_for_enter() {

    std::cout << "Press ENTER to continue...";
    std::cin.ignore(100, '\n');

}

// Clears the console screen
// Determines what OS is running and runs the
// Appropriate system command
void clear_screen() {

#ifdef _WIN32
	system("cls");
#elif _WIN64
	system("cls");
#else
	system("clear");
#endif

}