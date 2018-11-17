#include<my_global.h>
#include<mysql.h>
#include<stdio.h>
#include<string.h>


void finish_with_error(MYSQL *con)
{
	printf("\nReached here!\n");
	fprintf(stderr,"%s\n",mysql_error(con));
	mysql_close(con);
	exit(1);
}

void print_result(MYSQL *con)
{
	MYSQL_RES *result=mysql_store_result(con);
	int num_fields,i;
	MYSQL_ROW row;
	MYSQL_FIELD *field;

	if(result==NULL)
			finish_with_error(con);

	num_fields = mysql_num_fields(result);

	while(row=mysql_fetch_row(result))
  	{
    	for(i=0;i<num_fields;i++)
    	{
      	if(i==0)
      	{
        	while(field = mysql_fetch_field(result))
        	{
          	printf("%s ",field->name);
        	}
        	printf("\n");
      	}
      	printf("%s ",row[i] ? row[i]:"NULL");
    	}
  	}

  mysql_free_result(result);
}

void display_bill(MYSQL *con, int memid, char * date_and_time)
{
	char query_statement[500];
	snprintf(query_statement,500,"SELECT p.itemid 'Item Id', iname 'Item Name', i.cost 'Cost per no', quantity 'Quantity', p.cost 'Cost' FROM (purchase p JOIN item i ON i.itemid = p.itemid) WHERE p.date_time_purchase = '%s' AND memid = %d;",date_and_time,memid);
	if(mysql_query(con,query_statement))
		finish_with_error(con);
	print_result(con);
}

float calculate_total_cost(MYSQL *con,int memid, char * date_and_time)
{
	MYSQL_RES *result;
	MYSQL_ROW row;
	float totalcost;
	char query_statement[500];
	snprintf(query_statement,500,"SELECT sum(cost) FROM purchase WHERE date_time_purchase = \'%s\' AND memid = %d",date_and_time,memid);
	if(mysql_query(con,query_statement))
		finish_with_error(con);
	result = mysql_store_result(con);
	row = mysql_fetch_row(result);
	totalcost = (float)atof(row[0]);
	printf("\nTotal Cost: %.2f\n",totalcost);
	return totalcost;
}

void insert_items(MYSQL *con, int memid, char * date_and_time)
{
	MYSQL_RES *result;
	MYSQL_ROW row;
	char ch;
	char query_statement[500];

	int itemid,exists,itemstock;
	int quantity;
	float cost,totalcost=0,itemcost;
	printf("\nItemid: ");
	scanf("%d",&itemid);
	do
	{
		printf("\nQuantity: ");
		scanf("%d",&quantity);
		snprintf(query_statement,500,"SELECT cost,stock FROM item WHERE itemid = %d",itemid);
		if(mysql_query(con,query_statement))
			finish_with_error(con);
		result = mysql_store_result(con);
		row=mysql_fetch_row(result);
		itemcost = (float)atof(row[0]);
		itemstock = (int)atoi(row[1]);
		if(quantity >= itemstock)
		{
			snprintf(query_statement,500,"UPDATE item SET stock = 0 WHERE itemid = %d",itemid);
			if(mysql_query(con,query_statement))
				finish_with_error(con);
			quantity = itemstock;
		}

		else
		{
			itemstock = itemstock - quantity;
			snprintf(query_statement,500,"UPDATE item SET stock = %d WHERE itemid = %d",itemstock,itemid);
			if(mysql_query(con,query_statement))
				finish_with_error(con);
		}
		printf("\nItem cost: %.2f\n",itemcost);
		snprintf(query_statement,500,"SELECT count(*) FROM purchase WHERE itemid = %d AND date_time_purchase = \'%s\' AND memid = %d",itemid,date_and_time,memid);
		if(mysql_query(con,query_statement))
			finish_with_error(con);
		result = mysql_store_result(con);
		row = mysql_fetch_row(result);
		exists = (int)atoi(row[0]);
		if(exists!=0)
		{
			
			int q;
			snprintf(query_statement,500,"SELECT quantity FROM purchase WHERE itemid = %d AND date_time_purchase = \'%s\' AND memid = %d",itemid,date_and_time,memid);
			if(mysql_query(con,query_statement))
			finish_with_error(con);
			result = mysql_store_result(con);
			row = mysql_fetch_row(result);
			q=(int)atoi(row[0]);
			quantity = quantity + q;
			snprintf(query_statement,500,"DELETE FROM purchase WHERE itemid = %d AND date_time_purchase = \'%s\' AND memid = %d",itemid,date_and_time,memid);
			if(mysql_query(con,query_statement))
			finish_with_error(con);
		}
		
		cost = quantity * itemcost;
		snprintf(query_statement,500,"INSERT INTO purchase VALUES(\'%s\',%d,%d,%d,%.2f);",date_and_time,itemid,quantity,memid,cost);
		if(mysql_query(con,query_statement))
		finish_with_error(con);
		system("clear");
		display_bill(con,memid,date_and_time);
		calculate_total_cost(con,memid,date_and_time);
		printf("\nItemid: ");
		scanf("%d",&itemid);
	}while(itemid!=0);
}

