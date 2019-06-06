/*
 * Christian Schmid
 * CS163 - Data Structures
 * Program IV - term.h
 * 
 * The Term class holds all the information pertaining to
 * a term and its definition from the Carrano text
 * the primary element in the BiTree for this program
 * 
 */

#include "char_string.h"

class Term {

    public:
        // Compares two Terms / a Term's name and a CharString
        int compare(const Term & other);
        int compare(const CharString & name_of_other);

        // Getter for name of the Term, returning a const char array
        char *get_name() const;

        // Setters
        void set_name(CharString & from);
        void set_data_struct_rel(CharString & from);
        void set_definition(CharString & from);

        // Copies supplied Term
        void copy_from(Term & from);

        // Displays Term
        void display();

    private:
        CharString name;
        CharString data_struct_rel;
        CharString definition;

};