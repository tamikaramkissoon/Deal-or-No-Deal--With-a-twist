#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>
#include <iomanip>

using namespace std;

//list of structs used
struct CaseInfo {
  int Rounds;
  int NumCases;
};

struct Game {
  int caseUpdate;
  int Personalcase;
  int caseChoice;
  int displayCaseNum;
  bool GameEnd;
  int Casesleft;
  int moneyLeft;
};

//function prototypes
string CasesInGame();
string CreateFilename(string CasePerGame);
void toCString(string s, char c[]);
int toInteger(char str[]);
CaseInfo ReadFile(string Filename, string CasePerGame, int cases[], int rounds[]);
void DisplayCases(int cases[], CaseInfo info, Game Cases[]);
Game LuckyCase(int cases[], CaseInfo info, int rounds[]);
void shuffleCases(int cases[], CaseInfo info);
void RemovefromPlay(Game Cases[], CaseInfo info, Game gameInfo, int cases[]);
void DisplayUpdatedCases(CaseInfo info, int displaycases[], int selectedcases[]);
bool ValidChoice(Game gameInfo, Game Cases[], CaseInfo info, Game ChosenCases[]);
int solve();
int twist1();
int twist1banker(int numC);
int banker(Game Cases[], CaseInfo info, int cases[], Game gameInfo, int currentRound, int openCases[]);
void bubbleSort(int moneyboard[], CaseInfo info);
void DisplayMoneyBoard(int moneyboard[], CaseInfo info);
void DisplayUpdatedMoneyBoard(int moneyboard[], CaseInfo info, Game Cases[], int openCases[]);
bool search(CaseInfo info, int search[], int key);

//function to give the user the choice of playing the game with a certain amount of unopened cases
string CasesInGame() {

  string cases = "";

  cout << "\n\n		WELCOME TO DEAL OR NO DEAL - WITH A TWIST!" << endl;
  cout << "	There are 16, 18, 20, 22, 24 and 26 unopened case" << endl;
  cout << "	Please enter the amount of unopened cases you wish to enter the game with: ";
  cin >> cases;
  return cases;
}

//function to create filename
string CreateFilename(string CasePerGame) {
  string Filename = "";
  string data = "Data";
  string text = ".txt";

  Filename = data + CasePerGame + text;

  return Filename;
}

// funtion to conver a string to a cstring
void toCString(string s, char c[]) {

  int length = s.length();

  for (int i = 0; i < length; i = i + 1)
    c[i] = s[i];

  c[length] = '\0';
}
// function to convert a cstring to an int
int toInteger(char str[]) {
  int i, sum, length, power10, digit;

  length = strlen(str);
  sum = 0;
  power10 = 1;

  for (i = length - 1; i >= 0; i = i - 1) {
    digit = str[i] - '0';
    sum = sum + (digit * power10);
    power10 = power10 * 10;
  }
  return sum;
}

// function to read data from file based on the filename created
CaseInfo ReadFile(string Filename, string CasePerGame, int cases[], int rounds[]) {
  char c[25];

  CaseInfo info;
  for (int i = 0; i < 25; i = i + 1) {
    c[i] = ' ';
  }

  toCString(Filename, c);
  ifstream in ; in .open(c);

  // if statement to check whether the input file was successfully opened.
  if (! in .is_open()) {
    cout << "There was an error opening the data file!  Operation aborting!!..." << endl;
    exit(1);
  } else
    cout << "Reading " << CasePerGame << " cases from file " << Filename << endl;

  // converting string to int
  toCString(CasePerGame, c);
  int Cases = toInteger(c);
  info.NumCases = Cases;

  for (int i = 0; i < info.NumCases; i = i + 1) {
    in >> cases[i];
    
  }

  in >> info.Rounds;
 

  for (int i = 0; i < info.Rounds; i = i + 1) {
    in >> rounds[i];
    
  }

  in .close();

  return info;
}
//function to display the cases on the console
void DisplayCases(int cases[], CaseInfo info, Game Cases[]) {

  for (int i = 0; i < info.NumCases; i = i + 1) {
    cout << "		" << Cases[i].displayCaseNum;
    if (i % 5 == 4) {
      cout << endl;
    }
  }
}

