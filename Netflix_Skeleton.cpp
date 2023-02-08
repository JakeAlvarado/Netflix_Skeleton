#include <iostream>
#include <string>

using namespace std;

class Date
{

public:
    Date()
    {
        day = 12;
        month = 31;
        year = 2021;
    }
    Date(int x, int y, int z)
    {
        day = x;
        month = y;
        year = z;
    }
    void GetDate() const
    {
        std::cout << "Date: " << month << "/" << day << "/" << year << endl;
    }
    int GetMonth() const
    {
        return month;
    }

private:
    int day;
    int month;
    int year;
};

class Node
{
public:
    string cate_name;
    string movie_title;
    Node *down; // Next
    Node *up;   // Prev
    Node *next; // Right
    Node *prev; // Left

    Node()
    {
        cate_name = "";
        movie_title = "";
        down = NULL;
        up = NULL;
        next = NULL;
        prev = NULL;
    }
};

class CLL
{
public:
    CLL();
    void AddMovie(Node *ref, string name);                // Attaching Movies to "Next", Creating Seperate List of Movies
    Node *movieByCategory(Node *ref, string name);        // Search Movie by Name In Specified Category
    int GetMovieIndex(Node *ref, string name);            // Search Movie By Name and Get Index
    void PrintAllInCategory(Node *ref);                   // Print All Movies In A Specific Category
    void OrderMovies(string &s1, string &s2, string &s3); // String to Order the 3 Movies From User Input
};

CLL::CLL()
{
}

class DLL
{
public:
    DLL();
    void addCategory(Node **ref, string name);     // Adding Category to Linked List
    void printAll(Node *curr);                     // Print All Movies of All Categories
    Node *searchByName(Node *curr, string name);   // Search Movie By Name
    Node *search_Category(Node *ref, string name); // Search For Category By Name
    void rmv_Category(Node **ref);                 //Remove Categories And Movies Within Categories (Not Done)
    void DelByDate();                              //Delete Movies By Specific Date    (Not Done)
};

DLL::DLL()
{
}

void CLL::OrderMovies(string &s1, string &s2, string &s3) //Order Movies Before Input Into Linked List
{
    string first;
    string second;
    string third;
    if (s1 <= s2 && s1 <= s3) //If String 1 is Greater Than or Equal Too Both String 2 and 3, Then it should be First
    {
        first = s1;
        if (s2 <= s3) //Now if String 2 is Greater Than or Equal to String 3, String 2 second and String 3 Third
        {
            second = s2;
            third = s3;
        }
        else //Else Vice-Versa
        {
            second = s3;
            third = s2;
        }
    }
    else if (s2 <= s1 && s2 <= s3) //Same as First except if String 2 is String 1 and String 3, String 2 Is First
    {
        first = s2;
        if (s1 <= s3)
        {
            second = s1;
            third = s3;
        }
        else
        {
            second = s3;
            third = s1;
        }
    }
    else //Same as 1 and 2 But if String 3 is Greater than both than it should be first.
    {
        first = s3;
        if (s1 <= s2)
        {
            second = s1;
            third = s2;
        }
        else
        {
            second = s2;
            third = s1;
        }
    }
    s1 = first; //Organizing the sorted names in a position that my Insert Function would put them in the correct order.
    s2 = third;
    s3 = second;
}

void DLL::addCategory(Node **ref, string name) // Add Category to the Linked List
{
    Node *temp = new Node();
    temp->cate_name = name;
    temp->down = (*ref);
    temp->up = NULL;

    if ((*ref) != NULL)
    {
        (*ref)->up = temp;
    }
    (*ref) = temp;
    cout << "Created New Category!\n";
}

Node *DLL::search_Category(Node *ref, string name) // Search and Return A Pointer to A Node
{
    struct Node *curr = ref;
    while (curr != NULL)
    {
        if (curr->cate_name == name)
        {
            return curr;
        }
        curr = curr->down;
    }
    return NULL;
}

void CLL::AddMovie(Node *ref, string name)              //Insert Movies To The Front of The CLL (They are already sorted strings at this point)
{
    if (ref->movie_title == "") // If There Are No Movies In The Category
    {
        ref->movie_title = name;
        ref->next = ref;
        cout << "First Movie Added To " << ref->cate_name << endl;
        return;
    }
    else // When There Is At Least One Movie
    {

        Node *new_movie = new Node();
        new_movie->movie_title = name;
        new_movie->next = ref->next;
        ref->next = new_movie;
        new_movie->prev = ref;
        if (new_movie->next != NULL)
            new_movie->next->prev = new_movie;
        cout << "Added New Movie to " << ref->cate_name << endl;
    }
}

