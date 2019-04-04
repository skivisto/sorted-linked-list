// File:	sortedList.h
// Author:	Sam Kivisto
// Class:	CSIS 352
// Program:	Assignment 4
// Date:	3/17/2019

// Description
// This file contains the specification and implementation for the sortedList class.

#ifndef _SORTED_LIST_
#define _SORTED_LIST_

#include <stdexcept>
using std::out_of_range;
using std::logic_error;

namespace sortedListSpace{

enum sortType {ASCENDING, DESCENDING};

template<class Type>
struct node{
    
    Type data;
    node<Type> *link;
    
}; // node

template<class Type>
class sortedList{
    
    public:
        
        // Method: Default constructor
        // Description: Make a new, empty sortedList, with pointer set to NULL
        // and sort type set to default (ASCENDING)
        // Preconditions: None
        // Postconditions: count = 0, list = NULL, sort = ASCENDING
        // Input: None
        // Output: None
        explicit sortedList();
        
        // Method: Parameterized constructor
        // Description: Make a new sortedList 
        // Preconditions: None
        // Postconditions: count = 0, list = NULL, sort = s
        // Input: s (sortType)
        // Output: None
        explicit sortedList(sortType);
        
        // Method: Copy constructor
        // Description: Make a new sortedList identical to another one, for passing
        // sortedList objects as parameters
        // Preconditions: None
        // Postconditions: this sortedList is identical in content to otherList
        // Input: otherList (sortedList)
        // Output: None
        sortedList(const sortedList<Type>&);
        
        // Method: Destructor
        // Description: Delete all nodes from the list
        // Preconditions: None
        // Postconditions: sortedList has been destroyed and its memory freed
        // Input: None
        // Output: None
        ~sortedList();
        
        // Method: insertItem
        // Description: Adds a new node to the list; position depends on sort order
        // and the preexisting content of the list
        // Preconditions: None
        // Postconditions: sortedList has been destroyed and its memory freed
        // Input: item (Type)
        // Output: None
        void insertItem(Type);
        
        // Method: deleteItem
        // Description: Deletes the first occurence of itemToDelete; throws a logic_error if not in list
        // Preconditions: item exists within the list
        // Postconditions: One node has been deleted from the list
        // Input: item (Type)
        // Output: None
        void deleteItem(Type);
        
        // Method: deleteAll
        // Description: Deletes all nodes whose content matches item
        // Preconditions: item exists within the list
        // Postconditions: All nodes matching item have been deleted
        // Input: item (Type)
        // Output: None
        void deleteAll(Type);
        
        // Method: merge
        // Description: Adds every node in one list to another
        // Preconditions: None
        // Postconditions: Nodes have been added to this list
        // Input: otherList (sortedList)
        // Output: None
        void merge(const sortedList<Type>&);
        
        // Method: removeDuplicates
        // Description: Deletes every node that exists multiple times in the list
        // Preconditions: None
        // Postconditions: Nodes have been deleted, if neccesary
        // Input: None
        // Output: None
        void removeDuplicates();
        
        // Method: setOrder
        // Description: Changes the sort order, either from descending to ascending,
        // or from ascending to descending
        // Preconditions: None
        // Postconditions: sort has been changed and the list has been rearranged,
        // if needed
        // Input: newSort (sortType)
        // Output: None
        void setOrder(sortType);
        
        // Method: length
        // Description: Returns the number of items in the list
        // Preconditions: None
        // Postconditions: count has been returned
        // Input: None
        // Output: count (int)
        int length() const;
        
        // Method: traverse
        // Description: Calls the function pointed to by the function pointer on
        // each item of the list
        // Preconditions: list is not empty
        // Postconditions: None
        // Input: function (pointer to a function that does not return anything
        // and takes a pass-by-reference Type argument)
        // Output: None
        void traverse(void (*function) (Type&)) const;
        
