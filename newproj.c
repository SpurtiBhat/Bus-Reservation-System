
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
typedef struct BinarySearchTree BST;
// if bst is empty then we have to handle the error
struct BinarySearchTree
{
  int PassnNo; // busNo0SeatNo.
  char name[10];
  struct BinarySearchTree *left;
  struct BinarySearchTree *right;
};
BST *root = NULL;
int cost(BST *r);              // calculates costs
void status();                 // shows bus and seats status
void busLists();               // shows buslist and do booking seat and return customer ID
void DisplaySeat(int bus[33]); // Display the seats of buses
void cancel(int x);            //cancel the booking 
BST *reservationInfo(BST *, int, int *); // Display Reservation Info
BST *insert(BST **r, int custID); // inserting a node 

int busSeat[32][9] = {0};
void redColor() /// Print the message in redcolor
{
  printf("\033[0;35m");
}
void resetColor() /// reset the old color of console
{
  printf("\033[0m");
}
BST *reservationInfo(BST *r, int s, int *custIDmatched) // find function
{
  if (r == NULL)
    return NULL;
  BST *presentnode = r;
  while (presentnode)
  {
    // --------------------

    if (presentnode->PassnNo == s)
    {
      *custIDmatched = 1;
      redColor();
      printf("\n-----------------------------------------------------------------");
      printf("\n||              NAME: %10s                               ||", (presentnode->name));
      printf("\n||              CUSTOMER ID: %d                              ||", presentnode->PassnNo);
      printf("\n||              BUS NUMBER: %d                                  ||", (presentnode->PassnNo) / 1000);
      printf("\n||              SEAT NUMBER: %d                                 ||", (presentnode->PassnNo) % 100);
      printf("\n||              TICKET COST: Rs.%d                             ||", cost(presentnode));
      printf("\n-----------------------------------------------------------------");
      resetColor();
      getch();
      return r;
    }
    else if (presentnode->PassnNo > s)
      presentnode = presentnode->left;
    else
      presentnode = presentnode->right;
  }

  return NULL;
}
BST *insert(BST **r, int custId)
{
  if (*r == NULL)
  {

    *r = (BST *)malloc(sizeof(BST));
    (*r)->PassnNo = custId;
    if (*r == NULL)
    {
      printf("No memory…");
      return NULL;
    }
    else
    {
      (*r)->left = (*r)->right = NULL;
      printf("\n   ENTER THE PERSON NAME: ");
      scanf("%s", &((*r)->name));
    }
  }
  else
  {
    if ((*r)->PassnNo > custId)
    {
      (*r)->left = insert(&((*r)->left), custId);
    }
    else if ((*r)->PassnNo < custId)
    {
      (*r)->right = insert(&((*r)->right), custId);
    }
  }
  return *r;
}

void DisplaySeat(int bus[33])
{
  for (int i = 1; i <= 32; i++)
  {
    redColor();
    if (i < 10 && i > 0)
    {
      printf("0%d .", i);
    }
    else
    {
      printf("%d .", i);
    }

    resetColor();
    {
      if (bus[i] == 0)
        printf("EMPTY ");
      else
        printf("BOOKED"); // reserv
    }
    printf("         ");
    if (i % 4 == 0)
      printf("\n");
  }
}