void DisplayMoneyBoard(int moneyboard[], CaseInfo info) {
  for (int i = 0; i < info.NumCases / 2; i = i + 1) {
    cout << "		" << moneyboard[i] << "		" << moneyboard[info.NumCases / 2 + i] << endl;
  }
}
// function to sort the money board
void bubbleSort(int moneyboard[], CaseInfo info) {
  bool swapped = true;
  int j = 0;
  int temp = 0;

  while (swapped) {
    swapped = false;
    j = j + 1;
    for (int i = 0; i < info.NumCases - 1; i = i + 1) {
      if (moneyboard[i] > moneyboard[i + 1]) {
        temp = moneyboard[i];
        moneyboard[i] = moneyboard[i + 1];
        moneyboard[i + 1] = temp;
        swapped = true;
      }
    }
  }

}
// function to search for casesa and money
bool search(CaseInfo info, int search[], int key) {
  for (int i = 0; i < info.NumCases; i = i + 1) {
    if (search[i] == key)
      return true;
  }
  return false;
}


void DisplayUpdatedCases(CaseInfo info, int displaycases[], int selectedcases[]) {
bubbleSort(selectedcases, info);
bubbleSort(displaycases, info);
  bool found = false;

 for (int i = 0; i < info.NumCases; i = i + 1) { 

	found = search(info, selectedcases, displaycases[i]);

    cout << "		";
    if (found == true)
      cout << "  ";
    else
      cout << displaycases[i];

    if (i % 5 == 4) {
      cout << endl;
    }
  }

}

// funtion to display the uplated money board
void DisplayUpdatedMoneyBoard(int moneyboard[], CaseInfo info, Game Cases[], int openCases[]) {
 
  bool found1 = false;
  bool found2 = false;
  
  for (int i = 0; i < info.NumCases / 2; i = i + 1) { 
   
    found1 = search(info, openCases, moneyboard[i]);

    found2 = search(info, openCases, moneyboard[info.NumCases / 2 + i]);
    cout << "		";
    if (found1 == true && found2 == true) {
      cout << "  " << "	" << "  " << endl;
    }
    if (found1 == true && found2 == false) {
      cout << "  " << "	" << moneyboard[info.NumCases / 2 + i] << endl;
    }
    if (found1 == false && found2 == true) {
      cout << moneyboard[i] << "	" << "  " << endl;
    }
    if (found1 == false && found2 == false) {
      cout << moneyboard[i] << "	" << moneyboard[info.NumCases / 2 + i] << endl;
    }

  } 
}

// function to shuffles cases before game starts
void shuffleCases(int cases[], CaseInfo info) {

  int temp = 0;
  int randomIndex = 0;
  srand(time(NULL));
  for (int i = 0; i < info.NumCases; i = i + 1) {
    randomIndex = rand() % info.NumCases;
    temp = cases[i];
    cases[i] = cases[randomIndex];
    cases[randomIndex] = temp;

  }
}

// function to remove a case from the play after it is selected during the game rounds
void RemovefromPlay(Game Cases[], CaseInfo info, Game gameInfo, int cases[]) {
  int i = 0;
  for (i = 0; i < info.NumCases; i = i + 1) {
    if (Cases[i].displayCaseNum == gameInfo.caseChoice)
      break;

  }
  if (i < info.NumCases) {
    info.NumCases = info.NumCases - 1;
    for (int j = i; j < info.NumCases; j = j + 1) {
      Cases[j].displayCaseNum = Cases[j + 1].displayCaseNum;
    }
  }

  for (int i = 0; i < info.NumCases; i = i + 1) {
    if (Cases[i].displayCaseNum == gameInfo.caseChoice) {  
      Cases[i].Casesleft = -1;
      Cases[i].moneyLeft = 0;
    } else {
      Cases[i].Casesleft = Cases[i].displayCaseNum;
      Cases[i].moneyLeft = cases[Cases[i].Casesleft - 1];
    }
    
  }
  
}