void delete_items(MYSQL *con, int memid, char *date_and_time)
{
	MYSQL_RES *result;
	MYSQL_ROW row;
	char ch;
	char query_statement[500];

	int itemid,exists;
	int quantity,itemstock;
	float cost,totalcost=0,itemcost;
	printf("\nItemid: ");
	scanf("%d",&itemid);
	do
	{
		snprintf(query_statement,500,"SELECT count(*) FROM purchase WHERE itemid = %d AND date_time_purchase = \'%s\' AND memid = %d",itemid,date_and_time,memid);
		if(mysql_query(con,query_statement))
			finish_with_error(con);
		result = mysql_store_result(con);
		row = mysql_fetch_row(result);
		exists = (int)atoi(row[0]);
		if(exists!=0)
		{
			
			printf("\nQuantity: ");
			scanf("%d",&quantity);
			snprintf(query_statement,500,"SELECT cost,stock FROM item WHERE itemid = %d",itemid);
			if(mysql_query(con,query_statement))
				finish_with_error(con);
			result = mysql_store_result(con);
			row=mysql_fetch_row(result);
			itemcost = (float)atof(row[0]);
			itemstock = (int)atoi(row[1]);
			//printf("\nitemstock: %d",itemstock);
			int q;
			snprintf(query_statement,500,"SELECT quantity FROM purchase WHERE itemid = %d AND date_time_purchase = \'%s\' AND memid = %d",itemid,date_and_time,memid);
			if(mysql_query(con,query_statement))
			finish_with_error(con);
			result = mysql_store_result(con);
			row = mysql_fetch_row(result);
			q=(int)atoi(row[0]);
			//printf("\nq: %d",q);
			if(quantity > q)
			{
				itemstock =itemstock +q;
				quantity = 0;
			}
			else
			{
				itemstock = itemstock + quantity;
				quantity=q-quantity;
			}
			//printf("\nQ: %d",quantity);
			//printf("\nitemstock: %d",itemstock);
			snprintf(query_statement,500,"UPDATE item SET stock = %d WHERE itemid = %d",itemstock,itemid);
			if(mysql_query(con,query_statement))
				finish_with_error(con);
			snprintf(query_statement,500,"DELETE FROM purchase WHERE itemid = %d AND date_time_purchase = \'%s\' AND memid = %d",itemid,date_and_time,memid);
			if(mysql_query(con,query_statement))
			finish_with_error(con);

			if(quantity>=1)
			{
				cost = quantity * itemcost;
				snprintf(query_statement,500,"INSERT INTO purchase VALUES(\'%s\',%d,%d,%d,%.2f);",date_and_time,itemid,quantity,memid,cost);
				if(mysql_query(con,query_statement))
				finish_with_error(con);
			}
		}
		
		system("clear");
		display_bill(con,memid,date_and_time);
		calculate_total_cost(con,memid,date_and_time);
		printf("\nItemid: ");
		scanf("%d",&itemid);
	}while(itemid!=0);
}

