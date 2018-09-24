/*****************************************
 * UW User ID:  z353yang
 * Student Name: Zhicong Yang
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Fall 2018
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
list_head( new Double_node ),
list_tail( new Double_node ),
list_size( 0 )
{
	// Enter your implementation here
	list_head->previous_node = nullptr;
	list_head->next_node = list_tail;
	list_tail->previous_node = list_head;
	list_tail->next_node = nullptr;
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
// Updated the initialization list here
list_head(new Double_node),
list_tail(new Double_node),
list_size(list.list_size)
{
	// Enter your implementation here
	//Double_sentinel_list copy = Double_sentinel_list();
	this->list_head->node_value = list.list_head->node_value;
	this->list_tail->node_value = list.list_tail->node_value;
	this->list_size = list.list_size;
	Double_node *current = list.list_head->next_node;
	Double_node *copycurr;
	Double_node *copyprev = this->list_head;
	for (int i = 0; i < list.list_size; i++) {
		copycurr = new Double_node();
		copycurr->previous_node = copyprev;
		copyprev->next_node = copycurr;
		copycurr->node_value = current->node_value;
		current = current->next_node;
		copyprev = copycurr;
	}
	this->list_tail->previous_node = copyprev;
	copyprev->next_node = this->list_tail;
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
// Updated the initialization list here
list_head(new Double_node),
list_tail(new Double_node),
list_size(list.list_size)
{
	// Enter your implementation here
	this->swap(list);
	list.~Double_sentinel_list();
}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
	// Enter your implementation here
	Double_node *current = this->list_head;
	Double_node *temp = nullptr;
	while (current != nullptr) {
		temp = current->next_node;
		delete current;
		current = temp;
	}
	delete current;
}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
	// Enter your implementation here
	return this->list_size;
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
	// Enter your implementation here
	return this->list_size == 0;
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
	// Enter your implementation here
	if (this->list_size == 0)
		throw overflow();
	return this->list_head->next_node->node_value;
	//return Type(); // This returns a default value of Type
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
	// Enter your implementation here
	if (this->list_size == 0)
		throw overflow();
	return this->list_tail->previous_node->node_value;
	//return Type(); // This returns a default value of Type
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
	// Enter your implementation here
	return this->list_head->next_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
	// Enter your implementation here
	return this->list_tail;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
	// Enter your implementation here
	return this->list_tail->previous_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
	// Enter your implementation here
	return this->list_head;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {
	// Enter your implementation here
	Double_node *current = this->list_head;
	while (current != nullptr) {
		if (current->node_value == obj)
			return current;
		current = current->next_node;
	}
	return this->end();
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
	// Enter your implementation here
	Double_node *current = this->list_head;
	int same = 0;
	while (current != nullptr) {
		if (current->node_value == obj)
			same++;
		current = current->next_node;
	}
	return same;
}

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
	// This is done for you
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

// The assignment operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

// The move operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> &&rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {
	// Enter your implementation here
	Double_node *second = this->list_head->next_node;
	Double_node *new_node = new Double_node();
	new_node->previous_node = this->list_head;
	new_node->next_node = second;
	new_node->node_value = obj;
	this->list_head->next_node = new_node;
	second->previous_node = new_node;
	this->list_size++;
}

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
	// Enter your implementation here
	Double_node *second = this->list_tail->previous_node;
	Double_node *new_node = new Double_node();
	new_node->previous_node = second;
	new_node->next_node = this->list_tail;
	new_node->node_value = obj;
	this->list_tail->previous_node = new_node;
	second->next_node = new_node;
	this->list_size++;
}

template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
	// Enter your implementation here
	if (this->list_size == 0)
		throw overflow();
	Double_node *temp = this->list_head->next_node;
	this->list_head->next_node = temp->next_node;
	temp->next_node->previous_node = this->list_head;
	this->list_size--;
	delete temp;
}

template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
	// Enter your implementation here
	if (this->list_size == 0)
		throw overflow();
	Double_node *temp = this->list_tail->previous_node;
	this->list_tail->previous_node = temp->previous_node;
	temp->previous_node->next_node = this->list_tail;
	this->list_size--;
	delete temp;
}

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
	// Enter your implementation here
	int num = 0;
	Double_node *current = this->list_head->next_node;
	Double_node *temp;
	while (current->next_node != nullptr) {
		if (current->node_value == obj) {
			current->previous_node->next_node = current->next_node;
			current->next_node->previous_node = current->previous_node;
			temp = current;
			current = current->next_node;
			this->list_size--;
			num++;
			delete temp;
		}
		else 
			current = current->next_node;
	}
	return num;
}

template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(
	Type const &nv,
	typename Double_sentinel_list<Type>::Double_node *pn,
	typename Double_sentinel_list<Type>::Double_node *nn ):
// Updated the initialization list here
node_value( Type() ), // This assigns 'node_value' the default value of Type
previous_node( nullptr ),
next_node( nullptr )
{
	// Enter your implementation here
}

template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	// Enter your implementation here
	return this->node_value;
	//return Type(); // This returns a default value of Type
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
	// Enter your implementation here
	return this->previous_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
	// Enter your implementation here
	return this->next_node;
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
