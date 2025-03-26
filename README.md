# Watopoly
Watopoly is a video game project for CS246, which is a variant of the classic board game Monopoly. However, instead of the traditional locations, Watopoly's game board is based on the University of Waterloo campus.

---

## Table of Contents

- [1. Overview](#1.-overview)
  - [1.1 Introduction to Watopoly](#1-.-1-introduction-to-watopoly)
  - [Game Objectives](#game-objectives)
  - [Core Mechanics](#core-mechanics)
- [Design](#design)
  - [System Architecture](#system-architecture)
  - [Class Diagram](#class-diagrams)
  - [Design Patterns Utilized](#design-patterns-utilized)
  - [Data Structures](#data-structures)
- [Board Layout](#board-layout)
- [Game Logic](#game-logic)
- [Command Interpreter](#command-interpreter)
- [Player Management](#player-management)
- [Auctions](#auctions)
- [Saving and Loading](#saving-and-loading)
- [User Interface (UI)](#user-interface-(ui))
- [Team Members](#team-members)
- [Appendix](#appendix)


---

## Overview

### Introduction to Watopoly
In Watopoly, players take turns moving around the board, buying and improving on-campus buildings (which function as properties), and paying tuition (rent) to other players. The game features 40 squares, representing various locations on the University of Waterloo campus. The goal of the game is to be the last player remaining who has not gone bankrupt.

### Game Objectives

### Core Mechanics

---
## Design

### System Architecture

### Class Diagram

### Design Patterns Utilized

### Data Structures

---

## Board Layout

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
## Game Logic

---
## Command Interpreter

---
## Auctions

---
## Saving and Loading

---
## User Interface (UI)

---
## Team Members
1. Yashila Barnwal
2. Lakshit Luhadia
3. Dhruv Kumar

---
## Appendix