void billing(MYSQL *con)
{
	system("clear");
	MYSQL_RES *result;
	MYSQL_ROW row;
	char ch;
	int choice;
	int points;
	char *phno = (char *)malloc(11*sizeof(char));
	char *cardno = (char *)malloc(20*sizeof(char));
	int memid;
	char *date_and_time = (char *)malloc(20*sizeof(char));
	char query_statement[500];
	float totalcost,givamt,balance;
	printf("\nEnter member Phno: ");
	scanf("%s",phno);
	system("clear");
	snprintf(query_statement,500,"SELECT memid, mname, phno, points FROM member WHERE phno = %s",phno);
	if(mysql_query(con,query_statement))
		finish_with_error(con);
	result = mysql_store_result(con);
	row = mysql_fetch_row(result);
	printf("\n%s %s %s %s",row[0],row[1],row[2],row[3]);
	memid = (int)atoi(row[0]);
	snprintf(query_statement,500,"SELECT now();");
	if(mysql_query(con,query_statement))
		finish_with_error(con);
	result=mysql_store_result(con);
	row=mysql_fetch_row(result);
	date_and_time=row[0];
	printf("\nDate and Time: %s",date_and_time);
	printf("\n");
	insert_items(con,memid,date_and_time);

	while(1)
	{
		system("clear");
		printf("\nDo you want to modify the bill [y/n] ?");
		scanf(" %c",&ch);
		if(ch=='y')
		{
			printf("\n1. Add items\n2. Remove items\nEnter your choice: ");
			scanf("%d",&choice);
			system("clear");
			switch(choice)
			{
				case 1: display_bill(con,memid,date_and_time);
						totalcost = calculate_total_cost(con,memid,date_and_time);
						insert_items(con,memid,date_and_time);
					      break;

				case 2:  display_bill(con,memid,date_and_time);
						totalcost = calculate_total_cost(con,memid,date_and_time);
						delete_items(con,memid,date_and_time);
						  break;
			}
		}
		else
		{
			system("clear");
			display_bill(con,memid,date_and_time);
			totalcost = calculate_total_cost(con,memid,date_and_time);
			break;
		}
	}
	snprintf(query_statement,500,"SELECT points FROM member WHERE memid = %d",memid);
	if(mysql_query(con,query_statement))
		finish_with_error(con);
	result=mysql_store_result(con);
	row = mysql_fetch_row(result);
	points = (int)(1.0*totalcost/100);
	points = points + (int)atoi(row[0]);
	if(points >= 25 && totalcost>=200)
		{
			printf("\nCongratulations!\nYour points have exceeded 25!\nSo you get Rs.200 off!\n");
			points = points - 25;
			totalcost = totalcost - 200;
		}
	printf("\nTotal Cost: %.2f",totalcost);
	printf("\nPayment Mode\n1.Cash\n2.Card\nEnter your choice: ");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:	printf("\nGiven amount: ");
				scanf("%f",&givamt);
				balance = givamt - totalcost;
				printf("\nBalance: %.2f",balance);
				snprintf(query_statement,500,"INSERT INTO billing (date_time_purchase,memid,totamt,givamt,balance) VALUES (\'%s\',%d,%.2f,%.2f,%.2f);",date_and_time,memid,totalcost,givamt,balance);
				if(mysql_query(con,query_statement))
					finish_with_error(con);
				break;

		case 2: printf("\nEnter Cardno: ");
				scanf("%s",cardno);
				snprintf(query_statement,500,"INSERT INTO billing VALUES (\'%s\',%d,%.2f,0,0,%s);",date_and_time,memid,totalcost,cardno);
				if(mysql_query(con,query_statement))
					finish_with_error(con);
				break;

		default: printf("\nInvalid choice:!");
				 break;

	}
	snprintf(query_statement,500,"UPDATE member SET points = %d WHERE memid = %d",points,memid);
	if(mysql_query(con,query_statement))
		finish_with_error(con);
	printf("\nThank you for visiting our super market!");
	printf("\nPress any key to continue ...");
	ch=getchar();
	ch=getchar();
	return;
}

