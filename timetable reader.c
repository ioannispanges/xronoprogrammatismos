
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct courseintb{
	int course;
	struct courseintb *next;

};

typedef struct courseintb COURSEINTB;
typedef COURSEINTB *LINK4;

struct math{
	struct courseintb **timetable;
	double cost;
	struct math *next;
};
typedef struct math MATH;
typedef MATH *LINK3;


struct course
{
     int enrolment;
     int courses_num;
	struct course *next;
};

struct student{
	int student_id;
	int courses[16];
	struct student *next;
};

int lookforcourse(int coursetofind,struct courseintb **timetable,int timeslots);
double costforstudent(int *student,struct courseintb **timetable,int timeslots);
double calculatecost(struct student *ptr,struct courseintb **timetable,int timeslots);
typedef struct course COURSE;
typedef COURSE *LINK;
typedef struct student STUDENT;
typedef STUDENT *LINK2;
typedef struct sorted PROSTAKSINOMISI;
double distancecost(int A,int B);
struct math* Loadmath(struct student *ptrtostudentlist,int timeslots,int courses);
struct course *readcourseslist(int *a);
void printcourses( struct course *ptr,int crs_to_find);
struct student *load_student(void);
void printstudent(struct student *ptr,int Idlookup);
int choices(void);
void printallstudents(struct student *ptr);
struct course *ptr_to_crs=NULL;     //simeio opou krataei ton root tis courses list
struct student *ptr_to_std=NULL;    //simeio pou krataei ton root tis student list
int studentid_to_find,crs_to_find,main_number_of_courses=0;
struct math *ptrtothebest=NULL;
int timeslots;
struct courseintb** Make2dintArray(int arraySizeX);
void filltable(struct courseintb **timetable,int courses,int timeslots);
int main(void) {



	 printf("\nKalos itrthate ston xronoprogrammatismo exetasewn\n");

			printf("\nTi tha thelate na kanete ?\n\n");
		    while(1){
		    		switch(choices()){
		    											case 1: ptr_to_crs=readcourseslist(&main_number_of_courses);
		    			    							        break;

		    			    							case 2: printf("dwse ena id mathimatos pros anazitisi \n");
		    			    							        scanf("%d",&crs_to_find);
		    			    							        printcourses(ptr_to_crs,crs_to_find);
		    			    							        break;

		    			    							case 3: ptr_to_std=load_student();
		    			    							        break;

		    											case 4: printf("dwse ena id pros anazitisi tou mathimatos \n");
		    												    scanf("%d",&studentid_to_find);
		    												    printstudent(ptr_to_std,studentid_to_find);
		    												    break;

		    											case 5: printf("%d\n",main_number_of_courses);
		    											        break;

		    											case 6: printf(" dwse mia periodo  \n");
		    											        scanf("%d",&timeslots);
		    											        fflush(stdin);
		    											        ptrtothebest=Loadmath(ptr_to_std,timeslots,main_number_of_courses);
		    											        break;

		    											default: exit(0);
		    						}

		}
	return 0;
	}

	//basic menu

struct math* Loadmath(struct student *ptrtostudentlist,int timeslots,int courses){


		        				LINK3 new=NULL;
		                        new=(LINK3)malloc(sizeof(MATH));
		                        new->timetable=Make2dintArray(timeslots);
		                        filltable(new->timetable,courses,timeslots);
		                        new->cost=calculatecost(ptrtostudentlist,new->timetable,timeslots);
		                        printf("costos tis periodou %f",new->cost);

return new;
}


void filltable(struct courseintb **timetable,int courses,int timeslots){

	FILE *fp ;
    char *token;
	char filename[40],buffer[256];
	printf(" arithmos periodou provlimatos.<-------.sol>");
	gets(filename);
	fflush(stdin);
	if((fp=fopen(filename,"r"))==NULL)
	        {
	                fprintf(stderr,"Error opening file %s",filename);
	                getchar();
	        }else
	        {
	        	printf("File loaded succesfully \n ");
	        }

	        while (fgets(buffer,256, fp) != NULL)
	               {
	        	   struct courseintb *temp=(struct courseintb*)malloc(sizeof(COURSEINTB));
	        	    token=strtok(buffer," ");
	        	    temp->course=atoi(token);
	        	    token = strtok(NULL, " ");
	        	    int position=atoi(token);
	        	    temp->next=timetable[position];
	        	    timetable[position]=temp;

	               }



}










