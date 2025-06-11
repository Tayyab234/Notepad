#include<iostream>
#include<fstream>
#include<conio.h>
#include<string>
#include<windows.h>
using namespace std;

// Cursor movement utility
void gotoxy(int x, int y) {
    COORD coord = {SHORT(x), SHORT(y)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Node of 2D Doubly Linked List
class node {
public:
    node* up;
    node* down;
    node* left;
    node* right;
    char da;

    node(char c = ' ') : up(nullptr), down(nullptr), left(nullptr), right(nullptr), da(c) {}
};

class pointer {
protected:
    node* Cline;
    node* Uline;
    node* Dline;

    void settle(node* temp) {
        Cline = temp;
        Uline = temp ? temp->up : nullptr;
        Dline = temp ? temp->down : nullptr;
    }

    void manageCurUp(node* temp1, node* temp2) {
        while (temp1 || temp2) {
            if (temp1 && temp2) {
                temp2->down = temp1;
                temp1->up = temp2;
            } else if (temp1) {
                temp1->up = nullptr;
            } else if (temp2) {
                temp2->down = nullptr;
            }
            if (temp1) temp1 = temp1->right;
            if (temp2) temp2 = temp2->right;
        }
    }

    void manageCurDown(node* temp1, node* temp2) {
        while (temp1 || temp2) {
            if (temp1 && temp2) {
                temp2->up = temp1;
                temp1->down = temp2;
            } else if (temp1) {
                temp1->down = nullptr;
            } else if (temp2) {
                temp2->up = nullptr;
            }
            if (temp1) temp1 = temp1->right;
            if (temp2) temp2 = temp2->right;
        }
    }

    void gethead(node*& temp) {
        while (temp && temp->left) temp = temp->left;
    }

    void Backspace(node*& temp) {
        if (!temp || !temp->left) return;
        settle(temp);
        node* cur = temp->left;
        node* cur1 = cur->left;
        if (cur1) cur1->right = temp;
        temp->left = cur1;
        delete cur;
        gethead(temp);
        manageCurUp(temp, Uline);
        manageCurDown(temp, Dline);
    }

    void Delete(node*& temp) {
        if (!temp) return;
        settle(temp);
        node* curL = temp->left;
        node* curR = temp->right;
        delete temp;
        if (curL) curL->right = curR;
        if (curR) curR->left = curL;
        temp = curR ? curR : curL;
        gethead(temp);
        manageCurUp(temp, Uline);
        manageCurDown(temp, Dline);
    }

    void Enter(node*& temp) {
        settle(temp);
        node* left = temp->left;
        node* right = temp->right;

        if (left) left->right = nullptr;
        if (right) right->left = nullptr;

        gethead(right);

        node* newline = new node(13);
        newline->up = Uline;
        if (Uline) Uline->down = newline;
        newline->down = Dline;
        if (Dline) Dline->up = newline;

        newline->right = right;
        if (right) right->left = newline;

        temp = newline;
    }

    void insertion1(node*& temp, char d) {
        node* newNode = new node(d);
        node* right = temp->right;
        temp->right = newNode;
        newNode->left = temp;
        if (right) {
            newNode->right = right;
            right->left = newNode;
        }
        temp = newNode;
    }

};

template<class T>
class TDLlist : private pointer {
public:
    node* head;
    node* tail;
    node* up1;
    node* cursor;
    int x, y;

    TDLlist() : head(nullptr), tail(nullptr), up1(nullptr), cursor(nullptr), x(0), y(0) {}

    void managecursor(char gh) {
        if (!cursor) return;
        if (gh == 75 && cursor->left) cursor = cursor->left, x--;
        else if (gh == 77 && cursor->right) cursor = cursor->right, x++;
        else if (gh == 72 && cursor->up) cursor = cursor->up, y--;
        else if (gh == 80 && cursor->down) cursor = cursor->down, y++;
    }

    void insertion(T d) {
        if (!head) {
            node* temp = new node(d);
            head = tail = up1 = cursor = temp;
            return;
        }

        if (cursor == tail) {
            node* temp = new node(d);
            if (d == 13) {
                Enter(cursor);
                up1 = cursor;
                tail = cursor;
                x = -1;
                y++;
            } else {
                tail->right = temp;
                temp->left = tail;
                temp->up = up1;
                if (up1) up1->down = temp;
                tail = cursor = temp;
                x++;
            }
        } else {
            if (d == 13) {
                Enter(cursor);
                up1 = cursor;
                tail = cursor;
                x = -1;
                y++;
            } else {
                insertion1(cursor, d);
                x++;
            }
        }
    }

    void delete2() {
        Delete(cursor);
        x--;
    }

    void backspace1() {
        Backspace(cursor);
        x--;
    }

    void Save() {
        ofstream out("file.txt");
        node* row = head;
        while (row) {
            node* col = row;
            while (col) {
                if (col->da != 13) out << col->da;
                col = col->right;
            }
            out << endl;
            row = row->down;
        }
        out.close();
    }

    void load() {
        ifstream in("file.txt");
        if (!in) return;
        string line;
        while (getline(in, line)) {
            for (char ch : line) insertion(ch);
            insertion(13);  // new line
        }
        in.close();
    }

    void Print() {
        system("CLS");
        node* row = head;
        while (row) {
            node* col = row;
            while (col) {
                if (col->da != 13) cout << col->da;
                col = col->right;
            }
            cout << '\n';
            row = row->down;
        }
        gotoxy(x, y);
    }
};

int main() {
    TDLlist<char> editor;
    while (true) {
        char c = _getch();
        if (c == 0) continue;
        if (c == 72 || c == 75 || c == 80 || c == 77) {
            editor.managecursor(c);
        } else if (c == 4) {
            editor.delete2();
        } else if (c == 8) {
            editor.backspace1();
        } else if (c == 19) {
            editor.Save();
        } else if (c == 12) {
            editor.load();
        } else {
            editor.insertion(c);
        }
        editor.Print();
    }
}