void find_item(MYSQL *con)
{
    char statement[512],iname[20];
    printf("\nEnter Itemname:");
    scanf("%s",iname);
    snprintf(statement,512,"select distinct c.cname,c.secid,i.stock from item as i,category as c where i.catid=c.catid and i.iname='%s' and i.stock!=0",iname);
    if(mysql_query(con,statement))
   	finish_with_error(con);
   	MYSQL_RES *result = mysql_store_result(con);
	int num_fields,i;
	MYSQL_ROW row;
		if(result==NULL)
		 {
		 	printf("out off stock");
		 	finish_with_error(con);
		 }
	

        printf("\nCategory\t\t\tSection\t\tStock\n");
        while((row = mysql_fetch_row(result))!= NULL)
	{
	        num_fields= mysql_num_fields(result);
		for(i=0;i<num_fields;i++)
		 {
		 	printf("%s\t\t",row[i]);
		 }
		 printf("\n");
        }   
        char ch;
       	printf("\nPress any key to continue ...");
	ch=getchar();
	ch=getchar();
}
//change it
void view_shift_table(MYSQL *con)
{
    char stmt[250];
    snprintf(stmt,250,"select e1.empid,e1.shift,e1.shift_start_time,e1.shift_end_time from empshift e1");
	if(mysql_query(con,stmt))
		finish_with_error(con);
	MYSQL_RES *result = mysql_store_result(con);
	int num,i;
	unsigned long *lengths;
	MYSQL_ROW row;
	if(result==NULL)
	  finish_with_error(con);	
        printf("\nEMPID\t\tShift\t\tStartTime\t\tEndTime\n"); 
        while((row = mysql_fetch_row(result))!= NULL)
        {
          num= mysql_num_fields(result);
          lengths = mysql_fetch_lengths(result);
          for(int i = 0; i < num; i++)
           printf("%s\t\t",row[i]);
          printf("\n");
        }
        mysql_free_result(result);
        char ch;
       	printf("\nPress any key to continue ...");
	ch=getchar();
	ch=getchar();
}
//change this too
void apply_for_leave(MYSQL *con, int emp_id)
{
	char statment1[512];
    snprintf(statment1,512,"select empid,leave_date from empleave where empid=%d",emp_id);
	if(mysql_query(con,statment1))
	  	finish_with_error(con);
	print_result(con);
	char statement[512];
	char ldate[10];
	char ldur[10];
	int x;
	x=1;	
	if(x==1)
	{	    
	    printf("enter leave date\n");
	    scanf("%s",ldate);
		snprintf(statement,512,"update empleave set leave_date='%s' where empid= %d",ldate,emp_id);
	snprintf(statement,512,"insert into empleave values('%s',%d)",ldate,emp_id);
        if(mysql_query(con,statement))
   	    finish_with_error(con);
   	}
	char st[512];
	snprintf(st,512,"select empid,leave_date from empleave where empid=%d",emp_id);
	if(mysql_query(con,st))
          print_result(con);
    char ch;
    printf("\nPress any key to continue ...");
	ch=getchar();
	ch=getchar();
}

void add_members(MYSQL *con)
{
 	char st[512];
	int memid,points;
	char dob[10],addr[30],gender,phno[12],memname[30];
	snprintf(st,512,"select memid from member order by memid desc limit 1");
	if(mysql_query(con,st))
	  finish_with_error(con);
   	MYSQL_RES *result = mysql_store_result(con);
	int num_fields,i;
	MYSQL_ROW row;
	if(result==NULL)
	{
	  finish_with_error(con);
	}
	while((row=mysql_fetch_row(result))!=NULL)
	{
	  i=atoi(row[0]); 
        }
    i=i+1;
    printf("\nNew MemID                    :\t%d \n",i);
    char st1[512];
    printf("\nEnter MemberName             :\t");
    scanf("%s",memname);
    printf("\nEnter PhoneNo:               :\t");
    scanf("%s",phno);
    printf("\nEnter Date of Birth of Member:\t");
    scanf("%s",dob);
    gender=getchar();
    printf("\nEnter Gender of Member       :\t");
    scanf("%c",&gender);
    printf("\nEnter Address of Member      :\t");
    scanf("%s",addr);
    points=0;
    snprintf(st1,512,"insert into member values(%d,'%s','%s','%c','%s','%s',%d)",i,memname,phno,gender,dob,addr,points);
	if(mysql_query(con,st1))
	  finish_with_error(con);

   	char st21[512];
   	snprintf(st21,512,"select * from member where memid=%d",i);
  	if(mysql_query(con,st21))
	  finish_with_error(con);
   	MYSQL_RES *result1 =mysql_store_result(con);
	int num_fields1,i1;
	MYSQL_ROW row1;
		if(result1==NULL)
		 {
		 	printf("out off stock");
		 	finish_with_error(con);
		 }
	
	printf("\nNewly Inserted Member details:\n"); 
	while((row1=mysql_fetch_row(result1))!=NULL)
	{
		num_fields1=mysql_num_fields(result1);
		for(i=0;i<num_fields1;i++)
		 {
		 	printf("%s\t",row1[i]);
		 }
		 printf("\n");
    }
        char ch;
       	printf("\nPress any key to continue ...");
	ch=getchar();
	ch=getchar();
}

