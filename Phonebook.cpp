#include<iostream>
#include<ctime>
#include<string>
#include<windows.h>
using namespace std;

string correct_PIN = "1234";

string get_current_time()
{
    time_t now = time(0);
    return ctime(&now);   
}

class public_contact{
  public:
  string name;
  string ph_num;
  public_contact *left_contact;
  public_contact *right_contact;
  public_contact(string name, string ph_num)
  {
      this-> name = name;
      this-> ph_num = ph_num;
  }
};

class private_contact{
  public:
  string name;
  string ph_num;
  private_contact *left_contact;
  private_contact *right_contact;
  private_contact(string name, string ph_num)
  {
      this-> name = name;
      this-> ph_num = ph_num;
  }
};

class blocked_public_contact{
  public:
  string name;
  string ph_num;
  blocked_public_contact *next;
  blocked_public_contact *prev;
  blocked_public_contact(string name, string ph_num)
  {
      this-> name = name;
      this-> ph_num = ph_num;
  }
};


class blocked_private_contact{
  public:
  string name;
  string ph_num;
  blocked_private_contact *next;
  blocked_private_contact *prev;
  blocked_private_contact(string name, string ph_num)
  {
      this-> name = name;
      this-> ph_num = ph_num;
  }
};

class call{
  public:
  string name;
  string ph_num;
  string call_type;
  string call_time;
  call *next;
  call *prev;
  call(string name, string ph_num, string call_type, string call_time)
  {
      this-> name = name;
      this-> ph_num = ph_num;
      this-> call_type = call_type;
      this-> call_time = call_time;
  }
};




public_contact* insert_contact(string name, string ph_num, public_contact*t)
{
    if(t==NULL)
    {
        t = new public_contact(name, ph_num);
    }
    else if(name < t->name)
    {
        t->left_contact = insert_contact(name, ph_num, t->left_contact);
    }
    else 
    {
        t->right_contact = insert_contact(name, ph_num, t->right_contact);
    }
    return t;
}




private_contact* insert_contact(string name, string ph_num, private_contact*t)
{
    if(t==NULL)
    {
        t = new private_contact(name, ph_num);
    }
    else if(name < t->name)
    {
        t->left_contact = insert_contact(name, ph_num, t->left_contact);
    }
    else 
    {
        t->right_contact = insert_contact(name, ph_num, t->right_contact);
    }
    return t;
}


string pin_authentication(string entered_PIN)
{
    if(entered_PIN == correct_PIN)
    {
        return "successfull";
    }
    else
    {
        return "failed";
    }
}


public_contact* search_contact(string name, public_contact* t)
{
    if (t == NULL)
    {
        return NULL;
    }
    else if (name < t->name)
    {
        return search_contact(name, t->left_contact);
    }
    else if (name > t->name)
    {
        return search_contact(name, t->right_contact);
    }
    else 
    {
        return t;
    }
}

private_contact* search_contact(string name, private_contact* t)
{
    if (t == NULL)
    {
        return NULL;
    }
    else if (name < t->name)
    {
        return search_contact(name, t->left_contact);
    }
    else if (name > t->name)
    {
        return search_contact(name, t->right_contact);
    }
    else 
    {
        return t;
    }
}

void display(public_contact* t)
{
    if(t==NULL)
    {return;}
    display(t->left_contact);
    cout<<t->name<<"\t|\t "<<t->ph_num<<endl;
    display(t->right_contact);
}

void display(private_contact* t)
{
    if(t==NULL)
    {return;}
    display(t->left_contact);
    cout<<t->name<<"\t|\t "<<t->ph_num<<endl;
    display(t->right_contact);
}

void block(string name, string ph_num, blocked_public_contact* &blocked_public_head)
{
    
    blocked_public_contact *new_contact = new blocked_public_contact(name, ph_num);
    new_contact->prev = NULL;
    new_contact->next = blocked_public_head;
    blocked_public_head = new_contact;
}

void block(string name, string ph_num, blocked_private_contact* &blocked_private_head)
{
    
    blocked_private_contact *new_contact = new blocked_private_contact(name, ph_num);
    new_contact->prev = NULL;
    new_contact->next = blocked_private_head;
    blocked_private_head = new_contact;
}

