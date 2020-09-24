#include <iostream>
#include <fstream>
#include <curses.h>
#include <assert.h> 
#include "coord.h"  
#include <string>  
using namespace std;
fstream uname, upass;
char c;  
string password; 
string temp1, temp2;
string username;
int movement;
enum movement {ebox,pbox,obox,cbox};
coord frontcursorloc[4]={coord(22,4),coord(22,7),coord(20,13),coord(38,13)}; 

void cycletab(){
    int i=movement++%4;
    move(frontcursorloc[i].my,frontcursorloc[i].mx);
    cout << frontcursorloc[i].my;
} 

void nxtbox(){
noecho();
keypad(stdscr, TRUE);  
cycletab();

while (int c=getch()){
int tab=(movement%4==0)?3:movement%4-1;
assert(tab >= 0 && tab < 4);
switch (c){ 

	case 10:
  case -53:
		//if (c==' '){ 
			if(tab==obox)return;
			if(tab==cbox){
   	 	username="<no input>";
    	password="<no input>"; 
			break;
			}
      break;
		//}

	case KEY_RIGHT:
		cycletab();
		break;

	/*case KEY_LEFT:
			backcycletab1();
	break;*/
 
	default:
    switch(tab){ 
      case ebox:
      if(int(c)!=127)printw("%c",c);
       username.append(1,c);
      break;
			case pbox:
       if(int(c)!=127)printw("%c",'*');
       password.append(1,c);
      break;
        }

}
}
}

 
void displayLogin(){  
	initscr();
	int x=0, y=1, w=60, h=15;
	WINDOW *win = newwin(h,w,y,x);
	refresh();
	move(1, 27);
	attron(A_BOLD);
	printw("LOGIN");
	box(win, 0, 0);
	wrefresh(win);
}

void displayEmail(){
	mvprintw(4,4,"Username");
	WINDOW* ebox = newwin(3, 35, 3, 20);
	refresh();
	box(ebox, 0, 0); 
	wrefresh(ebox);
}

void displayPassword(){
	mvprintw(7, 4, "Password");
	WINDOW* pbox = newwin(3, 35, 6, 20);
	refresh();
	box(pbox, 0, 0);
	wrefresh(pbox);
}

void displayOkCancel(){
	WINDOW*  obox = newwin(3, 10, 12, 14);
	refresh();
	box(obox, 0, 0);
	attron(A_BOLD);
	mvwprintw(obox, 1, 1, "   OK");
	attron(A_BOLD);
	wrefresh(obox);


	WINDOW* cbox = newwin(3, 10, 12, 34);
	refresh();
	box(cbox, 0, 0);
	attron(A_BOLD); 
	mvwprintw(cbox,1, 1, " CANCEL");
	attron(A_BOLD);
	wrefresh(cbox);
}  
   
void resetpass(){
attron(A_UNDERLINE); 
mvprintw(10,21,"Reset password...");
attron(A_UNDERLINE);
} 

int verifyusername(){ 
		uname.open("names.txt"); 
			while (uname >> temp1) { 
				if (temp1.compare(username) == 0){
					cout<<"\n[ "<<username<<" ] has been found in the database.";	
					uname.close();
					return 1;
				}
				else{ 
					cout<<"\nACCESS DENIED [wrong username]";
					break;
				}
			}
		uname.close();
return 0; 
} 

int verifypass(){ 
			upass.open("pass.txt");
			while (upass >> temp2) { 
				if (temp2.compare(password) == 0){
					cout<<"\npass found.";
					upass.close();
					return 1;
				}
				else{
					cout<<"\nACCESS DENIED [wrong pass]";
					break; 
				} 
			}
			upass.close();
return 0; 
} 
  
int verifyboth(){
uname.open("names.txt"); 
upass.open("pass.txt");
	while ((upass >> temp2)&&(uname>>temp1)) {
		if (temp1.compare(username) ==0 && temp2.compare		(password) ==0){
			cout<<"\n\nyou can now login!!";
			uname.close();
			upass.close();
			return 1;
		}
		else {
			cout<<"\n\nyou can not login!!";
		break;
		}
	}
uname.close();
upass.close();
return 0;
}

int main(){
initscr(); 
noecho();
cbreak();
	displayLogin();
	displayEmail();
	displayPassword();
	resetpass();
	displayOkCancel();
	nxtbox();
	getch();
	endwin();
cout << "\n\nusername received was : " << username << endl;
cout << "passw obtained was : " << password << endl;
verifyusername();
verifypass();
verifyboth();
	return 0;
}