Node *DLL::searchByName(Node *curr, string title)       //Same traversal as Print ALL but instead of Couting the Movies and Categories, we just return Movie if found
{
    string temp = curr->movie_title;
    cout << "Searching For Movie... --\n";
    while (curr != NULL)
    {
        if (curr->movie_title == "")
        {
            if (curr->movie_title == title)
                return curr;
            curr = curr->down;
            if (curr != NULL)
                temp = curr->movie_title;
        }

        else if (curr->next == NULL)
        {
            if (curr->movie_title == title)
                return curr;
            curr = curr->down;

            if (curr != NULL)
                temp = curr->movie_title;
        }

        else if (curr->next->movie_title == temp)
        {
            if (curr->movie_title == title)
                return curr;
            curr = curr->next;
            curr = curr->down;

            if (curr != NULL)
                temp = curr->movie_title;
        }

        else
        {
            if (curr->movie_title == title)
                return curr;
            curr = curr->next;
        }
    }
    return NULL;
}

Node *CLL::movieByCategory(Node *ref, string name)          //Search Category gives ref node and then we traverse list to print out movie names
{
    cout << "Searching for Movie In Category: " << ref->cate_name << "... --\n";
    string temp = ref->movie_title;
    while (ref != NULL)
    {
        if (ref->movie_title == name)
            return ref;

        else if (ref->next->movie_title == temp)
            return NULL;

        else
            ref = ref->next;
    }
}

int CLL::GetMovieIndex(Node *ref, string name)          //I Used a Counter to keep track of the index as we moved right in the CLL
{
    string temp = ref->movie_title;
    int counter = 0;
    while (ref != NULL)
    {
        if (ref->movie_title == name)                   //If You find Movie cout "found movie" and output counter
        {
            cout << "Found Movie at Index: " << counter << endl
                 << endl;
            return counter;
        }

        else if (ref->next->movie_title == temp)            //If we reach end of CLL, return;
        {
            break;
        }

        else                                                //Else go next and check new movies
        {
            ref = ref->next;
            counter++;
        }
    }
    cout << "Movie Not In This Category\n";
}

void CLL::PrintAllInCategory(Node *ref)             //Copied Search Movie Traversal but Just Printed In Category
{
    string temp = ref->movie_title;
    cout << "Movies In Category " << ref->cate_name << " Are: \n";
    while (ref != NULL)
    {
        if (ref->next->movie_title == temp)                 //If At End of CLL Then Print and return/break;
        {
            cout << ref->movie_title << endl;
            cout << endl;
            break;
        }
        else if (ref->movie_title != "")                    //If There is A Movie Title there, print it and go next
        {
            cout << ref->movie_title << endl;
            ref = ref->next;
        }
    }
}

void DLL::rmv_Category(Node **ref) //Attempting to Pass in Address of Node To Delete
{
    string temp = (*ref)->cate_name; //For Ref to know when We Are At the End of The Movie Row
    Node *last;
    do
    {
        last = (*ref);         //Keep Track of Previous Node
        (*ref) = (*ref)->next; //Go To Next Movie While The Next Node You Get To Isn't The Category Node
    } while ((*ref)->next->cate_name != temp);

    do
    {
        last = (*ref);
        (*ref) = (*ref)->next;
        delete last; //Delete Previous Node Location

    } while ((*ref)->cate_name != temp);
}

void DLL::printAll(Node *curr) // Print All Category & Movies (Just Categories for Now)
{
    string temp = "";
    temp = curr->movie_title;
    cout << "Printing:\n";
    while (curr != NULL)
    {
        cout << curr->cate_name << endl;
        if (curr->movie_title == "") //If Current Ref doesn't have movie title go to next category
        {
            curr = curr->down;
            if (curr != NULL)
                temp = curr->movie_title;
        }

        else if (curr->next == NULL) //Or If the next doesn't have anything, then print current movie title and go to next category
        {
            cout << curr->movie_title;
            curr = curr->down;

            if (curr != NULL)
                temp = curr->movie_title;
        }

        else if (curr->next->movie_title == temp) //Now If The Next Node's Movie Title == Where We Started, We Are At End of CLL so print movie go next and go down to next category
        {
            cout << curr->movie_title << " (m) " << endl;
            curr = curr->next;
            curr = curr->down;

            if (curr != NULL)
                temp = curr->movie_title;
        }

        else                    //Else Go next and repeat checks
        {
            cout << curr->movie_title << " (m) ";
            curr = curr->next;
        }
    }
    cout << endl;
}

