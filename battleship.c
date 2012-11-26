#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>

char mainGrid[10][10];
char yourGrid[10][10];
int yourShips[10][10];
int enemyShips[10][10];
int difficulty = 1, success = 0, successRow = 0, successCol = 0, yourShipCount = 42, enemyShipCount = 42, successShipNum = 0;
int successDir = 42, successCount = 1, possibleDirs[4] = {1,1,1,1}, allDirections = 0, successCount2 = 0;
int previousShips = 5, previousEnemyShips = 5; 

//the int success determines whether or not the enemy has completed a successful attack.
//successRow and successCol hold the spot that was a successful hit. 
//possibleDirs[] holds an array of directions that the ship could be in.
//successCount counts how many times it has fired in that direction.
//successDir determines what direction success has most recently occured in.

void setGrids(void);
void printGrid(void);
void viewYourGrid(void);
void attack(int row, int col);
int charToNum(char ch);
char numToChar(int num);
int randomGenerator(int range);

void winFunct(void);
void loseFunct(void);

void placeShips(int shipNum);

void placeEnemyShips(void);
void checkGrids(void);
void enemyAttack(void);
void enemyContinueAttack();

int main (void)
{
    
    int choice, option, targetRow, targetCol, previous, dummy;
    
    char column;
    
    printf("                                  _/|                           \n");
    printf("                                 _|:|                           \n");
    printf("                               _|:::|                           \n");
    printf("                         _ /|  |::::|                           \n");
    printf("                         |::|  |::::|                           \n");
    printf("                         |::|  |:::::)__                        \n");
    printf("                       /:|:::: |::::::::|                       \n");
    printf("                      :::|::::_|::::::::|                       \n");
    printf("                ____(:::::::::::::::::::|___ _______         __ \n");
    printf("               (::::::::::::::::::::::::|:::|::::::|  ______|::)\n");
    printf("     ___________\\:::::::::::::::::::::::::::|:::|___|:::::::::|\n");
    printf("     \\::::::::::::::::::::::::::::::::::::::::::::::::::::::::|\n");
    printf("      |:::::::::::::::::::::::::::::::::::::::::::::::::::::::| \n");
    sleep(1500);
    printf("__________          __    __  .__                  .__    .__          \n");
    printf("\\______   \\_____  _/  |__/  |_|  |    ____   ______|  |__ |__|______ \n");
    printf(" |    |  _/\\__  \\ \\   __\\   __\\  |  _/ __ \\ /  ___/|  |  \\|  |\\____ \\  \n");
    printf(" |    |   \\ / __ \\_|  |  |  | |  |__\\  ___/ \\___ \\ |      \\  ||  |_> >    \n");
    printf(" |______  /(______/|__|  |__| |____/ \\_____>______>|___|  /__||   __/          \n");
    printf("       _\\/ _     _   _   _   _   _     _   _   _   _    \\/    |__|            \n");
    printf("      / \\ / \\   / \\ / \\ / \\ / \\ / \\   / \\ / \\ / \\ / \\   \n");
    printf("     ( 1 | : ) ( S   T   A   R   T ) ( G   A   M   E )             \n");
    printf("      \\_/ \\_/   \\_/ \\_/ \\_/ \\_/ \\_/   \\_/ \\_/ \\_/ \\_/   \n");
    scanf("%d",&choice);  
    
    while(choice!=1)
       {
       
          printf("Invalid input! Please re-enter!\n");
          scanf("%d",&choice);
          
       }

    switch(choice)
    {
    
    case 1:
    system("cls");     
    setGrids();
    system("cls");
    placeEnemyShips();
    placeShips(1);
    checkGrids();
    
    while(yourShipCount>0&&enemyShipCount>0)
     {  
       option = 1;
           
            printf("\n\nWhere would you like to fire at?\n");
            fflush(stdin);
            column = getchar();
            targetCol = charToNum(column);
            scanf("%d",&targetRow);
            
            if(success==0)
               enemyAttack();
            else if(success!=0)
               enemyContinueAttack();
            attack(targetRow, targetCol);   
            checkGrids();
       
     }//end main loop
    break;
    
    default: printf("Invalid input! Please re-enter.\n");
             scanf("%d",&choice);
             break;
                  
    }//end main switch(choice)
    
   system("cls");
   
    if(yourShipCount<=0)
    {
       loseFunct();
       printf("The enemy has sunk all of your ships!\n");
       printf("You lose\n");
    }
    else if(enemyShipCount<=0)
    {
       winFunct();
       printf("You have sunk all of the enemy ships! Conglaturation!!!(intended misspelling)\n");    
    }
      
   scanf("%d",&dummy);   
   
   return 42;   

}//end main()


void setGrids()
{
     
 int x,y;
    //grid of the computer player's ships, the one that is printed every turn
    for(y=0; y<10; y++)
    {
    
       for(x = 0; x<10; x++)
       {
               
       mainGrid[y][x] = ' ';
         
       }
       
    }
        
    //grid of your own ships, viewed with a selectable option  
    for(y=0; y<10; y++)
    {
    
       for(x = 0; x<10; x++)
       {
             
          switch(yourShips[y][x]) 
          {
          case 1:    yourGrid[y][x] = '1'; break;
       
          case 2:    yourGrid[y][x] = '2'; break;
       
          case 3:    yourGrid[y][x] = '3'; break;
       
          case 4:    yourGrid[y][x] = '4'; break;
       
          case 5:    yourGrid[y][x] = '5'; break;
       
          default:   yourGrid[y][x] = ' '; break;
          }//end switch(yourShips[y][x])  
         
       }//end x loop
       
    }// end y loop           
     
    //array to keep track of your ships, and which ships are at certain spots 
    for(y=0; y<10; y++)
    {
    
       for(x = 0; x<10; x++)
       {
               
       yourShips[y][x] = 0;
         
       }
       
    }     
     
    //array to keep track of enemy ships, and which ships are at certain spaces  
    for(y=0; y<10; y++)
    {
    
       for(x = 0; x<10; x++)
       {
               
       enemyShips[y][x] = 0;
         
       }
       
    }     
}//end setGrids()

