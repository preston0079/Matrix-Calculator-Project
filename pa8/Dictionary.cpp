//-----------------------------------------------------------------------------
//Preston Nguyen
//prhunguy
//pa8
//-----------------------------------------------------------------------------

#include "Dictionary.h"
#include <cstring>
#include <limits>
#include <sstream>
#include <stdexcept>

#define BLACK 1
#define RED 2


// Private Constructor --------------------------------------------------------

// Node constructor
Dictionary::Node::Node(keyType k, valType v){
    // set key to k, val to v, left & right & parent nodes to null pointers
    key = k;
    val = v;
    parent = NULL;
    left = NULL;
    right = NULL;

    color = BLACK;
}



// Helper Functions (Optional) ------------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of: "key : value\n" for each key-value pair in the tree
// rooted at R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{

    if(R != nil){
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string will consist of keys only, with the order determined by a pre-order
// tree walk. The keys stored in black Nodes will be appended as "key\n", and
// the keys stored in red Nodes will be appended as "key (RED)\n". The output 
// of this function is demonstrated in /Examples/pa8/DictionaryClient-out.  
void Dictionary:: preOrderString(std::string& s, Node* R) const{

    if(R != nil){

        if(R->color == RED){
            s += R->key + " (RED)\n";
        }else{
            s += R->key + "\n";
        }

        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// BST_insert()
// Inserts a copy of the Node *M into this Dictionary. Used by preOrderCopy().
// void Dictionary::BST_insert(Node* M){   
// }

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){

    if(R != N){
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }


}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R){

    if(R != nil){
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{

    while(R != nil){
        if(root == nil || k == R->key){
            return R;
        }else if(k < R->key){
            R = R->left;
        }else{
            R = R->right;
        }
    }
    return nil;



}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){

    Node* min = R;
    if(min != nil){

        while(min->left != nil){
            min = min->left;
        }
    }
    return min;

}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){

    Node* max = R;
    if(max != nil){

        while(max->right != nil){
            max = max->right;
        }

    }
    return max;


}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findNext(Node* N){

    if(N == nil){
        return nil;
    }else if(N->right != nil){
        return findMin(N->right);
    }else{
        Node* y = N->parent;

        while(y != nil && N == y->right){
            N = y;
            y = N->parent;
        }
        return y;
    }



}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){

    if(N == nil){
        return nil;
    }else if(N->left != nil){
        return findMax(N->left);
    }else{
        Node* y = N->parent;

        while(y != nil && N == y->left){
            N = y;
            y = N->parent;
        }
        return y;
    }

}

// RBT Helper Functions (Optional) -----------------------------------------
   
// LeftRotate()
void Dictionary::LeftRotate(Node* N){

    Node* y = N->right;

    N->right = y->left;
    if(y->left != nil){
        y->left->parent = N;
    }

    y->parent = N->parent;
    if(N->parent == nil){
        root = y;
    }else if(N == N->parent->left){
        N->parent->left = y;
    }else{
        N->parent->right = y;
    }

    y->left = N;
    N->parent = y;



}