void login()
{
  char userName[20] = "bus";
  char passWord[10] = "1234";
  char matchPass[10];
  char matchUser[10];
  int value;
  redColor();
  printf("\n\n=========================================================================================\n");
  printf("\n\t\t\tWELCOME TO ONLINE BUS RESERVATION");
  printf("\n\n=========================================================================================\n\n");
  resetColor();
login:
{
  printf("\n\nUserName: ");
  gets(matchUser);

  printf("\nPassWord: ");
  gets(matchPass);
}

  value = strcmp(passWord, matchPass); /// string compare is function defined in headerfile i.e string.h
  if (value != 0)
  {
    redColor();
    printf("\nINVALID DETAILS TRY AGAIN...\n");
    resetColor();
    goto login;
  }
  else
  {
    printf("\nLOGED IN SUCCESFULLY...\n");
  }
}
int cost(BST *r)
{
  int cost, buscost;
  buscost = (r->PassnNo) / 1000;
  switch (buscost % 3)
  {
  case 1://if remainder is 1
    return 70;
    break;
  case 2:
    return 55;
    break;
  case 0:
    return 40;
    break;
  default:
    return 0;
    break;
  }
}
void status()
{
  int busNum;
  busLists();
busInput:
  printf("\n\nENTER YOUR BUS NUMBER : ");
  scanf("%d", &busNum);
  if (busNum <= 0 || busNum >= 10)
  {
    redColor();
    printf("\n  PLEASE ENTER CORRECT BUS NUMBER !!\n");
    resetColor();
    goto busInput;
  }
  printf("\n");
  DisplaySeat(busSeat[busNum]);
  getch();
}
      
    void reserveForPhysicallyDisabled(int bus[32][9],int choice) {
    int CustId,numofSeats,seatnumber,i;
    printf("\n\nRESERVATION FOR PHYSICALLY DISABLED\n");

    do {
        printf("\n\nENTER THE NUMBER OF SEATS U WANT TO BOOK FOR PHYSICALLY DISABLED FROM (1-10): ");
        scanf("%d", &numofSeats);

        if (numofSeats <= 0 || numofSeats > 10) {
            redColor();
            printf("INVALID NUMBER OF SEATS ENTERD ONLY 10 SEATS ARE RESERVED FOR PHYSICALLY DISABLED PASSENGERS \n");
            resetColor();
        }
    } while (numofSeats <= 0 || numofSeats > 10);

    // Loop to reserve seats for physically disabled
    for (i = 0; i < numofSeats; i++) {
        while (1) {
            printf("\nCHOOSE A VALID SEAT NUMBER BETWEEN 1-10 ");
            scanf("%d", &seatnumber);

            // Check if the seat is valid and available
            if (seatnumber >= 1 && seatnumber <= 10 && bus[choice][seatnumber] == 0) {
                bus[choice][seatnumber] = 1; // Mark seat as reserved for physically disabled
                printf("Seat %d reserved for physically disabled.\n", seatnumber);
                CustId = choice * 1000 + seatnumber; // CustomerId
                busSeat[choice][seatnumber] = 1;
                root = insert(&root, CustId);
                redColor();
                printf("\n   YOUR CUSTOMER ID IS : %d", CustId);
                resetColor();
                printf("\n\n==================================================================================\n\n");
                break; // Break out of the inner loop if a valid seat is selected
            } else {
                redColor();
                printf("INVALID SEAT NUMBER OR SEAT ALREADY BOOKED.\n");
                printf("PLEASE CHOOSE ANOTHER SEAT.\n");
                resetColor();
            }
        }
    }

    printf("\nPress 'ENTER' key to continue.");
    getch();
}



void busLists()
{
  redColor();
  printf("-----------------------------------------------------------------------------------------");
  printf("\nBus.No\tName\t\t\tDestinations  \t\tCharges  \t\tTime\n");
  printf("-----------------------------------------------------------------------------------------");
  resetColor();
  printf("\n1\tRajahamsa Travels     \tBanglore  to Shivamogga     \tRs.70   \t\t07:00  AM");
  printf("\n2\tAiravatha Travels     \tBanglore to Manglore           \tRs.55    \t\t01:30  PM");
  printf("\n3\tKrishna Travels   \tAllahabad To Mumbai           \tRs.40          \t\t03:50  PM");
  printf("\n4\tSuper Deluxe         \tChennai To Banglore        \tRs.70    \t\t01:00  AM");
  printf("\n5\tVRL Travels     \tBanglore To Jaipur        \tRs.55        \t\t12:05  AM");
  printf("\n6\tSRS Travels     \tMysore to Goa              \tRs.40          \t\t09:30  AM");
  printf("\n7\tSam Travels        \tKolkata To Mysore            \tRs.70   \t\t11:00  PM");
  printf("\n8\tRaj Travels       \tPondicherry To Banglore       \tRs.55    \t\t08:15  AM");
  printf("\n9\tDharma Travels        \tOoty To Manglore            \tRs.40    \t\t04:00  PM");
  printf("\n");
  printf("\n   PRESS 'ENTER' KEY TO CONTINUE ");
  getch();
}