void edit_mem_details(MYSQL *con)
{
   char st[512],st2[512],st3[512],st11[512],st21[512];
   char st23[512],st1[512];
   char ch;
   int memid,points;
   int x,op;
	char dob[10],addr[30],gender,phno[12],mname[30];
	printf("\nEnter phno :\t");
    scanf("%s",phno);
	while(1)
	{
	system("clear");
	printf("\n1 to update dob\n2 to update addr\n3 to exit\nEnter :\t");
	scanf("%d",&op);
	switch(op)
	{
	  case 1:printf("\nEnter dob to be updated :\t");
	         scanf("%s",dob);
			 snprintf(st1,512,"update member set dob='%s' where phno=%s",dob,phno);
			 if(mysql_query(con,st1))
		       finish_with_error(con);
				snprintf(st11,512,"select memid,mname,phno,gender,dob,addr,points from member where phno=%s",phno);
				mysql_query(con,st11);
				print_result(con);
                        break;
	  case 2: printf("\nEnter address of member :\t");
              scanf("%s",addr);
				snprintf(st2,512,"update member set addr='%s' where phno=%s",addr,phno);
				if(mysql_query(con,st2))
				    finish_with_error(con);
				snprintf(st21,512,"select memid,mname,phno,dob,gender,addr,points from member where phno=%s",phno);
				mysql_query(con,st21);
				print_result(con);
                        break;
 
      case 3:exit(0);
             break;				
	}
	printf("\nPress any key to continue ...");
	ch=getchar();
	ch=getchar();
	
	}
    printf("\nPress any key to continue ...");
	ch=getchar();
	ch=getchar();	
}

void employee(MYSQL *con, int empid)
{
	int ch;
	while(1)
	{
		system("clear");
		printf("\n1.Billing\n2.Check for existance of product\n3.View shift table\n4.Apply for leave\n5.Add members\n6.Modify member details\n7.Back\nEnter your choice: ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: billing(con);
					break;

			case 2: find_item(con);
					break;

			case 3: view_shift_table(con);
					break;

			case 4: apply_for_leave(con,empid);
					break;

			case 5: add_members(con);
					break;

			case 6: edit_mem_details(con);
					break;

			case 7: return;

			default: printf("\nInvalid choice!");
		}
	}	
}

void create_new_user(int empid, char *password)
{
	MYSQL *con=mysql_init(NULL);
	char query_statement[500];
	if(mysql_real_connect(con,"localhost","root","1234","mysql",0,NULL,0)==NULL)
			finish_with_error(con);
	snprintf(query_statement,500,"CREATE USER '%d'@'localhost' identified with mysql_native_password by '%s'",empid,password);
	if(mysql_query(con,query_statement))
		finish_with_error(con);
	snprintf(query_statement,500,"GRANT ALL ON SUPERMARKET1.* TO '%d'@'localhost' IDENTIFIED BY '%s'",empid,password);
	if(mysql_query(con,query_statement))
		finish_with_error(con);
	mysql_close(con);
}