        // Method: destroyList
        // Description: Destroys the list and every node inside
        // Preconditions: None
        // Postconditions: list has been destroyed: count = 0, list = NULL, sort = ASCENDING
        // Input: None
        // Output: None
        void destroyList();
        
        // Method: isEmptyList
        // Description: Determines whether the list is empty
        // Preconditions: None
        // Postconditions: true or false has been returned
        // Input: None
        // Output: true if first and last are NULL, otherwise false
        bool isEmptyList() const;
        
        // Method: isEmptyList
        // Description: Determines whether a given item is in the list
        // Preconditions: None
        // Postconditions: true or false has been returned
        // Input: toFind (Type)
        // Output: true if toFind is in list, false otherwise
        bool inList(Type) const;
        
        // Method: valueAt
        // Description: Returns the item at given index, throws out_of_range if
        // index is invalid
        // Preconditions: i is valid
        // Postconditions: item at index has been returned
        // Input: index (int)
        // Output: Type
        const Type& valueAt(int) const;
        
        // Operator: []
        // Description: Overrides the const indexing operator to prevent the user
        // from assigning values themselves
        // Preconditions: None
        // Input: index (int)
        // Output: <Type> at provided index
        const Type& operator[](int) const;
        
        // Operator: =
        // Description: Overrides the assignment operator between sortedLists
        // Preconditions: None
        // Input: otherList (sortedList<Type>)
        // Output: sortedList<Type>
        const sortedList<Type>& operator=(const sortedList<Type>&);
        
    private:
            
