#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <cstdlib>
#include <windows.h>
using namespace std;

// Structure for the patient node
struct PatientNode {
    string name;             //name of the patient
    string phone;            //phone number of the patient (should be an Ethio Telecom SIM)
    int id;                  //id of the patient (should be unique)
    PatientNode* left;       // Pointer to the left child node
    PatientNode* right;      // Pointer to the right child node
};

// Function to create a new patient node
PatientNode* createPatientNode(string name, string phone, int id) {
     PatientNode* newNode = new PatientNode; 
    if (newNode == nullptr) {
        cout << "\033[1;31m" << "Error: Memory allocation failed. The tree is full." << "\033[0m" << endl;
        return nullptr;
    }
    newNode->name = name;
    newNode->phone = phone;
    newNode->id = id;
    newNode->left = NULL;
    newNode->right = NULL;
    cout <<  "\033[1;32m" <<"Patient inserted successfully."<< "\033[0m" << endl;
    Sleep(2000);
    system("cls");
    return newNode;
}

// Function to compare two keys
int compareKeys(int id1, int id2) {
    if (id1 < id2) {
        return -1;
    } else if (id1 > id2) {
        return 1;
    } else {
        return 0;
    }
}

// Function to insert a patient into the binary tre
void insertPatient(PatientNode*& root, string name, string phone, int id) {
    if (root == NULL) {
        root = createPatientNode(name, phone, id);
    }
    else {
        int cmp = compareKeys(id, root->id);
        if (cmp < 0) {
            insertPatient(root->left, name, phone, id);
        }
        else if (cmp > 0) {
            insertPatient(root->right, name, phone, id);
        }
        else {
            cout <<"\033[1;31m"<< "Error: Patient ID already assigned to another patient. Please enter a unique ID."<<"\033[0m" << endl;
             Sleep(2000);    system("cls");
        }
    }
}


// Function to delete a patient from the binary tree
PatientNode* deletePatient(PatientNode* root, int id) {
    if (root == NULL) {
        system("cls");
                cout << "\033[1;31m" << "Patient not found!" <<"\033[0m"<< endl;
                Sleep(2000);
        return root;}
    int cmp = compareKeys(id, root->id);
    if (cmp < 0) {
        root->left = deletePatient(root->left, id);
    }
    else if (cmp > 0) {
        root->right = deletePatient(root->right, id);
    }
    else {
        if (root->left == NULL && root->right == NULL) {
            delete root;
                system("cls");
                cout << "\033[1;32m" << "Patient deleted successfully." <<"\033[0m"<< endl;
                Sleep(2000);
            return NULL;
            }
        else if (root->left == NULL) {
            PatientNode* temp = root->right;
            delete root;
                system("cls");
                cout << "\033[1;32m" << "Patient deleted successfully." <<"\033[0m"<< endl;
                Sleep(2000);
            return temp;
        }
        else if (root->right == NULL) {
            PatientNode* temp = root->left;
            delete root;
                system("cls");
                cout << "\033[1;32m" << "Patient deleted successfully." <<"\033[0m"<< endl;
                Sleep(2000);
            return temp;
        }
        PatientNode* minNode = root->right;
        while (minNode->left != NULL) {
            minNode = minNode->left;
        }
        root->name = minNode->name;
        root->phone = minNode->phone;
        root->id = minNode->id;
        root->right = deletePatient(root->right, minNode->id);
    }
    return root;
}

// Function to search for a patient in the binary tree
PatientNode* searchPatient(PatientNode* root, int id) {
    if (root == NULL  || id == root->id) {
        return root;
    }
    int cmp = compareKeys(id, root->id);
    if (cmp < 0) {
        return searchPatient(root->left, id);
    } else {
        return searchPatient(root->right, id);
    }
}


// Function to display patients in preorder traversal
void displayPatientsPreorder(PatientNode* root) {
    if (root != NULL) {
        cout << "\033[1;94m"<<"Id:" <<root->id<<endl<<"NAME: " << root->name<<endl<<"PHONE NUMBER: " << root->phone<<"\033[0m"<<endl<<endl;
        displayPatientsPreorder(root->left);
        displayPatientsPreorder(root->right);
    }
}