// function for choice validation
bool ValidChoice(Game gameInfo, Game Cases[], CaseInfo info, Game ChosenCases[]) {

  if (gameInfo.caseChoice > info.NumCases)
    return false;
  else if (gameInfo.caseChoice < 1)
    return false;
  else if (gameInfo.caseChoice == gameInfo.Personalcase)
    return false;
  else
    for (int i = 0; i < gameInfo.caseUpdate; i = i + 1) {
      if (gameInfo.caseChoice == ChosenCases[i].caseUpdate)
        return false;
    }
  return true;
}

//Function to request the user to choose a case to start the game nad play the game
Game LuckyCase(int cases[], CaseInfo info, int rounds[]) {
  Game gameInfo;
  Game Cases[27];
  Game ChosenCases[27];
  bool check = false;
  int Twist1Offer = 0;
  int dealOrNoDeal = 0;
  int displaycases[27]; 
  int openCases[27]; 
  int selectedcases[27];
  int i = 0, z = 0;
  int caseNum = 0;
  int chosenCases[27];
  int temp[27];
  int moneyboard[27];
  for (int i = 0; i < info.NumCases; i = i + 1) {
    Cases[i].displayCaseNum = 0;
  }
  for (int i = 0; i < 27; i = i + 1) {
    ChosenCases[i].caseUpdate = 0;
    displaycases[i] = 0;
    moneyboard[i] = 0;
    openCases[i] = 0;
    selectedcases[i] = 0;
  }
  for (int i = 0; i < info.NumCases; i = i + 1) {
    Cases[i].displayCaseNum = i + 1;
    displaycases[i] = i + 1;
    moneyboard[i] = cases[i];
  }

  bubbleSort(moneyboard, info);

  int x = 0, j = 0;

  gameInfo.Personalcase = 0;
  cout << endl;
  cout << "\n 		The money Board At The Start Of The Game" << endl;
  DisplayMoneyBoard(moneyboard, info);
  cout << "\n		The Amount Of Cases At The Start Of The Game" << endl;
  DisplayCases(cases, info, Cases);

  cout << "\n\n		Please Select Your Personal Case To start The Game: ";
  cin >> gameInfo.Personalcase;
  if (gameInfo.Personalcase > info.NumCases) {
    cout << "		Invalid Case, Please select another case: ";
    cin >> gameInfo.Personalcase;
    while (gameInfo.Personalcase > info.NumCases || gameInfo.Personalcase < 1) {
      cout << "		Invalid Case, Please select another case: ";
      cin >> gameInfo.Personalcase;
      if (gameInfo.Personalcase <= info.NumCases && gameInfo.Personalcase >= 1)
        break;
    }
  }
  if (gameInfo.Personalcase < 1) {
    cout << "		Invalid Case, Please select another case: ";
    cin >> gameInfo.Personalcase;
    while (gameInfo.Personalcase > info.NumCases || gameInfo.Personalcase < 1) {
      cout << "		Invalid Case, Please select another case: ";
      cin >> gameInfo.Personalcase;
      if (gameInfo.Personalcase <= info.NumCases && gameInfo.Personalcase >= 1)
        break;
    }
  }

  gameInfo.caseUpdate = 0;
  gameInfo.caseUpdate = gameInfo.caseUpdate + 1;
  selectedcases[0] = gameInfo.Personalcase;
  
  
  for (int i = 0; i < info.Rounds; i = i + 1) {
    

    if (i == 1) { 

      dealOrNoDeal = twist1(); 
      if (dealOrNoDeal == 1) {
        gameInfo.GameEnd = true;
        break;
      } else
        gameInfo.GameEnd = false;
    }
    if (gameInfo.GameEnd == false) {

      cout << "\n\n		We are in round " << i + 1 << endl;
      cout << "		You must choose " << rounds[i] << " cases in this round." << endl;
      cout << "		Cases Choices Left:" << endl;
      RemovefromPlay(Cases, info, gameInfo, cases);
      DisplayUpdatedCases(info, displaycases, selectedcases);
      cout << "\n		Updated Money Board" << endl;
      DisplayUpdatedMoneyBoard(moneyboard, info, Cases, openCases);

      for (j = 0; j < rounds[i]; j = j + 1) {
        cout << "\n\n		Please choose a case: ";
        cin >> gameInfo.caseChoice;
        check = ValidChoice(gameInfo, Cases, info, ChosenCases);
        if (check == false) {
          while (check == false) {
            cout << "		Invalid choice please select an unopen case: ";
            cin >> gameInfo.caseChoice;
            check = ValidChoice(gameInfo, Cases, info, ChosenCases);
            if (check == true)
              break;
          }
        }

        if (check = true) {
          selectedcases[i + j + 1] = gameInfo.caseChoice;
          ChosenCases[x].caseUpdate = gameInfo.caseChoice;
          x = x + 1;
         
          gameInfo.caseUpdate = gameInfo.caseUpdate + 1;

          cout << "\n		The value of case " << gameInfo.caseChoice << " is $" << cases[gameInfo.caseChoice - 1] << ".00" << endl;

          openCases[z] = cases[gameInfo.caseChoice - 1];
          z = z + 1;
          int count = i + 1;
          RemovefromPlay(Cases, info, gameInfo, cases);
          if (i < info.Rounds - 1) {
            cout << "		The Unopened cases contain the following values: " << endl;
            DisplayUpdatedCases(info, displaycases, selectedcases);
            cout << "\n		Updated Money Board" << endl;
            DisplayUpdatedMoneyBoard(moneyboard, info, Cases, openCases);
          }

        }

      }

    }
   
    if (i < info.Rounds - 1) {
      cout << "\n\n";
      system("pause");
      system("cls");
      cout << "		The Unopened cases contain the following values: " << endl;
      DisplayUpdatedCases(info, displaycases, selectedcases);
      cout << "\n		Updated Money Board" << endl;
      DisplayUpdatedMoneyBoard(moneyboard, info, Cases, openCases);
      float offer = 0.0;
      int currentRound = i + 1;
      offer = banker(Cases, info, cases, gameInfo, currentRound, openCases); 

      if (offer == 1) {
        gameInfo.GameEnd = true;
        break;
      } else
        gameInfo.GameEnd = false;
    }

  }
  
  gameInfo.GameEnd = true;
  
  return gameInfo;
}
// function to implement the first twist where the player solves a few randomly generated arithmetic problems
int solve() {
  int num1 = 0, num2 = 0, prod = 0, answer = 0, numC = 0;
  char ch = '*';

  srand(time(NULL));

  for (int i = 0; i < 6; i = i + 1) {

    num1 = 1 + rand() % 200;
    num2 = 1 + rand() % 200;

    prod = num1 * num2;

    cout << "		Solve: " << num1 << " " << ch << " " << num2 << " = ";
    cin >> answer;

    if (answer == prod) {
      cout << "		Correct!\n" << endl;
      numC = numC + 1;
    } else {
      cout << "		Sorry, the answer is " << prod << endl << endl;
    }
  }

  return numC;
}

