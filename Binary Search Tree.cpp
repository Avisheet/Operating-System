#include <bits/stdc++.h>
using namespace std; 
struct Node {
    int key;
    struct Node *left, *right;
};
Node* newNode(int item)
{
    Node* temp = new Node;
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
} 
void inorder(Node* root)
{
    if (root != NULL) {
        inorder(root->left);
        cout<<root->key<<"-->";
        inorder(root->right);
    }
}
void preorder(Node* root){
    if(root!=NULL){
        cout<<root->key<<"-->";
        preorder(root->left);
        preorder(root->right);
    }
}
void postorder(Node* root){
    if(root!=NULL){
        postorder(root->left);
        postorder(root->right);
        cout<<root->key<<"-->";
    }
}
Node* insert(Node* node, int key)
{
    if (node == NULL)
        return newNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);
    return node;
} 
Node* deleteNode(Node* root, int k)
{
    // Base case
    if (root == NULL)
        return root;
    if (root->key > k) {
        root->left = deleteNode(root->left, k);
        return root;
    }
    else if (root->key < k) {
        root->right = deleteNode(root->right, k);
        return root;
    }
    if (root->left == NULL) {
        Node* temp = root->right;
        delete root;
        return temp;
    }
    else if (root->right == NULL) {
        Node* temp = root->left;
        delete root;
        return temp;
    } 
    // If both children exist
    else { 
        Node* succParent = root; 
        // Find successor
        Node* succ = root->right;
        while (succ->left != NULL) {
            succParent = succ;
            succ = succ->left;
        }
        if (succParent != root)
            succParent->left = succ->right;
        else
            succParent->right = succ->right; 
        // Copy Successor Data to root
        root->key = succ->key; 
        // Delete Successor and return root
        delete succ;
        return root;
    }
} 
int main()
{   
    int choice;
    Node* root = NULL;
    do{
    cout<<"\n=========================MENU=========================\n";
    cout<<"\n**********************************************************\n";
    cout<<"1. Insert the element.\n";
    cout<<"2. Delete the Element.\n";
    cout<<"3. Inorder Traversal.\n";
    cout<<"4. Preorder Traversal.\n";
    cout<<"5. Postorder Traversal.\n";
    cout<<"6. Exit.\n";
    cout<<"\nEnter your choice:\n";
    cin>>choice;
    switch (choice)
    {
    case 1:
        int value;
        cout<<"Enter the value to be inserted:\n";
        cin>>value;
        root= insert(root, value);
        break;   
    case 2:
        int a;
        cout<<"Enter the value to be deleted:\n";
        cin>>a;
        root=deleteNode(root, a);
        break;
    case 3:
        cout<<"\nInorder Traversal:\n";
        inorder(root);
        break;
    case 4:
        cout<<"\nPreorder Traversal:\n";
        preorder(root);
        break;
    case 5:
        cout<<"\nPostorder Traversal:\n";
        postorder(root);
        break;
    case 6:
        cout<<"\nExiting Program.........\n";
        break;   
    default:
        break;
    }
    }while(choice!=6);
    return 0;
}