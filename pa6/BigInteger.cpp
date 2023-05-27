//-----------------------------------------------------------------------------
//Preston Nguyen
//prhunguy
//pa6
//-----------------------------------------------------------------------------

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"
#include"BigInteger.h"

#include<sstream>
#include<iomanip>

#include <algorithm>

using namespace std;

const long base = 1000000000;
const int power = 9;


// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L){

    // iterate through the list of L
    L.moveFront();
    while(L.position() < L.length()){
    	long x = L.moveNext();
    	if (x != 0){
    		L.eraseBefore();
    		L.insertBefore(x * -1);
    	}

    }
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn){
    
    //modified from TA pseudo

    ListElement x, y;
    S.clear();
    A.moveBack();
    B.moveBack();

    while (A.position() > 0 && B.position() > 0){
    	x = A.movePrev();
    	y = B.movePrev();
    	S.insertAfter(x + (y * sgn));

    }
    while (A.position() > 0){
    	x = A.movePrev();
    	S.insertAfter(x);
    }
    while (B.position() > 0){
   	 	y = B.movePrev();
   	 	S.insertAfter(y * sgn);
    }

}

// normalizeList()
// Performs carries from right to left (least to most significant 
// digits), then returns the sign of the resulting integer. Used 
// by add(), sub() and mult().
int normalizeList(List& L){

    //help from Norton Choy pseudo

    int sgn;
	ListElement q, r;
	ListElement num, carry = 0;

    
	// loop through the list from the LSD
	L.moveBack(); 
	while (L.position() > 0){
		num = L.movePrev();
		num += carry;
		q = num / base;
		r = num % base; 

		if (r < 0){
			num = r + base;
			carry = q - 1;
		}else{
			num = r;
			carry = q;
		}
		
		L.setAfter(num);
		
        // if at beginning of list
		if (L.position() == 0){
			if (carry > 0){
				L.insertBefore(0);
			}else if(carry < 0){
				L.insertBefore(carry);
				break;
			}
		}
	}

   // eliminate all leading zeros
	L.moveFront();
	while (L.position() < L.length()){
        
        if (L.moveNext() == 0){
        	L.eraseBefore();
        }else{
        	break;
        }
	}

    // calculate and return sign
	if (L.length() != 0){
        // if the leftmost digit is positive:
		if (L.front() > 0){
			sgn = 1;
		}else if (L.front() < 0){
			sgn = -1;
			negateList(L);
			normalizeList(L);
		}
	}else{
        // List is empty
		sgn = 0;
	}
   	return sgn;

    
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p){

    // modified from TA psuedo

    L.moveBack();
	for (int i = 0; i < p; i++){
		L.insertBefore(0);
	}

}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m){

    // from TA psuedo

    if (m != 1){
		L.moveFront();
		while(L.position() < L.length()){
			ListElement x = L.moveNext();
			if (x != 0){
				L.eraseBefore();
				L.insertBefore(x * m);
			}
		}
	}

}





// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
    // set the signum to 0, create a list of digits()
    signum = 0;
    List digits;
}

// BigInteger()
// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x){    

    if (x > 0) {
        signum = 1;
    } else if (x < 0) {
        signum = -1;
        x = std::abs(x);
    } else {
        //if 0, return early
        signum = 0;
        digits.insertBefore(0);
        return;
    }

    // get x and insert them into the digits list
    while (x > 0) {
        digits.insertAfter(x % base);
        x /= base;
    }


}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {

    // if the first character is + or -
    if (s[0] == '-' || s[0] == '+') {
        // get sign and remove it from the string
        signum = (s[0] == '-') ? -1 : 1;
        s = s.substr(1);
    } else {
        signum = 1;
    }
    
    // Reverse the string
    reverse(s.begin(), s.end());
    
    std::string temp = "";

    for (unsigned int i = 0; i < s.length(); i++) {
        temp += s[i];
        
        // Split the string into chunks of 'power' digits
        if ((i + 1) % power == 0 || i == s.length() - 1) {
            reverse(temp.begin(), temp.end());
            
            // Convert the chunk into a long integer and insert it into the digits list
            digits.moveFront();
            digits.insertAfter(std::stol(temp));
            temp = "";
        }
    }
    
    // Handle leading zeros
    while (!digits.length() == 0 && digits.front() == 0) {
        digits.moveFront();
        digits.eraseAfter();
    }
    
    // If the digits list is empty, set signum to 0
    if (digits.length() == 0) {
        signum = 0;

        digits.moveFront();
        digits.insertAfter(0);
    }
}



// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
    this->signum = N.signum;
    this->digits = N.digits;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{

    List A = digits;
    List B = N.digits;

    // if the signums are different
    if (signum != N.signum){
        if (signum > N.signum) {
            return 1;
        }else{
            return -1;
        }
    }else if(signum == 0){
        return 0;
    }

    // Remove leading zeros
    List tempA(A);
    List tempB(B);
    while (!tempA.length() != 0 && tempA.front() == 0){
        tempA.moveFront();
        tempA.eraseAfter();
    }
    while (!tempB.length() != 0 && tempB.front() == 0){
        tempB.moveFront();
        tempB.eraseAfter();
    }

    int lengthA = tempA.length();
    int lengthB = tempB.length();

    // Compare the lengths of the lists
    if(lengthA > lengthB){
        return signum;
    }else if(lengthA < lengthB){
        return -signum;
    }else{
        tempA.moveFront();
        tempB.moveFront();
        int position = 0;

        // check elements
        while (position < lengthA) {
            if (tempA.front() > tempB.front()){
                return signum;
            } else if (tempA.front() < tempB.front()){
                return -signum;
            }

            tempA.moveFront();
            tempA.eraseAfter();

            tempB.moveFront();
            tempB.eraseAfter();
            
            position++;
        }

        return 0;
    }

}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
    // clear the digits list and set signum to 0
    signum = 0;
    digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
    if (signum != 0) {
        signum *= -1;
    }
}


// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
    
    BigInteger Sum;
    int sgn;

    List A = this->digits;
    List B = N.digits;
    List& s =Sum.digits;


    if(signum == N.signum){
        sumList(s, A, B, 1);
        normalizeList(s);
        Sum.signum = signum;
    }else{
        sumList(s, A, B, -1);
        sgn = normalizeList(s);
        Sum.signum = sgn * signum;
    }
        
    return Sum;

}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
    
    BigInteger A = BigInteger(N);
    A.negate();
    return add(A);

}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{

    // help recieved but no code was shared, explain on whiteboard
    // modified from TA pseudo


    int col = 0;
    BigInteger Prod;
    List A = this->digits;
	List B = N.digits;
	List C;


	BigInteger P;
	
    // set P's signum by multiplying the signs of A and B's signums
	Prod.signum = this->signum * N.signum;

    // mult 0 scenario
	if (this->signum == 0 || N.signum == 0){
		Prod = BigInteger(0);
		return Prod;
	}

	B.moveBack();
	while (B.position() > 0){
		C = A;
		ListElement x = B.movePrev();
        // multiply list C by "x"
        scalarMultList(C, x);

        normalizeList(C);
        shiftList(C, col);

        P.digits = C;
        P.signum = signum;
        Prod += P;

        normalizeList(C);

        //increment the column number
		col++;
	}

    //update signum
	Prod.signum = this->signum * N.signum;

	return Prod;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
    
    // help recieved but no code was shared, explain on whiteboard
    // modified from TA pseudo

    std::string s;

    // if the sign is -1:
    if(signum == -1){
        s += "-";
    }
    // if sign is 0:
    if(signum == 0){
        s += "0";
    }else{

        digits.moveFront();

        // iterate through digits
        while(digits.position() < digits.length()){

            //length of next element
            int temp = (std::to_string(digits.peekNext())).length();

            //pad zero's
            //skip first chunk (use && position != 0)
            if (digits.position() != 0 && temp < power){
                for (int i = 0; i < (power - temp); i++){
                    s += "0";
                }
            } 
            
            // add element to string
            s += std::to_string(digits.peekNext());
            
            digits.moveNext();
        }
    }
        
    return s;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
    if(A.BigInteger::compare(B) == 0){
        return true;
    }else{
        return false;
    }
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
    if(A.BigInteger::compare(B) == -1){
        return true;
    }else{
        return false;
    }
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
    if(A.BigInteger::compare(B) == -1 || A.BigInteger::compare(B) == 0){
        return true;
    }else{
        return false;
    }
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
    if(A.BigInteger::compare(B) == 1){
        return true;
    }else{
        return false;
    }
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    if(A.BigInteger::compare(B) == 1 || A.BigInteger::compare(B) == 0){
        return true;
    }else{
        return false;
    }
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    return A.BigInteger::add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    A = A.BigInteger::add(B);
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    return A.BigInteger::sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    A = A.BigInteger::sub(B);
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return A.BigInteger::mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    A = A.BigInteger::mult(B);
    return A;
}


