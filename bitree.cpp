/*
 * Christian Schmid
 * CS163 - Data Structures
 * Program IV - bitree.h
 * 
 * Implementation for BiTree class and BiVertex struct
 */

#include "bitree.h"

BiVertex::BiVertex(Term & term) {

    // Copy the supplied Term, and
    // insert the copied Term into the Vertex
    Term *new_term = new Term();
    new_term->copy_from(term);

    data = new_term;
    left = NULL;
    right = NULL; 

}

BiVertex::~BiVertex() {

    delete data;
    delete left;
    delete right;

}

/* *************************************
 * BITREE
 * *************************************
 */

/* PUBLIC FUNCTIONS ********************
*/
// Constructor / Destructor
BiTree::BiTree() {

    root = NULL;
    vertex_count = 0;

    // Prompt the User to open either the balanced tree file, the unbalanced tree file
    // or start with an empty tree
    int input;
    using namespace std;
    cout << "Would you like to import a balanced tree, unbalanced tree, or empty tree?\n"
         << "1) Balanced\n"
         << "2) Unbalanced\n"
         << "3) Empty\n"
         << ">> ";

    cin >> input; cin.ignore(100, '\n');

    if(input == 1) load_from("terms_balanced.dat");
    else if(input == 2) load_from("terms_unbalanced.dat");

}

BiTree::~BiTree() {

    delete root;

}

// Find the height of the deepest node in BiTree
int BiTree::get_height() {
    
    return get_height(root);

}

// Test efficiency, based on height and node_count
bool BiTree::is_efficient() {

    // The margin for the difference between height and full height    
    static int margin = 1;

    // Find the difference between the true vertex count, and what
    // a full tree vertex count would be
    int diff = abs(
            (log2(vertex_count) + 1) - get_height()
        );

    return diff <= margin;

}

// Inserts a new Term into the BiTree, based on Term's name
bool BiTree::insert(Term & term) {
    
    return insert(term, root);

}

// Removes a Term from the list, using supplied CharString as key
bool BiTree::remove(const CharString & to_remove) {
    
    return remove(to_remove, root);

}

// Retrieves and displays a single term from the BiTree, returning false 
// if not found
bool BiTree::display(CharString & name_of_term) {

    return display(name_of_term, root);

}

// Displays all Terms in BiTree. Returns false if BiTree is empty
bool BiTree::display_all() {
    
    if(root == NULL) return false;
    
    display_all(root);
    return true;

}

// Displays all Terms in BiTree, based on supplied range. Searches for
// partial match on supplied CharStrings, and every Term in between.
// (ie. "Ha"-"Lin" => {"HashTable", "HelloWorld", "Iguanas", "LinkedList"})
bool BiTree::display_range(CharString & start, CharString & end) {
    
    if(root == NULL) return false;
    else if(display_range(start, end, root) == 0) return false;

    return true;

}

// Displays the whole BiTree breadth-first
// Mostly used for debugging - function traverses *height* number of times
// O(h) where "h" is height
bool BiTree::display_breadth_first() {

    // First retrieve the height of the Tree
    int height = get_height();
    // The current iteration
    int count = 0;

    std::cout << "\nBreadth-first display: \n";

    // If root is NULL simply note so and return
    if(root == NULL) {
        std::cout << "Height 1 (Root): NULL";
        return false;
    }

    else std::cout << "Height 1 (Root): " << root->data->get_name() << "\n\n";

    for(int i = 1; i < height; ++i) {

        std::cout << "Height " << i + 1 << ":\n";
        count += display_breadth_first(root, 0, i);
        std::cout << std::endl;

    }

    return count;

}


/* PRIVATE FUNCTIONS ********************
*/
// Traverses vertex, determining which side is higher
// and returning the height
int BiTree::get_height(BiVertex *current) {

    if(current == NULL) return 0;
    int height_left = get_height(current->left) + 1;
    int height_right = get_height(current->right) + 1;

    return height_left > height_right ? height_left : height_right;
    
}

// Traverses vertices until leaf is found. Creates new node with
// supplied Term
bool BiTree::insert(Term & term, BiVertex *& current) {

    // If current BiVertex is NULL, assign it the term
    // and return true
    if(current == NULL) {

        current = new BiVertex(term);
        ++vertex_count;
        return true;

    }

    else {

        // Retrieve the comparison of the two term names
        // Current's data and the term being entered
        int cmp_names = term.compare(*(current->data));

        // Return false if names are the same - multiple entries of same term
        // cannot be entered
        if(cmp_names == 0) return false;
        
        // If not, return the next recursion
        else return insert(
            term,
            cmp_names < 0 ? current->left : current->right
        );
    }

}

