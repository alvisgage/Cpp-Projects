                                                                     
                                                                     
                                                                     
                                             
//---------------------------------------------------------------------------
// Program:  hw5.cpp 
// Purpose:  This is an implementation of a dice game. When the game starts, 
//           the player has 1000 points.
//           The player starts by wagering a number of points.
//           Then the player rolls a pair of dice. 
//           If the total of the face values of the dice add up to more than
//           seven or the face values are equal, then the player wins. 
//           Otherwise the player loses. 
//           A winning roll will add the wager to the total points.
//           A losing roll causes the player to lose the wager. 
//---------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std; 

//---------------------------------------------------------------------------
// Name: RollDice    
// Parameters:                 
// Returns:
// Purpose:     
//---------------------------------------------------------------------------

int RollDice(int &Die1, int &Die2)               
{

   Die1 = rand()%6+1;
   Die2 = rand()%6+1;

}


//---------------------------------------------------------------------------
// Name:  CheckWinner
// Parameters:
// Returns:
// Purpose:
//---------------------------------------------------------------------------

int CheckWinner(int Die1, int Die2)
{

   int Sum = 0;
   bool Winner;
   Sum = Die1 + Die2;
   if(Die1 == Die2 || Sum > 7)
   {              

      cout << "###################################\n"
           << "#     You rolled a " << Die1 << " and a " << Die2 << ".     #\n"
           << "#    Congratulations, You Win!    #\n";
      return(Winner = 'T');
   }                 
   else                        
   {       
      cout << "###################################\n"
           << "#     You rolled a " << Die1 << " and a " << Die2 << ".     #\n"
           << "#             You Lose!           #\n";
   }
    
      return(Winner == 'F');

}


//---------------------------------------------------------------------------
// Name: PrintDice   
// Parameters: none
// Returns: void
// Purpose: Output dice pattern
//---------------------------------------------------------------------------
void PrintDice()
{
    cout << "       .-------.    ______      \n"
         << "       /   o   /|   /\\     \\   \n"
         << "      /_______/o|  /o \\  o  \\  \n"
         << "      | o     | | /   o\\_____\\ \n"
         << "      |   o   |o/ \\o   /o    /  \n"
         << "      |     o |/   \\ o/  o  /   \n"
         << "      '-------'     \\/____o/    \n\n\n";
}

//---------------------------------------------------------------------------
// Name: ShowHomeScreen
// Parameters:
// Returns:
// Purpose:                
//---------------------------------------------------------------------------

void ShowHomeScreen(int TotalPoints)
{

    cout << "\n\n             DICE GAME!           \n\n ";
         PrintDice();  
       
   cout << "###########Instructions###########\n"
        << "Roll the dice. If the face values\n" 
        << "are equal or add up to more than 7,\n"
        << "you win!\n\n"
     
        << "############Total Points###########\n"
        << "Total Points: " << TotalPoints << "\n\n";

}



//---------------------------------------------------------------------------
// Name: GetWager
// Parameters:
// Returns:
// Purpose:
//---------------------------------------------------------------------------

int GetWager(int Wager)
{

   cout << "How many points would you like to wager?\n";
   cin >> Wager;
   cout << "\n\n";

   return(Wager);

}


//---------------------------------------------------------------------------
// Name: ConfirmContinue
// Parameters:
// Returns:
// Purpose:
//---------------------------------------------------------------------------

bool ConfirmContinue(int TotalPoints)
{
   char answer;
   if(TotalPoints == 0)
   {
      cout << "You do not have enough points to continue.";
      return(false);
   }
   else
   {   
      cout << "Would you like to roll again?(Y/N)?\n";
      cin >> answer;
      if(answer == 'Y' || answer == 'y')
      {    
         return(true);
         while(answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n')
               cout << "Invalid entry. Please type Y for Yes or N for No.\n";
      }
      else   
         return(false);
   }            

}

//---------------------------------------------------------------------------
// Function calls in main have been commented out so that this code will 
// compile. It is you task to write these functions. Once a function
// has been written, you can uncomment its function call to see if the 
// function works. Do not change the function calls.
//---------------------------------------------------------------------------
int main ()   
{          
        // Declare Variables
        int TotalPoints = 1000;
        int Wager = 0;
        int Die1 = 0;                
        int Die2 = 0;
        bool Confirm;
        bool Winner;   

        // Seed the random number generator                
        srand(time(0));

        // Show home screen
        ShowHomeScreen(TotalPoints);
        
        // Each loop is one roll of the dice
        do {
                Wager = GetWager(TotalPoints); // Get the amount of points wagered on this roll
                while(Wager>TotalPoints){
                    cout<<"You only have "<<TotalPoints<<" points. Please enter a wager amount.\n\n";
                    Wager=GetWager(TotalPoints);
                }                    
                RollDice(Die1, Die2); // Roll the dice
                
                Winner = CheckWinner(Die1, Die2); // Determine if the roll was a winning roll
                
                if (Winner)
                        TotalPoints += Wager; // If the roll was a winning roll, add the wager to the total points
                else
                        TotalPoints -= Wager; // If the roll was not a winner, deduct the wager from the total points
                
                ShowHomeScreen(TotalPoints); // Show home screen
        
        // Make sure the player has sufficient points to continue        
        // and ask if the player wants to roll again                           
           Confirm = ConfirmContinue(TotalPoints); 
                      
        } while(Confirm);            

        return 0;    
}
