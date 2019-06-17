/*
 * 2048.cpp
 * COMP11 Project 1, Spring 2019, Tufts University
 * Zhitong Zhang
 * Date: 3/2/19
 */

#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <time.h>
using namespace std;
// CONSTANTS (IF ANY) GO HERE
const string empty = "-";
const string goup = "w";
const string godown = "s";
const string goleft = "a";
const string goright = "d";
const int dim = 4;


// FUNCTION PROTOTYPES GO HERE
int string2int(string s);
string int2string(int num);
void print_padded_string(string s);
void fill(string board[][dim]);
void display(string board[][dim]);
void play();
int move(string direction, string board[][dim]);
string getinput();
int right(string board[][dim]);
int left(string board[][dim]);
void addnewtile(string board[][dim]);
bool gameend(string board[][dim]);
int up(string board[][dim]);
int down(string board[][dim]);


int main() {
    play();
    return 0;
}

// void play()
// Purpose: Runs the 2048 program
// Parameters: None
// Returns: None
// Effects: None
// Notes: game continues until done == true, score is added 
//contiguously.
void play() {
    int score = 0;
    srand(time(NULL)); //randomize seed
    string board[dim][dim];
    fill(board);
    bool done = false;
    cout << "Starting game!\n";
    while(done == false){
        display(board);
        cout << "Current score: " << score << endl; 
        string direction = getinput();
        int scoreprev = score;
        if (direction == "q")
            break;
        score = score + move(direction, board);
        if (scoreprev > score){ //in case user doesn't put correct direction 
            do{
            score = scoreprev;
            direction = getinput();
            score = score + move(direction, board);
            }while (score < scoreprev);
        }
        addnewtile(board);
        done = gameend(board);
    }
    display(board);
    cout << "Game over! Your score is " << score << ".\n";
}
//the 2D string array board is the parameter, no returns
// void fill(string board[][dim])
// Purpose: Initialize the 2D array w/ two "2" at random pos and rest "-"
// Parameters: The 2d array string board
// Returns: none
// Effects: None
// Notes: None

void fill(string board[][dim]){
    int randnum1 = 1 + (rand() % 16); //random num from 1 to 16
    int randnum2 = 1 + (rand() % 16); //random num from 1 to 16  
    while (randnum1 == randnum2){  //just in case randnum1 is same as randnum2 
        randnum2 = 1 + (rand() % 16);   
    } 
    int counter = 0;
    for(int r = 0; r < dim; r++){
        for(int c = 0; c < dim; c++){
            board[r][c] = empty;
            counter++;
            if ((counter == randnum1) or (counter == randnum2))
                board[r][c] = "2";
        }
    }
    cout << counter << endl;
}

// void display(string board[][dim])
// Purpose: displays 2D the board
// Parameters: the 2D array string board
// Returns: None
// Effects: None
// Notes: None

void display(string board[][dim]){
    for(int h = 0; h < dim; h++){
        for(int w = 0; w < dim; w++){
            string s;
            s = board[h][w]; //turns char into type string
            print_padded_string(s);
        }
        cout << endl;
    }
}
// string getinput()
// Purpose: Gets user input
// Parameters: None
// Returns: input String (user input)
// Effects: None
// Notes: None

string getinput(){
    string input;
    cin >> input;
    return input; 
}
//This function will take in a direction (string) and the 2D string array board
//This function will call on the left, right, up, or down function or
// if no conditions are satisfied, will display to user to try again, returning
// a -100 to play function which will result in play to call move() again with
//no change in score.
// int move(string direction, string board[][dim])
// Purpose: Call on left,right,up , or down function.
// Parameters: The string direction, and 2d array string board
// Returns: Integer score
// Effects: None
// Notes: if none of those are called, will display to user to try again, 
//returning  -100 to play function which will result in play to 
//call move() again with no score change