struct courseintb** Make2dintArray(int arraySizeX){
struct courseintb** theArray;
int i;
theArray = (struct courseintb**) malloc(arraySizeX*sizeof(COURSEINTB));
for(i=0;i<arraySizeX;i++)
{
	theArray[i]=NULL;
}
   return theArray;
}





	int choices(void){

	int choice=0;
	printf( "1)----   Fortosi Provlimatos      ----\n"
	        "2)----    Euresi mathimatos       ----\n"
	        "3)----      Fortwsi lusis         ----\n"
		    "4)----   Euresi mathimatos (lisis) ----\n"
			"5)---- Sunolikos arithmos mathimatwn ----\n"
			"6)----     Epilisi provlimatos	    ----\n");

	scanf("%d",&choice);
	fflush(stdin);
	return choice;
	}



	//function to read courses file
	struct course *readcourseslist(int *globalcoursesaddress)
	{
	        FILE *fp ;
	        char *token;
	        int courses=0,total_enrolments=0;
	        char filename[40],buffer[256];
	        printf("Eisagogi arxeiou mathimatwn <------.stu>\n\n\n");
	        gets(filename);
	        fflush(stdin);
	       // if((fp=fopen("lse-f-91.stu","r"))==NULL)
	        if((fp=fopen(filename,"r"))==NULL)
	        {
	                fprintf(stderr,"provlima kata to anoigma tou arxeiou %s",filename);
	                getchar();
	        }else
	        {
	        	printf("to arxeio fortothike epitixws");
	        }
	        LINK root=NULL;
	        LINK new=NULL;
	        LINK current=NULL;
	        while (fgets(buffer,256, fp) != NULL)
	        {
	                if(root==NULL)
	                {
	                     new=(LINK)malloc(sizeof(COURSE));
	                     if(new==NULL)
	                          {
	                	      printf("memory error");
	                	      getchar();
	                	      exit(0);
	                          }
	                      new->next=root;
	                      token=strtok(buffer," ");
	                      new->courses_num=atoi(token);
	                      token = strtok(NULL, " ");
	                      new->enrolment=atoi(token);
	                      total_enrolments+=new->enrolment;
	                      root=new;

	                }
	                else
	                {
	                	current=root;
	                	while(current->next!=NULL)
	                	{
	                        	current=current->next;
	                	}
	                	LINK new=NULL;
	                	new=(LINK)malloc(sizeof(COURSE));
	                      	  if(new==NULL)
	                      	  {
	                      		  	 printf("error");
	                      		  	 getchar();
	                      		  	 exit(0);
	                      	  }
	                    current->next=new;
	                    new->next=NULL;
	                    token=strtok(buffer," ");
	                    new->courses_num=atoi(token);
	                    token = strtok(NULL, " ");
	                    new->enrolment=atoi(token);
	                    total_enrolments+=new->enrolment;
	                //printf("course me id %d  exei tosous %d\n",new->courses_num ,new->enrolment);
	              }

	        courses++;

	        }

	        printf("%d seires kai  %d  synolikes eggrafes \n ",courses,total_enrolments);
	        *globalcoursesaddress=courses;
	        fclose(fp);
	        return (root);

	}



	//function to read students file
	struct student *load_student(void){
			FILE *fp2 ;
			char *token;
		    int filelines=0,i=0;
		    char filename[40],buffer[256];
			printf("Eisagwgi arxeiou <------.stu > \n\n\n");
			gets(filename);
			fflush(stdin);
			//if((fp2=fopen("lse-f-91(9.82).sol","r"))==NULL)
			if((fp2=fopen(filename,"r"))==NULL)
			{
				fprintf(stderr,"provlima kata to anoigma tou arxeiou %s",filename);
				getchar();
		    }
			else
			{
				printf("to arxeio fortothike epitixws");
			}
		    LINK2 root=NULL;
			LINK2 new=NULL;
			LINK2 current=NULL;
			while (fgets(buffer,256, fp2) != NULL)
			{
				i++;
				filelines+=1;
				if(root==NULL)
				 {
		        new=(LINK2)malloc(sizeof(STUDENT));
		                if(new==NULL)
		                {
		                	printf("memory error");
		                    getchar();
		                }
				new->next=root;
				new->student_id=i;
				token=strtok(buffer," ");
				int courseid=0;
				while (token!=NULL)
				    {
					new->courses[courseid]=atoi(token);
					new->courses[courseid+1]=0;
					new->courses[courseid+2]=0;
					courseid++;
					token=strtok(NULL," ");}
				    root=new;
				    }
				else
				{
					current=root;
				    while(current->next!=NULL)
				    {
				    	current=current->next;
				    }
				LINK2 new=NULL;
				new=(LINK2)malloc(sizeof(STUDENT));
						if(new==NULL)
							{
								printf("error");
							}
			   current->next=new;
			   new->student_id=i;
			   new->next=NULL;
			   token=strtok(buffer," ");
			   int courseid=0;
			   while (token!=NULL)
			   {
					    new->courses[courseid]=atoi(token);
					    new->courses[courseid+1]=0;
					    new->courses[courseid+2]=0;
					    token=strtok(NULL," ");
					    courseid++;

			   }
				}
	        fflush(stdin);
				}
			printf("%d arithmos seirwn  \n",filelines);
			fclose(fp2);
	        return(root);

	}



	// Gia debugging anazitisi mathimatos

	void printcourses(struct course *ptr,int crs_to_find){
		int found=0;
		do{
			 if(ptr->courses_num==crs_to_find)
			 {
				 	 printf("arithmos mathimatos  %d  einai eggegramenoi %d\n", ptr->courses_num,ptr->enrolment);
				 	 found=1;
			 }
			 else
			 {
				ptr=ptr->next;
			 }
		   }while (ptr!=NULL&&found==0);

		if (found==0)
		{
			printf("Student not found!\n");
		 }
	}


	// Gia debugging anazitisi mathiti

	void printstudent(struct student *ptr,int Idlookup){
		int found=0;
		do{
			if(ptr->student_id==Idlookup)
			{
				found=1;
			}
			else
			{
				ptr=ptr->next;
			}
			}while((found==0)&&(ptr!=NULL));
	    if(found==1){
		int i=0;
		printf("O student me arithmo id  %d exei parei ta eksis mathimata \n ",ptr->student_id);
		do{
			printf("%d\n",ptr->courses[i]);
			i++;
	       }while(ptr->courses[i]!=0);
	    }
	    else
	    {
	    	printf("Student not found!\n");
	    }
	}

	// gia debugging
	void printallstudents(struct student *ptr){
	do{
			int i=0;
			printf("o student me arithmo id  %d exei parei ta eksis mathimata \n ",ptr->student_id);

			do{
				printf("%d\n",ptr->courses[i]);
				i++;
				}while(ptr->courses[i]!=0);
			 ptr=ptr->next;

		}while(ptr!=NULL);
	}

	double calculatecost(struct student *ptr,struct courseintb **timetable,int timeslots){
		double cost=0.0;
		int studentcount=0;
		do{
			cost+=costforstudent(ptr->courses,timetable,timeslots);
			studentcount++;
			ptr=ptr->next;
		}while(ptr!=NULL);

	return cost/(studentcount);
	}


	//safes
	double costforstudent(int *student,struct courseintb **timetable,int timeslots){
		double studentcost=0.0;
		int temp=0,temp2=0,distance=0,distance2=0,i=0,j=0;
		while(student[i]!=0){
			temp=student[i];
			j=i;
			while(student[j+1]!=0){
	        temp2=student[j+1];
	        distance=lookforcourse(temp,timetable,timeslots);
	        distance2=lookforcourse(temp2,timetable,timeslots);
	        studentcost+=distancecost(distance,distance2);
	        j++;
			}
	i++;
		}
		return studentcost;
	}

	//gia debug
	int lookforcourse(int coursetofind,struct courseintb **timetable,int timeslots){
		int timeslot=0,i;
		for(i=0;i<timeslots;i++){
			struct courseintb *temp=timetable[i];
			    do{

				         if(coursetofind==temp->course){
						  timeslot=i;
						  goto Ifoundit;
				         }
	                     temp=temp->next;
		               }while(temp!=NULL);

				}
	Ifoundit:

		return timeslot;
	}


	//gia debug
	void countcourses(struct courseintb **timetable,int timeslots){
		int sum=0,i;
		for(i=0;i<timeslots;i++){
			struct courseintb *temp=timetable[i];
					do{
						     sum+=temp->course;
						     temp=temp->next;
					   }while(temp!=NULL);
		}
		//edw
	printf("course sum is %d\n",sum);
	}

	////kostos analoga to distance


	double distancecost(int A,int B){
		double cost=0;
		int C=abs(A-B);
		switch (C){
		case 0:cost=400000000.0;break;
		case 1:cost=16.0;break;
		case 2:cost=8.0;break;
		case 3:cost=4.0;break;
		case 4:cost=2.0;break;
		case 5:cost=1.0;break;
		default:cost=0.0;break;
		}
		return cost;
	}