// Function to display patients in inorder traversal
void displayPatientsInorder(PatientNode* root) {
    if (root != NULL) {
        displayPatientsInorder(root->left);
        cout << "\033[1;94m"<<"Id:" <<root->id<<endl<<"NAME: " << root->name<<endl<<"PHONE NUMBER: " << root->phone<<"\033[0m"<<endl<<endl;
        displayPatientsInorder(root->right);
    }
}


// Function to display patients in postorder traversal
void displayPatientsPostorder(PatientNode* root) {
    if (root != NULL) {
        displayPatientsPostorder(root->left);
        displayPatientsPostorder(root->right);
        cout << "\033[1;94m"<<"Id:" <<root->id<<endl<<"NAME: " << root->name<<endl<<"PHONE NUMBER: " << root->phone<<"\033[0m"<<endl<<endl;
    }
}


// Function to delete the entire binary tree
void deleteTree(PatientNode* root) {
    if (root == NULL) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}


// Function to clear the input buffer
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


// Function to get a valid name from the user
string getValidName() {
    string name;
    bool valid = false;
    while (!valid) {
        cout <<"\033[1;94m"<< "Enter patient name: "<<"\033[0m";
        getline(cin, name);
        bool validFormat = true;
        for (unsigned int i = 0; i < name.length(); i++ ) {
        if (!isalpha(name[i])) {
            validFormat = false;
                break; }
        }
        if (name.empty() || (name.length() < 2)){
            validFormat= false;
        }
         if (validFormat) {
              valid = true;
         } else {
            cout << "\033[1;31m" << "Invalid name! Please enter a valid name with only alphabetic characters with atleast two letters." << "\033[0m" << endl;
        }
        }return name;
    }


// Function to get a valid phone number from the user
string getValidPhoneNumber() {
    string phone;
    bool valid = false;
    while (!valid) {
        cout <<"\033[1;94m"<< "Enter patient phone number: "<<"\033[0m";
        getline(cin, phone);
        bool validFormat = true;
        for (unsigned int i = 0; i < phone.length(); i++) {
            if (!isdigit(phone[i])) {
                validFormat = false;
                break; }
        }
        if (phone.length()==10  && validFormat && phone.substr(0, 2) == "09") {
            valid = true;
        } else {
            cout <<"\033[1;31m"<< "Error: Invalid phone number format. Please enter a valid 10-digit phone number that starts with \"09\"."<<"\033[0m" << endl;
        }
    }return phone;
}


// Function to get a valid integer from the user
int getValidInt() {
    int num;
    bool valid = false;
    while (!valid) {
        if ((cin >> num)&&(num>0)) {
            valid = true;
        } else {
            cout <<"\033[1;31m"<< "Error: Invalid input. Please enter an integer."<<"\033[0m"  << endl;
            clearInputBuffer();
        }
    } return num;
}


