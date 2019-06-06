/*
 * Christian Schmid
 * CS163 - Data Structures
 * Program IV - tester.h
 * 
 * Prototype for Tester class - tests all particular use cases
 * of a BiTree (BST). Also includes helper functions for the Tester.
 * 
 */

#include <iostream>
#include "bitree.h"

class Tester {

    public:
        // The test loop - run in main
        void test_loop();

    private:
        // The BiTree used in the testing process
        BiTree bitree;

        // Prints the introduction, with directions
        void introduction();
        // The primary tree testing loop: runs insertion, removal,
        // and retrieval test loops
        void test_tree();
        // Prints goodbye to the User
        void goodbye();

        // Prompts User for information on new element to add, repeating
        // if desired by User
        void insertion_loop();

        // Prompts User to remove an element from the BiTree,
        // repeating if desired
        void removal_loop();

        // Prompts User for a Term to retrieve from the BiTree, displaying either one
        // or a range of Terms. Repeats if desired by User
        void retrieval_loop();
};

// Waits for User to hit ENTER
void wait_for_enter();

// Clears the console screen
// Determines what OS is running and runs the
// Appropriate system command
void clear_screen();