void insert_employee(MYSQL *con, int secid)
{
    char query_statement[500];
    char name[30];
	int empid,salary;
	char dob[10],addr[30],gender,phno[12],jdate[10];
	char password[30];
	snprintf(query_statement,500,"select max(empid) from employee where empid+1 not in (select empid from employee) and empid not in (select mgrid from section)");
	if(mysql_query(con,query_statement))
	  finish_with_error(con);
   	MYSQL_RES *result = mysql_store_result(con);
	MYSQL_ROW row;
	if(result==NULL)
	{
	  finish_with_error(con);
	}
	row=mysql_fetch_row(result);
	empid=atoi(row[0]); 
    empid++;
	printf("\nEnter name of employee: ");
	scanf("%s",name);
    printf("\nEnter phno: ");
    scanf("%s",phno);
    printf("\nEnter date od birth of employee: ");
    scanf("%s",dob);
    printf("\nEnter gender of employee: ");
    scanf(" %c",&gender);
    printf("\nEnter address of employee: ");
    scanf("%s",addr);
    printf("\nEnter salary of employee: ");
	scanf("%d",&salary);
	printf("\nEnter join date: ");
	scanf("%s",jdate);
	printf("\nEnter password: ");
	scanf("%s",password);
    snprintf(query_statement,500,"insert into employee values(%d,'%s',%d,'%s','%s','%c','%s',%d,'%s')",empid,name,secid,phno,dob,gender,addr,salary,jdate);
	if(mysql_query(con,query_statement))
	  finish_with_error(con);
	create_new_user(empid,password);
	snprintf(query_statement,500,"INSERT INTO emp_pass VALUES (%d,'%s');",empid,password);
	if(mysql_query(con,query_statement))
		finish_with_error(con);
   	snprintf(query_statement,500,"select * from employee where empid=%d",empid);
  	if(mysql_query(con,query_statement))
	  finish_with_error(con);
   	result =mysql_store_result(con);
	int num_fields,i;
	if(result==NULL)
		finish_with_error(con);	
	printf("\nNewly Hired employee:\n"); 
	while((row=mysql_fetch_row(result))!=NULL)
	{
		num_fields=mysql_num_fields(result);
		for(i=0;i<num_fields;i++)
		 {
		 	printf("%s\t\t",row[i]);
		 }
		 printf("\n");
    }  	
    printf("\nPress any key to continue ...");
    gender = (char)getchar();
    gender = (char)getchar();
    return;
}

void delete_user(int empid)
{
	MYSQL *con = mysql_init(NULL);
	char query_statement[500];
	if(mysql_real_connect(con,"localhost","root","1234","mysql",0,NULL,0)==NULL)
			finish_with_error(con);
	snprintf(query_statement,500,"DROP USER '%d'@'localhost'",empid);
	if(mysql_query(con,query_statement))
		finish_with_error(con);
	snprintf(query_statement,500,"flush privileges;");
	if(mysql_query(con,query_statement))
		finish_with_error(con);
	mysql_close(con);
}
void delete_employee(MYSQL *con, int secid)
{
    char query_statement[500],g;
	int empid,exists;
	MYSQL_RES *result;
	MYSQL_ROW row;
	int i,num_fields;
	printf("\nEnter Employee ID: ");
	scanf("%d",&empid);
    snprintf(query_statement,500,"SELECT count(*) FROM employee WHERE empid = %d AND secid = %d",empid,secid);
	if(mysql_query(con,query_statement))
	  finish_with_error(con);
	result = mysql_store_result(con);
	row = mysql_fetch_row(result);
	exists = (int)atoi(row[0]);
	system("clear");
	if(exists!=0)
	{
		printf("\nFiring employee:\n"); 
		snprintf(query_statement,500,"SELECT * FROM employee WHERE empid=%d",empid);
		if(mysql_query(con,query_statement))
			finish_with_error(con);
		result = mysql_store_result(con);
		while((row=mysql_fetch_row(result))!=NULL)
		{
			num_fields=mysql_num_fields(result);
			for(i=0;i<num_fields;i++)
			 {
			 	printf("%s\t\t",row[i]);
			 }
			 printf("\n");
   		}
   		snprintf(query_statement,500,"DELETE FROM emp_pass WHERE empid = %d;",empid);
		if(mysql_query(con,query_statement))
			finish_with_error(con);
		snprintf(query_statement,500,"DELETE FROM empleave WHERE empid = %d;",empid);
		if(mysql_query(con,query_statement))
			finish_with_error(con);
		delete_user(empid);
		snprintf(query_statement,500,"DELETE FROM employee WHERE empid = %d;",empid);
		if(mysql_query(con,query_statement))
			finish_with_error(con);
		
	}
	else
	{
		printf("\nCannot delete given employee as employee either doesn't exist or doesn't belong to your section");
	}
    printf("\nPress any key to continue ...");
    g = (char)getchar();
    g = (char)getchar();
    return;
}

void modify_empho(MYSQL *con,int emp_id)
{
	char st1[512];
   	char sta1[512],sta12[512],sta2[512],sta21[512],sta31[512],sta3[512],sta4[512],sta41[512],sta5[512],sta51[512];
   	int empide,salary,op;
   	char phno[30],name[30],dob[30],addr[30],jdate[30];
    printf("\nEnter updated phno: ");
	scanf("%s",phno);
	snprintf(sta1,512,"update employee set phno =%s where empid = %d",phno,emp_id);
	if(mysql_query(con,sta1))
	finish_with_error(con);
	snprintf(sta12,512,"select empid,name,phno,gender,dob,addr,salary,joindate from employee where empid=%d",emp_id);
    if(mysql_query(con,sta12))
		finish_with_error(con);
	print_result(con);
}

