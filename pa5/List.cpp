//-----------------------------------------------------------------------------
//Preston Nguyen
//prhunguy
//pa5
//-----------------------------------------------------------------------------

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
   data = x;
   next = nullptr;
   prev = nullptr;
}




// Class Constructors & Destructors -------------------------------------------

// Creates new List in the empty state.
List::List(){


    frontDummy = new Node(ListElement());
    backDummy = new Node(ListElement());
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;

    pos_cursor = 0;
    num_elements = 0;
}

// Copy constructor.
List::List(const List& L){
    frontDummy = new Node(ListElement());
    backDummy = new Node(ListElement());

    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;

    Node* curr = L.frontDummy->next;

    while(curr != L.backDummy){
        insertBefore(curr->data);
        curr = curr->next;
    }
}

// Destructor
List::~List(){
    clear();
    delete frontDummy;
    delete backDummy;

}
    
// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
    return num_elements;
}

// front()S
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
    
    if(length() < 0){
        throw std::range_error("List: front(): empty list");
    }
    
    return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
    
    if(length() <= 0){
        throw std::range_error("List: back(): empty list");
    }
    
    return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
    
    if(position() >= length()){
        throw std::range_error("List: peekNext(): cursor at back");
    }

    return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
    
    if(position() <= 0){
        throw std::range_error("List: peekPrev(): cursor at front");
    }

    return beforeCursor->data;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    
    Node* current = frontDummy;

    while (current != backDummy) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    delete current;

    beforeCursor = frontDummy;
    afterCursor = backDummy;
    

    frontDummy = nullptr;
    backDummy = nullptr;

    pos_cursor = 0;
    num_elements = 0;
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
    pos_cursor = length();
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext(){

    if(position() >= length()){
        throw std::range_error("List: moveNext(): cursor at back");
    }

    beforeCursor = beforeCursor->next;
    afterCursor = afterCursor->next;
    pos_cursor++;

    return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){

    if(position() <= 0){
        throw std::range_error("List: movePrev(): cursor at front");
    }

    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    pos_cursor--;

    return afterCursor->data;

}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
    Node* temp = new Node(x);
    temp->prev = beforeCursor;
    temp->next = afterCursor;
    beforeCursor->next = temp;
    afterCursor->prev = temp;
    afterCursor = temp;

    num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
    Node* temp = new Node(x);
    temp->next = afterCursor;
    temp->prev = beforeCursor;
    beforeCursor->next = temp;
    afterCursor->prev = temp;
    beforeCursor = temp;

    pos_cursor++;
    num_elements++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){

    if(position() >= length()){
        throw std::range_error("List: setAfter(): cursor at back");
    }

    afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){

    if(position() <= 0){
        throw std::range_error("List: setBefore(): cursor at front");
    }

    beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){

    if(position() >= length()){
        throw std::range_error("List: eraseAfter(): cursor at back");
    }

    Node* temp = afterCursor;

    afterCursor = temp->next;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;

    delete temp;
    num_elements--;

}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){

    if(position() <= 0){
        throw std::range_error("List: eraseBefore(): cursor at front");
    }

    Node* temp = beforeCursor;

    beforeCursor = temp->prev;
    afterCursor->prev = beforeCursor;
    beforeCursor->next = afterCursor;
        
    delete temp;
    num_elements--;
    pos_cursor--;

}


// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){


    while (afterCursor != backDummy) {
        if (afterCursor->data == x) {
            moveNext();
            return pos_cursor;
        }
        moveNext();
    }
    pos_cursor = length();
    return -1;



}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
    
    while (beforeCursor != frontDummy) {
        if (beforeCursor->data == x) {
            movePrev();
            return pos_cursor;
        }
        movePrev();
    }

    pos_cursor = 0;
    return -1;

}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.----------------------------------------------------------------------------------
void List::cleanup(){

    int original = position();
	int before = 0;
    int counter = 0;

	moveFront();
	
	while(afterCursor != backDummy){

		moveNext();

        //if not found add to counter
		if(findNext(beforeCursor->data) == -1){
			counter++;
		}else{

            //if found delete prev
			if(position() < original){
				before++;
			}
			eraseBefore();
		}


        //reset and continue going through
		moveFront();
		for(int i = 1; i <= counter; i++){
			moveNext();
		}
	}


	//move cursor to correct spot
	int moves= original - before;

	moveFront();
	for(int i= 0; i < moves; i++){
		moveNext();
	}
}
 
// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{

    List result = List();

    Node* N = nullptr;
    Node* M = nullptr;

    for(N=this->frontDummy->next; N != this->backDummy; N=N->next){
        result.insertBefore(N->data);
    }

    for(M=L.frontDummy->next; M != L.backDummy; M=M->next){
        result.insertBefore(M->data);
    }

    result.moveFront();
    return result;

}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
    
    Node* N = nullptr;
    std::string s = "(";

    for(N=frontDummy->next; N->next->next != nullptr; N=N->next){
        s += std::to_string(N->data)+ ", ";
    }

    s += std::to_string(N->data)+= ")";
    return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{

    if (length() != R.length()) {
        return false;
    }

    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;

    eq = ( this->num_elements == R.num_elements );
    N = this->frontDummy;
    M = R.frontDummy;
    while( eq && N != backDummy){
        eq = (N->data==M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}



// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
    if( this != &L ){ // not self assignment
    // make a copy of Q
    List temp = L;

    // then swap the copy's fields with fields of this
    std::swap(frontDummy, temp.frontDummy);
    std::swap(backDummy, temp.backDummy);
    std::swap(num_elements, temp.num_elements);
    }

    // return this with the new data installed
    return *this;

    // the copy, if there is one, is deleted upon return
}