int move(string direction, string board[][dim]){
    if (direction == goup)
        return up(board);
    else if (direction == goleft)
        return left(board);
    else if(direction == godown)
        return down(board);
    else if (direction == goright)
        return right(board);
    else 
        cout << "Command not recognized. Please try again." << endl;
        return -100; //returns negative to trigger if statement in play()
}

// int right(string board[][dim])
// Purpose: add numbers horizontally in 2d array if they are "near", meaning
//that they are next to or seperated by "-". Then will shift all numbers
//to the right.
// Parameters: The 2D array string board.
// Returns: the integer score that is to be added.
// Effects: None
// Notes: None

int right(string board[][dim]){
    int score = 0;
    for(int h = 0; h < dim; h++){
        for(int w = 0; w < dim; w++){
            for (int k = w + 1; k < dim; k++){
                if (board[h][k] != empty){
                    if(board[h][w] == board[h][k]){ 
                        board[h][w] = int2string(2 * (string2int(board[h][w])));
                        board[h][k] = empty;
                        score = score + string2int(board[h][w]);
                        break;
                    }
                    else
                        break; //no adding b/c no same numbers are near. 
                }
            }
        }
        for(int w = dim - 1; w > 0; w--){ //translation part
            if (board[h][w] == empty){
                for (int k = w - 1; k >= 0; k--){
                    if (board[h][k] != empty){
                        board[h][w] = board[h][k];
                        board[h][k] = empty;
                        break;
                    }
                }
            }
        }
    }
    return score;
}
// int down(string board[][dim])
// Purpose: add numbers vertically in 2d array if they are "near", meaning
//that they are next to or seperated by "-". Then will shift all numbers
//down.
// Parameters: The 2D array string board.
// Returns: the integer score that is to be added.
// Effects: None
// Notes: None
int down(string board[][dim]){
    int score = 0;
    for (int w = 0; w < dim; w++){
        for (int h = 0; h < dim; h++){
            for (int k = h + 1; k < dim; k++){
                if(board[k][w] != empty){
                    if (board[h][w] == board[k][w]){
                        board[h][w] = int2string(2 * (string2int(board[h][w])));
                        board[k][w] = empty;
                        score = score + string2int(board[h][w]);
                        break;
                    }
                    else 
                        break;
                }
            }
        }
        for (int h = dim - 1; h > 0; h--){
            if (board[h][w] == empty){
                for (int k = h - 1; k >= 0; k--){
                    if (board[k][w] != empty){
                        board[h][w] = board[k][w];
                        board[k][w] = empty;
                        break;
                    }
                }
            }
        }
    }
    return score; 


}
// int up(string board[][dim])
// Purpose: add numbers vertically in 2d array if they are "near", meaning
//that they are next to or seperated by "-". Then will shift all numbers
//up.
// Parameters: The 2D array string board.
// Returns: the integer score that is to be added.
// Effects: None
// Notes: None
int up(string board[][dim]){
    int score = 0;
    for (int w = 0; w < dim; w++){
        for (int h = 0; h < dim; h++){
            for (int k = h + 1; k < dim; k++){
                if(board[k][w] != empty){
                    if (board[h][w] == board[k][w]){
                        board[h][w] = int2string(2 * (string2int(board[h][w])));
                        board[k][w] = empty;
                        score = score + string2int(board[h][w]);
                        break;
                    }
                    else 
                        break;
                }
            }
        }
        for (int h = 0; h < dim ; h++){
            if (board[h][w] == empty){
                for (int k = h + 1; k < dim; k++){
                    if (board [k][w] != empty){
                        board[h][w] = board[k][w];
                        board[k][w] = empty;
                        break;
                    }
                }
            }
        }
    }
    return score; 
}
// int left(string board[][dim])
// Purpose: add numbers horizontally in 2d array if they are "near", meaning
//that they are next to or seperated by "-". Then will shift all numbers
//to the left.
// Parameters: The 2D array string board.
// Returns: the integer score that is to be added.
// Effects: None
// Notes: None
int left(string board[][dim]){
    int score = 0;
    for(int h = 0; h < dim; h++){
        for(int w = 0; w < dim; w++){
            for (int k = w + 1; k < dim; k++){
                if (board[h][k] != empty){
                    if(board[h][w] == board[h][k]){ 
                        board[h][w] = int2string(2 * (string2int(board[h][w])));
                        board[h][k] = empty;
                        score = score + string2int(board[h][w]);
                        break;
                    }
                    else
                        break; //no adding b/c no same numbers are near. 
                }
            } 
        }
        for (int w = 0; w < dim; w++){ //translation part
            if (board[h][w] == empty){
                for (int k = w + 1; k < dim; k++){
                    if (board[h][k] != empty){
                        board[h][w] = board[h][k];
                        board[h][k] = empty;
                        break;
                    }
                }
            }
        }
    }   
    return score;
}
// void addnewtile(string board[][dim])
// Purpose: add 2 (90%) or add a 4 (10%) to a random empty position in array.
// Parameters: The 2D array string board.
// Returns: None
// Effects: None
// Notes: None
void addnewtile(string board[][dim]){
    int emptypos = 0;
    int random = 1 + (rand() % 10); //generates random integer from 1-10 
    for(int h = 0; h < dim ; h++){
        for(int w = 0; w < dim; w++){
            if (board[h][w] == empty)
                emptypos++; 
        }
    }
    if (emptypos == 0) //makes sure no new element is added if board is full.
        return;
    int randemptypos = rand() % emptypos; // get random empty position #
    emptypos = 0; //now I am using emptypos to compare with randemptypos.
    for(int h = 0; h < dim ; h++){
        for(int w = 0; w < dim; w++){
            if (board[h][w] == empty){
                if (randemptypos == emptypos){
                   if (random == 1)
                       board[h][w] = "4";
                  else 
                       board[h][w] = "2";
                }
                emptypos++;
            }
        }
    }
}
// 
/* string2int
 * Convert a string to an int. Returns the int form of the given string.
 * Throw logic error if the string is not numerical. 
 */
