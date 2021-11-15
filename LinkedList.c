// Fig. 12.3: fig12_03.c
// Inserting and deleting nodes in a list
// Modified by Bob Langelaan on July 10th, 2015

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// self-referential structure                       
struct listNode {                                      
   char data; // each listNode contains a character 
   struct listNode *nextPtr; // pointer to next node
}; 

typedef struct listNode ListNode; // synonym for struct listNode
typedef ListNode *ListNodePtr; // synonym for ListNode*

// prototypes
void insert(ListNodePtr *sPtr, char value);
char delete(ListNodePtr *sPtr, char value);
int isEmpty(ListNodePtr sPtr);
void printList(ListNodePtr currentPtr);
void instructions(void);
ListNodePtr merge(ListNodePtr *sPtr, ListNodePtr *lPtr );

int main(void)
{ 
   ListNodePtr startPtr = NULL; // initially there are no nodes
   ListNodePtr secondListPtr = NULL;

   char item; // char entered by user
   
   instructions(); // display the menu
   unsigned int choice; // user's choice

   // loop while user does not choose 3

   int timeToExit = 0;  // false to begin with
   do{
	  printf("%s", "? ");
	  scanf("%u", &choice);

      switch (choice) { 
         case 1:
            printf("%s", "Enter a character: ");
            scanf("\n%c", &item);
            insert(&startPtr, item); // insert item in list
            printList(startPtr);
            break;

         case 2: // delete an element
            // if list is not empty
            if (!isEmpty(startPtr)) { 
               printf("%s", "Enter character to be deleted: ");
               scanf("\n%c", &item);

               // if character is found, remove it
               if (delete(&startPtr, item)) { // remove item
                  printf("%c deleted.\n", item);
                  printList(startPtr);
               } 
               else {
                  printf("%c not found.\n\n", item);
               } 
            } 
            else {
               puts("List is empty.\n");
            } 

            break;
         case 3://insert into list 2
             printf("%s", "Enter a character: ");
             scanf("\n%c", &item);
             insert(&secondListPtr, item); // insert item in list
             printList(secondListPtr);
             break;

         case 4://delete from list 2
            // if list is not empty
             if (!isEmpty(secondListPtr)) {
                 printf("%s", "Enter character to be deleted: ");
                 scanf("\n%c", &item);

                 // if character is found, remove it
                 if (delete(&secondListPtr, item)) { // remove item
                     printf("%c deleted.\n", item);
                     printList(secondListPtr);
                 }
                 else {
                     printf("%c not found.\n\n", item);
                 }
             }
             else {
                 puts("List is empty.\n");
             }

             break;

         case 5://merge list 2 into list 1
            
             printf("Before merge, the 2 lists are:\n\n");

             if (!isEmpty(startPtr)) {
                 printList(startPtr);
             }
             else {
                 puts("List 1 empty.\n");
             }

             if (!isEmpty(secondListPtr)) {
                 printList(secondListPtr);
             }
             else {
                 puts("List 2 empty.\n");
             }
            
             printf("After merge, the 2 lists are:\n\n");
           
             if (!isEmpty(startPtr)) {
                 merge(&startPtr, &secondListPtr);
                 printList(startPtr);
             }
             else {
                 puts("List 1 empty.\n");
             }

             if (!isEmpty(secondListPtr)) {
                 printList(secondListPtr);
             }
             else {
                 puts("List 2 empty.\n");
             }
  
             break;

		 case 6:
			 timeToExit = 1; // now set to true
			 break;

         default:
            puts("Invalid choice.\n");
            instructions();
            break;
      } // end switch

   } while (!timeToExit);

   puts("End of run.");

   // Time to go home
   _getch();
} 

// display program instructions to user
void instructions(void)
{ 
   puts("Enter your choice:\n"
      "   1 to insert an element into the list 1.\n"
      "   2 to delete an element from the list 1.\n"
      "   3 to insert an element into the list 2.\n"
      "   4 to delete an element from the list 2.\n"
      "   5 to merge list 2 into list 1"
      "   6 to end.");
} 

