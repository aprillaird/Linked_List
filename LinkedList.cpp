// April Laird - Chapter 19 - Assignment 5
//This program demonstrates a simple linked list

//#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

//Define the stuct that will be the nodes in the linked list
struct nodeType {
    string name;  //stores a string
    nodeType* next; //pointer to the next link in the node, which is of type nodeType
};

nodeType* headNode;

//function prototypes
void insert(string, nodeType*);
void printList(nodeType*);
void wipeList(nodeType*);
int remove(string);
void displayMenu();

int main() {
    string studentName;
    int choice;

    //create the first node and initialize it to an empty string
    //nodeType *headNode;
    headNode = new nodeType;
    headNode->name = " ";
    headNode->next = nullptr;

    displayMenu();
    cin >> choice;

    // determine choice and either add, print, remove, wipe, or exit
    while (choice != 5) {
        // add student
        if (choice == 1) {
            cin.ignore();
            cout << "Enter the student name." << endl;
            getline(cin, studentName);
            insert(studentName, headNode);
        }
        // Print list
        else if (choice == 2) {
            cout << "The current list contains:" << endl;
            printList(headNode);
        }
        // remove student
        else if (choice == 3) {
            cin.ignore();
            cout << "Enter the student name to be removed from the list." << endl;
            getline(cin, studentName);
            remove(studentName);
        }
        // wipe list
        else if (choice == 4) {
            wipeList(headNode);
        }
        else if (choice == 5) {
            break;
        }
        // Exit
        else {
            cout << "Invalid choice." << endl;
        }
        displayMenu();
        cin >> choice;
    }

    system("pause");
    return 0;
}

//insert() adds a string onto the end of the list
void insert(string studentName, nodeType* head) {
    nodeType* temp, * traverse;

    if (head->name == " ")
    {
        //if the name field in the head of the list is empty then this is the first name entered
        head->name = studentName;
    }
    else
    {
        temp = new nodeType; //allocate the memory
        temp->name = studentName;
        temp->next = nullptr;

        traverse = head;
        while (traverse->next != nullptr)
            traverse = traverse->next;

        traverse->next = temp;

    }
}

//printList() traverses the list and outputs the string in each node to the output device
void printList(nodeType* head) {
    nodeType* traverse;
    traverse = head;

    if (traverse->name == " ")
        cout << "The list is empty" << endl;
    else
    {
        while (true)
        {
            cout << traverse->name << endl;
            if (traverse->next != nullptr)
                traverse = traverse->next;
            else break;
        }
    }
}

//wipeList() will traverse the linked list and delete all items in the list, freeing the memory
//a double linked list would make this much more efficient, but we have a single linked list
void wipeList(nodeType* head) {
    nodeType* traverse1, * traverse2;  //pointers used to traverse the linked list

    while (true)
    {
        if (head->next != nullptr)
        {
            traverse1 = head;  //point to head of the linked list
            traverse2 = traverse1->next; //point to the next item in the list
        }
        else {
            //if head->next is null then the head is the only node in the list
            // make the head null, don't delete it
            if (head->name != " ") {
                cout << "Emptying the head node " << head->name << endl;
                head->name = " ";
                head->next = nullptr;
            }
            else {
                cout << "The list is empty.\n";
            }
            break;
        }

        while (traverse2->next != nullptr) {
            //cycle through to the end of the list
            //keep traverse1 one link behind traverse2
            traverse1 = traverse2;
            traverse2 = traverse2->next;
        }

        //now traverse2 is at the end of the list
        cout << "Deleting " << traverse2->name << endl;
        delete traverse2; //delete the item
        traverse1->next = nullptr; //make this is the end of the list now
    }
}

void displayMenu() {
    cout << "Please choose one of the following:\n"
        << "1. Enter a new student.\n"
        << "2. Print the list.\n"
        << "3. Remove a student.\n"
        << "4. Wipe the list.\n"
        << "5. Exit\n";
}

int remove(string studentName) {
    // using traverse1 and traverse2 was confusing so I renamed the pointers
    nodeType* previous, * current, * temp;
    current = headNode; //point to head of the linked list
    previous = new nodeType;

    // If the headNode is empty, the list is empty
    if (current->name == " ") {
        cout << "Remove failed because list is empty.\n";
        return 3;
    }

    // Delete the current if next is not null
    if (current->name == studentName) {
        if (current->next != nullptr) {
            headNode = current->next;
            delete current;
            cout << "The node containing " + studentName + " has been deleted.\n";
            return 1;
        }

        // if current->next is null, empty current, ->next = nullptr
        else {
            current->name = " ";
            current->next = nullptr;
            cout << "The node containing " + studentName + " has been deleted. List is now empty.\n";
            return 2;
        }
    }

    // Name is not on list if not found && current->next is nullptr
    else if (current->name != studentName && current->next == nullptr) {
        cout << studentName + " is not on the list.\n";
        return 4;
    }

    // Traverse list until student name is found
    while (current->next != nullptr && current->name != studentName) {
        previous = current;
        current = current->next;
    }

    // if match found, delete the element
    if (current->name == studentName) {
        previous->next = current->next;
        delete current;
        cout << "The node containing " + studentName + " has been deleted.\n";
        return 1;
    }

    // Else name is not found
    else {
        cout << studentName + " is not on the list.\n";
        return 4;
    }
}




