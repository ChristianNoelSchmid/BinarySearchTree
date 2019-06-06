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

#include "term.h"


// Copies supplied Term
void Term::copy_from(Term & from) {

    name.copy_from(from.name);
    data_struct_rel.copy_from(from.data_struct_rel);
    definition.copy_from(from.definition);

}

// Compares the Term's name to a supplied CharString
int Term::compare(const CharString & name_of_other) {

    return name.compare(name_of_other, true);

}

// Compares the Term's name with another Term's name
int Term::compare(const Term & other) {

    return name.compare(other.name, true);

}

// Retrieves the name of the Term
char *Term::get_name() const { return name.to_char(); }

// Set's the Term name
void Term::set_name(CharString & from) {

    name.copy_from(from);

}

// Set's the Term data structure relation
void Term::set_data_struct_rel(CharString & from) {

    data_struct_rel.copy_from(from);

}

// Set's the Term definition
void Term::set_definition(CharString & from) {

    definition.copy_from(from);

}

// Displays the Term
void Term::display() {

    name.print("Name: ", "\n");
    data_struct_rel.print("Associated Data Structure: ", "\n");
    definition.print(">> ", "\n--\n");

}