t9 predictive text Author: Blake Berringer Version: 9/18/2020.

This distribution contains:

-- README -- this file

-- T9.c -- program

-- smallDictionary.txt / dictionary.txt -- inputs 

Shell command to build the program: gcc t9.c -o t9   

Shell command to run the program: ./t9 [input]  

This program implements a T9 predictive text, a text input mode available on many old cell phones, automated customer service phone systems, and keypads. Each number from 2-9 on the keypad represent three or four letters, the number 0 represents a space, and 1 represents a set of symbols such as { , . ! ? } etc. In this program, we only use the numbers 2-9, which represent the following letters:
•2 abc
•3 def
•4 ghi
•5 jkl
•6 mno
•7 pqrs
•8 tuv
•9 wxyz

Since multiple letters map to a single number, many key sequences represent multiple words. For example, the input 2665 represents "book" and "cool", among other possibilities.To translate from number sequences to words, we use a data structure known as a trie.  

The user should type numbers and the program will print a word corresponding to the sequence of numbers entered. If the user then enters '#', the program will print the next word in the trie that has the same numeric value, and so forth. The user can also type a number followed by one or more '#' characters -this will print the same word that would be found by typing the number and individual '#' characters on separate input lines.