void display(blocked_public_contact *blocked_public_head)
{
    blocked_public_contact *temp;
    temp = blocked_public_head;
    while(temp!=NULL)
    {
        cout<<temp->name<<"\t\t\t"<<temp->ph_num<<endl;
        temp = temp->next;
    }
}

void display(blocked_private_contact *blocked_private_head)
{
    blocked_private_contact *temp;
    temp = blocked_private_head;
    while(temp!=NULL)
    {
        cout<<temp->name<<"\t\t\t"<<temp->ph_num<<endl;
        temp = temp->next;
    }
}

bool block_checking(string name, blocked_public_contact *blocked_public_head)
{
    blocked_public_contact *temp;
    temp = blocked_public_head;
    while(temp!=NULL)
    {
        if(temp->name == name)
        {
            return true;
        }
        else
        {temp = temp->next;}
    }
    return false;
}

bool block_checking(string name, blocked_private_contact *blocked_private_head)
{
    blocked_private_contact *temp;
    temp = blocked_private_head;
    while(temp!=NULL)
    {
        if(temp->name == name)
        {
            return true;
        }
        else
        {temp = temp->next;}
    }
    return false;
}

void unblock(string name, blocked_public_contact* &blocked_public_head)
{
    blocked_public_contact* temp;
    temp = blocked_public_head;
    
    while(temp->name != name)
    {
        temp = temp->next;
    }
    if(temp->prev != NULL)
    {temp->prev->next = temp->next;}
    else
    {blocked_public_head = temp->next;}
    
    if(temp->next != NULL)
    {temp->next->prev = temp->prev;}
    delete temp;
}

void unblock(string name, blocked_private_contact* &blocked_private_head)
{
    blocked_private_contact* temp;
    temp = blocked_private_head;
    
    while(temp->name != name)
    {
        temp = temp->next;
    }
    if(temp->prev != NULL)
    {temp->prev->next = temp->next;}
    else
    {blocked_private_head = temp->next;}
    
    if(temp->next != NULL)
    {temp->next->prev = temp->prev;}
    delete temp;
}

public_contact* find_smallest_contact(public_contact* public_root)
{
    if (public_root == NULL)
        {return NULL;}
    else if (public_root->left_contact == NULL)
        {return public_root;}
    else 
        {return find_smallest_contact(public_root->left_contact);}
}


private_contact* find_smallest_contact(private_contact* private_root)
{
    if (private_root == NULL)
        {return NULL;}
    else if (private_root->left_contact == NULL)
        {return private_root;}
    else 
        {return find_smallest_contact(private_root->left_contact);}
}


public_contact* delete_contact(string name, public_contact* public_root)
{
    if(name < public_root->name)
    {
        public_root->left_contact = delete_contact(name, public_root->left_contact);
    }
    else if(name > public_root->name)
    {
        public_root->right_contact = delete_contact(name, public_root->right_contact);
    }
    else 
    {
        if(public_root->left_contact == NULL)
        {
            public_contact* temp = public_root->right_contact;
            delete public_root;
            return temp;
        }
        else if(public_root->right_contact == NULL)
        {
            public_contact* temp = public_root->left_contact;
            delete public_root;
            return temp;
        }
        else
        {
            public_contact* temp;
            temp = find_smallest_contact(public_root->right_contact);
            public_root->name = temp->name;
            public_root->right_contact = delete_contact(temp->name, public_root->right_contact);
        }
    }
    
    return public_root;
}


private_contact* delete_contact(string name, private_contact* private_root)
{
    if(name < private_root->name)
    {
        private_root->left_contact = delete_contact(name, private_root->left_contact);
    }
    else if(name > private_root->name)
    {
        private_root->right_contact = delete_contact(name, private_root->right_contact);
    }
    else 
    {
        if(private_root->left_contact == NULL)
        {
            private_contact* temp = private_root->right_contact;
            delete private_root;
            return temp;
        }
        else if(private_root->right_contact == NULL)
        {
            private_contact* temp = private_root->left_contact;
            delete private_root;
            return temp;
        }
        else
        {
            private_contact* temp;
            temp = find_smallest_contact(private_root->right_contact);
            private_root->name = temp->name;
            private_root->right_contact = delete_contact(temp->name, private_root->right_contact);
        }
    }
    
    return private_root;
}