        int count;     // stores the number of elements in the list
        node<Type> *list; // pointer to the first node of the list
        sortType sort;  // stores the sort method used for this list
      
}; // sortedList

template<class Type>
sortedList<Type>::sortedList(){

    count = 0;
    list = NULL;
    sort = ASCENDING;
    
} // Default constructor

template<class Type>
sortedList<Type>::sortedList(sortType s){

    count = 0;
    list = NULL;
    sort = s;
    
} // Parameterized constructor

template<class Type>
sortedList<Type>::sortedList(const sortedList<Type>& otherList){

    node<Type> *other;   // node pointer for traversing the other list
    node<Type> *p;       // and one trailing for the new list
    node<Type> *copy;     // node pointer for copying nodes
    
    p = NULL;           // initialize all variables
    other = NULL;
    copy = NULL;
    count = otherList.count;
    sort = otherList.sort;
    
    if (otherList.list != NULL){  // if the other list is nonempty...
        other = otherList.list;
        copy = new node<Type>;  // copy the first node
        copy->data = other -> data;
        copy->link = p;
        list = copy;           // assign the list and trailing pointer to it
        p = copy;
        
        other = other->link;   // advance the otherList pointer
        while (other != NULL){ // while not at the end of the other list...
            copy = new node<Type>; // make a new node
            copy->data = other->data;
            p->link = copy;   // link the last item to this one
            other = other->link;  // advance both pointers
            p = p->link;
        } // loop
        p->link = NULL;  // set all pointers to null to prevent dangling
        p = NULL;        // pointers (even though they're about to be destroyed)
        other = NULL;
        copy = NULL;
    } // if
    
    else
        list = NULL;  // if the other list is empty, make this one empty.
    
} // Copy constructor

template<class Type>
sortedList<Type>::~sortedList(){
    
    destroyList();
    
} // Destructor

template<class Type>
void sortedList<Type>::insertItem(Type item){
    
    node<Type> *p;        // node pointer (p) and trailing pointer (q), for 
    node<Type> *q;        // traversing the list
    node<Type> *newNode;  // node that will be inserted
    newNode = new node<Type>();
    newNode->data = item;
    p = list;
    q = NULL;

    if (sort == ASCENDING){
        while (p != NULL && p->data < item){ // test every item except larger ones
            q = p;
            p = p->link;
        } // loop
    } // if ASCENDING
    
    else{
        while (p != NULL && p->data > item){
            q = p;
            p = p->link;
        } // loop
    } // else DESCENDING
    
    if (list == NULL){ // if the list is empty, this new item is now the list
        list = newNode;
        newNode->link = NULL;
    } // if
    
    else if (q == NULL && p != NULL){ // if the list has 1 item, and this is the
        list = newNode;      // new first item, connect the two and make list
        newNode->link = p;   // equal to this one
    } // else if
    
    else{ // otherwise, q must now point to this item
        q->link = newNode;
        newNode->link = p; // link the item to p
    } // else
    
    count++;
    newNode = NULL;
    p = NULL; // set pointers to null
    q = NULL;
    
} // insertItem

template<class Type>
void sortedList<Type>::deleteItem(Type itemToDelete){
    
    node<Type> *p;         // node pointer (p) and trailing pointer (q), for 
    node<Type> *q;         // traversing the list
    bool found;              // flag that determines whether the item was found
    
    p = list;
    q = NULL;
    found = false;

    while (!found && p != NULL){ // search the entire list or until a match is found
        if (p->data == itemToDelete)
            found = true;
        else{
            q = p;
            p = p->link;
        } // else
    } // loop
    
    if (found){
        if (q == NULL)
            list = list->link;
        else
            q->link = p->link;
        
        count--;
        delete p;   // delete the item
        p = NULL;   // set pointers to null
        q = NULL;
    } // if
    
    else
        throw logic_error("deleteItem failed, item not in list");
    
} // deleteItem

template<class Type>
void sortedList<Type>::deleteAll(Type item){
    
    node<Type> *p;        // node pointer (p) and trailing pointer (q), for 
    node<Type> *q;        // traversing the list
    bool found;             // flag that determines whether the item was found
    p = list;
    q = NULL;
    found = false;
    
    if (sort == ASCENDING){
        while (p != NULL && p->data <= item){  // for everything less than item
            if (p->data == item){ // if they have the same content
                found = true;
                if (q != NULL){
                    q->link = p->link;// set the last item's link to the one 
                                      // after p
                    delete p;
                    p = q->link;        // p is now p's old link
                    count--;
                } // if (q != NULL)
                else{
                    list = p->link; // set the start of the list to p's link
                    delete p;
                    p = list;
                    count--;
                } // else
            } // if (p->data == item)
            else{
                q = p;
                p = p->link;
            } // else
        } // loop
    } // if ASCENDING
    
    if (sort == DESCENDING){
        while (p != NULL && p->data >= item){  // for everything less than item
            if (p->data == item){ // if they have the same content
                found = true;
                if (q != NULL){
                    q->link = p->link;// set the last item's link to the one 
                                      // after p
                    delete p;
                    p = q->link;        // p is now p's old link
                    count--;
                } // if (q != NULL)
                else{
                    list = p->link; // set the start of the list to p's link
                    delete p;
                    p = list;
                    count--;
                } // else
            } // if (p->data == item)
            else{
                q = p;
                p = p->link;
            } // else
        } // loop
    } // if DESCENDING
    
    if (!found)
        throw logic_error("deleteAll failed, item not in list");
        
} // deleteAll

template<class Type>
void sortedList<Type>::merge(const sortedList<Type>& otherList){

    for (int i = 0; i < otherList.count; i ++)
        insertItem(otherList.valueAt(i));

} // merge

template<class Type>
void sortedList<Type>::removeDuplicates(){

    if (list != NULL){
        node<Type> *p;      // node pointer for traversing the list
        node<Type> *q;      // trailing node pointer
        q = list;   // if the list has one or zero items, there are no duplicates
        p = list->link; // therefore, start at item two
        while (p != NULL){
            if (p->data == q->data){
                q->link = p->link;
                delete p;
                p = q->link;
                count --;
            } // if ==
            else{
                q = p;
                p = p->link;
            } // else
        } // loop
        p = NULL; // prevent dangling pointers
        q = NULL;
    } // if
} // removeDuplicates

template<class Type>
void sortedList<Type>::setOrder(sortType newSort){

    if (sort != newSort){
        if (list != NULL){
            node<Type> *p;  // node pointer for list traversal
            sortedList<Type> temp; // copy list
            temp.sort = newSort;
            p = list;
            while (p != NULL){
                temp.insertItem(p->data); // copy every item into temp
                p = p->link; // advance p
            } // loop
            *this = temp; // temp is sorted properly, so assign this to temp
        } // if
        else
            sort = newSort; // list is null, so just change the sort type
    } // if 
} // setOrder

template<class Type>
int sortedList<Type>::length() const{

    return count;
    
} // length

template<class Type>
void sortedList<Type>::traverse(void (*function) (Type&)) const{

    node<Type> *n; // node pointer for list traversal
    n = list;
    while (n != NULL){
        function(n->data);
        n = n->link;
    } // loop
} // traverse

template<class Type>
void sortedList<Type>::destroyList(){

    node<Type> *n; // node pointer for deleting nodes
    n = list;
    while (n != NULL){
        list = n->link;  // destroy each node in the list, and advance list
        delete n;       // so at the loop's conclusion it will be null
        n = list;
    } // loop
    count = 0;
    sort = ASCENDING;
    n = NULL;    // prevent dangling pointer

} // destroyList

template<class Type>
bool sortedList<Type>::isEmptyList() const{

    if (count > 0)
        return false;
    
    else
        return true;
} // isEmptyList

template<class Type>
bool sortedList<Type>::inList(Type toFind) const{

    if (list == NULL) // if the list is empty, the item is not in it
        return false;
        
    else{
        node<Type> *p;      // node pointer for traversing list
        bool found;         // flag tracking if toFind is found
        found = false;
        p = list;
        while (p != NULL){ // iterate over the list and test every item for
            if (p->data == toFind) // equivalence
                found = true;
            p = p->link;
        } // loop
        return found;
    } // else
} // inList

template<class Type>
const Type& sortedList<Type>::valueAt(int index) const{

    if (list == NULL || index < 0 || index > (count-1))
        throw out_of_range("index is not valid");
        
    else{
        node<Type> *p; // node pointer for list traversal
        p = list;
        for (int i = 0; i < index; i++) // get p to the provided index 
            p = p->link;
        return p->data; // return the item
    } // else
} // valueAt

template<class Type>
const Type& sortedList<Type>::operator[](int index) const{

    if (list == NULL || index < 0 || index > count -1)
        throw out_of_range("index is not valid");
    
    node<Type> *p; // node pointer for list traversal
    p = list;
    for (int i = 0; i < index; i++) // move p to provided index
        p = p->link;
    return p->data; // return item

} // operator[]

template<class Type>
const sortedList<Type>& sortedList<Type>::operator=(const sortedList<Type>& otherList){

    if (this != &otherList){
        destroyList();
        
        node<Type> *other;   // node pointer for traversing the other list
        node<Type> *p;       // and one trailing for the new list
        node<Type> *copy;     // node pointer for copying nodes
    
        p = NULL;           // initialize all variables
        other = NULL;
        copy = NULL;
        count = otherList.count;
        sort = otherList.sort;
    
        if (otherList.list != NULL){  // if the other list is nonempty...
            other = otherList.list;
            copy = new node<Type>;  // copy the first node
            copy->data = other -> data;
            copy->link = p;
            list = copy;           // assign the list and trailing pointer to it
            p = copy;
        
            other = other->link;   // advance the otherList pointer
            while (other != NULL){ // while not at the end of the other list...
                copy = new node<Type>; // make a new node
                copy->data = other->data;
                p->link = copy;   // link the last item to this one
                other = other->link;  // advance both pointers
                p = p->link;
            } // loop
            p->link = NULL;  // set all pointers to null to prevent dangling
            p = NULL;        // pointers (even though they're about to be destroyed)
            other = NULL;
            copy = NULL;
        } // if
    
        else
            list = NULL;  // if the other list is empty, make this one empty.
    } // if
    return *this;
} // operator=

} // sortedListSpace

#endif