int string2int(string s) {
    stringstream ss(s);
    int result;
    ss >> result;
    if (ss.fail())
        throw logic_error("ERROR: " + s + " is not a numerical value");
    return result;
}

/* Converts an int to string.
 * Returns the string form of the given int
 */
string int2string(int num) {
    string result;
    ostringstream oss;
    oss << num;
    result = oss.str();
    return result;
}
/* Print a string (persumably an int in the form of a string) with 
 * right paddings of up to 5 spaces
 */
void print_padded_string(string s) {
    printf("%-6s", s.c_str());
}

// bool gameend(string board[][dim])
// Purpose: checks for empty spaces and no two elements are next to 
//each other are the same.
// Parameters: The 2D array string board.
// Returns: boolean (true/false).
// Effects: None
// Notes: return true of no emepty spaces and no two elements are next
//to eachother, elsewise return false.
bool gameend(string board[][dim]){
    int count = 0; 
    for(int h = 0; h < dim; h++){
        for(int w = 0; w < dim; w++){
            if (board[h][w] == empty){
                count++;
            } //will first compare submatrix excluding last row/column
            if ((w != dim - 1) and (h != dim - 1)){ 
                if ((board[h][w] == board[h][w + 1]) or 
                   (board[h][w] == board[h + 1][w])){
                    count++;
                }
            } //compare last row
            else if ((h == dim - 1) and (w != dim - 1)){
                if (board[h][w] == board[h][w + 1])
                    count++;
            } //compare last column
            else if ((w == dim - 1) and (h != dim - 1)){
                if (board[h][w] == board[h + 1][w]) 
                    count++;
            } 
        }     
    }
    if (count == 0) // count is only 0 if there are no more moves to make
        return true;
    else
        return false;
}

