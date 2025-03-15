#include <iostream>
#include <fstream>
#include <functional>
#include "llrec.h"
using namespace std;

/**
 * Reads integers (separated by whitespace) from a file
 * into a linked list.
 *
 * @param[in] filename
 *  The name of the file containing the data to read
 * @return
 *  Pointer to the linked list (or NULL if empty or the
 *  file is invalid)
 */
Node* readList(const char* filename);

/**
 * Prints the integers in a linked list pointed to
 * by head.
 */
void print(Node* head);

/**
 * Deallocates the linked list nodes
 */
void dealloc(Node* head);


Node* readList(const char* filename)
{
    Node* h = NULL;
    ifstream ifile(filename);
    int v;
    if( ! (ifile >> v) ) return h;
    h = new Node(v, NULL);
    Node *t = h;
    while ( ifile >> v ) {
        t->next = new Node(v, NULL);
        t = t->next;
    }
    return h;
}

void print(Node* head)
{
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void dealloc(Node* head)
{
    Node* temp;
    while(head) {
        temp = head->next;
        delete head;
        head = temp;
    }
}

struct pred{
  bool operator()(int headVal){
    if(headVal%2 == 1) return true;
    return false;
  }
};

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cout << "Please provide an input file" << endl;
        return 1;
    }

    Node* head = readList(argv[1]);
    cout << "Original list: ";
    print(head);

    // Test out linked list code
    //Test for llpivot
    Node* small;
    Node* large;
    llpivot(head, small, large, 5);
    cout << "small is ";
    print(small);
    cout << "large is ";
    print(large);

    //Test for llfilter
    // pred c;
    // cout << "llfilter test starts" << endl;
    // head = llfilter(head, c);
    // cout << "Result is ";
    // print(head);	
    return 0;
}