void printGrid()
{
   
   printf("_______________________\n");
   printf("\nYour opponent's grid: \n_______________________\n");
   int x, y, z, w;  
   int yCount[9]; /*char array to store the numbers 0-9 in to print it at the 
                  bottom of the grid*/
   printf("\n     A     B     C     D     E     F     G     H     I     J   \n");
   printf("   ___________________________________________________________ \n");
   printf("  |     |     |     |     |     |     |     |     |     |     |\n");
   
    for(x=9; x>=0; x--)
    {
       printf("%d ",x);
    
          for(y = 0; y<10; y++)
          {
             printf("|  ");   
             putchar(mainGrid[x][y]);
           printf("  ");
           yCount[y] = y; 
          }   
       
       printf("|\n");
       printf("  |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|");
       if(x!=0)
          printf("\n  |     |     |     |     |     |     |     |     |     |     |\n");

       
       if(x==0)
       {
         printf("\n   ");
               
       }

     }//end loop 
     
     printf("\n");
     
}//end printGrid()

void attack(int row, int col)
{
     char column;
     
     if(enemyShips[row][col]==0)
     {
                                
         mainGrid[row][col] = 'X';
         enemyShips[row][col] = 6;
         printf("Spot [%c,%d] was a miss! No ships were damaged.\n", numToChar(col) ,row );
         sleep(850);
         
     }
     else if(enemyShips[row][col]==6)
          {
                                     
          while(enemyShips[row][col]==6)
             {
                
                printf("You have already fired at [%c,%d] before! Please re-enter a coordinate.\n",numToChar(col),row);
                fflush(stdin);
                column = getchar();
                col = charToNum(column);
                fflush(stdin);
                scanf("%d",&row);
                
             }
             
          attack(row, col);/*recursive call to attack() if the entered
                                   coordinates were already fired at*/
             return;                                              
          }
          else
          {
              
             mainGrid[row][col] = 'O';
             enemyShips[row][col] = 6;
             printf("You have successfully fired at [%c,%d]!\a\a\n", numToChar(col), row);
             sleep(1000);
          }
          
          viewYourGrid();
          printGrid();
     
}//end attack()

void placeShips(int shipNum)
{
     
     if(shipNum>5)
        return;
        
     printf("\n%d\n", shipNum);
     int direction = 0, col = 0, row = 0, count = 0, count2 = 0, breakNum = 0;
     int shipLength;
     char yourcolumn, ch, shipName[11];
	 
	 switch(shipNum)
        {
             
             case 1: shipLength = 2; ch = 'D'; 
                     shipName[0] = 'D';
                     shipName[1] = 'e';
                     shipName[2] = 's';
                     shipName[3] = 't';
                     shipName[4] = 'r';
                     shipName[5] = 'o';
                     shipName[6] = 'y';
                     shipName[7] = 'e';
                     shipName[8] = 'r';
                     shipName[9] = '\0';
                     break;
             case 2: shipLength = 3; ch = 'C';
                     shipName[0] = 'C';
                     shipName[1] = 'r';
                     shipName[2] = 'u';
                     shipName[3] = 'i';
                     shipName[4] = 's';
                     shipName[5] = 'e';
                     shipName[6] = 'r';
                     shipName[7] = '\0';
                     break;
             case 3: shipLength = 3; ch = 'S';
                     shipName[0] = 'S';
                     shipName[1] = 'u';
                     shipName[2] = 'b';
                     shipName[3] = 'm';
                     shipName[4] = 'a';
                     shipName[5] = 'r';
                     shipName[6] = 'i';
                     shipName[7] = 'n';
                     shipName[8] = 'e';
                     shipName[9] = '\0';
                     break;
             case 4: shipLength = 4; ch = 'B';
                     shipName[0] = 'B';
                     shipName[1] = 'a';
                     shipName[2] = 't';
                     shipName[3] = 't';
                     shipName[4] = 'l';
                     shipName[5] = 'e';
                     shipName[6] = 's';
                     shipName[7] = 'h';
                     shipName[8] = 'i';
                     shipName[9] = 'p';
                     shipName[10] = '\0';
                     break;
             case 5: shipLength = 5; ch = 'A';
                     shipName[0] = 'C';
                     shipName[1] = 'a';
                     shipName[2] = 'r';
                     shipName[3] = 'r';
                     shipName[4] = 'i';
                     shipName[5] = 'e';
                     shipName[6] = 'r';
                     shipName[7] = '\0';
                     break;
             
        }
			 
           printf("Where do you want the topmost, or leftmost spot of your %s to be placed?\n", shipName);
           printf("NOTE: Enter the Top(letter) Coordinate, then the Left(number)\n");
           fflush(stdin);
           yourcolumn = getchar();
           col = charToNum(yourcolumn);
           scanf("%d",&row);
           printf("Do you want your %s to be placed horizontally or vertically?\n", shipName);
           printf("1: horizontally or 2: vertically?\n");
           fflush(stdin);
           scanf("%d",&direction);
           
           switch(direction)
           {
              case 1 : 
                   
                   for(count2 = 0; count2<shipLength; count2++)
                      {
                              
                         if(yourShips[row][col + count2]!=0||col + shipLength>10)
                         {
                                               
                         printf("That space is invalid!\n");
                         placeShips(shipNum);
						 return;
                         breakNum = 1;
						 break;
							/*The last three commands ensure that there 
							will be no infinite iteration of the function call*/
                         }
                         
                     }//end validation loop
                   
                   if(breakNum==1)
                      break;
						
                   
                   for(count = 0; count<shipLength; count++)
                   {
					  if(yourShips[row][col + count]==0)
					  {
                      yourShips[row][col + count] = shipNum;
                      yourGrid[row][col + count] = ch;
					  }
					  
                   }
                   break;
                   
              case 2 : 
                   
                   for(count2 = 0; count2<shipLength; count2++)
                      {
                              
                         if(yourShips[row - count2][col]!=0||row - shipLength<-1)
                         {
                                               
                         printf("That space is invalid!\n");
                         placeShips(shipNum);
						 return;
                         breakNum = 1;
                         count2 = 42;
						 break;
                                   
                         }
                         
                      }//end validation loop
                      
                      if(breakNum==1)
                         break;
                      
                   for(count = 0; count<shipLength; count++)
                   {
					  if(yourShips[row - count][col]==0)
					  {
                      yourShips[row - count][col] = shipNum;
                      yourGrid[row - count][col] = ch;
					  }
					  
                   }
                   break;
                   
              default : 
                      printf("Invalid input!\n"); 
                      placeShips(shipNum);
					  return;
                       
           }//end switch(direction)
           viewYourGrid();
           placeShips(shipNum + 1);
           return;
           
		   
}//end placeShips(); */