//function to implement and call the first twist functions
int twist1() {
  int numCorrect = 0, offer = 0, dealOrNOdeal = 0;
  cout << "\n\n";
  system("pause");
  system("cls");
  cout << "		IT TIME FOR THE BONUS ROUND\n		**LETS TWIST**" << endl;
  cout << "		Instructions:\n		You must answer 6 arithmetic questions\n";
  cout << "		The Banker would then present you an offer\n";
  cout << "		You can select NO DEAL and continue the game / DEAL and end the game " << endl;
  cout << "\n\n";
  system("pause");
  system("cls");
  numCorrect = solve();

  offer = twist1banker(numCorrect);

  if (offer != 0) {
    cout << "		Bankers Offer: $" << offer << ".00" << endl;
    cout << "		DEAL(1) or NO DEAL(2) ";
    cin >> dealOrNOdeal;
  } else {
    cout << "		Bankers Offer: $" << offer << ".00" << endl;
    cout << "		Better luck next time!!";
    cout << "\n\n";
    system("pause");
    system("cls");
    return 2;
  }

  if (dealOrNOdeal == 1) {
    system("cls");
    cout << "		CONGRATULATIONS!!! \n";
    cout << "		You walk away with $" << offer << ".00" << endl;
    
    cout << "\n\n";
    system("pause");
    system("cls");
    return dealOrNOdeal;
  }
  cout << "\n\n";
  system("pause");
  system("cls");
  return dealOrNOdeal;
}