// insert a new value into the list in sorted order
void insert(ListNodePtr *sPtr, char value)
{ 
   ListNodePtr newPtr = malloc(sizeof(ListNode)); // create node

   if (newPtr != NULL) { // is space available
      newPtr->data = value; // place value in node
      newPtr->nextPtr = NULL; // node does not link to another node

      ListNodePtr previousPtr = NULL;
      ListNodePtr currentPtr = *sPtr;

      // loop to find the correct location in the list       
      while (currentPtr != NULL && value > currentPtr->data) {
         previousPtr = currentPtr; // walk to ...               
         currentPtr = currentPtr->nextPtr; // ... next node 
      }                                          

      // insert new node at beginning of list
      if (previousPtr == NULL) { 
         newPtr->nextPtr = *sPtr;
         *sPtr = newPtr;
      } 
      else { // insert new node between previousPtr and currentPtr
         previousPtr->nextPtr = newPtr;
         newPtr->nextPtr = currentPtr;
      } 
   } 
   else {
      printf("%c not inserted. No memory available.\n", value);
   } 
} 

// delete a list element
char delete(ListNodePtr *sPtr, char value)
{ 
   // delete first node if a match is found
   // we need to treat deleting the first node as a special case
   if (value == (*sPtr)->data) { 
      ListNodePtr tempPtr = *sPtr; // hold onto node being removed
      *sPtr = (*sPtr)->nextPtr; // de-thread the node
      free(tempPtr); // free the de-threaded node
      return value;
   } 

   // normal case of potentially deleting node, but not first node
   else { 
      ListNodePtr previousPtr = *sPtr;
      ListNodePtr currentPtr = (*sPtr)->nextPtr;

      // loop to find the correct location in the list
      while (currentPtr != NULL && currentPtr->data != value) { 
         previousPtr = currentPtr; // walk to ...  
         currentPtr = currentPtr->nextPtr; // ... next node  
      } 

      // delete node at currentPtr
      if (currentPtr != NULL) { 
         ListNodePtr tempPtr = currentPtr;
         previousPtr->nextPtr = currentPtr->nextPtr;
         free(tempPtr);
         return value;
      } 

	  else // data item not found so return NULL
	  { 
		  return '\0';
	  }
   } 

} 

// return 1 if the list is empty, 0 otherwise
int isEmpty(ListNodePtr sPtr)
{ 
   return sPtr == NULL;
   
} 

// print the list
void printList(ListNodePtr currentPtr)
{ 
   // if list is empty
   if (isEmpty(currentPtr)) {
      puts("List is empty.\n");
   } 
   else { 
      puts("The list is:");

      // while not the end of the list
      while (currentPtr != NULL) { 
         printf("%c --> ", currentPtr->data);
         currentPtr = currentPtr->nextPtr;   
      } 

      puts("NULL\n");
   } 
} 

//merge list 2 into list 1
ListNodePtr merge(ListNodePtr *list1Ptr, ListNodePtr *list2Ptr)
{
         if (list1Ptr == NULL) {
             return list2Ptr;
            }
         else if(list2Ptr == NULL){
             return list1Ptr;
         }
         ListNodePtr head1 = *list1Ptr;
         ListNodePtr head2 = *list2Ptr;
         ListNodePtr mergedHead = NULL;
         if (head1->data <= head2->data) {
             mergedHead = head1;
             head1 = head1->nextPtr;
         }
         else
         {
             mergedHead = head2;
             head2 = head2->nextPtr;
         }

         ListNodePtr mergedTail = mergedHead;

         while (head1 != NULL && head2 != NULL) {
             ListNodePtr temp = NULL;
             if (head1->data <= head2->data) {
                 temp = head1;
                 head1 = head1->nextPtr;
             }
             else
             {
                 temp = head2;
                 head2 = head2->nextPtr;
             }
             mergedTail->nextPtr = temp;
             mergedTail = temp;
         }
         if (head1 != NULL)
         {
             mergedTail->nextPtr = head1;
         }
         else if (head2 != NULL )
         {
             mergedTail->nextPtr = head2;
         }
         *list2Ptr = NULL;
         return mergedHead;
}




/**************************************************************************
 * (C) Copyright 1992-2015 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