int main()
{

    Node *c_head = NULL;                               // Creating Node Head
    DLL obj;                                           // Creating DLL Obj
    obj.addCategory(&c_head, "Action");                // List Should Be Action
    obj.addCategory(&c_head, "Romance");               // List Is Now Romance->Action
    obj.addCategory(&c_head, "Comedy");                // List Is Now Comedy->Romace->Action
    obj.printAll(c_head);                              // Check to See If Prediction is Correct
    if (obj.search_Category(c_head, "Comedy") != NULL) // Checking if Search Function works
    {
        cout << "found category\n\n";
    }
    else
    {
        cout << "not found\n";
    }

    CLL obj2;                 // Create obj2 to Access CLL Functions for Movies
    string Action1 = "Taken"; //Initialize Strings For Movies (Out of Order)
    string Action2 = "Die Hard";
    string Action3 = "Mission Impossible";

    string Comedy1 = "Ghostbusters";
    string Comedy2 = "Ice Age";
    string Comedy3 = "Central Intelligence";

    string Romance1 = "The Notebook";
    string Romance2 = "Sleepless In Seattle";
    string Romance3 = "Holidate";

    obj2.OrderMovies(Action1, Action2, Action3); //Function To Order Movies Before Inserting Into Linked List
    obj2.OrderMovies(Comedy1, Comedy2, Comedy3);
    obj2.OrderMovies(Romance1, Romance2, Romance3);

    obj2.AddMovie(obj.search_Category(c_head, "Action"), Action1); // Adding Movies Function to Linked List of Categories In Order
    obj2.AddMovie(obj.search_Category(c_head, "Action"), Action2);
    obj2.AddMovie(obj.search_Category(c_head, "Action"), Action3);

    obj2.AddMovie(obj.search_Category(c_head, "Comedy"), Comedy1);
    obj2.AddMovie(obj.search_Category(c_head, "Comedy"), Comedy2);
    obj2.AddMovie(obj.search_Category(c_head, "Comedy"), Comedy3);

    obj2.AddMovie(obj.search_Category(c_head, "Romance"), Romance1);
    obj2.AddMovie(obj.search_Category(c_head, "Romance"), Romance2);
    obj2.AddMovie(obj.search_Category(c_head, "Romance"), Romance3);

    cout << endl;

    obj.printAll(c_head); // Testing If Movies Were Added Properly

    if (obj.searchByName(c_head, "Ghostbusters") != NULL) // Returns Node of Movie, Testing If Properly Done
    {
        cout << "Found Movie\n\n";
    }
    else
    {
        cout << "Not Found\n";
    }

    if (obj.searchByName(c_head, "ghostbusters") != NULL) // Remark: Notice Failed Input, Results to Failed Test
    {
        cout << "Found Movie\n\n";
    }
    else
    {
        cout << "Not Found\n\n";
    }

    if (obj2.movieByCategory(obj.search_Category(c_head, "Action"), "Ice Age") != NULL) // Notice How We Search for Movie "Ice Age" In Category Action and It Returns NULL
    {
        cout << "Found Movie!\n";
    }
    else
    {
        cout << "Not Found!\n";
    }

    if (obj2.movieByCategory(obj.search_Category(c_head, "Action"), "Taken") != NULL) // Notice How We Search for Movie "Taken" in Category Action and It Returns the Movie
    {
        cout << "Found Movie!\n\n";
    }
    else
    {
        cout << "Not Found!\n\n";
    }

    obj2.GetMovieIndex(obj.search_Category(c_head, "Comedy"), "The Notebook"); // Expecting "Movie Is Not In This Category"
    obj2.GetMovieIndex(obj.search_Category(c_head, "Comedy"), "Ice Age");      // Expecting Index 2

    obj2.PrintAllInCategory(obj.search_Category(c_head, "Action"));  // Expecing Movies: "Die Hard, Mission Impossible, Taken";
    obj2.PrintAllInCategory(obj.search_Category(c_head, "Romance")); // Expecting Movies: "Holidate, Sleepless In Seattle, The Notebook"
    obj2.PrintAllInCategory(obj.search_Category(c_head, "Comedy"));  // Expecting Movies: "Central Intelligence, Ghostbusters, Ice Age"

    return 0;
}