// function to generate the banker offer based on the maount of correct answers in solve()
int twist1banker(int numC) {

  srand(time(0));

  int amount = 0;
  if (numC == 6) {
    amount = 200000 + rand() % (600000 - 200000 + 1);
    return amount;
  } else if (numC == 5) {
    amount = 200000 + rand() % (500000 - 200000 + 1);
    return amount;
  } else if (numC == 4) {
    amount = 200000 + rand() % (400000 - 200000 + 1);
    return amount;
  } else if (numC == 3) {
    amount = 200000 + rand() % (250000 - 200000 + 1);
    return amount;
  }

  return 0;
}
//function to create banker/offer
int banker(Game Cases[], CaseInfo info, int cases[], Game gameInfo, int currentRound, int openCases[]) {
  float offer = 0.0;
  float sum = 0.0, average = 0.0, mul = 0.0;
  int dealOrNOdeal = 0;
  int x = 0; 
  bool found = false;
  

  for (int i = 0; i < info.NumCases; i = i + 1) { 
    found = search(info, cases, openCases[i]);

    if (found == false) {
      sum = sum + cases[i];
      //cout << cases[i] << " addedd to sum"<< endl;
      x = x + 1;
    }
    // cout << cases[i] << " cases" << endl;
    // cout << openCases[i] <<" open cases" << endl;
    
  }
  
  average = sum / x * 1.0;
//  cout << average << "average" << x<< "x" <<endl;
  mul = currentRound * 1.0 / info.Rounds;
 // cout << currentRound << " current round" << endl;
 //  cout << info.Rounds << " total rounds" << endl;
  // cout << mul << " mul" <<endl;
  offer = average * mul * 1.0;
  cout << "\n\n		The Banker is Making an Deal!!" << endl;
  cout << "		Enter 1 to accept the Deal and 2 to decline" << endl;
  cout << "		The banker offers you a sum of $" << fixed << setprecision(2) << offer << endl;
  if (offer != 0) {
    
    cout << "		DEAL(1) or NO DEAL(2) ";
    cin >> dealOrNOdeal;
  }
  

  if (dealOrNOdeal == 1) {
    system("cls");
    cout << "		CONGRATULATIONS!!! \n";
    cout << "		You walk away with $" << offer << endl;

    return dealOrNOdeal;
  }

  return dealOrNOdeal;
}

int main() {
  string CasePerGame = "";
  string Filename = "";
  int cases[27]; 
  int rounds[27]; 
  for (int i = 0; i < 26; i = i + 1) {
    cases[i] = 0;
    rounds[i] = 0;
  }

  CasePerGame = CasesInGame();
  cout << "\n\n";
  system("pause");
  system("cls");

  Filename = CreateFilename(CasePerGame);
  
  CaseInfo info = ReadFile(Filename, CasePerGame, cases, rounds);
  
  shuffleCases(cases, info);
  
  cout << "\n\n		The Game is about to start with " << info.NumCases << " unopened cases " << endl;

  Game gameInfo = LuckyCase(cases, info, rounds);
  if (gameInfo.GameEnd == true) {

    cout << "		END OF GAME" << endl;
    
    cout << "\n\n		Your Personal Case chosen at the start of the game contains: $" << cases[gameInfo.Personalcase - 1] << ".00" << endl;

    cout << "\n\n		END OF ASSIGNMENT 4" << endl;
  }
  	
  return 0;
}