void cancel(int randomNum)
{
  int reservationNo;
  int seatNumber;
  int choice;
  char c;
  int seatCancel;

aa:
{
  printf("\nENTER YOUR RESERVATION NUMBER : ");
  scanf("%d", &reservationNo);
  if (reservationNo == randomNum)
  {
    printf("\nRESERVATION NUMBER IS IT CORRECT ? %d \nENTER (Y/N) : ", reservationNo);
    scanf("%s", &c);
    if (c == 'y' || c == 'Y')
    {
      printf("\n\n============================================\n\n");
      printf("   ENTER THE BUS NUMBER: ");
      scanf("%d", &choice);

      printf("\n HOW MANY SEATS DO WANT TO CANCEL : ");
      scanf("%d", &seatCancel);
      for (int i = 0; i < seatCancel; i++)
      {
        printf("   \nENTER THE SEAT NUMBER: ");
        scanf("%d", &seatNumber);

        busSeat[choice][seatNumber] = 0;
      }
      printf("\n\nYOUR RESERVATION HAS BEEN CANCEL !!\n\n");
      printf("\n  PRESS 'ENTER' KEY TO CONTINUE \n");
      getch();
      DisplaySeat(busSeat[choice]);
    }

    else if (c == 'n' || c == 'N')
    {
      printf("\nYOUR RESERVATION CANCELATION HAS BEEN DENIED\n");
    }
  }
  else
  {
    printf("\nNOT FOUND!! ENTER THE CORRECT RESERVATION NUMBER\n");
    goto aa;
  }
}
}

