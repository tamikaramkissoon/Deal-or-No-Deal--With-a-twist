# Deal-or-No-Deal--With-a-twist

--- 

## Table of Contents
- [Overview](#overview)
- [Description](#description)
- [Lanaguages tools and technologies](#lanaguages-tools-and-technologies)
- [Project](#project)
- [Acknowledgement](#acknowledgement)
- [Author Info](#author-info)

---

## Overview
The deal or no deal with a twist program uses the C++ language to create a program to play a modified version of the popular game “Deal or No Deal”. The twist to the game involves the user playing a separate game at the end of round one to modify the outcome of the game.

--- 

## Description
* The program starts by requesting the player to choose the number of cases for the game (16, 18, 20, 22, 24, or 26).

* Based on the number of cases chosen, the appropriate text file is opened and the data is read and stored in an array.

* The player is requested to choose a case to start the game. The case chosen is then removed from play and set aside without revealing its contents.

* In each round of the game, the player is requested to pick a certain number of unopened cases, one by one. At the start of the round and before the player is asked to
choose a case, the unopened cases are displayed.

* As each case is opened, the monetary value is shown and the monetary value for that case is removed from the money board.

* At the end of each round, except the last, the banker makes an offer to the player. The offer is calculated as follows:
  * The average of the monetary amount in the unopened cases.
  * Multiply the result above by (number of the current round / total number of rounds).

* The player can accept the offer and terminate the game (“Deal”). If the player does not accept the offer (“No Deal”), the next round is entered. This continues until there are no more rounds.

* The twist implemented has the following characteristics:
  * The user is asked to solve six arithmetic problems at the end of round one of the game.
  * The figures are randomly generated between one and two hundred.
  * Feedback is given based on the answer entered by the user and the number of correct answers is counted.
  * Based on the number of correct answers the banker generates a random number between a certain range:
  * If the user gets less than three correct answers, the banker offers an amount of $0.00, and the game continues.
  * If the user gets three or more correct answers the random offer is generated and then displayed to the user allowing him/her to choose ‘DEAL or “NO DEAL”
  * If the user accepts the offer the game ends else if the user refuses the offer the game continues to round two.

---

## Lanaguages tools and technologies
* C++
* Data structures

---

## Project
![Screenshot (633)](https://user-images.githubusercontent.com/77646306/124199031-06e18e80-daa0-11eb-9ef3-bd013e75e55b.png)


---

## Acknowledgement
* COMP1602 - Assignment

---

## Author Info
* [Linkedin](https://www.linkedin.com/in/tamika-ramkissoon-1a2622214/)