int charToNum(char ch)
{
                   
            ch = toupper(ch);
            int num;
    
            switch(ch)
            {
            
             case 'A':   num = 0; break;
        
             case 'B':   num = 1; break;
             
             case 'C':   num = 2; break;
             
             case 'D':   num = 3; break;   
             
             case 'E':   num = 4; break;   
        
             case 'F':   num = 5; break;   
             
             case 'G':   num = 6; break;   
             
             case 'H':   num = 7; break;       
        
             case 'I':   num = 8; break;    
             
             case 'J':   num = 9; break;   
             
             default: printf("Invalid input! Please re-enter the column\n");
                      fflush(stdin);
                      ch = getchar();
                      num = charToNum(ch);
                
             }//end switch(ch) 
             
             return num;
             
}//end charToNum()

char numToChar(int num)
{
     
            char ch;
    
            switch(num)
            {
            
             case 0:   ch = 'A'; break;
        
             case 1:   ch = 'B'; break;
             
             case 2:   ch = 'C'; break;
             
             case 3:   ch = 'D'; break;   
             
             case 4:   ch = 'E'; break;   
        
             case 5:   ch = 'F'; break;   
             
             case 6:   ch = 'G'; break;   
             
             case 7:   ch = 'H'; break;       
        
             case 8:   ch = 'I'; break;    
             
             case 9:   ch = 'J'; break;
             
             }//end switch(num) 
             
             return ch;
             
}//end numToChar()

void viewYourGrid()
{
 
   int x, y;
   printf("_____________\n");
   printf("\nYour grid: \n_____________\n");
   printf("     A     B     C     D     E     F     G     H     I     J   \n");
   printf("   ___________________________________________________________ \n");
   printf("  |     |     |     |     |     |     |     |     |     |     |\n");
   
    for(x=9; x>=0; x--)
    {
       printf("%d ",x);
    
          for(y = 0; y<10; y++)
          {
                
             printf("|  "); 
             printf("%c", yourGrid[x][y]);  
             //putchar(yourGrid[x][y]);
             printf("  ");
           
          }   
       
       printf("|\n");
       printf("  |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|");
       if(x!=0)
          printf("\n  |     |     |     |     |     |     |     |     |     |     |\n");

       
       if(x==0)
       {
         printf("\n   ");
       }

     }//end loop 
     
     printf("\n");
    printf("D: Destroyer(2)  S: Submarine(3)\nC: Cruiser(3)   B: Battleship(4)\nA: Aircraft Carrier(5)\n");
     printf("X: miss   O: hit   \n1 beep: Opponent's hit   2 beeps: Your hit\n");
     printf("3 beeps: Sunken ship\n\n");
     
}//end viewYourGrid()

int randomGenerator(int range)
{
    
   int num;

  /* initialize random seed: */
  srand( getpid() ^ clock() );

  /* generate random number: */
  num = rand() % range;
  
  sleep(99);
  
  return num;
    
}//end randomGenerator

void placeEnemyShips()
{

     printf("Enemy ships are being deployed...Please wait\n");
     switch(difficulty)
     {
     
        case 1: 
            { 
             int direction = 0, col = 0, row = 0, count2 = 0, breakNum = 0, count3 = 0;
             int shipLength = 0;
             int counter = 1, distance = 0;
             char ch;
             
          for(counter = 1; counter<=5; counter++)
          {
             switch(counter)
             {
             
             case 1: shipLength = 2; ch = '1'; break;
             case 2: shipLength = 3; ch = '2'; break;
             case 3: shipLength = 3; ch = '3'; break;
             case 4: shipLength = 4; ch = '4'; break;
             case 5: shipLength = 5; ch = '5'; break;
             
             }
             
             row = randomGenerator(9);
             col = randomGenerator(9);
             direction = randomGenerator(1337);
             distance = randomGenerator(2);
             
             if(direction%2==0)
             {
                       
                     for(count3 = 0; count3<=shipLength+distance; count3++)
                      {
                              
                         if(enemyShips[row][col + count3]!=0||col + shipLength>9)
                         {
                         count3 = -1;
                         row = randomGenerator(9);
                         col = randomGenerator(9);
                         }
                         
                      }//end validation loop
                      
                      for(count2 = 0; count2<shipLength; count2++)
                          {
                   
                          enemyShips[row][col+count2] = counter;
                          }
                   
             }
             else
             {
                 
                 for(count3 = 0; count3<=shipLength+distance; count3++)
                      {
                              
                         if(enemyShips[row - count3][col]!=0||row - shipLength<0)
                         {
                         count3 = -1;
                         row = randomGenerator(9);
                         col = randomGenerator(9);
                                   
                         }
                         
                      }//end validation loop
                   
                   for(count2 = 0; count2<shipLength; count2++)
                          {
                                    
                          enemyShips[row-count2][col] = counter;
                          }
                   
             }
                
          }
          
          //break;
          
          }
          
     }//end switch(difficulty)
     
     printGrid();
}//end placeEnemyShips()

void enemyAttack()
{
     
     int row = randomGenerator(10);
     //sleep(333);
     int col = randomGenerator(10);
     //sleep(333);
     
     if(yourShips[row][col]==0)
     {
                                
         yourGrid[row][col] = 'X';
         yourShips[row][col] = 6;
         printf("Enemy has unsuccessfully fired at [%c,%d]\n", numToChar(col) ,row );
         
     }
     else if(yourShips[row][col]==6)
          {
             
          enemyAttack();/*recursive call to enemyAttack() if the entered
                                   coordinates were already fired at*/
          }
          else
          {
              
             yourGrid[row][col] = 'O';
             yourShips[row][col] = 6;
             success = 1;
             successRow = row;
             successCol = col;
             successShipNum = yourShipCount;
             
             printf("Enemy has successfully fired at [%c,%d]\a\n", numToChar(col) ,row );
             sleep(200);
             
          }
     
}

