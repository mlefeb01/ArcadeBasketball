#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// the pin each baskets switch is connected too
const int leftBasketSwitch = 7;
const int rightBasketSwitch = 6;

// left basket and right baskets score, starts at 0
int leftBasket = 0;
int rightBasket = 0;

// if a player reaches whatever value scoreLimit is, the game will end and they win
int scoreLimit = 100;
// how much time the game should last, in seconds
int timeLeft = 120;
// 
String winner;

/*
 * Counts down
 * 3
 * (waits 1 second)
 * 2
 * (waits 1 second)
 * 1
 * (waits 1 second)
 * Start!
 * (waits 1/2 second then clears the display)
 */
void countdown() {
  // print "3", wait a second, clear the display
  lcd.setCursor(10, 1);
  lcd.print(3);
  delay(1000);
  lcd.clear();

  // print "2", wait a second, clear the display
  lcd.setCursor(10, 1);
  lcd.print(2);
  delay(1000);
  lcd.clear();

  // print "1", wait a second, clear the display
  lcd.setCursor(10, 1);
  lcd.print(1);
  delay(1000);
  lcd.clear();

  // print "Start!", wait 1/2 a second, clear the display
  lcd.setCursor(7, 1);
  lcd.print("Start!");
  delay(500);
  lcd.clear();
}

/*
 * Updates the display to the following
 * -------------------------------------------
 *            Time: {timeLeft}
 *   Left: {leftBasket}  Right: {rightBasket}
 * -------------------------------------------
 */
void updateDisplay() {
  // clear the display
  lcd.clear();

  // print the time
  lcd.setCursor(6, 0);
  lcd.print("Time: ");
  lcd.setCursor(12, 0);
  lcd.print(timeLeft);

  // print the left baskets score
  lcd.setCursor(0, 2);
  lcd.print("Left:");
  lcd.setCursor(6, 2);
  lcd.print(leftBasket);

  // print the right baskets score
  lcd.setCursor(10, 2);
  lcd.print("Right: ");
  lcd.setCursor(17, 2);
  lcd.print(rightBasket);
}

/*
 * Initializes the winner variable so it can be used to update the display
 */
void getWinner() {
  winner = (leftBasket == rightBasket) ? "Winner: Tie" : 
  ( (leftBasket > rightBasket) ? "Winner: Left" : "Winner: Right" ); 
}

/*
 * Checks if the game is over by one of the players being over the scoreLimit
 */
boolean winnerFound() {
  return (leftBasket >= scoreLimit || rightBasket >= scoreLimit);
}

/*
 * 
 */
void startGame() {
  // Create a seperate variable to hold the total time
  int tempTime = timeLeft;
  
  // run the game loop 
  for (int n = 0; n < tempTime; n++){
    for (int m = 0; m < 10; m++) {
      int leftBasketState = digitalRead(leftBasketSwitch);
      int rightBasketState = digitalRead(rightBasketSwitch);
      
      // if the left switch is triggered, add a point to the left basket
      if (leftBasketState == HIGH) {
        delay(1);
        leftBasket++;
      } 

      // if the right switch is triggered, add a point to the left basket
      if (rightBasketState == HIGH) {
        delay(1);
        rightBasket++;  
      }

      // check if a winnner is found 
      if (winnerFound()) {
        gameover();
        break;
      } else {
        updateDisplay();  
      }
      
      delay(100);  
  }
  timeLeft--;
  }  

  gameover();
  
}

void gameover() {
  // Get the winner, print "GAMEOVER!" and the winner of that round
  getWinner();
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("GAMEOVER!");
  lcd.setCursor(4, 1);
  lcd.print(winner);

  // print the left baskets score
  lcd.setCursor(0, 3);
  lcd.print("Left:");
  lcd.setCursor(6, 3);
  lcd.print(leftBasket);

  // print the right baskets score
  lcd.setCursor(10, 3);
  lcd.print("Right: ");
  lcd.setCursor(17, 3);
  lcd.print(rightBasket);
}

void setup() {
  // setup the LCD's number of columns and rows:
  lcd.begin(20, 4);

  // setup the micro switches
  pinMode(leftBasketSwitch, INPUT);
  pinMode(rightBasketSwitch, INPUT);

  // run the countdown method
  countdown();

  // start the game
  startGame();

}

void loop() {
}