int main() {
    PatientNode* root = NULL;
    int choice, id;
    string name, phone, choice2;
    system("cls");
    do {
        cout << "\n";
        cout <<"\033[1;94m"<< "-------------------------------------------------------------------------------------------------------" << endl;                                                               
        cout << "                                    BINARY TREE ABSTRACT DATA TYPE" << endl;  
        cout << "------------------------------------------------------------------------------------------------------" << endl;
        cout << "                                                  MENU:" << endl;
        cout << "\n";
        cout << "1. Insert a patient" << endl;
        cout << "2. Delete a patient"  << endl; 
        cout << "3. Search for a patient" << endl;
        cout << "4. Display patients (preorder)" << endl;
        cout << "5. Display patients (inorder)" << endl;
        cout << "6. Display patients (postorder)" << endl;
        cout << "7. Exit" <<"\033[0m"<< endl;
        cout << "Enter a choice: ";
        choice = getValidInt();
        clearInputBuffer();
        cout << endl;
        system("cls");

        switch (choice) {
            case 1:
                cout <<"\033[1;94m" <<  "INSERT PATIENT"<<"\033[0m" << endl;
                name = getValidName();
                phone = getValidPhoneNumber();
                cout <<"\033[1;94m"<< "Enter an ID: "<<"\033[0m";
                id = getValidInt();
                insertPatient(root, name, phone, id);
                break;

            case 2:
                if (root == NULL) {
                cout << "\033[1;31m" << "Error: The tree is empty. No patients to delete." << "\033[0m" << endl;
                Sleep(2000);
                break;
                }
                cout << "\033[1;94m" << "DELETE PATIENT"<<"\033[0m" << endl;
                cout <<"\033[1;94m" <<  "Enter the ID of the patient to delete: "<<"\033[0m";
                id = getValidInt();
                root = deletePatient(root, id); 
                break;

            case 3:{
                if (root == NULL) {
                cout << "\033[1;31m" << "Error: The tree is empty. No patients to search." << "\033[0m" << endl;
                Sleep(2000);
                break;
                }
                cout <<"\033[1;94m" <<  "SEARCH PATIENT"<<"\033[0m" << endl;
                cout << "\033[1;94m" << "Enter the ID of the patient to search: "<<"\033[0m";
                id = getValidInt();
                PatientNode* result = searchPatient(root, id);
                if (result == NULL) {
                system("cls");
                cout << "\033[1;31m" << "Patient not found."<<"\033[0m" << endl;
                Sleep(2000);    system("cls");
                }
                else {
                system("cls");
                cout << "\033[1;32m" << "Patient found: " <<"\033[0m"<<endl<<endl<< "\033[1;94m"<<"Id:" <<result->id<<endl<<"NAME: " <<result->name
                <<endl<<"PHONE NUMBER: " << result->phone<<"\033[0m"<<endl;
                cout <<endl<<"\033[1;94m"<<"Press any key to continue" <<"\033[0m"<<endl;
                clearInputBuffer();
                cin.get();
                    }
                break;
                }
            case 4:{
                if (root == NULL) {
                cout << "\033[1;31m" << "Error: The tree is empty. No patients to display." << "\033[0m" << endl;
                Sleep(2000);
                break;
                }
                cout <<"\033[1;94m" <<  "DISPLAY PATIENTS (PREORDER)" <<"\033[0m"<< endl;
                displayPatientsPreorder(root);
                cout <<endl<<"\033[1;94m"<<"Press any key to continue" <<"\033[0m"<<endl;
                cin.get();
                system("cls");
                break;
            }

            case 5:
                if (root == NULL) {
                cout << "\033[1;31m" << "Error: The tree is empty. No patients to display." << "\033[0m" << endl;
                Sleep(2000);
                break;
                }
                cout <<"\033[1;94m" <<  "DISPLAY PATIENTS (INORDER)"<<"\033[0m" << endl;
                displayPatientsInorder(root);
                cout <<endl<<"\033[1;94m"<<"Press any key to continue" <<"\033[0m"<<endl;
                cin.get();
                system("cls");
                break;

            case 6:
                if (root == NULL) {
                cout << "\033[1;31m" << "Error: The tree is empty. No patients to display." << "\033[0m" << endl;
                Sleep(2000);
                break;
                }
                cout <<"\033[1;94m" <<  "DISPLAY PATIENTS (POSTORDER)"<<"\033[0m" << endl;
                displayPatientsPostorder(root);
                cout <<endl<<"\033[1;94m"<<"Press any key to continue" <<"\033[0m"<<endl;
                cin.get();
                system("cls");
                break;

            case 7:
                while (true) {
                cout << "\033[1;94m" << "Do you want to delete the tree? (Yes/No): "<<"\033[0m";
                getline(cin, choice2);
                if (choice2 == "yes" || choice2 == "Yes") {
                    deleteTree(root);
                    cout << "\033[1;94m" << "Exiting after deleting..." <<"\033[0m"<<endl;
                    return 0;
                    }
                else if (choice2 == "no" || choice2 == "No") {
                    cout << "Exiting..." << endl;
                    return 0;
                    }
                else {
                    cout <<  "\033[1;31m"<<"Error: Invalid input!"<<"\033[0m" << endl;
                    }
                }
                break;

            default:
            system("cls");
            cout <<  "\033[1;31m"<<"Error: Invalid choice. Please try again." << "\033[0m"<< endl;
            Sleep(2000);
        }

        cout << endl;
    } while (choice != 7);

    return 0;
}