// RightRotate()
void Dictionary::RightRotate(Node* N){

    Node* y = N->left;

    N->left = y->right;
    if(y->right != nil){
        y->right->parent = N;
    }

    y->parent = N->parent;
    if(N->parent == nil){
        root = y;
    }else if(N == N->parent->right){
        N->parent->right = y;
    }else{
        N->parent->left = y;
    }

    y->right = N;
    N->parent = y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N){
    
    while(N->parent->color == RED){
        if(N->parent == N->parent->parent->left){
            Node* y = N->parent->parent->right;
            if(y->color == RED){
                N->parent->color = BLACK;
                y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }else{
                if(N == N->parent->right){
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                RightRotate(N->parent->parent);
            }

        }else{

            Node* y = N->parent->parent->left;
            if(y->color == RED){
                N->parent->color = BLACK;
                y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }else{
                if(N == N->parent->left){
                    N = N->parent;
                    RightRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                LeftRotate(N->parent->parent);
            }
        }
    }

    root->color = BLACK;

   
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v){
    if(u->parent == nil){
        root = v;
    }else if(u == u->parent->left){
        u->parent->left = v;
    }else{
        u->parent->right = v;
    }

    v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N){
    
    while(N != root && N->color == BLACK){
        if(N == N->parent->left){
            Node* w = N->parent->right;
            if(w->color == RED){
                w->color = BLACK;
                N->parent->color = RED;
                LeftRotate(N->parent);
                w = N->parent->right;
            }

            if(w->left->color == BLACK && w->right->color == BLACK){
                w->color = RED;
                N = N->parent;
            }else{
                if(w->right->color == BLACK){
                    w->left->color = BLACK;
                    w->color = RED;
                    RightRotate(N);
                    w = N->parent->right;
                }
                w->color = N->parent->color;
                N->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(N->parent);
                N = root;
            }

        }else{

            Node* w = N->parent->left;
            if(w->color == RED){
                w->color = BLACK;
                N->parent->color = RED;
                RightRotate(N->parent);
                w = N->parent->left;
            }

            if(w->right->color == BLACK && w->left->color == BLACK){
                w->color = RED;
                N = N->parent;
            }else{
                if(w->left->color == BLACK){
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotate(N);
                    w = N->parent->left;
                }
                w->color = N->parent->color;
                N->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotate(N->parent);
                N = root;
            }
        }
    }

    N->color = BLACK;

}

// RB_Delete()
void Dictionary::RB_Delete(Node* N){
    
    Node* y = N;
    int yogcolor = y->color;
    Node* x = NULL;

    if(N->left == nil){
        x = N->right;
        RB_Transplant(N, x);

    }else if(N->right == nil){
        x = N->left;
        RB_Transplant(N, x);

    }else{
        y = findMin(N->right);
        yogcolor = y->color;
        x = y->right;
        if(y->parent == N){
            x->parent = y;

        }else{
            RB_Transplant(y, y->right);
            y->right = N->right;
            y->right->parent = y;
        }

        RB_Transplant(N, y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;
    }

    if(yogcolor == BLACK){
        RB_DeleteFixUp(x);
    }
    delete N;

}


// Class Constructors & Destructors -------------------------------------------

// Creates new Dictionary in the empty state.
Dictionary::Dictionary(){

    nil = new Node(keyType("idontknowhowbuttheyfoundme"), 999);
    root = nil;
    current = nil;
    num_pairs = 0;

    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){


    nil = new Node(keyType("idontknowhowbuttheyfoundme"), 999);
    root = nil;
    current = nil;
    num_pairs = 0;

    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;

    preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary(){

    postOrderDelete(root);
    delete nil;
}


// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{

    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{

    Node* temp = search(root, k);
    if(temp != nil){
        return true;
    }else{
        return false;
    }

}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{

    Node* temp = search(root, k);
    if(temp == nil){
        throw std::logic_error("Dictionary: getValue(): key \""+k+"\" does not exist");
    }
    return temp->val;

}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false
// otherwise.
bool Dictionary::hasCurrent() const{

    if(current != nil){
        return true;
    }else{
        return false;
    }
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent()
keyType Dictionary::currentKey() const{

    if(hasCurrent() == false){
        throw std::logic_error("Dictionary: currentKey(): current undefined");
    }

    return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{

    if(hasCurrent() == false){
        throw std::logic_error("Dictionary: currentVal(): current undefined");
    }

    return current->val;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){

    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;

}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v,
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){

    Node* y = nil;
    Node* x = root;

    Node* z = new Node(k, v);

    while (x != nil) {
        y = x;

        if ((z->key).compare(x->key) < 0) { 
            x = x->left;
        }
        else if ((z->key).compare(x->key) > 0) {
            x = x->right;
        }
        else {
            x->val = z->val;
            delete z;
            return;
        }

    }
    z->parent = y;
    if (y == nil) {
        root = z;
    }
    else if ((z->key).compare(y->key) < 0) {
        y->left = z;
    }
    else {
        y->right = z;
    }
    z->left = nil;
    z->right = nil;
    z->color = RED;
    num_pairs++;
    RB_InsertFixUp(z);

}

// added a helper function to help with remove()
void Dictionary::transplant(Node* u, Node* v){
    // copied from handout
    if(u->parent == nil){
        root = v;
    }else if(u == u->parent->left){
        u->parent->left = v;
    }else{
        u->parent->right = v;
    }

    if(v != nil){
        v->parent = u->parent;
    }
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){

    Node* N = search(root, k);

    if(N == nil){
        throw std::logic_error("Dictionary: remove(): key \""+k+"\" does not exist");
    }

    if (current == N) {
        current = nil;
    }
    
    RB_Delete(N);

    num_pairs--;


}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::begin(){

    // set the current node to the minimum leaf node from the root
    current = findMin(root);
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::end(){

    // set the current node to the maximum leaf node from the root
    current = findMax(root);
}

// next()
// If the current iterator is not at the last pair, advances current
// to the next pair (as defined by the order operator < on keys). If
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){

    if(hasCurrent() == false){
        throw std::logic_error("Dictionary: next(): current undefined");
    }

    if (current->right != nil) {
        current = findNext(current);
    } else {
        while (current->parent != nil && current == current->parent->right) {
            current = current->parent;
        }
        current = current->parent;
    }
    
}

// prev()
// If the current iterator is not at the first pair, moves current to
// the previous pair (as defined by the order operator < on keys). If
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){

    if(hasCurrent() == false){
        throw std::logic_error("Dictionary: prev(): current undefined");
    }

    if(current->left != nil){
        current = findPrev(current);
    }else{
        while (current->parent != nil && current == current->parent->left) {
            current = current->parent;
        }
        current = current->parent;
    }
}


// Other Functions ------------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value
// are separated by the sequence space-colon-space " : ". The pairs are arranged
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{

    std::string s = "";
    inOrderString(s, root);
    return s;

}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{

    std::string s = "";
    preOrderString(s, root);
    return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
    
    if((num_pairs == D.num_pairs) && (this->to_string() == D.to_string())){
        return true;
    }else{
        return false;
    }
}


// Overloaded Operators -------------------------------------------------------


// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
    return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals().
bool operator==( const Dictionary& A, const Dictionary& B ){
    return A.Dictionary::equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
    if( this != &D ){ // not self assignment
        // make a copy of D
        Dictionary temp = D;

        // then swap the copy's fields with fields of this
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);

        preOrderCopy(temp.root, temp.nil);
    }

    // return this with the new data installed
    return *this;

    // the copy, if there is one, is deleted upon return
}


