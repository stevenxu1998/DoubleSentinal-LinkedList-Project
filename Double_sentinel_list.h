/*****************************************
 * UW User ID:  sfxu
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#include <iostream>
#include "Exception.h"

template <typename Type>
class Double_sentinel_list {
	public:
		class Double_node {
			public:
				Double_node( Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr );

				Type value() const;
				Double_node *previous() const;
				Double_node *next() const;

				Type         node_value;
				Double_node *previous_node;
				Double_node *next_node;
		};

		Double_sentinel_list();
		Double_sentinel_list( Double_sentinel_list const & );
		Double_sentinel_list( Double_sentinel_list && );
		~Double_sentinel_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Double_node *begin() const;
		Double_node *end() const;
		Double_node *rbegin() const;
		Double_node *rend() const;

		Double_node *find( Type const & ) const;
		int count( Type const & ) const;

		// Mutators

		void swap( Double_sentinel_list & );
		Double_sentinel_list &operator=( Double_sentinel_list );
		Double_sentinel_list &operator=( Double_sentinel_list && );

		void push_front( Type const & );
		void push_back( Type const & );

		void pop_front();
		void pop_back();

		int erase( Type const & );

	private:
		Double_node *list_head;
		Double_node *list_tail;
		int list_size;

		// List any additional private member functions you author here
	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
// Updated the initialization list here
list_head( nullptr ),//set everything to a default value
list_tail( nullptr ),
list_size( 0 )
{
    //This constructor creates a new empty sentinel list
	Double_node *sentinal1 = new Double_node();//Declaring 2 instances of pointers (type Double_node)
	Double_node *sentinal2 = new Double_node();//The 1st instance is for the sentinal head and the 2nd instance is for the sentinal tail
	sentinal1->node_value = 1998;//set an arbitraty value to each sentinal because it's not important
	sentinal2->node_value = 1999;
	// Get these pointed to each other...
	list_head = sentinal1;//point the list_head node to the 1st instance of the sentinal
	list_tail = sentinal2;//point the list_tail node to the 2nd instance of the sentinal
    sentinal1->next_node = sentinal2;//Since this is a double sentinel linked list, get the next node of the 1st sentinal to point to the 2nd sentinal
    sentinal2->previous_node = sentinal1;//Get the previous node of the 2nd sentinal (tail sentinal) to point to the 1st sentinel (head sentinal)
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
// Updated the initialization list here
list_head( nullptr ),//set everything to a default value
list_tail( nullptr ),
list_size( 0 )
{
	// This copy constructor creates a empty sentinel list (just like the constructor above) and then use push_back to add all
	// the nodes in list to this list from the original list
    Double_node *sentinal11 = new Double_node();//Declaring 2 instances of pointers (type Double_node)
    Double_node *sentinal12 = new Double_node();//The 1st instance is for the sentinel head and the 2nd instance is for the sentinal tail
    sentinal11->node_value = 1990;//set an arbitraty value to each sentinel because it's not important
    sentinal12->node_value = 1991;
    list_head = sentinal11;//point the list_head node to the 1st instance of the sentinel
    list_tail = sentinal12;//point the list_tail node to the 2nd instance of the sentinel
    sentinal11->next_node = sentinal12;//Since this is a double sentinel linked list, get the next node of the 1st sentinal to point to the 2nd sentinal
    sentinal12->previous_node = sentinal11;//Get the previous node of the 2nd sentinal (tail sentinal) to point to the 1st sentinel (head sentinal)
    if (list.list_size == 0)//if original size of the linked list contains nothing (i.e. only the head and tail sentinals)
    {
        return;//then there's no need to copy anything because the copy list is already done
    }
    else//if original size of the linked list contains something (i.e. more than just the head and tail sentinals)
    {
        list_size = 0;//initialize the copy constructor's list size to zero
        for (Double_node *pointer = list.begin() ; pointer != list.end(); pointer = pointer ->next_node)//traverse through the original list
        {
            push_back(pointer->node_value);//while traversing through the original list, add all the node values to the copied list from front to back
        }
    }

}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
// Updated the initialization list here
list_head( nullptr ),//set everything to a default value
list_tail( nullptr ),
list_size( 0 )
{
    //First, this function changes the previous pointer of the head sentinel to point to a new list_head
    //And this function does the same with the next pointer of the tail sentinel to point to a new list_tail
    //Secondly it makes the next pointer of the new list_head point to the head sentinel
    //And it makes the previous pointer of the new list_tail to point to the tail sentinel
    swap(list);//swap the original list with the new list
}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
    //This destructor will delete every single node in the linked list including the head and tail sentinels
    while (!empty())//check if the double sentinel list is empty (i.e. are there any sentinels left?)
    {
        pop_front();//delete the first sentinel in the list using the method pop_front
    }
    //at the end of this while loop everything, will be deleted except for the list_head and the list_tail so delete both of those too
    delete list_head;//delete list_head and whatever also delete whatever it is pointing to (i.e. head sentinel)
    delete list_tail;//delete list_tail and whatever also delete whatever it is pointing to (i.e. tail sentinel)
}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
	return list_size;//This function return the size of the list (i.e. number of sentinels not including the head and tail sentinels)
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
	return (list_size == 0);//This function checks if the list is empty by seeing if list_size is 0
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
    //This function will return value at the front of the linked list
    if (list_size == 0)//if the list is empty
    {
        throw underflow();//throw an exception
    }
    else//if the list is not empty
    {
        return list_head->next_node->node_value;//return the value of the first sentinel (i.e. right after the head sentinel)
    }
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
    //This function will return value at the back of the linked list
    if (list_size == 0)//if the list is empty
    {
        throw underflow();//throw an exception
    }
    else//if the list is not empty
    {
        return list_tail->previous_node ->node_value;//return the value of the last sentinel (i.e. right before the tail sentinel)
    }
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
	return list_head -> next();//returns the address stored by the next pointer of list_head (i.e. address of the 1st item on the list)
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
	return list_tail;//return the tail sentinel (where ever list_tail points to)
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
	return list_tail -> previous();//returns the address stored by the previous pointer of list_tail (i.e. address of the last item on the list)
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
    return list_head;//return the head sentinel (where ever list_head points to)
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {
    //This function will find the 1st occuring node with a given integer and return its address
    //Finding the address of where the 1st node in the list with the number is
    for (Double_node *pointer = begin() ; pointer != end(); pointer = pointer ->next_node)//Traverse through the entire list
    {
        if (pointer ->value() == obj)//if the data/node_value is equal to what the user wants
        {
            return pointer ->previous_node ->next_node;//return the address of where the 1st node that stores this value is
        }
    }
    return end();//if after traversing through the entire loop, and the requested number still can't be found, return end();
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
    //This function counts how many particular numbers there are in the list
    int counter =0;//initialize a counter to zero
    for (Double_node *pointer = begin() ; pointer != end(); pointer = pointer ->next_node)//traverse through the whole list
    {
        if (pointer->node_value == obj)//if the value in the pointer is equal to the requested number
        {
            counter++;//increment counter if the value in the pointer is equal to the requested number
        }
    }
	return counter;//After traversing through the list, return the number times a number appears in the linked list
}

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
	// This is done for you
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> &&rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {
    //This function will add a new node to the front of the double sentinel linked list
    //Create a new instance of a Double_node with the request number (obj), set previous pointer to point to the head sentinel
    //And set the next pointer to point the 1st item in the list
    Double_node *new_node = new Double_node(obj, list_head, list_head ->next_node);
    list_head -> next_node = new_node;//set the next pointer of the head sentinel to point to the new node
    new_node ->next_node ->previous_node = new_node;//set the previous pointer of the original 1st item on the list to point to new node
    //After all the pointers are moved to the right place, the new node added in should now be the 1st item on the list
    list_size++;//increment the size of the list since the user has added a node

}

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
    //This function will add a new node to the back of the double sentinel linked list
    //Create a new instance of a Double_node with the request number (obj), set previous pointer to point to the last item in the list
    //And set the next pointer to point the tail sentinel
    Double_node *new_node = new Double_node(obj, list_tail ->previous_node, list_tail);
    list_tail -> previous_node = new_node;//set the previous pointer of the tail sentinel to point to the new node
    new_node ->previous_node ->next_node = new_node;//set the next pointer of the original last item on the list to point to new node
    //After all the pointers are moved to the right place, the new node added in should now be the last item on the list
    list_size++;//increment the size of the list since the user has added a node
}

template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
    //This function will take away or erase the 1st item on the list
    if (list_size == 0)//if the list is empty, then there is nothing to remove
    {
        throw underflow();//throw an exception is the list is empty
    }
    else
    {
        Double_node *p = list_head;//create a new instance of a pointer of type Double_node and point it to the head sentinel
        while (p != list_head->next_node) {//traverse through the list until you get to the 1st item on the list
            p = p->next_node;//increment p to traverse
        }
        Double_node *store_next = p->next_node;//create another new instance of a pointer of type Double_node and point it to what p is pointing to next
        Double_node *store_prev = p->previous_node;//create another new instance of a pointer of type Double_node and point it to what p is pointing to before it
        store_next->previous_node = store_prev;//allow the previous pointer of the node after p to point to the node before p
        store_prev->next_node = store_next;//allow the next pointer of the node before p to point to the node after p
        delete (p);//deallocate all memory from p
        list_size--;//decrement the list size the user is removing a node
    }

}

template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
    //This function will take away or erase the last item on the list
    if (list_size == 0)//if the list is empty, then there is nothing to remove
    {
        throw underflow();//throw an exception is the list is empty
    }
    else
    {
        Double_node *p = list_head;//create a new instance of a pointer of type Double_node and point it to the head sentinel
        while (p != list_tail->previous_node) {//traverse through the list until you get to the last item on the list
            p = p->next_node;//increment p to traverse
        }
        Double_node *store_next = p->next_node;//create another new instance of a pointer of type Double_node and point it to what p is pointing to next
        Double_node *store_prev = p->previous_node;//create another new instance of a pointer of type Double_node and point it to what p is pointing to before it
        store_next->previous_node = store_prev;//allow the previous pointer of the node after p to point to the node before p
        store_prev->next_node = store_next;//allow the next pointer of the node before p to point to the node after p
        delete (p);//deallocate all memory from p
        list_size--;//decrement the list size the user is removing a node
    }
}

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
    //This function will erase any requested integers given by the user
    int counter = 0;//initialize a counter to zero
    Double_node * p = list_head;//create a new instance of a pointer of type Double_node and point it to the head sentinel
    while (p != nullptr)//check if p is pointing to nullptr
    {
        if (p->node_value == obj)//if the node value of the p is equal to the requested integer the user wants to delete
        {
            Double_node *node1 = p;//create a new instance of a pointer of type Double_node and point it to p
            node1->previous_node->next_node = node1->next_node;//set the next pointer of the node before p to the node after p
            node1->next_node->previous_node = node1->previous_node;//set the previous pointer of the node after p to the node before p
            node1 = node1->next_node;//go on to the next node in the list
            delete (p);//deallocate the pointer
            counter++;//increment the counter to keep track of how many times you had to delete that same number
            list_size--;//decrement list size because you are removing a node
            p = node1;//allow p to point to the new node
        }
        else//if the node value of the p is not equal to the requested integer the user wants to delete
        {
            p = p->next_node;//increment p or move to the next node
        }
    }
    return counter;//return how many times the number had to be deleted in the list
}

template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(
	Type const &nv,
	typename Double_sentinel_list<Type>::Double_node *pn,
	typename Double_sentinel_list<Type>::Double_node *nn ):
// Updated the initialization list here
node_value( nv ), // This assigns 'node_value' the default value of Type
previous_node( pn ),//not sure about this implementation, going to ask TA!!!
next_node( nn )
{

}

template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	return node_value; // This returns a default value of Type
    //return Type();
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
    return previous_node; // This returns a default value of previous node
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
	return next_node; // This returns a default value of next node
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// If you author any additional private member functions, include them here

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
	out << "head";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.rend(); ptr != nullptr; ptr = ptr->next() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0" << std::endl << "tail";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.end(); ptr != nullptr; ptr = ptr->previous() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0";

	return out;
}

#endif