void modify_employee(MYSQL *con, int secid)
{
	int i=secid;
	int x=1;
    char st1[512];
    char sta1[512],sta12[512],sta2[512],sta21[512],sta31[512],sta3[512],sta4[512],sta41[512],sta5[512],sta51[512];
    int empide,salary,op;
    char phno[30],name[30],dob[30],addr[30],jdate[30];
    while(1)
    {
     	system("clear");
     	snprintf(st1,512,"SELECT * FROM employee WHERE secid = %d",secid);
     	if(mysql_query(con,st1))
     		finish_with_error(con);
     	print_result(con);
     	printf("\nEnter emp_id to be updated: ");
     	scanf("%d",&empide);
     	printf("\nempid: %d",empide);
	 	printf("\n1.Update phno\n2.Update salary\n3.Update address\n4.Back\nEnter your choice: ");
	 	scanf("%d",&op);
	 	switch(op)
	 	{
	   	case 1:modify_empho(con,empide);
                break;
	   	case 2:printf("\nEnter updated salary: ");
	          scanf("%d",&salary);
			  snprintf(sta2,512,"update employee set salary=%d where empid=%d and secid=%d",salary,empide,i);
			 if(mysql_query(con,sta2))
		       finish_with_error(con);
				snprintf(sta21,512,"select empid,name,phno,gender,dob,addr,salary,joindate from employee where empid=%d",empide);
				mysql_query(con,sta21);
				print_result(con);	
				break;
      	case 3:   printf("Enter updated address: \n");
	          	scanf("%s",addr);
			  	snprintf(sta4,512,"update employee set addr='%s' where empid=%d and secid=%d",addr,empide,i);
			 	if(mysql_query(con,sta4))
		       finish_with_error(con);
				snprintf(sta41,512,"select empid,name,phno,gender,dob,addr,salary,joindate from employee where empid=%d",empide);
				mysql_query(con,sta41);
				print_result(con);	
				break;
      case 4:return;
  			  
     	}
     	char ch;
     	printf("\nPress any key to continue ...");
	    ch = (char)getchar();
	    ch = (char)getchar();
	    return;
   }
}

void change_password(int empid,char *password)
{
	MYSQL *con = mysql_init(NULL);
	char query_statement[500];
	if(mysql_real_connect(con,"localhost","root","1234","mysql",0,NULL,0)==NULL)
			finish_with_error(con);
	snprintf(query_statement,500,"SET PASSWORD FOR '%d'@'localhost' = PASSWORD('%s');",empid,password);
	if(mysql_query(con,query_statement))
		finish_with_error(con);
}

void reset_emp_password(MYSQL *con, int secid)
{
	char query_statement[500];
	system("clear");
	snprintf(query_statement,500,"SELECT * FROM employee WHERE secid = %d",secid);
	if(mysql_query(con,query_statement))
		finish_with_error(con);
	print_result(con);

	printf("\nEnter empid: ");
	int empid;
	scanf("%d",&empid);
	char password[30];
	printf("\nNew Password: ");
	scanf("%s",password);

	snprintf(query_statement,500,"UPDATE emp_pass SET password = '%s' WHERE empid = %d AND empid in (SELECT empid FROM employee WHERE secid = %d) ;",password,empid,secid);
	if(mysql_query(con,query_statement))
		finish_with_error(con);

	change_password(empid,password);
}

void contact_suppliers(MYSQL *con, int secid)
{
	char query_statement[512];
  	snprintf(query_statement,512,"select s.supid,i.iname,s.sname,s.locn,s.phno from supplier as s,category as c,item as i where  i.catid = c.catid and c.secid = %d and i.supid=s.supid and i.stock =0;",secid);
  	if(mysql_query(con,query_statement))
  		finish_with_error(con);
  	print_result(con);

  	char ch;
  	printf("\nPress any key to continue ...");
  	ch = (char)getchar();
  	ch = (char)getchar();
}