int main()
{
  srand(time(0));
  int randomNum = rand();
  int num, i, custID, reservationNo;
  BST *root1;
  login();
main:
{
  do
  {
    printf("\n\n====================================================================\n\n");
    printf("\t\t\t\033[1;31mBUS RESERVATION\033[0m\t\t");
    printf("\n\n=====================================================================\n");
    printf("\n====================");
    redColor();
    printf("  MAIN MENU ");
    resetColor();
    printf("=====================\n\n");
    printf("   \033[1;31m[1]\033[0m VIEW BUS LIST \n\n");
    printf("   \033[1;31m[2]\033[0m BOOK TICKETS\n\n");
    printf("   \033[1;31m[3]\033[0m CANCEL BOOKING\n\n");
    printf("   \033[1;31m[4]\033[0m BUSES SEATS INFO\n\n");
    printf("   \033[1;31m[5]\033[0m RESERVATION INFO\n\n");
    printf("   \033[1;31m[6]\033[0m EXIT\n");
    printf("\n=====================================================\n");
    printf("\n   ENTER YOUR CHOICE: ");
    scanf("%d", &num);
    switch (num)
    {
    case 1:
      busLists(); // for list of bus
      break;
    

    case 2:
      busLists(); // for booking the tickets

      int CustId, choice, seats;

    busChoice:
      printf("\n\nCHOOSE YOUR BUS  : ");
      scanf("%d", &choice);
      if (choice <= 0 || choice > 9)
      {
        redColor();
        printf("\nENTER VALID BUS NUMBER !! \n");
        resetColor();
        getch();
        goto busChoice;
      }
      printf("\n");
      DisplaySeat(busSeat[choice]);
      // Display the status of physically disabled seats
      printf("FIRST 10 SEATS ARE RESERVED FOR PHYSICALLY DISABLED PASSENGERS\n");
     printf("WOULD U LIKE TO BOOK A TICKET FOR PHYSICALLY DISABLED\n");
     printf("ENTER 1 FOR YES AND 0 FOR NO\n");
        int n;
        scanf("%d",&n);
        if(n==1)/*{
        for (int i = 1; i< 11; i++) {
        if (busSeat[i][0] == 2) {
            printf("%d ", i); // Displaying physically disabled seats
        }
        //reserveForPhysicallyDisabled(busSeat);
        }*/
        {
        reserveForPhysicallyDisabled(busSeat,choice);
        redColor();
        
    printf("\n SUCCESSFULLY BOOKED SEATS FOR PHYSICALLY DISABLED \n");
    resetColor();
        }
        
    int yn;
    printf("DO YOU WANT TO CONTINUE NORMAL BOOKING IN THE SAME BUS press 1 for YES or 0 for NO\n");
    scanf("%d",&yn);
    if(yn==1)
    {

    busSeatChoice:
      printf("\n\nNO. OF SEATS YOU WUD LIKE TO BOOK : ");
      scanf("%d", &seats);
      if (seats <= 0)
      {
        redColor();
        printf("\nENTER VALID SEAT NUMBER!!\n");
        resetColor();
        goto busSeatChoice;
      }
      else if (seats > 32)
      {
        redColor();
        printf("\nENTER VALID SEAT NUMBER WE HAVE ONLY 32 SEATS IN A BUS !!\n");
        resetColor();
        goto busSeatChoice;
      }
      int seatNumber;
      for (int i = 1; i <= seats; i++)   
      {
        printf("\n\n==================================================================================\n\n");
      seat:
        printf("   ENTER THE SEAT NUMBER: ");
        scanf("%d", &seatNumber);
        if (seatNumber <= 10)
        {
          redColor();
          printf("\n   ENTER VALID SEAT NUMBER  FIRST 10 SEATS ARE RESERVED FOR PHYSICALLY DISABLED!!\n\n");
          resetColor();
          goto seat;
        }
        else if (seatNumber > 32)
        {
          redColor();
          printf("\n   ENTER VALID SEAT NUMBER WE HAVE ONLY 32 SEATS IN A BUS !!\n\n");
          resetColor();
          goto seat;
        }
        CustId = choice * 1000 + seatNumber; // CustumerId
        busSeat[choice][seatNumber] = 1;
        root = insert(&root, CustId);
        redColor();
        printf("\n   YOUR CUSTOMER ID IS : %d", CustId);
        resetColor();
        printf("\n\n==================================================================================\n\n");
      }
    }

    if(n==0&&yn==0)
        {
          printf("YOU HAVENT BOOKED ANY TICKETS\n");
        }
    
    if(n>0||yn>0)
    {

        printf("Your Reservation Is completed\n");
         printf("\nYOUR RESERVATION NUMBER IS : ");
         redColor();
        printf("%d\n", randomNum);
         printf("\nPLEASE NOTE DOWN YOUR RESERVATION NUMBER FOR CANCEL BOOKING TICKETS!!\n");
        resetColor();   
    }
      printf("PRESS 'ENTER' KEY TO CONTINUE ");
      getch();
      break;
      
    
    
    case 3:
      cancel(randomNum);
      break;
    case 4:
      status(randomNum);
      break;
    case 5:
    takingReservationNo:
      printf("\n   ENTER YOUR RESERVATION NUMBER :");
      scanf("%d", &reservationNo);

      if (randomNum == reservationNo)
      {
      cust:
        printf("\n   ENTER YOUR CUSTOMER ID :");
        scanf("%d", &custID);
        int custIDmatched = 0;
        root1 = reservationInfo(root, custID, &custIDmatched);
        if (custIDmatched == 0)
        {
          redColor();
          printf("\n   ENTER CORRECT CUSTOMER ID!!\n");
          resetColor();
          goto cust;
        }
      }
      else
      {
        redColor();
        printf("\n INVALID RESERVATION NUMBER PLEASE ENTER CORRECT RESERVATION NUMBER !!\n");
        resetColor();
        goto takingReservationNo;
      }
      break;
      case 6:break;
    default:
      redColor();
      printf("\n\n   INVALID INPUT CHOOSE CORRECT OPTION\n");
      resetColor();
      break; 
    }
  
    

    printf("\nPress 'ENTER' key to continue.");
    getch();

  }while (num!=6);
  printf("\n\n=====================================================================\n\n");
  printf("THANK YOU FOR USING THIS BUS RESERVATION SYSTEM");
  printf("\n\nPRESS ANY KEY TO EXIT THE END PROGRAM !! \n");
  printf("\n\n");
  getch();
  return 0;
}
}