void enemyContinueAttack()
{ //note to Kuykendall: Disregard the debug statements that are commented out.
     
     if(successShipNum==yourShipCount)
     {
        int rowNum = 0, colNum = 0;
        int dir = randomGenerator(4);
        //printf("Direction initially: %d\n", dir);
        if(successCol + successCount>9)
           possibleDirs[0] = 0;
        if(successRow - successCount<0)
           possibleDirs[1] = 0;
        if(successRow + successCount>9)
           possibleDirs[2] = 0;
        if(successCol - successCount<0)
           possibleDirs[3] = 0;
      //printf("Another direction: %d\n", dir);
       
        
        /*if(possibleDirs[0]==0&&possibleDirs[1]==0&&possibleDirs[2]==0&&possibleDirs[3]==0||(
           yourShips[successRow][successCol+1]==6&&yourShips[successRow][successCol-1]==6
           &&yourShips[successRow+1][successCol]==6&&yourShips[successRow-1][successCol]==6))
        {
           //printf("all directions = 0");
            if(yourShips[successRow][successCol+1]>0&&yourShips[successRow][successCol+1]<6)
              { 
               possibleDirs[0] = 1;
               if(allDirections==1) 
                  successCount2++;
               allDirections = 1; 
              }   
            if(yourShips[successRow-1][successCol]>0&&yourShips[successRow][successCol+1]<6)
              { 
              possibleDirs[1] = 1; 
              if(allDirections==1)
                successCount2++; 
              allDirections = 1;
              }
            if(yourShips[successRow+1][successCol+1]>0&&yourShips[successRow][successCol+1]<6)
               { 
               possibleDirs[2] = 1;
               if(allDirections==1) 
                  successCount2++; 
               allDirections = 1; 
               }
            if(yourShips[successRow][successCol-1]>0&&yourShips[successRow][successCol+1]<6)
              { 
               possibleDirs[3] = 1;
               if(allDirections==1) 
                  successCount2++; 
               allDirections = 1; 
              }                                                            
        }*/
      
        //printf("direction 1: %d successDir: %d\n", dir, successDir);
        
        if(successDir<4)
           dir = successDir;
           
        //printf("direction 2: %d\n", dir);
           
        while(possibleDirs[dir]==0)
        {
           dir = randomGenerator(4);
           successCount = 1;
        }
        
        //printf("direction 3: %d\n", dir);
        
		switch(dir)
        {
           
           case 0: rowNum = successRow;
				   colNum = successCol + successCount;
				   /*if(allDirections==1){
                      successCol++;                  
				      enemyContinueAttack();
                      return;
                      }*/
                   break;
           case 1: rowNum = successRow - successCount;
				   colNum = successCol;
				   /*if(allDirections==1){
                      successRow--;                  
				      enemyContinueAttack();
                      return;
                      }*/
                   break;
           case 2: rowNum = successRow + successCount;
				   colNum = successCol;
				   /*if(allDirections==1){
                      successRow++;                  
				      enemyContinueAttack();
                      return;
                      }*/
                   break;
           case 3: rowNum = successRow;
				   colNum = successCol - successCount;
				   /*if(allDirections==1){
                      successCol--;                  
				      enemyContinueAttack();
                      return;
                      }*/
                   break;  
				   
        }
        
        /*if(successDir==0)
              {
                 possibleDirs[1] = 0;
                 possibleDirs[2] = 0;
              }
              else if(successDir==1)
              {
                 possibleDirs[0] = 0;
                 possibleDirs[3] = 0;
              }
              else if(successDir==2)
              {
                 possibleDirs[0] = 0;
                 possibleDirs[3] = 0;
              }
              else if(successDir==3)
              {
                 possibleDirs[1] = 0;
                 possibleDirs[2] = 0;
              }*/
		
        //printf("%d\n", dir);
		//printf("%d %d %d \n", rowNum, colNum, yourShips[rowNum][colNum]);
           if(yourShips[rowNum][colNum]!=0&&yourShips[rowNum][colNum]!=6)
           {
		   
              successDir = dir;
     
              yourShips[rowNum][colNum] = 6;
              yourGrid[rowNum][colNum] = 'O';
              successCount += 1;
              printf("Enemy has successfully fired at [%c,%d] lol\a\n", numToChar(colNum), rowNum);
              sleep(200);
              return;                                        
              
           }
           else 
           {
              successDir = 42;
              
              if(yourShips[rowNum][colNum]==0)
              {
                successCount = 1;
                possibleDirs[dir] = 0;
				successDir = 42;
                yourShips[rowNum][colNum] = 6;
                yourGrid[rowNum][colNum] = 'X';
                printf("Enemy has unsuccessfully fired at [%c,%d] lol\n", numToChar(colNum), rowNum);
              }
              else if(yourShips[rowNum][colNum]==6)
              {
                   //printf("hit a 6");
                   successCount = 1;
				   successDir = 42;
                   printf("%d %d: %d",rowNum, colNum, yourShips[rowNum][colNum] );
                   possibleDirs[dir] = 0;
                   enemyContinueAttack();
                   return;
              }
              
              return;  
           }
		 
     }
     else
     {
        int x;
        successDir = 42;
        for(x=0;x<4;x++)
            possibleDirs[x] = 1;
        success = 0;
        successCount = 1;
        successCount2 = 0;
        successRow = 0;
        successCol = 0;
        enemyAttack();
     }
     
}//end continueEnemyAttack()