void make_call(string name, string ph_num, string call_type, string call_time, call* &call_head)
{

    call* temp;
    temp = call_head;
    call* new_call = new call(name, ph_num, call_type, call_time);
    new_call->prev = NULL;
    new_call->next = call_head;
    if (call_head != NULL)
        {call_head->prev = new_call;}
    call_head = new_call;
}

void display(call* call_head)
{
    call* temp;
    temp = call_head;
    while(temp!=NULL)
    {
        if(temp->call_type == "public")
        {
            cout<<temp->name<<endl;
            cout<<temp->ph_num<<endl;
            cout<<temp->call_time<<endl;
        }
        else
        {
            cout<<"Private Contact"<<endl;
            cout<<temp->call_time<<endl;
        }
        cout<<"-----------------------------------------"<<endl;
        temp = temp->next;
    }
}


int main()
{
    public_contact* public_root = NULL;
    private_contact* private_root = NULL;
    
    blocked_public_contact* blocked_public_head = NULL;
    blocked_private_contact* blocked_private_head = NULL;
    
    call* call_head = NULL;
    
    cout<<"------------------------------------PHONE BOOK----------------------------------------"<<endl;
    cout<<endl;
    HOME:
    char choice;
    cout<<"--------------------HOME------------------------"<<endl;
    cout<<"Press 1 to SEARCH contact"<<endl;
    cout<<"Press 2 to ADD contact"<<endl;
    cout<<"Press 3 to check settings"<<endl;
    cout<<"Press 4 to Display contacts"<<endl;
    cout<<"Press 5 to Display Call History"<<endl;
    cout<<"Press 6 for KEYPAD"<<endl;
    cin>>choice;
    
    switch(choice)
    {
        case '1':
        {
            cout<<"--------------------SEARCH------------------------"<<endl;
            char contact_choice;
            
            SEARCH_HOME_PAGE:
            cout<<"Press 1 to search for public contact"<<endl;
            cout<<"Press 2 to search for private contact"<<endl;
            cout<<"Press any other KEY to go back to HOME"<<endl;
            cin>>contact_choice;
            
            switch(contact_choice)
            {
                case '1':
                {
                    public_contact *result;
                    string search_name;
                    
                    ENTER_PUBLIC_CONTACT:
                    cout<<"Enter contact name"<<endl;
                    cin.ignore();
                    getline(cin,search_name);
                    result = search_contact(search_name,public_root);
                    if(result == NULL)
                    {
                        char choice;
                        cout<<"Contact NOT found"<<endl;
                        PUBLIC_LABEL_1:
                        cout<<"Press T/t to try again"<<endl;
                        cout<<"Press B/b to BACK"<<endl;
                        cin>>choice;
                        if(choice=='T' || choice=='t')
                        {
                            goto ENTER_PUBLIC_CONTACT;
                        }
                        else if(choice=='B' || choice=='b')
                        {
                            goto SEARCH_HOME_PAGE;
                        }
                        else
                        {
                            goto PUBLIC_LABEL_1;
                        }
                    }
                    else
                    {
                        char choice;
                        cout<<"Contact Found"<<endl;
                        SHOW_PUBLIC_DETAILS:
                        bool block_check = block_checking(result->name,blocked_public_head);
                        if(block_check==true)
                        {
                            char choice;
                            cout<<"Contact Blocked"<<endl;
                            cout<<"Press U/u to Unblock "<<result->name<<endl;
                            cout<<"Press any other KEY to BACK"<<endl;
                            cin>>choice;
                            if(choice=='U' || choice=='u')
                            {
                                unblock(result->name,blocked_public_head);
                                cout<<result->name<<" is unblocked successfully"<<endl;
                                goto SEARCH_HOME_PAGE;
                            }
                            else
                            {
                                goto SEARCH_HOME_PAGE;
                            }
                        }
                        else{
                        cout<<"Name = "<<result->name<<endl;
                        cout<<"Phone Number = "<<result->ph_num<<endl;
                        cout<<"Press 1 to call"<<endl;
                        cout<<"Press 2 to delete"<<endl;
                        cout<<"Press 3 to block"<<endl;
                        cout<<"Press 4 to edit name"<<endl;
                        cout<<"Press any other KEY to BACK"<<endl;
                        cin>>choice;
                        switch(choice)
                        {
                            case '1':
                            {
                                for(int i=0; i<3; i++)
                                {
                                    cout<<"calling..."<<endl;
                                    Sleep(1000);
                                }

                                string call_time = get_current_time();

                                if(call_head == NULL)
                                {
                                    call_head = new call(result->name,result->ph_num, "public", call_time);
                                }
                                else
                                {
                                    make_call(result->name,result->ph_num, "public", call_time, call_head);
                                }
                                cout<<"Successfully called "<<result->name<<endl;
                                char input;
                                cout<<"Press any key to BACK"<<endl;
                                cin>>input;
                                if(input=='i')
                                {
                                    goto SEARCH_HOME_PAGE;
                                }
                                else{
                                    goto SEARCH_HOME_PAGE;
                                }
                            }
                            break;
                            case '2':
                            {
                                cout<<result->name<<" is deleted successfully"<<endl;
                                delete_contact(result->name, public_root);
                                goto SEARCH_HOME_PAGE;
                            }
                            break;
                            case '3':
                            {
                                if(blocked_public_head==NULL)
                                {
                                    blocked_public_head = new blocked_public_contact(result->name, result->ph_num);
                                    cout<<result->name<<" is blocked successfully"<<endl;
                                    goto SHOW_PUBLIC_DETAILS;
                                }
                                else
                                {
                                    block(result->name, result->ph_num, blocked_public_head);
                                    cout<<result->name<<" is blocked successfully"<<endl;
                                    goto SHOW_PUBLIC_DETAILS;
                                }
                            }
                            break;
                            case '4':
                            {
                                string new_name;
                                cout<<"Enter new name for "<<result->name<<endl;
                                cin.ignore();
                                getline(cin,new_name);
                                result->name = new_name;
                                cout<<"Name changed to "<<result->name<<" successfully"<<endl;
                                goto SHOW_PUBLIC_DETAILS;
                            }
                            break;
                            default:
                            {
                                goto SEARCH_HOME_PAGE;
                            }
                        }}
                    }
                }
                break;
                case '2':
                {
                    string entered_pin;
                    private_contact *result;
                    string search_name;
                    int attempts = 0;
                    string auth_result;
                    do
                    {
                        cout<<"Enter PIN"<<endl;
                        cin>>entered_pin;
                        auth_result = pin_authentication(entered_pin);
                        if(auth_result=="failed")
                        {
                            cout<<"Wrong PIN. Try again"<<endl;
                        }
                        else
                        {
                            ENTER_PRIVATE_CONTACT:
                            cout<<"Enter contact name"<<endl;
                            cin.ignore();
                            getline(cin,search_name);
                            result = search_contact(search_name,private_root);
                            if(result == NULL)
                            {
                                char choice;
                                cout<<"Contact NOT found"<<endl;
                                PRIVATE_LABEL_1:
                                cout<<"Press T/t to try again"<<endl;
                                cout<<"Press B/b to BACK"<<endl;
                                cin>>choice;
                                if(choice=='T' || choice=='t')
                                {
                                    goto ENTER_PRIVATE_CONTACT;
                                }
                                else if(choice=='B' || choice=='b')
                                {
                                    goto SEARCH_HOME_PAGE;
                                }
                                else
                                {
                                    goto PRIVATE_LABEL_1;
                                }
                            }
                            else
                            {
                                cout<<"Contact Found"<<endl;
                                SHOW_PRIVATE_DETAILS:
                                bool block_check = block_checking(result->name,blocked_private_head);
                                if(block_check==true)
                                {
                                    char choice;
                                    cout<<"Contact Blocked"<<endl;
                                    cout<<"Press U/u to Unblock "<<result->name<<endl;
                                    cout<<"Press any other KEY to BACK"<<endl;
                                    cin>>choice;
                                    if(choice=='U' || choice=='u')
                                    {
                                        unblock(result->name,blocked_private_head);
                                        cout<<result->name<<" is unblocked successfully"<<endl;
                                        goto SEARCH_HOME_PAGE;
                                    }
                                    else
                                    {
                                        goto SEARCH_HOME_PAGE;
                                    }
                                }
                                else{
                                cout<<"Name = "<<result->name<<endl;
                                cout<<"Phone Number = "<<result->ph_num<<endl;
                                cout<<"Press 1 to call"<<endl;
                                cout<<"Press 2 to delete"<<endl;
                                cout<<"Press 3 to block"<<endl;
                                cout<<"Press 4 to edit name"<<endl;
                                cout<<"Press any other KEY to BACK"<<endl;
                                cin>>choice;
                                switch(choice)
                                {
                                    case '1':
                                    {
                                        for(int i=0; i<3; i++)
                                        {
                                            cout<<"calling..."<<endl;
                                            Sleep(1000);
                                        }

                                        string call_time = get_current_time();

                                        if(call_head == NULL)
                                        {
                                            call_head = new call(result->name,result->ph_num, "private", call_time);
                                        }
                                        else
                                        {
                                            make_call(result->name,result->ph_num, "private", call_time, call_head);
                                        }

                                        cout<<"Successfully called "<<result->name<<endl;
                                        char input;
                                        cout<<"Press any key to BACK"<<endl;
                                        cin>>input;
                                        if(input=='i')
                                        {
                                            goto SEARCH_HOME_PAGE;
                                        }
                                        else{
                                            goto SEARCH_HOME_PAGE;
                                        }
                                    }
                                    break;
                                    case '2':
                                    {
                                        cout<<result->name<<" is deleted successfully"<<endl;
                                        delete_contact(result->name, private_root);
                                        goto SEARCH_HOME_PAGE;
                                    }
                                    break;
                                    case '3':
                                    {
                                        if(blocked_private_head==NULL)
                                        {
                                            blocked_private_head = new blocked_private_contact(result->name, result->ph_num);
                                            cout<<result->name<<" is blocked successfully"<<endl;
                                            goto SHOW_PRIVATE_DETAILS;
                                        }
                                        else
                                        {
                                            block(result->name, result->ph_num, blocked_private_head);
                                            cout<<result->name<<" is blocked successfully"<<endl;
                                            goto SHOW_PRIVATE_DETAILS;
                                        }
                                    }   
                                    break;
                                    case '4':
                                    {
                                        string new_name;
                                        cout<<"Enter new name for "<<result->name<<endl;
                                        cin.ignore();
                                        getline(cin,new_name);
                                        result->name = new_name;
                                        cout<<"Name changed to "<<result->name<<" successfully"<<endl;
                                        goto SHOW_PRIVATE_DETAILS;
                                    }
                                    break;
                                    default:
                                    {
                                        goto SEARCH_HOME_PAGE;
                                    }
                                }}
                            }
                        }
                        attempts++;
                    }
                    while(auth_result=="failed" && attempts<3);
                }
                break;
                default:
                {
                    goto HOME;
                }
            }
        }
        break;
        case '2':
        {
            cout<<"--------------------ADD CONTACT------------------------"<<endl;
            char contact_choice;
            ADD_HOME_PAGE:
            cout<<"Press 1 to add a public contact"<<endl;
            cout<<"Press 2 to add a private contact"<<endl;
            cout<<"Press any other KEY to back to HOME"<<endl;
            cin>>contact_choice;
            switch(contact_choice)
            {
                case '1':
                {
                    string contact_name,contact_num;
                    ADD_PUBLIC_CONTACT:
                    cout<<"Contact Name: ";
                    cin.ignore();
                    getline(cin,contact_name);
                    cout<<"Contact Number: ";
                    cin>>contact_num;
                    cout<<endl;
                    if(public_root == NULL)
                    {
                        public_root = new public_contact(contact_name,contact_num);
                    }
                    else
                    {
                        insert_contact(contact_name,contact_num,public_root);
                    }
                    char choice;
                    cout<<"Contact Saved"<<endl;
                    PUBLIC_LABEL_2:
                    cout<<"Press A/a to save another contact"<<endl;
                    cout<<"Press B/b to BACK"<<endl;
                    cin>>choice;
                    if(choice=='A' || choice=='a')
                    {
                        goto ADD_PUBLIC_CONTACT;
                    }
                    else if(choice=='B' || choice=='b')
                    {
                        goto ADD_HOME_PAGE;
                    }
                    else
                    {
                        goto PUBLIC_LABEL_2;
                    }
                }
                break;
                case '2':
                {
                    int attempt = 0;
                    string PIN;
                    string auth_result;
                    do
                    {
                        cout<<"Enter Personal Identification Number(PIN)"<<endl;
                        cin>>PIN;
                        auth_result = pin_authentication(PIN);
                        if(auth_result == "successfull")
                        {
                            string contact_name,contact_num;
                            ADD_PRIVATE_CONTACT:
                            cout<<"Contact Name: ";
                            cin.ignore();
                            getline(cin,contact_name);
                            cout<<"Contact Number: ";
                            cin>>contact_num;
                            cout<<endl;
                            if(private_root == NULL)
                            {
                                private_root = new private_contact(contact_name,contact_num);
                            }
                            else
                            {
                                insert_contact(contact_name,contact_num,private_root);
                            }
                            cout<<"Contact Saved"<<endl;
                            PRIVATE_LABEL_2:
                            cout<<"Press A/a to save another contact"<<endl;
                            cout<<"Press B/b to BACK"<<endl;
                            cin>>choice;
                            if(choice=='A' || choice=='a')
                            {
                                goto ADD_PRIVATE_CONTACT;
                            }
                            else if(choice=='B' || choice=='b')
                            {
                                goto ADD_HOME_PAGE;
                            }
                            else
                            {
                                goto PRIVATE_LABEL_2;
                            }
                        }
                        else
                        {
                            cout<<"Wrong PIN"<<endl;
                        }
                        attempt++;
                        if(attempt == 3)
                        {
                            goto ADD_HOME_PAGE;
                        }
                    }
                    while(auth_result == "failed" && attempt<3);
                }
                break;
                default:
                {
                    goto HOME;
                }
            }
            
        }
        break;
        case '3':
        {
            cout<<"--------------------SETTINGS------------------------"<<endl;
            char settings_choice;
            SETTINGS:
            cout<<"Press 1 to change PIN"<<endl;
            cout<<"Press 2 to visit Blocked contacts"<<endl;
            cout<<"Press any other KEY to BACK"<<endl;
            cin>>settings_choice;
            switch(settings_choice)
            {
                case '1':
                {
                    string current_pin;
                    int attempts = 0;
                    string auth_result;
                    do
                    {
                        cout<<"Enter old PIN (For Security purpose)"<<endl;
                        cin>>current_pin;
                        auth_result = pin_authentication(current_pin);
                        if(auth_result =="successfull")
                        {
                            cout<<"Enter new PIN"<<endl;
                            cin>>correct_PIN;
                            cout<<"PIN changed successfully"<<endl;
                            goto SETTINGS;
                        }
                        else
                        {
                            cout<<"Incorrect PIN. Please enter correct current PIN to change your PIN"<<endl;
                        }
                        attempts++;
                        if(attempts == 3)
                        {
                            goto SETTINGS;
                        }
                    }
                    while(auth_result =="failed" && attempts<3);
                }
                break;
                case '2':
                {
                    char choice;
                    VISIT_BLOCKED_CONTACTS:
                    cout<<"Press 1 to visit Blocked public contacts"<<endl;
                    cout<<"Press 2 to visit Blocked private contacts"<<endl;
                    cout<<"Press any other KEY to BACK"<<endl;
                    cin>>choice;
                    switch(choice)
                    {
                        case '1':
                        {
                            display(blocked_public_head);
                            char input;
                            UNBLOCK:
                            cout<<"Press U/u to unblock any contact"<<endl;
                            cout<<"Press B/b to BACK"<<endl;
                            cin>>input;
                            if(input=='B' || input=='b')
                            {
                                goto VISIT_BLOCKED_CONTACTS;
                            }
                            else if(input=='U' || input=='u')
                            {
                                string name;
                                cout<<"Enter the name of the contact u want to unblock"<<endl;
                                cin.ignore();
                                getline(cin,name);
                                unblock(name,blocked_public_head);
                                cout<<name<<" is unblocked successfully"<<endl;
                                goto UNBLOCK;
                            }
                        }
                        break;
                        case '2':
                        {
                            int attempt = 0;
                            string PIN;
                            string auth_result;
                            do
                            {
                                cout<<"Enter Personal Identification Number(PIN)"<<endl;
                                cin>>PIN;
                                auth_result = pin_authentication(PIN);
                                if(auth_result == "successfull")
                                {
                                    display(blocked_private_head);
                                    char input;
                                    cout<<"Press B/b to BACK"<<endl;
                                    cin>>input;
                                    if(input=='B' || input=='b')
                                    {
                                        goto VISIT_BLOCKED_CONTACTS;
                                    }
                                }
                                else
                                {
                                    cout<<"Incorrect PIN"<<endl;
                                }
                                attempt++;
                                if(attempt == 3)
                                {
                                    goto VISIT_BLOCKED_CONTACTS;
                                }
                            }
                            while(auth_result == "failed" && attempt<3);
                            
                        }
                        break;
                        default:
                        {
                            goto SETTINGS;
                        }
                    }
                }
                break;
                default:
                {
                    goto HOME;
                }
            }
        }
        break;
        case '4':
        {
            cout<<"--------------------DISPLAY CONTACTS------------------------"<<endl;
            char choice;
            DISPLAY_CONTACTS:
            cout<<"Press 1 to Display public contacts"<<endl;
            cout<<"Press 2 to Display private contacts"<<endl;
            cout<<"Press any other KEY to BACK"<<endl;
            cin>>choice;
            switch(choice)
            {
                case '1':
                {
                    char input;
                    cout<<"NAME"<<"\t\t "<<"CONTACT NUMBER"<<endl;
                    display(public_root);
                    cout<<"Press any KEY to BACK"<<endl;
                    cin>>input;
                    if(input=='1')
                    {
                        goto DISPLAY_CONTACTS;
                    }
                    else
                    {
                        goto DISPLAY_CONTACTS;
                    }
                }
                break;
                case '2':
                {
                    int attempt = 0;
                    string PIN;
                    string auth_result;
                    do
                    {
                        cout<<"Enter Personal Identification Number(PIN)"<<endl;
                        cin>>PIN;
                        auth_result = pin_authentication(PIN);
                        if(auth_result == "successfull")
                        {
                            cout<<"NAME"<<"\t\t "<<"CONTACT NUMBER"<<endl;
                            display(private_root);
                            char input;
                            cout<<"Press any KEY to BACK"<<endl;
                            cin>>input;
                            if(input=='1')
                            {
                                goto DISPLAY_CONTACTS;
                            }
                            else
                            {
                                goto DISPLAY_CONTACTS;
                            }
                        }
                        else
                        {
                            cout<<"Incorrect PIN"<<endl;
                        }
                        attempt++;
                        if(attempt == 3)
                        {
                            goto DISPLAY_CONTACTS;
                        }
                    }
                    while(auth_result == "failed" && attempt<3);
                }
                break;
                default:
                {
                    goto HOME;
                }
            }
        }
        break;
        case '5':
        {
            cout<<"--------------------CALL HISTORY------------------------"<<endl;
            display(call_head);
            char input;
            BACK_FEATURE_IN_DISPLAY_FUNCTION:
            cout<<"Press B/b to go BACK to HOME"<<endl;
            cin>>input;
            if(input=='B' || input=='b')
            {
                goto HOME;
            }
            else
            {
                cout<<"Invalid Input"<<endl;
                goto BACK_FEATURE_IN_DISPLAY_FUNCTION;
            }
        }
        break;
        case '6':
        {
            cout<<"--------------------KEYPAD------------------------"<<endl;
            string number;
            char choice;
            ENTER_NUMBER:
            cout<<"Enter the Phone Number to call"<<endl;
            cin>>number;
            UNKNOWN_NUM_HANDLE:
            cout<<"Press 1 to call"<<endl;
            cout<<"Press 2 to add to contacts"<<endl;
            cout<<"Press 3 to block"<<endl;
            cout<<"Press any other Key to BACK"<<endl;
            cin>>choice;
            switch(choice)
            {
                case '1':
                {
                    for(int i=0; i<3; i++)
                    {
                        cout<<"calling..."<<endl;
                        Sleep(1000);
                    }

                    string call_time = get_current_time();
                    if(call_head == NULL)
                    {
                        call_head = new call("UNKNOWN",number, "public", call_time);
                    }
                    else
                    {
                        make_call("UNKNOWN",number, "public", call_time, call_head);
                    }
                    
                    cout<<"Successfully called "<<number<<endl;
                    goto HOME;
                }
                break;
                case '2':
                {
                    char choice;
                    cout<<"Press 1 to add to Public Contacts"<<endl;
                    cout<<"Press 2 to add to Private Contacts"<<endl;
                    cout<<"Press any other Key to BACK"<<endl;
                    cin>>choice;
                    switch(choice)
                    {
                        case '1':
                        {
                            string name;
                            cout<<"Enter Name: ";
                            cin.ignore();
                            getline(cin,name);
                            if(public_root == NULL)
                            {
                                public_root = new public_contact(name,number);
                            }
                            else
                            {
                                insert_contact(name,number,public_root);
                            }
                            char input;
                            cout<<number<<" is saved as "<<name<<" in public contacts"<<endl;
                            TO_BACK:
                            cout<<"Press B/b to BACK"<<endl;
                            cin>>input;
                            if(input=='B' || input=='b')
                            {
                                goto HOME;
                            }
                            else
                            {
                                cout<<"Invalid Input"<<endl;
                                goto TO_BACK;
                            }
                        }
                        break;
                        case '2':
                        {
                            int attempt = 0;
                            string PIN;
                            string auth_result;
                            do
                            {
                                cout<<"Enter Personal Identification Number(PIN)"<<endl;
                                cin>>PIN;
                                auth_result = pin_authentication(PIN);
                                if(auth_result == "successfull")
                                {
                                    string name;
                                    cout<<"Enter Name: ";
                                    cin.ignore();
                                    getline(cin,name);
                                    if(private_root == NULL)
                                    {
                                        private_root = new private_contact(name,number);
                                    }
                                    else
                                    {
                                        insert_contact(name,number,private_root);
                                    }
                                    char input;
                                    cout<<number<<" is saved as "<<name<<" in private contacts"<<endl;
                                    TO_BACK_2:
                                    cout<<"Press B/b to BACK"<<endl;
                                    cin>>input;
                                    if(input=='B' || input=='b')
                                    {
                                        goto HOME;
                                    }
                                    else
                                    {
                                        cout<<"Invalid Input"<<endl;
                                        goto TO_BACK_2;
                                    }
                                }
                                else
                                {
                                    cout<<"Incorrect PIN"<<endl;
                                }
                                attempt++;
                                if(attempt == 3)
                                {
                                    goto UNKNOWN_NUM_HANDLE;
                                }
                            }
                            while(auth_result == "failed" && attempt<3);
                        }
                        break;
                        default:
                        {
                            goto UNKNOWN_NUM_HANDLE;
                        }
                    }
                }
                break;
                case '3':
                {
                    if(blocked_public_head ==  NULL)
                    {
                        blocked_public_head = new blocked_public_contact("UNKNOWN", number);
                    }
                    else
                    {
                        block("UNKNOWN", number, blocked_public_head);
                    }
                    cout<<"Number is blocked Successfully"<<endl;
                    goto HOME;
                }
                break;
                default:
                {
                   goto ENTER_NUMBER;
                }
            }
        }
        break;
        default:
        {
            char choice;
            cout<<"Invalid Input"<<endl;
            cout<<"Press T/t to Try again"<<endl;
            cout<<"Press any other KEY to exit program"<<endl;
            cin>>choice;
            if(choice=='T' || choice=='t')
            {
                goto HOME;
            }
            else
            {
                cout<<"Exiting the Phone Book"<<endl;
                exit(0);
            }
        }
    }
}