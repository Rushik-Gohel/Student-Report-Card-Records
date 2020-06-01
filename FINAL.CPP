#include<fstream.h>
#include<iomanip.h>
#include<stdio.h>
#include<conio.h>
#include<graphic.h>
#include<string.h>
#include<process.h>
#include<stdlib.h>
#include<dos.h>


class Stud
{
	int rollno;
	char name[50];
	int phym, chem, matm, engm, csm;
	float per;
	char grade;
	void calculate();
public:
	void getdata();
	void showdata();
	void show_tabular();
	int retrollno();
};


void Stud::calculate()
{
	per=(phym+chem+matm+engm+csm)/5.0;
	if(per>=80)
		grade='A';
	else if(per>=60)
		grade='B';
	else if(per>=40)
		grade='C';
	else if(per>=33)
		grade='D';
	else
		grade='F';
}

void Stud::getdata()
{
	cout<<"\nEnter Roll number of student: ";
	cin>>rollno;
	cout<<"\n\nEnter Name of student : ";
	gets(name);
	cout<<"\nEnter marks in physics (out of 100) : ";
	cin>>phym;
	cout<<"\nEnter marks in chemistry (out of 100) : ";
	cin>>chem;
	cout<<"\nEnter marks in maths (out of 100) : ";
	cin>>matm;
	cout<<"\nEnter marks in english (out of 100) : ";
	cin>>engm;
	cout<<"\nEnter marks in computer science (out of 100) : ";
	cin>>csm;
	calculate();
}

void Stud::showdata()
{
	cout<<"\nRoll number of student : "<<rollno;
	cout<<"\nName of student        : "<<name;
	cout<<"\nMarks in Physics       : "<<phym;
	cout<<"\nMarks in Chemistry     : "<<chem;
	cout<<"\nMarks in Maths         : "<<matm;
	cout<<"\nMarks in English       : "<<engm;
	cout<<"\nMarks in Computer Sci. : "<<csm;
	cout<<"\nPercentage of student  : "<<per;
	cout<<"\nGrade of student is    : "<<grade;
}

void Stud::show_tabular()
{
	cout<<rollno<<setw(6)<<" "<<name<<setw(10)<<phym<<setw(4)<<chem<<setw(4)<<matm<<setw(4)
		<<engm<<setw(4)<<csm<<setw(6)<<per<<setw(6)<<" "<<grade<<endl;
}

int  Stud::retrollno()
{
	return rollno;
}


void write_student();
void display_all();
void display_sp(int);
void modify_student(int);
void delete_student(int);
void class_result();
void result();
void intro();
void entry_menu();
void entry_menu1();
void login();


int main()
{
	char ch;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2);
	clrscr();
	intro();
	login();
	do
	{
		clrscr();
		int dd=DETECT,dm;
		initgraph(&dd,&dm,"tc:\bgi");
		settextstyle(8,0,3);
		outtextxy(240,30,"MAIN MENU");
		cout<<"\n\n\n\n\n\n\n\t1. RESULT MENU";
		cout<<"\n\n\t2. ADD RECORD";
		cout<<"\n\n\t3. MODIFY RECORD";
		cout<<"\n\n\t4. EXIT";
		cout<<"\n\n\tEnter choice (1-4):";
		cin>>ch;
		sound(500);
		delay(250);
		nosound();
		clrscr();
		switch(ch)
		{
			case '1': result();
				break;
			case '2': entry_menu();
				break;
			case '3': entry_menu1();
				break;
			case '4':
				break;
			default :cout<<"\a";
		}
	}while(ch!='4');
	getch();
	return 0;
}

void write_student()
{
	Stud st;
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	st.getdata();
	outFile.write((char *) &st, sizeof(Stud));
	outFile.close();
	cout<<"\n\nRecord Successfully Created ";
	cin.ignore();
	getch();
}

void display_all()
{
	Stud st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"ERROR!!File could not be open !!";
		cout<<"\nPress any key to continue...";
		getch();
		return;
	}
	int dd=DETECT,dm;
	initgraph(&dd,&dm,"tc:\bgi");
	settextstyle(8,0,3);
	outtextxy(180,30,"ALL STUDENT RECORDS");
	cout<<"\n\n\n\n\n";
	while(inFile.read((char *) &st, sizeof(Stud)))
	{
		st.showdata();
		cout<<"\n\n====================================\n";
	}
	inFile.close();
	getch();
}

void display_sp(int n)
{
	Stud st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"ERROR!!File could not be open!! ";
		cout<<"\nPress any key to continue...";
		getch();
		return;
	}

	int flag=0;
	while(inFile.read((char *) &st, sizeof(Stud)))
	{
		if(st.retrollno()==n)
		{
			 st.showdata();
			 flag=1;
		}
	}
	inFile.close();
	if(flag==0)
		cout<<"\n\nSorry!Record does not exist.";
	getch();
}

void modify_student(int n)
{
	int found=0;
	Stud st;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"ERROR!!File could not be open !!";
		cout<<"\nPress any key to continue...";
		getch();
		return;
	}
	while(File.read((char *) &st, sizeof(Stud)) && found==0)
	{
		if(st.retrollno()==n)
		{
			st.showdata();
			cout<<"\n\nEnter New Details of student"<<endl;
			st.getdata();
			int pos=(-1)*sizeof(st);
			File.seekp(pos,ios::cur);
			File.write((char *) &st, sizeof(Stud));
			cout<<"\n\n\t Record successfully updated!";
			found=1;
		}
	}
	File.close();
	if(found==0)
		cout<<"\n\nSorry!Record Not Found ";
	getch();
}