void checkGrids()
{
     int x = 0, y = 0,yourCount[5] = {0,0,0,0,0},enemyCount[5] = {0,0,0,0,0};
     //these arrays keep track of how many of each ship each player has
      
     yourShipCount = 0;
     enemyShipCount = 0;
     
     for(x=0;x<10;x++)
     {
     
        for(y=0;y<10;y++)
        {
        
           if(yourShips[x][y]==0||yourShips[x][y]==6)
              continue;
           else if(yourShips[x][y]!=0&&yourShips[x][y]!=6)
                yourCount[yourShips[x][y]-1] += 1;
                
        }
                      
     }
     
      for(x=0;x<10;x++)
     {
     
        for(y=0;y<10;y++)
        {
                         
           if(enemyShips[x][y]==0||enemyShips[x][y]==6)
              continue;
           else if(enemyShips[x][y]!=0&&enemyShips[x][y]!=6)
                enemyCount[enemyShips[x][y]-1] += 1;
                
        }
        
     }
     
     for(x=0;x<5;x++)
     {
     
        if(yourCount[x]==0||yourCount[x]==6)
           continue;
        else if(yourCount[x]!=0&&yourCount[x]!=6)
           yourShipCount += 1;
           
     }    
      
     for(x=0;x<5;x++)
     {
                     
      if(enemyCount[x]==0||enemyCount[x]==6)
           continue;
      else if(enemyCount[x]!=0&&yourCount[x]!=6)
           enemyShipCount += 1;
           
      }
     
     if(yourShipCount<previousShips)
     {
         printf("The enemy has sunk a ship!\a\a\a\n");
     }
     
     if(enemyShipCount<previousEnemyShips)
     {
         printf("You have sunk an enemy ship!\a\a\a\n");
     }
     printf("You have %d ships, and your opponent has %d ships", yourShipCount, enemyShipCount);
     previousShips = yourShipCount;
     previousEnemyShips = enemyShipCount;
}