void edit_emp_shift(MYSQL *con,int secid)
{
	char st[512];
	int i;
	i = secid;
	char sday[30];
	int shift;
	char sstime[30],sendtime[30];
	char st21[512];
	int empiid;
	char  st4[512],st5[512],st6[512];
	char st1[512];
	snprintf(st5,512,"select * from empshift");
	if(mysql_query(con,st5))
		finish_with_error(con);
	print_result(con);
	printf("\nEnter day of shift to change: ");
	scanf("%s",sday);
	printf("Enter shift: ");
	scanf("%d",&shift);
	snprintf(st1,512,"select empid from empshift where day='%s' and shift = %d and secid =%d ",sday,shift,secid);
	if(mysql_query(con,st1))
	  finish_with_error(con);
   	MYSQL_RES *result1 = mysql_store_result(con);
	int num_fields1,j;
	MYSQL_ROW row1;
	if(result1==NULL)
	{
	  finish_with_error(con);
	}
	while((row1=mysql_fetch_row(result1))!=NULL)
	{
	  j=atoi(row1[0]);
    }
    //printf("\nJ: %d",j);
	//if(i==j)
	{
	    printf("\nEmployees belonging to  secid %d ",i);
	    snprintf(st6,512,"select empid from employee where secid='%d'",i);
	    mysql_query(con,st6);
	    print_result(con);
	    printf("\nEnter employee id to given in above shift: ");
	    scanf("%d",&empiid);
	    snprintf(st4,512,"update empshift set empid=%d where day='%s' and shift=%d and secid = %d",empiid,sday,shift,secid);
	    if(mysql_query(con,st4))
		   finish_with_error(con);
	    snprintf(st5,512,"select * from empshift");
		if(mysql_query(con,st5))
			finish_with_error(con);
		print_result(con);	   
	}
	char ch;
	printf("\nPress any key to continue ...");
  	ch = (char)getchar();
  	ch = (char)getchar();
}

void view_leave_application(MYSQL *con, int secid)
{
	char query_statement[500];
	system("clear");
	snprintf(query_statement,500,"SELECT e.*, e1.name, e1.secid FROM empleave e, employee e1 WHERE e.empid=e1.empid AND e1.secid = %d",secid);
	if(mysql_query(con,query_statement))
		finish_with_error(con);
	print_result(con);

	char ch;
	printf("\nPress any key to continue ...");
  	ch = (char)getchar();
  	ch = (char)getchar();
}

void manager(MYSQL *con,int secid, int mgrid)
{
	int ch;
	while(1)
	{
		system("clear");
		printf("\n1.Hire an employee\n2.Fire an employee\n3.Edit an employee's details\n4.Reset an employee's password\n5.Contact Suppliers\n6.Edit employee shifts\n7.Employees who've applied for leave\n8.Enter employee module\n9.Back\nEnter your choice: ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: insert_employee(con,secid);
					break;

			case 2: delete_employee(con,secid);
					break;

			case 3: modify_employee(con,secid);
					break;

			case 4: reset_emp_password(con,secid);
					break;

			case 5: contact_suppliers(con,secid);
					break;

			case 6: edit_emp_shift(con,secid);
					break;

			case 7: view_leave_application(con,secid);
					break;

			case 8: employee(con,mgrid);
					break;

			case 9: return;

			default: printf("'\nInvalid choice!");
		}
	}	
}

void main(void)
{
	char *empid= (char *)malloc(3*sizeof(char));
	char *password = (char *)malloc(20*sizeof(char));
	int flag;

	MYSQL *con;

	while(1)
	{
		system("clear");
		flag =0;
		con=mysql_init(NULL);
		printf("\nEmployee id: ");
		scanf("%s",empid);
		printf("Password: ");
		scanf("%s",password);
		if(mysql_real_connect(con,"localhost",empid,password,"SUPERMARKET1",0,NULL,0)==NULL)
			finish_with_error(con);
		if(mysql_query(con,"SELECT * FROM section"))
			finish_with_error(con);
		MYSQL_RES *result = mysql_store_result(con);
		int num_fields,i;
		MYSQL_ROW row;

		if(result==NULL)
			finish_with_error(con);

		while(row=mysql_fetch_row(result))
		{
			if(row[0]!=NULL && strcmp(empid,row[1])==0)
			{
				manager(con,(int)atoi(row[0]),(int)atoi(row[1]));
				flag =1;
			}
		}

		if(flag==0)
			employee(con,(int)atoi(empid));
		mysql_close(con);
	}
}