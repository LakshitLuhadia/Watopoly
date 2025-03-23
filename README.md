# Watopoly

## Overview
Watopoly is a video game project for CS246, which is a variant of the classic board game Monopoly. However, instead of the traditional locations, Watopoly's game board is based on the University of Waterloo campus.

In Watopoly, players take turns moving around the board, buying and improving on-campus buildings (which function as properties), and paying tuition (rent) to other players. The game features 40 squares, representing various locations on the University of Waterloo campus. The goal of the game is to be the last player remaining who has not gone bankrupt.

---

## Board Layout

```C++
_________________________________________________________________________________________
 |Goose | |NEEDLES| | |V1 | | |CIF | |GOTO |
 |Nesting|-------|HALL |-------|-------| |-------|-------| |-------|TIMS |
 | |EV1 | |EV2 |EV3 | |PHYS |B1 | |B2 | |
 | | | | | | | | | | | |
 |_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|
 | | | |
 |-------| |-------|
 |OPT | |EIT |
 | | | |
 |_______| |_______|
 | | | |
 |-------| |-------|
 |BMH | |ESC |
 | | | |
 |_______| |_______|
 |SLC | |SLC |
 | | | |
 | | | |
 | | | |
 |_______| |_______|
 | | | |
 |-------| |-------|
 |LHI | |C2 |
 | | _____________________________________________ | |
 |_______| | | |_______|
 |UWP | |# # ## ##### ### ### ### # # #| |REV |
 | | |# ## # # # ## ## ## # #| | |
 | | |####### # # #### # ## ## | | |
 | | |#### # # # ## # ## # | | |
 |_______| |###### # # ### # ### ### # | |_______|
 | | |_____________________________________________| |NEEDLES|
 |-------| |HALL |
 |CPH | | |
 | | | |
 |_______| |_______|
 | | | |
 |-------| |-------|
 |DWE | |MC |
 | | | |
 |_______| |_______|
 |PAC | |COOP |
 | | |FEE |
 | | | |
 | | | |
 |_______| |_______|
 | | | |
 |-------| |-------|
 |RCH | |DC |
 | | | |
 |_______|_______________________________________________________________________|_______|
 |DCTims| | |NEEDLES| |MKV |TUITION| |SLC | |COLLECT|
 |Line |-------|-------|HALL |-------| | |-------| |-------|OSAP |
 | |HH |PAS | |ECH | | |ML | |AL | |
 | | | | | | | | | | | |
 |_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|```