void winFunct (void)
{
     //NOTE: 100 character width
int dummy;
printf("                               7777777777?I777777:I777777~77777777777                               \n");
printf("                                77~777777:::7777:~:+777~::I77777+7777                               \n");
printf("                               77I:::777:::~~??:::::~7:::::777~::=777                               \n");
printf("               777777777777~77777::::~=:::::::::::::::::::::+:::::77777+77777777                    \n");
printf("               777777777777:~:~77~:::~::::::::::::::::::::::::::::I7+:::I 777777                    \n");
printf("               77777777777?::::::::::::,::~?77777777777I~,:::::::::::::::7777777                    \n");
printf("          7777777777~::777:::::::::::I777~..,:~+++++=~,..:7777,,:,:::::::777~::777777               \n");
printf("          7777777777=::~::::::::~77~.~++?+::+++++++++=..,=++++.: 7~:,::::::::::777777               \n");
printf("          7777777777+::::::::+7+.+?++=,.,+++..+++++++,..+++..?++++.=7?:::::::::7777777              \n");
printf("          7777?::+77?:::::,I7.~++++++~..++++=..++++++....:,..+++,.??+.77,:::::~77?::~7              \n");
printf("     7777777777::::::::::7?.++.....:++..?++++.:++++++..?+?,.,+++...,.++,+7,,~:::::::7777777         \n");
printf("     7777777777::::::::7~~+~.++++...+::.....,++++++++,..::..:++....?+?.:+=:7::::::::7777777         \n");
printf("     7777777777~:::::?7.+?...?++++..,::,.,,::,??+==+?+++++++++,..?++.++++++.77::::::7777777         \n");
printf("     77777::::::::,:I.?++++..,+++..::.=+++:..:.++++++++++:.~++?:..,:,=++++++?. :,::::::::?7         \n");
printf("     77777:::::::,7?~+.+++++.....+,:,==+++++.,:,,,,,,.,,.,~?++,:::..,::+++++++++7,:::::::7          \n");
printf("     7777 7:~::::7~+?.++.++++..+==,:.+++++..,::::::::::::~~,...:,+???,....:+..++,7,:::::777         \n");
printf("     777777~::::7.+:.?+,=+++++?,++.:.+++.,::,:::::::~~~~~~~~~~:,:??I??:,+.++..+++.7,,:::7777777     \n");
printf("     7:::::::,,7.+,....+++.++,?+++,::..,::::::::::~~~~~~~~~~~~~~~,????:,?+=..+++++,7:::::::::+77    \n");
printf("     7?::::::,7.+++++....:=+:++++++,,::::::::::::~~~~~~~~~~~~~~~~~.+?~:,+++..++++.?:7:,:::::=777    \n");
printf("     77::::::7.+?,,=++~.~+:++++++++?,:::::::::::~~~~~~~~~~~~~~~~~~~.,:,?,?=.+??....+.7,::::,7777    \n");
printf("77777777~::,7.+=...++++++.+++++++++::::::::::::~~~~~~~~~~~~~~~~~~~~~.,+++.++,....,?.+.7,:::777777777\n");
printf("777~::::,:,?I++.+=.+=+++.++++++++++::::::::::::~~~~~~~~~~~~~~~~~~~~~~+++++,+?.:?.++:=+~7,::~::::I777\n");
printf("777:::::::,7.+.+++.++++,++++++++++,:::::::::.....~~~~~~~~~~~~~~~~~~~~.+++++.++++?.++.+:7::::::::7777\n");
printf("7777+:::::I~+..~+.++++:++++++++++=:::::::::.......~~~~~~~~~~~~~...~~~,++++++.+++...+.++.7,::::~77777\n");
printf("777777:::,7,?.......++=++++++++++,:::::::::,.....:~~~~~~~~~~~~.....~~~=+++++?++.......+~7,:::?777777\n");
printf("7777=::::~7?++,....,+.+++++++++++,::::::::::....,~~~~~~~~~~~~:.....~~~:++++++.+~.??..=++++:::::77777\n");
printf("7:~::::::7.++++++++++=++++++++++,:::::::::::::::~~~~~~~~~~~~~~.....~~:,+++++++=+==++++++.7::::::::I7\n");
printf("77:::::::7.+++++++++,+++++++++++.::::::::::::::,,=+?+++++?~~~~~~~~~~~~,+++++++.+++++++++~7,::::::7 7\n");
printf("777?~:::,7~+++++++++.+++++++++++,:::::::::::::.~++++++...?++=:~~~~~~~~,+++++++,+++++++++?7,::::~7777\n");
printf("7777I::::7++++++++++,++++++++++~:::::::::::::.+++++++,....++++,~~~~~~~,++++++++?+++++++++?=:::=77777\n");
printf("77::::::~I++++++++++~+++++++++,::::::::::::::,+++++++,...+++++?:~~~~~~,++++++++++++++++++=?:::::,777\n");
printf("::::::::~?++++++++++=++++++++::::::::::::::::,++++++++=+?+++++?:~~~~~~,++++++++++++++++++~I::::::::7\n");
printf("77::::::~I++++++++++~+++++++::,.,:::::::::::::....,.=I??,++?++.~~~~~~~~=++++++?++++++++++~?::::::777\n");
printf("7777=::::7++++++++++,++++++~+?,,::::::::::::::::,~,I?????:~.~~~~~~~~~~~~=++++++?+++++++++?=:::~77777\n");
printf(" 777:::::7~+++++++++.+++++++++,:::::::::::::::::.~,??????,~,~~~~~~.~~.:~~:++++,+++++++++?7,::::?7 77\n");
printf("77:::::::7.+++++++++,+++++++++,..::.,:,:::::::::,~~:I???I~,~~~~.~~..~.++++++++.+++++++++~7:::::::777\n");
printf("7::::::::7.++++++++++=+++++++++.....:,,,,::::::::.~~.?I::~,~~~:,~.,..:++++++++=+++++++++.7:::::::,?7\n");
printf("7777:::::~7?+++++++++.++++++++,,,,:,.,:,,:::::::~,.~~~~~:.~~~~~..,::,:+++++++.++++++++++=?,::::77777\n");
printf("777777:::,7,++++++++++=+++++++:,::::::::::::::~~~~.,.,:.,~~~~~~::::~~~~,+++++=+++++++++~7,:::I777777\n");
printf("777?:::::7~++++++++++:++++++:::::::::::::::~~~~~~~~~~~~~~~~~~~,,:::~~~~~:++.++++++++++.7,:::~=777777\n");
printf("777:::::::,7.++++++++++.++++:::::::::::::::~~~~~~~~~~~~~~~~~~~~,,::::~~~~~:.?+++++++++,7::::::::7777\n");
printf("77?:::::::,?+?++++++++++.++,:::::::.::::::~~~~~~~~~~~~~~~~~~~~~,+,::::~~~~:+++++++++++:7::::::::=777\n");
printf("77777777~::,7.+++++++++++.+,::::::,,::::::~~~~~~~~~~~~~~~~~~~~~,++:.,,,~~~~++++++++++.7::::I77777777\n");
printf("7777777=:::::7.+++++=+:+,+~:::::::.:::::::~~~~~~~~~~~~~~~~~~~~~:+++++,~~~~~+++++++++.7,,::::77777777\n");
printf("     77::::::,7,++++:+:+:+++,,::::,,:::::,,,~~~~~~~~~~~~~~~~~~~=++++:~~~~~::,?,++++:7~::::::+777    \n");
printf("     7:::::::::7.++++,,=?::~+,,::::,,.,~~~~~~.~~~~~~~~~~~~~~~~:++++::~~~~:::+~++++:7:,:::::::I77    \n");
printf("     777777~:::,7.++++?:~:++:++.::::::::::::::,~~~~~~~~~~~~~~~.+++~~~~~~,:,++++++.7,::::77777777    \n");
printf("     777777:::::,7.++++:~+:++,,++.::::::::::::,~~~~~~~~~~~~~~~=+?.:~~~:,+~:+++++.7,:::::777 7 77    \n");
printf("     77777~:::::::7?=+++++::~=:+,=++.,:::::::,~~~~~~~~~~~~~~~,.=+,:,,+:::+++++++7::::::::7          \n");
printf("     77777::::::::::7.+++++++:+:+++++++=.,,.:~~~~~~~~~~~~:.:++:~=:++~~+++++++.7::::::::::77         \n");
printf("     7777777777+::::,?7.++=++=:+++++~:+:+++?++?=~~~=??+++==+,++:+:++:=+++++.77::::::7777777         \n");
printf("          77777:::::::,7~==++++=:+++:+++:+:+:+++:=+::::+:+~:=,::=?+=++++=+:7,:::::::7               \n");
printf("          77777:::::::::,7?,++++++++,+?,+:::=++:+:+=~=:+:::++,+++++++++:+7,:::~~::::77              \n");
printf("          77777::~?7?::::,,77.=++++++++++:+++++:::,+:+++:++++++++++++.77:,::::~7I~::=7              \n");
printf("              7777 7?::::::,,?7=.+++++++++++++=+++=?=+++++++++++++,~7I,::::::::7  777               \n");
printf("             7777777+:::::::::::=77:.=++++++++++++++++++++++++.,77+::::::::::::7                    \n");
printf("                7777=::+77~:::::::,::777I,..:=+++++?+=:,.,?777~::::::::::77I:::7                    \n");
printf("               77777777777?::::::::::,,:::+7777777777777+::::::::::::::::7777777                    \n");
printf("                        7 7:::,7I::::::::::::::::,:::::::::::::::~?7::::I77                         \n");
printf("                          7:77777::::::::::::~::::::::::::::=:::::77777~777                         \n");
printf("                          77777777:::777:::::~=~:::::?,::::777:::=77777777                          \n");
printf("                               777:777777:::777I:::=777:::?77777~7777                               \n");
printf("                               7777777777??777777:?777777~77777777777                               \n");
printf("                               777777777777 77777I7777777777777777777                               \n");
printf("               Y88b    /   ,88~-_   888   |       Y88b         / 888  888b    |  d8b  \n");
printf("                Y88b  /   d888   \\  888   |        Y88b       /  888  |Y88b   | !Y88! \n");
printf("                 Y88b/   88888    | 888   |         Y88b  e  /   888  | Y88b  |  Y8Y  \n");
printf("                  Y8Y    88888    | 888   |          Y88bd8b/    888  |  Y88b |   8   \n");
printf("                   Y      Y888   /  Y88   |           Y88Y8Y     888  |   Y88b|   e   \n");
printf("                  /        `88_-~    \\8__/             Y  Y      888  |    Y888  (8)  \n");
                                                                
scanf("%d", &dummy);
}

