/*
 * Christian Schmid
 * CS163 - Data Structures
 * Program IV - bitree.h
 * 
 * Prototype info for BiTree class and BiNode struct
 */

#include <iostream>
#include <fstream>

#include "term.h"
#include "math.h"

// The BiNode contains a left and right BiNode *
struct BiVertex {

    // Constructor / Destructor
    // Constructor requires the Term being inserted
    BiVertex(Term & term);
    ~BiVertex();

    Term *data; // The term, with its assoc. data struct and def.
    BiVertex *left; // The left BiVertex (< data)
    BiVertex *right; // The right BiVertex (>= data)

};

// The BiTree: a binary search tree of Terms
// Allows insertion, removal, and retrieval of any Terms
// Retrieval displays the Term's definition
class BiTree {

    public:
        // Constructor / Destructor
        BiTree();
        ~BiTree();

        // Find the height of the deepest node in BiTree
        int get_height();
        // Test efficiency, based on height and node_count
        bool is_efficient();

        // Inserts a new Term into the BiTree, based on Term's name
        bool insert(Term & term);

        // Removes a Term from the list, using supplied CharString as key
        bool remove(const CharString & to_remove);

        // Retrieves and displays a single term from the BiTree, returning false 
        // if not found
        bool display(CharString & name_of_term);
        // Displays all Terms in BiTree. Returns false if BiTree is empty
        bool display_all();
        // Displays all Terms in BiTree, based on supplied range. Searches for
        // partial match on supplied CharStrings, and every Term in between.
        // (ie. "Ha"-"Lin" => {"HashTable", "HelloWorld", "Iguanas", "LinkedList"})
        bool display_range(CharString & start, CharString & end);
        // Display's the BiTree's elements, breadth-first, so that display precidence is
        // determined by the height of the vertex storing the element
        bool display_breadth_first();

    private:
        BiVertex *root; // The Root of the BiTree
        int vertex_count; // The # of BiNodes in the BiTree

        // Recursive private functions: called from their
        // public wrapper functions
        int get_height(BiVertex *current);
        bool is_efficient(BiVertex *current);
 
        bool insert(Term & term, BiVertex *& current);

        bool remove(const CharString & to_remove, BiVertex *& current);

        bool display(const CharString & term, BiVertex * current);
        void display_all(BiVertex *current);
        int display_range(CharString & start, CharString & end, BiVertex *current);

        int display_breadth_first(BiVertex *head, int current_height, int height);

        // Retrieves the inorder successor of the current BiNode.
        // Used for the removal of nodes (if necessary)
        // Requires BiNode** in order to make adjustments to the BiNode itself
        BiVertex **get_leftmost(BiVertex *& current);

        // Loads Term data from file. Expediates insertion process
        // (for testing/grading purposes)
        bool load_from(const char *filename);

};