void delete_student(int n)
{
	Stud st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"ERROR!!File could not be open !!";
		cout<<"\nPress any key to continue...";
		getch();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char *) &st, sizeof(Stud)))
	{
		if(st.retrollno()!=n)
		{
			outFile.write((char *) &st, sizeof(Stud));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	cout<<"\n\n\tRecord succesfully deleted ..";
	getch();
}

void class_result()
{
	Stud st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"ERROR!!File could not be open !!";
		cout<<"\nPress any Key to continue...";
		getch();
		return;
	}

	int dd=DETECT,dm;
	initgraph(&dd,&dm,"tc:\bgi");
	settextstyle(8,0,3);
	outtextxy(180,30,"ALL STUDENTS RESULT");
		cout<<"\n\n\n\n\n";
	cout<<"________________________________________________________\n";
	cout<<"R.No       Name        P   C   M   E   CS   %age   Grade"<<endl;
	cout<<"________________________________________________________\n";
	while(inFile.read((char *) &st, sizeof(Stud)))
	{
		st.show_tabular();
	}
	getch();
	inFile.close();
}

void result()
{
	char ch;
	int rno;
	int dd=DETECT,dm;
		initgraph(&dd,&dm,"tc:\bgi");
		settextstyle(8,0,3);
		outtextxy(240,30,"RESULT MENU");
		cout<<"\n\n\n\n\n";
	cout<<"\n\n\n\t1. CLASS RESULT";
	cout<<"\n\n\t2. STUDENT REPORT CARD";
	cout<<"\n\n\t3. BACK TO MAIN MENU";
	cout<<"\n\n\n\tENTER CHOICE (1-3): ";
	cin>>ch;
	sound(500);
	delay(250);
	nosound();
	clrscr();
	switch(ch)
	{
	case '1' :class_result(); break;
	case '2' :cout<<"\n\n\tEnter Roll Number Of Student : ";
		  cin>>rno;
		  display_sp(rno); break;
	case '3' :break;
	default :cout<<"\a";
	}
}

void intro()
{
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"tc:\bgi");
	settextstyle(7,0,4);
	outtextxy(56,30,"COMPUTER SCIENCE PROJECT");
	settextstyle(7,0,3);
	outtextxy(230,100,"REPORT CARD");
	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t   DEVELOPER : MANAN PATEL\n\n";
	cout<<"\t\t\t\t  CLASS 12-A";
	getch();

}

void entry_menu()
{
	char ch;
	int num;
	clrscr();
	int dd=DETECT,dm;
		initgraph(&dd,&dm,"tc:\bgi");
		settextstyle(8,0,3);
		outtextxy(240,30,"ADD MENU");
		cout<<"\n\n\n\n\n";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
	cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
	cout<<"\n\n\t4.BACK TO MAIN MENU";
	cout<<"\n\n\tEnter Your Choice (1-4) ";
	cin>>ch;
	sound(500);
	delay(250);
	nosound();
	clrscr();
	switch(ch)
	{
	case '1':	write_student(); break;
	case '2':	display_all(); break;
	case '3':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
			display_sp(num); break;

	case '4':	break;
	default:	cout<<"\a"; entry_menu();
	}
}
void entry_menu1()
{
	char ch;
	int num;
	clrscr();
	int dd=DETECT,dm;
		initgraph(&dd,&dm,"tc:\bgi");
		settextstyle(8,0,3);
		outtextxy(240,30,"MODIFY MENU");
		cout<<"\n\n\n\n\n";
	cout<<"\n\n\t1.DISPLAY ALL STUDENTS RECORDS";
	cout<<"\n\n\t2.MODIFY STUDENT RECORD";
	cout<<"\n\n\t3.DELETE STUDENT RECORD";
	cout<<"\n\n\t4.BACK TO MAIN MENU";
	cout<<"\n\n\tEnter Your Choice (1-4) ";
	cin>>ch;
	sound(500);
	delay(250);
	nosound();
	clrscr();
	switch(ch)
	{
	case '1':	display_all(); break;

	case '2':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
			modify_student(num);break;
	case '3':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
			delete_student(num);break;
	case '4':	break;
	default:	cout<<"\a"; entry_menu1();
	}
}
void login()
{system("cls");
 char user[30],usern[30],pass[30],passn[30];
 int x=0,a=0,p=0,len=0;
 strcpy(user,"system");
 strcpy(pass,"manager");
 int dd=DETECT,dm;
	initgraph(&dd,&dm,"tc:\bgi");
	settextstyle(10,0,3);
	outtextxy(260,30,"LOGIN");
 cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t     USERNAME:";
 gets(usern);
 if(strcmp(usern,user)==0)
 x++;
 cout<<"\t\t\t     PASSWORD:";
 for(int i=0;i<40;i++)
 {passn[i]=getch();
  cout<<"*";
  a++;
  if(passn[i]==13)
  break;
  }
 len=strlen(pass);
 for(i=0;i<len;i++)
 {if(pass[i]==passn[i])
  p++;
 }
 if(len==p&&x==1)
 {cout<<"\n\n\t\t\t     ACCESS GRANTED!";
  sound(700);
  delay(250);
  nosound();
  cout<<"\n\t\t\t        LOADING...";
  cout<<endl;
  for(int i=0;i<80;i++)
  {cout<<"_";
   delay(50);
  }
  cout<<"\n\t\t\t       PRESS ENTER";
 }
 else
 {cout<<"\n\n\t\t\t     ACCESS DENIED!";
  getch();
  exit(0);
 }
 getch();
}


//_________________________THANK_YOU_______________________________________