void loseFunct (void)
{
     int dummy;
printf("                                        7I?77   7:+77   7:                                          \n");
printf("                                77:777777:::7777:::~777:::=77777+7                                  \n");
printf("                                77:::777:::::~?::::::7:::::777~:::                                  \n");
printf("                          7:77777::::::~::::::::::::::::::::?:::::77777=77                          \n");
printf("                          7::::77:::::::::::::::::::::::::::::::::=7=:::=7                          \n");
printf("                  777777  I:::::::::::::,:+7777777777777?~,::::::::::::::7777777                    \n");
printf("                  77+::?77~::::::::,~7 7?,..:=+++++++=~,..=777=,:::::::::777:::7                    \n");
printf("                   7+:::::::::::=77,.=+++~,.:++++++++=...:++++,.77I,:::::::::::7                    \n");
printf("             7 77777?:::::::,I7=.+++++..,+++..:++++++:..+++..=++++:.77,::::::::77777                \n");
printf("             7I::=I7?:::::,77.=++++++~..++++=..++++++........+++,.~++.77,::::::77+:::               \n");
printf("             77:::::::::,7+,++......++..=+++=.,++++++..=++~..+++...~.~+=,7~:::::::::I               \n");
printf("        7777777:::::::,7:=+,.++++,..=,:......++++++++~,.....,++....=++,.++.7=:::::::7 7777          \n");
printf("        77 7777+:::::I7.++...+++++..:::,.,,::.=~:::~=+++++++++,..+++.++++++:?7::::::777777          \n");
printf("        77::::::::::7.+++++...+++..::.=+++=..:.++++++++++=..+++=..::::+++++++.7+:::::::::+          \n");
printf("        7 ~:::::::7+~+.=++++.....+.:,~++++++.,:..,,,,,,...,=++.:::,..,:++++++++.7,:::::::7          \n");
printf("          7::::::7:++.++.++++,.++:,:,+++++..,:::::::::::~~~:...:,+???....,~+,.~+.7,:::::?7          \n");
printf("           =:::,7.+,.++.+++=+++.++.:,=+=.,::::::::::~~~~~~~~~~~..?????=:=.:+..+++,7~::::77          \n");
printf("     7:::::::::7.+:....+++.++.++++:::.,,::::::::::~~~~~~~~~~~~~~~,????::+++..=++++=7+::::::::=77    \n");
printf("     77:::::::7.+++++....,+=:++++++.,::::::::::::~~~~~~~~~~~~~~~~~.~?~:.+++..++++.+=7?:::::::       \n");
printf("     77~::::,7.++..+++=.:+:+++++++++.:::::::::::~~~~~~~~~~~~~~~~~~~.,:.+.++.=++....+,7::::::7       \n");
printf("  777 77::::7.+~...~+++++.+++++++++::::::::::::~~~~~~~~~~~~~~~~~~~~~..+++,++,....,+.+.7,:::777777   \n");
printf("  I::::::::+I+=.++.+++++.++++++++++:::::::::::~~~~~~~~~~~~~~~~~~~~~~~:++++~++.,+.+++:+.7::::::::+7  \n");
printf("  7::::::::7.+.++=.++++.++++++++++.:::::::::.~~~~~~~~~~~~~~~~~~~~~~~~.+++++.+++++.++.+=7::::::::77  \n");
printf("  77?:::::I=+..:+.++++:++++++++++=:::::::::,...~~~~~~~~~~~~~~~~~~~~~~~++++++.+++...+.:+.7::::::7    \n");
printf("  7777:::,7.+.......++~++++++++++.:::::::::,.....~~~~~~~~~~~~~~~~..~~~~++++++,+...,...++7::::+77    \n");
printf("7777~::::~7+++:....,+.+++++++++++,::::::::::....,~~~~~~~~~~~~~~....~~~,++++++,++.++..~++.7:::::77777\n");
printf("7::::::::7.++++++++++~++++++++++:::::::::::::::~~~~~~~~~~~~~~~.....~~~.+++++++:+++++++++,7,:::::::=7\n");
printf("77:::::::7.+++++++++,+++++++++++.::::::::::::::,:=+++++++?=~~~~~~~~~~~.+++++++.+++++++++=7:::::::7  \n");
printf("777I::::,7:+++++++++.+++++++++++.:::::::::::::.~+++++?...?+++~~~~~~~~~,+++++++~++++++++++?=::::~77  \n");
printf("  77?::::7=+++++++++.++++++++++~:::::::::::::,=++++++.....++++,~~~~~~~,++++++++=+++++++++:I::::77   \n");
printf("77::::::~7++++++++++:+++++++++,::::::::::::::.+++++++~...=++++?,~~~~~~,++++++++~+++++++++.7::::::777\n");
printf("::::::::~I++++++++++~++++++++::::::::::::::::.=+++++++~=++++++?:~~~~~~:++++++++:+++++++++.7::::::::7\n");
printf("77::::::~7++++++++++:+++++++:,,.,:::::::::::::,,....:.~+,=+++?.~~~~~~~~:+++++++~+++++++++.7::::::7  \n");
printf("7777+:::: =+++++++++.++++++==+.,::::::::::::::::::,,:~~~~,.~~~~~~~~~~~~~:++++++=+++++++++:I::::77777\n");
printf("  77::::,7:+++++++++.+++++++++.::::::::::::::::::::~.....~~~~~~~~~,~~,:=~:++++~++++++++++?=::::~77  \n");
printf("77~:::::,7.+++++++++:+++++++++,.,::.::,::::::::::~~~~~~~~~~~~~~.~~..~.++++++++.+++++++++=7:::::::777\n");
printf("7::::::::7.++++++++++:+++++++++....,:.,..,::::::~~~~~~~~~~~~~~~.~.,.,,++++++++:+++++++++,7,:::::::~7\n");
printf("  77:::::~7++++++++++.++++++++:,,::,.,:,,::::::~~~~~~~~~~~~~~~~,,,::,~+++++++.++++++++++,7:::::I77  \n");
printf("  7777:::,7.++++++++++~+++++++::::::::::::::::~~~~~~~~~~~~~~~~~::::~~~~,+++++:++++++++++7::::+7777  \n");
printf("   7I:::::I=++++++++++~++++++:::::::::::::::~~~~~~~~~~~~~~~~~~~:,:::~~~~~,++.++++++++++.7::::::777  \n");
printf("  7~:::::::7.++++++++++,++++:::::::::::::::~~~~~~~~~~~~~~~~~~~~,,::::~~~~~..++++++++++=7::::::::77  \n");
printf("  I::::::::+I+++++++++++.++,:::::::.::::::~~~~~~~~~~~~~~~~~~~~~,+,::::~~~~~+++++++++++.7::::::::+7  \n");
printf("     777::::7,+++++++:::+.+,::::::,,::::::~~~~~~~~~~~~~~~~~~~~~.++~,,,,:~~~=+++++++++.7,:::77       \n");
printf("     77=::::,7.+++~:+:+:++~,::::::.,::::::~~~~~~~~~~~~~~~~~~~~~,+++++.~~~~~:~+++~~++,7,:::::7       \n");
printf("     77::::::,7.++:~+:=+~:=+.:::::.,::::,,,,~~~~~~~~~~~~~~~~~~~~++++~~~~~~~++:~~:++=7+::::::~777    \n");
printf("     7::::::::,7.+++~+~::+=~+,,:::::,,,~~~~~~.~~~~~~~~~~~~~~~~:++++~~~~~~~=::++=++~7=::::::::=77    \n");
printf("     777 77=:::,7.+++:~++~++::+,,:::::::::::::.~~~~~~~~~~~~~~~.+++:~~~~~,+::+++++.7:::::77777777    \n");
printf("        777:::::,7.+++~:++:::++~+.::::::::::::,~~~~~~~~~~~~~~~:++.,~~~~.~++:++++.7::::::77          \n");
printf("        77=:::::::7I:+++:+~:=+:+++++.,:::::::.~~~~~~~~~~~~~~~..~++:~::++::+++++:7,:::::::7          \n");
printf("        77:::::::::,7.+++++:+:+++++::~+=..,.,~~~~~~~~~~~~,.,++::=:~=++:++++++.7=:::::::::+          \n");
printf("        7777777?:::::?7.++++~:++++:++:+::~+++++=~~~~=+++=:+:=:+::~+=:::++++,77::::::777777          \n");
printf("             77:::::::,7=:++++~++~=++:~++++~::+:+::++:++=+::+:=~++:=++++++.7::::::::7               \n");
printf("             77:::::::::,7I.++++++:::+:+~++:+==:~~++==~+:::+:+++:++++++~~7::::::::::I               \n");
printf("             77::~?7I::::::I7.~++++++:+++++~+~+:++~=:::+:+++~++++++++.77,::::::77=:::               \n");
printf("                  77I:::::::,?7+.+++++++++~:::+::~:=:++:==++++++++,:77,::::::::7                    \n");
printf("                  77?:::::::::::=77:.=++++++++++++++++++++++++,.77?,:::::::::::7                    \n");
printf("                  77+::+77=::::::::::777I:..:~=++++++=:,..+777=,:::::::::77I:::7                    \n");
printf("                  77777777I:::::::::::::,:+7777777777777?~,::::::::::::::7777777                    \n");
printf("                          7::::77:::::::::::::::::::::::::::::::::=7~:::+7                          \n");
printf("                          7:7   7::::::~::::::::::::::::::::+:::::   77=77                          \n");
printf("                          777   77:::777:::::~?::::::7:::::777:::~   77777                          \n");
printf("                                77:77   7:::7777:::~777:::=77777=7                                  \n");
printf("                                77777    I+777777:+777777:77777777                                  \n");
printf("                                        77       77      7                                          \n");
printf("YYYYYYY       YYYYYYY                                     lllllll                                                       \n");
printf("Y:::::Y       Y:::::Y                                     l:::::l                                                       \n");
printf("Y:::::Y       Y:::::Y                                     l:::::l                                                       \n");
printf("Y::::::Y     Y::::::Y                                     l:::::l                                                       \n");
printf("YYY:::::Y   Y:::::YYYooooooooooo   uuuuuu    uuuuuu        l::::l    ooooooooooo       ssssssssss       eeeeeeeeeeee    \n");
printf("   Y:::::Y Y:::::Y oo:::::::::::oo u::::u    u::::u        l::::l  oo:::::::::::oo   ss::::::::::s    ee::::::::::::ee  \n");
printf("    Y:::::Y:::::Y o:::::::::::::::ou::::u    u::::u        l::::l o:::::::::::::::oss:::::::::::::s  e::::::eeeee:::::ee\n");
printf("     Y:::::::::Y  o:::::ooooo:::::ou::::u    u::::u        l::::l o:::::ooooo:::::os::::::ssss:::::se::::::e     e:::::e\n");
printf("      Y:::::::Y   o::::o     o::::ou::::u    u::::u        l::::l o::::o     o::::o s:::::s  ssssss e:::::::eeeee::::::e\n");
printf("       Y:::::Y    o::::o     o::::ou::::u    u::::u        l::::l o::::o     o::::o   s::::::s      e:::::::::::::::::e \n");
printf("       Y:::::Y    o::::o     o::::ou::::u    u::::u        l::::l o::::o     o::::o      s::::::s   e::::::eeeeeeeeeee  \n");
printf("       Y:::::Y    o::::o     o::::ou:::::uuuu:::::u        l::::l o::::o     o::::ossssss   s:::::s e:::::::e           \n");
printf("       Y:::::Y    o:::::ooooo:::::ou:::::::::::::::uu     l::::::lo:::::ooooo:::::os:::::ssss::::::se::::::::e          \n");
printf("    YYYY:::::YYYY o:::::::::::::::o u:::::::::::::::u     l::::::lo:::::::::::::::os::::::::::::::s  e::::::::eeeeeeee  \n");
printf("    Y:::::::::::Y  oo:::::::::::oo   uu::::::::uu:::u     l::::::l oo:::::::::::oo  s:::::::::::ss    ee:::::::::::::e  \n");
printf("    YYYYYYYYYYYYY    ooooooooooo       uuuuuuuu  uuuu     llllllll   ooooooooooo     sssssssssss        eeeeeeeeeeeeee  \n");
scanf("%d",&dummy);
} 
