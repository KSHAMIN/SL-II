#!/bin/bash

Create_Database()
{
   read -p "Enter filename:- " filename
   if test -f "$filename" 
   then
      echo -e "\t\t\t*****Database already exists!*****\n"
      echo "File contents are:"
      cat $filename
      echo "-----------------------------------------------------------------------" 
      echo -e "Check your file below:\n"
      pwd 
      ls
      echo -e "-----------------------------------------------------------------------\n" 
   else
      echo -e "\t\t\t*****Creating a new database*****\n"
      touch $filename 
      echo "-----------------------------------------------------------------------" >> $filename
      echo "|     Book ID     |         Author        |          Book Name        |" >> $filename
      echo "-----------------------------------------------------------------------" >> $filename 			    
      echo -e "New database created!!!\n"
   fi 
}

View_Database()
{
   if test -f "$filename"
   then
       cat $filename
       # echo "-----------------------------------------------------------------------" 
   else
       echo "No database to view :("
   fi
}

Insert_Record()
{
if test -f "$filename"
then
   #book = "$filename"
   echo -n "Name of the book:"
   read name
   echo -n "Name no. of the author:"
   read author
   echo -n "Enter book no.:"
   read id_no
   echo "Do you want to enter these values:"
   echo "Name: $name ; Author: $author ; Book no.: $id_no"
   echo -n "y/n: "
   echo -e "\n"
   read answer
   
   if [ $answer = "y" ]
   then
       echo -e "|\t$id_no \t |\t$author \t\t|\t$name\t\t|" >> $filename
   else
       echo "Name: $name ; Author: $author ; Book no.: $id_no NOT written to book"
   fi
else
    echo -e "First create a database using option (1)\n"
fi
}

Delete_Record()
{
   if test -f "$filename"
   then
   	read -p "Enter the book id you want to delete: " book_id
   	if grep -q $book_id $filename
   	then
   	     sed -in "/$book_id/d" $filename
   	     echo -e "Record deleted successfully\n"
   	else
   	     echo "Record not found\n"
   	fi
   else
   	echo -e "File does not exist!\n"
   	echo -e "First create a database using option (1)\n"
   fi
}

Modify_Record()
{
if test -f "$filename"
then
      read -p "Enter book id you want to modify: " book_id
      val={$(grep -iw $book_id $filename)}
      if grep -q $book_id $filename
      then
   	  echo -e "Record found!\n"
   	  echo "$book_id	${val[1]}		${val[2]}"
   	  echo "Enter new details: "
   	  read -p "Enter author's name: " val[1]
   	  read -p "Enter book name: " val[2]
   	  sed -in "/$book_id/d" $filename
   	  echo -e "|\t$book_id \t |\t${val[1]} \t\t|\t${val[2]}\t\t|" >> $filename
   	  echo "Modified successfully!\n"
   	  View_Database
      else
   	  echo "*****Record not found*****\n"
      fi
else
	echo -e "First create a database using option (1)\n"
fi
}

echo ""
echo "library database"
echo ""

while true
do
echo 		"1) Create database.
2) View database.
3) Insert a record.
4) Delete a record.
5) Modify a record.
6) Exit."
echo "------------------------------------------------------------"
echo -n "Enter your choice: " 
read option
echo "------------------------------------------------------------"

 case $option in
		1)	Create_Database ;;
			
		2)	View_Database ;;
			
		3)	Insert_Record ;;
		
		4)	Delete_Record ;;
		
		5)	Modify_Record ;;
			
		6)	echo "*****Exiting Program******"	
			exit ;;
 esac
done




      