// Traverses vertices, comparing names with supplied CharString. If
// found, deletes element
bool BiTree::remove(const CharString & to_remove, BiVertex *& current) {

    // If root is NULL, Term was not found in BiTree: return false
    if(current == NULL) return false; 

    else {

        int cmp = current->data->compare(to_remove);

        // If comparison between current->data and to_remove are < or >
        // Term has not been reached -> continue traversal
        if(cmp < 0) return remove(to_remove, current->right);
        else if(cmp > 0) return remove(to_remove, current->left);

        // If Term has been reached, remove
        else {

            // Because current's data is being removed, deallocate now
            // This will ensure deletion even if the node isn't deleted
            delete current->data;

            // Simple #1 - if current is a leaf, simply delete
            if(current->left == NULL && current->right == NULL) {

                delete current;
                current = NULL;

            }

            // If there is one child, simply replace current with that child
            else if(current->left == NULL || current->right == NULL) {

                // Assign temp * to current
                BiVertex *temp = current;
                // Move current down to child BiVertex
                current = (current->left == NULL) ? current->right : current->left;

                // Disconnect temp (previously current) and delete
                temp->left = temp->right = NULL;
                delete temp;

            }

            // If there are two children
            else {

                // But if the right child has no left children
                // copy right to current, set current to right's next,
                // and delete right
                BiVertex *right = current->right;
                if(right->left == NULL) {

                    current->data = right->data;
                    current->right = right->right;

                    // Set right's data to NULL, so the data isn't deleted
                    // when right is
                    right->data = NULL;
                    right->right = NULL;
                    delete right;

                }

                // If right has left and right children, find the left-most
                // child of right, copy it's contents to current, then delete the node,
                // connecting it's previous and right children
                else {

                    BiVertex **leftmost = get_leftmost(current->right);

                    current->data = (*leftmost)->data;
                    (*leftmost)->data = NULL;

                    BiVertex *temp = *leftmost;
                    *leftmost = (*leftmost)->right;

                    temp->right = NULL;
                    delete temp;

                }

            }

            --vertex_count;
            return true;

        }

    }

}

// Traverses BiTree until supplied element is found and displayed,
// returns false if end of BiTree is reached with no match (ie. Term doesn't exist)
bool BiTree::display(const CharString & term, BiVertex * current) {

    if(current != NULL) {

        // Store comparison
        int cmp = current->data->compare(term);

        // If equal
        if(cmp == 0) {

            current->data->display();
            return true;

        }

        // If not equal, traverse down to appropriate child
        else if(cmp > 0) return display(term, current->left);
        else return display(term, current->right);

    }

    else return false;

}

// Recursive display of all vertices of current
// BiNode, inorder
void BiTree::display_all(BiVertex *current) {

    if(current != NULL) {

        display_all(current->left);
        current->data->display();
        display_all(current->right);

    }

}

// Traverses BiTree inorder, displaying all elements that
// fall within range of supplied CharStrings
int BiTree::display_range(CharString & start, CharString & end, BiVertex *current) {

    if(current == NULL) return 0;

    int count = display_range(start, end, current->left);
    
    int cmp_start = current->data->compare(start);
    int cmp_end = current->data->compare(end);

    if(cmp_start >= 0 && cmp_end <= 0) { 

        current->data->display();
        ++count;

    }

    count += display_range(start, end, current->right);

    return count;

}

// Retrieves the left-most child of the current BiVertex.
// Used for the removal of nodes (if necessary)        
// Defined "get_leftmost" rather than "get_inorder_successor" because the
// function does not, technically, retrieve the inorder successor of ANY BiVertex.
// It simply retrieves the left-most child, which, in the case of removal, is
// effectively the same as the inorder successor.
// Requires BiVertex** in order to make adjustments to the BiVertex itself
BiVertex **BiTree::get_leftmost(BiVertex *& current) {

    if(current->left == NULL) return &current;

    else return get_leftmost(current->left);

}

// Loads Term data from file. Expediates insertion process
// (for testing/grading purposes)
bool BiTree::load_from(const char *filename) {

    static int MAX_STR = 255;

    // Open the file with the provided name
    std::ifstream file_in = std::ifstream(filename);

    // Test validity of file: was is opened, and is there data in it?
    if(file_in) file_in.peek();

    CharString char_str; char str[MAX_STR];

    // While file is valid and end isn't reached
    while(file_in && !file_in.eof()) {

        Term term;

        file_in.get(str, MAX_STR, '|');
        file_in.ignore(MAX_STR, '|');

        char_str.copy_from(str);
        term.set_name(char_str);

        file_in.get(str, MAX_STR, '|');
        file_in.ignore(MAX_STR, '|');

        char_str.copy_from(str);
        term.set_data_struct_rel(char_str);

        file_in.get(str, MAX_STR, '\n');
        file_in.ignore(MAX_STR, '\n');
        
        char_str.copy_from(str);
        term.set_definition(char_str);

        insert(term); 

    }

    // If, during the process, the file was made invalid, return false
    if(!file_in) return false;

    // If not, close it, and return true
    else {

        file_in.close();
        return true;

    }

}

// Displays the whole tree, breadth-first. Useful for debugging
int BiTree::display_breadth_first(BiVertex *current, int current_height, int height) {

    if(current == NULL) return 0;

    using namespace std;
    if(current_height + 1 == height) {

        if(current->left != NULL) 
            cout << current->left->data->get_name() << " - " << current->data->get_name() << " left child\n";

        if(current->right != NULL) 
            cout << current->right->data->get_name() << " - " << current->data->get_name() << " right child\n";

    }


    return 1 + display_breadth_first(current->left, current_height + 1, height)
             + display_breadth_first(current->right, current_height + 1, height);

}