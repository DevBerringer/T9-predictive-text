// Blake Berringer
// Fall 2020 Computer Orginization
// T9.c will take a inputed dictionary and convert these words
// to a numerical value.  Then takes input from the user to find words.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LEN 100

// struct nodes  of our trie data
struct TrieNode {
  char *word;
  struct TrieNode *child[BUFFER_LEN];
};
typedef struct TrieNode TrieNode_l;

// function used to find the letter dependent on
// the number that was inputed
int findNum(char letter) {
  if (strchr("abc", letter) != NULL) {
    return 2;
  }
  if (strchr("def", letter) != NULL) {
    return 3;
  }
  if (strchr("ghi", letter) != NULL) {
    return 4;
  }
  if (strchr("jkl", letter) != NULL) {
    return 5;
  }
  if (strchr("mno", letter) != NULL) {
    return 6;
  }
  if (strchr("pqrs", letter) != NULL) {
    return 7;
  }
  if (strchr("tuv", letter) != NULL) {
    return 8;
  }
  if (strchr("wxyz", letter) != NULL) {
    return 9;
  } else {
    // prints and exits if dictionary is not only words
    printf("Could not find number that corrasponds to input\n");
    exit(1);
  }
}

// function to make a new node
// set the data value to NULL
// set its children to NULL
TrieNode_l *makeNewNode() {
  TrieNode_l *newNode = (TrieNode_l *)malloc(sizeof(TrieNode_l));
  newNode->word = NULL;
  for (int i = 0; i < BUFFER_LEN; i++) {
    newNode->child[i] = NULL;
  }
  return newNode;
};

// funtion to insert the words into the tree structure
// finds the numerical value of work letter my letter
// and add these to the trie
void insert(TrieNode_l *head, char *word) {
  TrieNode_l *curr = head;
  int length = strlen(word);
  char *dicWord = (char *)malloc(length);
  strncpy(dicWord, word, length - 1);
  dicWord[length - 1] = '\0';
  for (int i = 0; word[i] != '\n'; i++) {
    int num = findNum(word[i]);
    if (curr->child[num] == NULL) {
      curr->child[num] = makeNewNode();
    }
    curr = curr->child[num];
  }
  while (curr->child[BUFFER_LEN - 1] != NULL) {
    curr = curr->child[BUFFER_LEN - 1];
  }
  if (curr->word == NULL) {
    curr->word = dicWord;
  } else {
    curr->child[BUFFER_LEN - 1] = makeNewNode();
    curr = curr->child[BUFFER_LEN - 1];
    curr->word = dicWord;
  }
}

// Funtion used to find the word in the trie retuns null if
// can not find the word at that data point.
// else returns the word
TrieNode_l *findWord(TrieNode_l *head, char *buffer) {
  TrieNode_l *curr = head;
  for (int i = 0; i < strlen(buffer); i++) {
    if (buffer[i] != '#') {
      if (curr->child[(buffer[i] - '0')] == NULL) {
        return NULL;
      }
      curr = curr->child[(buffer[i] - '0')];
    } else {
      if (curr->child[BUFFER_LEN - 1] == NULL) {
        return NULL;
      }
      curr = curr->child[BUFFER_LEN - 1];
    }
  }
  return curr;
}

// Function used to take input from the user or text input file
// prints words if they can be found
// prints exausted or not found depending on having # or not
void takeInput(TrieNode_l *head) {
  char searching[BUFFER_LEN];
  TrieNode_l *curr = head;
  int x = 1;
  // BUG: doesnt accept QUIT or Quit
  printf("Enter exit to quit.\n");
  while (x == 1) {
    printf("Enter key Sequence (or # for next word):\n");
    scanf("%s", searching);
    if (strcmp(searching, "exit") == 0) {
      x = 0;
    }
    if (searching[0] != '#') {
      curr = findWord(head, searching);
    } else {
      curr = findWord(curr, searching);
    }
    if (curr != NULL) {
      if (curr->word) {
        printf("%s\n", curr->word);
      }
    } else {
      if (searching[strlen(searching) - 1] == '#') {
        printf("Exhausted all T9onyms in the current dictionary\n");
        curr = head;
      } else if (x != 0) {
        printf("%s not found in the current dictionary.\n", searching);
        curr = head;
      }
    }
  }
}

// recursive free function needed here to free the trie structure
void freeMalloced(TrieNode_l *head) {
  for (int i = 0; i < BUFFER_LEN; i++) {
    if (head->child[i] != NULL) {
      freeMalloced(head->child[i]);
      free(head->child[i]);
    }
  }
  if (head->word != NULL) {
    free(head->word);
  }
}
// Main Function
// used to take command line input
// finished with freeing mallocked data
int main(int argc, char **argv) {
  TrieNode_l *head = makeNewNode();
  if (argc < 2) {
    printf("missing FILE argument\n");
    exit(1);
  }
  char *filename = argv[1];

  FILE *file;
  char buffer[BUFFER_LEN];
  file = fopen(filename, "r");

  // read all lines
  while (fgets(buffer, BUFFER_LEN, file)) {
    insert(head, buffer);
  }
  fclose(file);
  takeInput(head);
  freeMalloced(head);
  free(head);
  return 0;
}
