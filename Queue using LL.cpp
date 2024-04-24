#include<iostream>
using namespace std;
struct node   
{  
    int data;   
    node *next;  
};  
node *front = nullptr;  
node *rear = nullptr;   

void insert();  
void remove();  
void display();  
int main ()  
{  
    int choice;   
    while(choice != 4)   
    {     
        cout << "\n*************************Main Menu*****************************\n";  
        cout << "\n=================================================================\n";  
        cout << "\n1. Insert an element\n2. Remove an element\n3. Display the queue\n4. Exit\n";  
        cout << "\nEnter your choice: ";  
        cin >> choice;  
        switch(choice)  
        {  
            case 1:  
                insert();  
                break;  
            case 2:  
                remove();  
                break;  
            case 3:  
                display();  
                break;  
            case 4:  
                exit(0);  
                break;  
            default:   
                cout << "\nEnter valid choice\n";  
        }  
    }  
}  
void insert()  
{  
    node *ptr = new node;  
    int item;   
          
    if(ptr == nullptr)  
    {  
        cout << "\nOVERFLOW\n";  
        return;  
    }  
    else  
    {   
        cout << "\nEnter value: ";  
        cin >> item;  
        ptr->data = item;  
        ptr->next = nullptr;  
        if(front == nullptr)  
        {  
            front = ptr;  
            rear = ptr;   
        }  
        else   
        {  
            rear->next = ptr;  
            rear = ptr;  
        }  
    }  
}     
void remove()  
{  
    node *ptr;  
    if(front == nullptr)  
    {  
        cout << "\nUNDERFLOW\n";  
        return;  
    }  
    else   
    {  
        ptr = front;  
        front = front->next;  
        delete ptr;  
    }  
}  
void display()  
{  
    node *ptr = front;      
    if(front == nullptr)  
    {  
        cout << "\nEmpty queue\n";  
    }  
    else  
    {   
        cout << "\nPrinting values .....\n";  
        while(ptr != nullptr)   
        {  
            cout << "\n" << ptr->data << "\n";  
            ptr = ptr->next;  
        }  
    }  
}  
