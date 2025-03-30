# Watopoly
Watopoly is a video game project for CS246, which is a variant of the classic board game Monopoly. However, instead of the traditional locations, Watopoly's game board is based on the University of Waterloo campus.

---

## Table of Contents

- [1. Overview](#1-overview)
  - [1.1 Introduction to Watopoly](#11-introduction-to-watopoly)
  - [1.2 Game Objectives](#12-game-objectives)
  - [1.3 Core Mechanics](#13-core-mechanics)
    - [1.3.1 Board and Movement](#131-board-and-movement)
    - [1.3.2 Properties and Ownership](#132-properties-and-ownership)
    - [1.3.3 Financial Transactions](#133-financial-transactions)
    - [1.3.4 Special Squares](#134-special-squares)
    - [1.3.5 Player Interactions](#135-player-interactions)
    - [1.3.6 Game Progression](#136-game-progression)
    - [1.3.7 Additional Mechanics](#137-additional-mechanics)
- [2. Design](#2-design)
  - [2.1 Class Diagram](#21-class-diagram)
  - [2.2 Design Patterns Utilized](#22-design-patterns-utilized)
- [3. Board Layout](#3-board-layout)
- [4. Game Logic](#4-game-logic)
- [5. Command Interpreter](#5-command-interpreter)
- [6. Player Management](#6-player-management)
- [7. Auctions](#7-auctions)
- [8. Saving and Loading](#8-saving-and-loading)
- [9. User Interface](#9-user-interface)
- [10. Team Members](#10-team-members)
- [11. Appendix](#11-appendix)
  - [11.1 Code Snippets](#111-code-snippets)


---

## 1. Overview

### 1.1 Introduction to Watopoly
In Watopoly, players take turns moving around the board, buying and improving on-campus buildings (which function as properties), and paying tuition (rent) to other players. The game features 40 squares, representing various locations on the University of Waterloo campus. The goal of the game is to be the last player remaining who has not gone bankrupt.

### 1.2 Game Objectives
The objective of the game Watopoly is to be the last player remaining who has not dropped out of university (declared bankruptcy). Players take turns moving around a 40-square board, buying and improving on-campus buildings (properties), and paying tuition (rent) to other players. The game continues until only one player remains solvent, and that player is declared the winner.

### 1.3 Core Mechanics
#### 1.3.1 Board and Movement
• The game is played on a 40-square board representing the University of Waterloo campus.

• Players roll two dice to move around the board.

• Landing on different squares triggers specific actions.

#### 1.3.2 Properties and Ownership
• Players can purchase unowned properties (academic buildings, gyms, and residences) they land on.

• Academic buildings are grouped into monopolies.

• Owning all properties in a monopoly allows for improvements (bathrooms and cafeterias).

#### 1.3.3 Financial Transactions
• Players pay tuition (rent) when landing on owned properties.

• Collect OSAP (similar to "Passing Go") awards $200 to players.

• Players can mortgage properties to raise funds.

#### 1.3.4 Special Squares
• DC Tims Line (similar to "Jail").

• SLC and Needles Hall squares trigger random events.

• Goose Nesting, Tuition, and Coop Fee squares have specific effects.

#### 1.3.5 Player Interactions
• Players can trade properties and money with each other.

• Auctions occur when players choose not to buy properties or go bankrupt.

#### 1.3.6 Game Progression
• Players take turns moving, buying properties, and paying fees.

• The game continues until all but one player have declared bankruptcy.

#### 1.3.7 Additional Mechanics
• Improvements increase property value and rent.

• Roll Up the Rim cups can be collected to get out of DC Tims Line.

• Players can mortgage and unmortgage properties.

• Bankruptcy occurs when a player owes more than they can pay.

---
## 2. Design

### 2.1 Class Diagram

```mermaid
classDiagram
    class Subject {
        <<abstract>>
        - vector<Observer*> observers
        + attach(Observer* observer)
        + detach(Observer* observer)
        + notifyObserver()
        + virtual ~Subject() = 0
    }

    class Game {
        - board: unique_ptr<Board>
        - numPlayers: Integer
        - testingMode: Boolean
        + roll()
        + next()
        + trade(string player, string give, string receive)
        + improve(string property, string action)
        + mortgage(string property)
        + unmortgage(string property)
        + bankrupt()
        + assets()
        + all()
        + save(string filename)
        + setNumPlayers(int numPlayers)
        + setNumRollsInTimsLine(int numRollsInTimsLine)
        + setPlayerTimCups(int pos, int TimCups)
        + setPlayerMoney(int pos, int money)
        + setPlayerPosition(int pos, int position)
        + setPlayerCharacter(int pos, char character)
        + setupBoard()
        + setBuildingOwner(string buildingName, string owner)
        + setBuildingImprovements(string buildingName, int numImprovements)
        + setTestingMode()
        + end()
        + getState()
    }

    class Observer {
        <<abstract>>
        + virtual notify() = 0
    }

    class TextDisplay {
       - game: unique_ptr<Game>
       + notify()
       + display()
    }

    class GraphicalDisplay {
       - Display: display
       - Game* game
       - width: Integer
       - height: Integer
       - window: Window
       - gc: GC
       + notify()
       + getWidth(): Integer
       + getHeight(): Integer
       + drawBoard()
       + drawPlayers()
       + drawImprovements()
    }

    class Board {
       - squares: vector<shared_ptr<Square>>
       - players: vector<unique_ptr<Player>>
       - currentPlayerIndex: Integer
       + addSquare(square: shared_ptr<Square>)
       + addPlayer(player: unique_ptr<Player>)
       + removePlayer(player: unique_ptr<Player>)
       + getSquare(int index): shared_ptr<Square>
       + getPlayer(int index): unique_ptr<Player>
       + getCurrentPlayer(): unique_ptr<Player>
       + nextPlayer()
    }

    class Player {
       - name: String
       - character: Character
       - money: Integer
       - position: Integer
       - inTimsLine: Boolean
       - TurnsInTimsLine: Integer
       - isBankrupt: Boolean
       - numDoubleRolls: Integer
       - numRimCups: Integer
       - numResidences: Integer
       - properties: vector<shared_ptr<Property>>
       + getName(): String
       + getCharacter(): Character
       + setCharacter(char Character)
       + getMoney(): Integer
       + setMoney(int money)
       + getPosition(): Integer
       + setPosition(int position)
       + getInTimsLine(): Boolean
       + setInTimsLine(bool inTimsLine)
       + getTurnsInTimsLine(): Boolean
       + setTurnsinTimsLine(int turnsInTimsLine)
       + getIsBankrupt(): Boolean
       + getNumDoubleRolls(): Integer
       + setNumDoubleRolls(int numDoubleRolls)
       + getNumRimCups(): Integer
       + setNumRimsCups(int numRimCups)
       + getNumResidences(): Integer
       + setNumResidences(int numResidences)
       + getProperties(): vector<shared_ptr<Property>>  
       + move(int distance)
       + addMoney(int amount)
       + subtractMoney(int amount)
       + addProperty(Property* property)
       + removeProperty(Property* property)
       + auction(Property* property, Player* player)
    }

    class Dice {
       - dice1: Integer
       - dice2: Integer
       - testing: Boolean
       + roll(int d1 = -1, int d2 = -1): 
       + add(): Integer
       + isEqual(): Boolean
    }

    class Square {
       <<abstract>>
       - name: String
       - index: Integer
       - isProperty: Boolean
       + getName(): String
       + getIndex(): Integer 
       + getIsProperty(): Boolean
       + virtual performAction(player: unique_ptr<Player>) = 0
    }

    class NonProperty {
       <<abstract>>
       + virtual performAction(player: unique_ptr<Player>) = 0
    }

    class TimsLineSquare {
       - bailCost: Integer
       + performAction(player: unique_ptr<Player>)
    }

    class GoToTimsSquare {
       - TimsLineIndex: Integer
       + performAction(player: unique_ptr<Player>)
    }

    class ChanceSquare {
       + randomMove(): Integer
       + randomDeduct(): Integer
       + performAction(player: unique_ptr<Player>)
    }

    class FeesSquare {
       - fees: Integer
       + performAction(player: unique_ptr<Player>)
    }

    class OSAPSquare {
       - collectAmount: Integer
       + performAction(player: unique_ptr<Player>)
    }

    class Property {
       - cost: Integer
       - mortgageValue: Integer
       - owner: unique_ptr<Player>
       - isMortgaged: Boolean
       - isAcademic: Boolean
       - isResidence: Boolean
       - isGym: Boolean
       + getCost(): Integer
       + getMortgageValue(): Integer
       + getOwner(): unique_ptr<Player>
       + getIsMortgaged(): Boolean
       + getIsMortgaged(): Boolean
       + getIsAcademic: Boolean
       + getIsResidence: Boolean
       + getIsGym(): Boolean
       + setOwner(player: unique_ptr<Player>)
       + setMortgageValue(int mortgageValue)
       + setIsMortgaged(bool isMortgaged)
       + performAction(player: unique_ptr<Player>)
    }

    class Academic {
       - block: String
       - improvementCost: Integer
       - tution: Vector <Integer>
       - numImprovements: Integer
       - isMonopoly: Boolean
       - isImprovable: Boolean
       - isSellable: Boolean
       + getBlock(): String
       + getImprovementCost(): Integer
       + getTuition(int level): Integer
       + getNumImprovements(): Integer
       + getIsMonopoly(): Boolean
       + getIsImprovable(): Boolean
       + getIsSellable(): Boolean
       + setNumImprovements(int numImprovements)
       + setIsMonopoly(bool isMonopoly)
       + setIsImprovable(bool isImprovable)
       + setIsSellable(bool isSellable)
       + addimprove()
       + sellimprove()
       + performAction(player: unique_ptr<Player>)
    }

    class Residence {
       - rent: Integer
       + getRent(): Integer
       + performAction(player: unique_ptr<Player>)
    }

    class Gym {
       - usageFee: Integer
       - isMonopoly: Boolean
       + getusageFee(): Integer
       + getIsMonopoly(): Boolean
       + setIsMonopoly(bool isMonopoly)
       + performAction(player: unique_ptr<Player>)
    }

    %% Relationships
    Subject <|-- Game
    Subject o-- Observer
    Observer <|-- TextDisplay
    Observer <|-- GraphicalDisplay
    TextDisplay o-- Game
    GraphicalDisplay o-- Game
    Game *-- Board
    Game o-- Player
    Game o-- Dice
    Property o-- Player
    Player *-- Property
    Board *-- Square
    Square <|-- Property
    Property <|-- Academic
    Property <|-- Residence
    Property <|-- Gym
    Square <|-- NonProperty
    NonProperty <|-- TimsLineSquare
    NonProperty <|-- OSAPSquare
    NonProperty <|-- FeesSquare
    NonProperty <|-- ChanceSquare
    NonProperty <|-- GoToTimsSquare
```

### 2.2 Design Patterns Utilized
#### Obsever Pattern
This pattern is used to define a one-to-many dependency between objects so that when one object changes state, all its dependents are notified and updated automatically.

**Components** of the **Observer Pattern** in Watopoly:

• Subject: It maintains a list of observers and provides methods to attach, detach, and notify observers. The ```Game``` class is responsible for updating the state of the game, such as player positions, ownership of properties, and other game-related data.

• Observers: The ```TextDisplay``` and ```GraphicalDisplay``` classes act as observers. They are notified whenever the state of the game changes, allowing them to update their displays accordingly. The ```TextDisplay``` class might update a text-based representation of the game board, while the ```GraphicalDisplay``` class updates a graphical representation.

• Notification: When the game state changes (e.g., a player moves or buys a property), the ```Game``` class notifies its observers by calling their ```notify()``` methods. This ensures that both the text and graphical displays are updated to reflect the new state of the game.

#### UML Class Diagram
```mermaid
classDiagram
    class Subject {
        <<abstract>>
        - vector<Observer*> observers
        + attach(Observer* observer)
        + detach(Observer* observer)
        + notifyObserver()
        + virtual ~Subject() = 0
    }

    class Game {
        - board: unique_ptr<Board>
        - numPlayers: Integer
        - testingMode: Boolean
        + roll()
        + next()
        + trade(string player, string give, string receive)
        + improve(string property, string action)
        + mortgage(string property)
        + unmortgage(string property)
        + bankrupt()
        + assets()
        + all()
        + save(string filename)
        + setNumPlayers(int numPlayers)
        + setNumRollsInTimsLine(int numRollsInTimsLine)
        + setPlayerTimCups(int pos, int TimCups)
        + setPlayerMoney(int pos, int money)
        + setPlayerPosition(int pos, int position)
        + setPlayerCharacter(int pos, char character)
        + setupBoard()
        + setBuildingOwner(string buildingName, string owner)
        + setBuildingImprovements(string buildingName, int numImprovements)
        + setTestingMode()
        + end()
        + getState()
    }

    class Observer {
        <<abstract>>
        + virtual notify() = 0
    }

    class TextDisplay {
       - game: unique_ptr<Game>
       + notify()
       + display()
    }

    class GraphicalDisplay {
       - Display: display
       - Game* game
       - width: Integer
       - height: Integer
       - window: Window
       - gc: GC
       + notify()
       + getWidth(): Integer
       + getHeight(): Integer
       + drawBoard()
       + drawPlayers()
       + drawImprovements()
    }

    %% Relationships
    Subject <|-- Game
    Subject o-- Observer
    Observer <|-- TextDisplay
    Observer <|-- GraphicalDisplay
    TextDisplay o-- Game
    GraphicalDisplay o-- Game
    
```

---

## 3. Board Layout

```cpp
____________________________________________________________________________________________________
|Goose   |        |NEEDLES |        |        |V1      |        |        |CIF     |        |GO TO   |
|Nesting |--------|HALL    |--------|--------|        |--------|--------|        |--------|TIMS    |
|        |EV1     |        |EV2     |EV3     |        |PHYS    |B1      |        |B2      |        |
|        |        |        |        |        |        |        |        |        |        |        |
|________|________|________|________|________|________|________|________|________|________|________|
|        |                                                                                |        |
|--------|                                                                                |--------|
|OPT     |                                                                                |EIT     |
|        |                                                                                |        |
|________|                                                                                |________|
|        |                                                                                |        |
|--------|                                                                                |--------|
|BMH     |                                                                                |ESC     |
|        |                                                                                |        |
|________|                                                                                |________|
|SLC     |                                                                                |SLC     |
|        |                                                                                |        |
|        |                                                                                |        |
|        |                                                                                |        |
|________|                                                                                |________|
|        |                                                                                |        |
|--------|                                                                                |--------|
|LHI     |                                                                                |C2      |
|        |                 ______________________________________________                 |        |
|________|                |                                              |                |________|
|UWP     |                | #   # #### ##### ##### #### ##### #    #   # |                |REV     |
|        |                | #   # #  #   #   #   # #  # #   # #    #   # |                |        |
|        |                | # # # ####   #   #   # #### #   # #    ##### |                |        |
|        |                | # # # #  #   #   #   # #    #   # #      #   |                |        |
|________|                | ##### #  #   #   ##### #    ##### ####   #   |                |________|
|        |                |______________________________________________|                |NEEDLES |
|--------|                                                                                |HALL    |
|CPH     |                                                                                |        |
|        |                                                                                |        |
|________|                                                                                |________|
|        |                                                                                |        |
|--------|                                                                                |--------|
|DWE     |                                                                                |MC      |
|        |                                                                                |        |
|________|                                                                                |________|
|PAC     |                                                                                |COOP    |
|        |                                                                                |FEE     |
|        |                                                                                |        |
|        |                                                                                |        |
|________|                                                                                |________|
|        |                                                                                |        |
|--------|                                                                                |--------|
|RCH     |                                                                                |DC      |
|        |                                                                                |        |
|________|________________________________________________________________________________|________|
|DC Tims |        |        |NEEDLES |        |MKV     |TUITION |        |SLC     |        |COLLECT |
|Line    |--------|--------|HALL    |--------|        |        |--------|        |--------|OSAP    |
|        |HH      |PAS     |        |ECH     |        |        |ML      |        |AL      |        |
|        |        |        |        |        |        |        |        |        |        |        |
|________|________|________|________|________|________|________|________|________|________|________|
```

---
## 4. Game Logic

---
## 5. Command Interpreter

---
## 6. Player Management

---
## 7. Auctions

---
## 8. Saving and Loading

---
## 9. User Interface

---
## 10. Team Members
1. Yashila Barnwal
2. Lakshit Luhadia
3. Dhruv Kumar

---
## 11. Appendix

### 11.1 Code Snippets
