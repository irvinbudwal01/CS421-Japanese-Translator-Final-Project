#include <fstream>
#include <iostream>
#include <map>
#include <string>
using namespace std;
void getEword();
void gen();
void s();
void AfterSubject();
void AfterNoun();
void AfterObject();
void Noun();
void Verb();
void Be();
void Tense();

/* INSTRUCTION  :  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .
       and then append the two files into one:
          cat scanner.cpp parser.cpp > myparser.cpp
*/

//===============================================
// File parser.cpp written by Group Number: 15
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------
enum token_type {
  WORD1,
  WORD2,
  PERIOD,
  VERB,
  VERBNEG,
  VERBPAST,
  VERBPASTNEG,
  IS,
  WAS,
  OBJECT,
  SUBJECT,
  DESTINATION,
  PRONOUN,
  CONNECTOR,
  ERROR,
  EOFM
};

int scanner(token_type &, string &);
void gen(string);
void syntaxerror1(token_type expected, string lexeme);
void syntaxerror2(string, string);
string tokenName[30] = {"WORD1",   "WORD2",     "PERIOD",      "VERB",
                        "VERBNEG", "VERBPAST",  "VERBPASTNEG", "IS",
                        "WAS",     "OBJECT",    "SUBJECT",     "DESTINATION",
                        "PRONOUN", "CONNECTOR", "ERROR",       "EOFM"};

string reservedWords[30] = {
    "masu", "masen",   "mashita",  "masendeshita", "desu", "deshita", "o",
    "wa",   "ni",      "watashi",  "anate",        "kare", "kanojo",  "sore",
    "mata", "soshite", "shikashi", "dakara",       "EOFM"};
// from the notes in week9a
bool token_available = false; // global flag indicating whether we have saved a
                              // token to eat up or not
token_type saved_token; // global buffer for the token the scanner returned
string saved_lexeme;    // sequence of characters in the source program that
                        // matches the pattern
// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.

// Type of error: ** The lexeme was found instead of type
// Done by: ** Irvin Budwal
void syntaxerror1(token_type expected, string lexeme) {
  cout << "SYNTAX ERROR1: unexpected " << saved_lexeme
       << " found in " // raise error type 1
       << tokenName[expected] << endl;
}
// Type of error: ** Lexeme found in parser
// Done by: ** Irvin Budwal
void syntaxerror2(string function, string lexeme) {
  cout << "SYNTAX ERROR2: unexpected " << lexeme << " found in "
       << function // raise error type 2
       << endl;
}

//-------------------------------Semantic Function
//------------------------------------------------
string e_word;

void getEword() {
  if (saved_lexeme == "watashi")
    e_word = "I/me";
  else if (saved_lexeme == "anata")
    e_word = "you";
  else if (saved_lexeme == "Kare")
    e_word = "he/him";
  else if (saved_lexeme == "kanojo")
    e_word = "she/her";
  else if (saved_lexeme == "sore")
    e_word = "it";
  else if (saved_lexeme == "mata")
    e_word = "Also";
  else if (saved_lexeme == "soshite")
    e_word = "Then";
  else if (saved_lexeme == "shikashi")
    e_word = "However";
  else if (saved_lexeme == "dakara")
    e_word = "Therefore";
  // nouns
  else if (saved_lexeme == "daigaku")
    e_word = "college";
  else if (saved_lexeme == "Kurasu")
    e_word = "class";
  else if (saved_lexeme == "hon")
    e_word = "book";
  else if (saved_lexeme == "tesuto")
    e_word = "test";
  else if (saved_lexeme == "ie")
    e_word = "home";
  else if (saved_lexeme == "isu")
    e_word = "chair";
  else if (saved_lexeme == "seito")
    e_word = "student";
  else if (saved_lexeme == "sensei")
    e_word = "Teacher";
  else if (saved_lexeme == "tomodachi")
    e_word = "friend";
  else if (saved_lexeme == "jidoosha")
    e_word = "car";
  else if (saved_lexeme == "ayuunyuu")
    e_word = "milk";
  else if (saved_lexeme == "biiru")
    e_word = "beer";
  else if (saved_lexeme == "choucho")
    e_word = "butterfly";
  else if (saved_lexeme == "ryouri")
    e_word = "cooking";
  else if (saved_lexeme == "toire")
    e_word = "restroom";
  else if (saved_lexeme == "gohan")
    e_word = "meal";
  // Description
  else if (saved_lexeme == "yasashii")
    e_word = "easy";
  else if (saved_lexeme == "muzukashii")
    e_word = "difficult";
  else if (saved_lexeme == "ureshii")
    e_word = "pleased";
  else if (saved_lexeme == "shiawase")
    e_word = "happy";
  else if (saved_lexeme == "kanashii")
    e_word = "sad";
  else if (saved_lexeme == "omoi")
    e_word = "heavy";
  else if (saved_lexeme == "oishii")
    e_word = "delicious";
  else if (saved_lexeme == "tennen")
    e_word = "natural";
  // Verbs
  else if (saved_lexeme == "nakI")
    e_word = "cry";
  else if (saved_lexeme == "ikI")
    e_word = "go";
  else if (saved_lexeme == "tabE")
    e_word = "eat";
  else if (saved_lexeme == "ukE")
    e_word = "take";
  else if (saved_lexeme == "kakI")
    e_word = "write";
  else if (saved_lexeme == "yamI")
    e_word = "read";
  else if (saved_lexeme == "namI")
    e_word = "drinkr";
  else if (saved_lexeme == "agE")
    e_word = "give";
  else if (saved_lexeme == "moraI")
    e_word = "receive";
  else if (saved_lexeme == "butsI")
    e_word = "hit";
  else if (saved_lexeme == "kerI")
    e_word = "kick";
  else if (saved_lexeme == "shaberI")
    e_word = "talk";
  else if (saved_lexeme == "yarI")
    e_word = "do";
  else if (saved_lexeme == "yorokobI")
    e_word = "enjoy";
  // else not in dictionary
  else
    e_word = saved_lexeme;
}
ofstream outfile;

void gen(string word) {
  if (word != "TENSE") {
    outfile << word << ": " << e_word << endl;
  } else {
    outfile << word << ": " << tokenName[saved_token] << endl;
  }
}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme
//-------------------------------Translation Function
//------------------------------------------------
// Purpose: ** Grab next token from file.
// Done by: Eliseo Izazaga
token_type next_token() {
  if (!token_available) {
    scanner(saved_token, saved_lexeme); // scan for next
    cout << "String/token from scanner: " << saved_lexeme << "/"
         << tokenName[saved_token] << endl;

    token_available = true; // set available to true

    if (saved_token == ERROR) { // if token is error then raise error
      syntaxerror1(saved_token, saved_lexeme); // call error
    }
  }
  return saved_token; // return saved token
}

// Purpose: Match tokens.
// Done by: Eliseo Izazaga
bool match(token_type expected) {
  if (next_token() != expected) { // if next token is not unexpected then error
    syntaxerror1(expected, saved_lexeme); // call error function
    return false;                         // no match
  } else {
    token_available = false; // eat token
    return true;             // on match
  }
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: ** Listed below
// Done by: ** Irvin/Efrain/Eliseo
//<story> -> <sentence> { <sentence> }
void story() {
  cout << "Processing <story>" << endl; // print
  s();                                  // call starter
  bool flag = true;                     // set flag to true while looping
  while (flag) {                        // loop while no eofm
    switch (next_token()) {
      // on good switch keep running
    case CONNECTOR: // check all cases
    case WORD1:
    case PRONOUN:
      s(); // run s() on repeat
      break;
    case EOFM:                        // on eofm end loop
      cout << "EOFM REACHED" << endl; // print
      flag = false;                   // set flag to false to break out
      break;
    default: // on default break out
      cout << "DEFAULT REACHED" << endl;
      flag = false;
      break;
    }
  }
}

//<s>  ::=  [CONNECTOR] <noun> SUBJECT <afterSubject>
void s() {
  cout << "Processing <S>" << endl;      // print
  if (next_token() == CONNECTOR) {       // check next_token is connector
    match(CONNECTOR);                    // match it
    cout << "Matched CONNECTOR" << endl; // print
    getEword();
    gen("CONNECTOR");
  }
  Noun(); // call noun function
  getEword();
  match(SUBJECT);                    // match subject
  cout << "Matched SUBJECT" << endl; // print
  gen("ACTOR");
  AfterSubject(); // call afterSubject
}

//<noun>  ::= WORD1 | PRONOUN
void Noun() {
  cout << "Processing <Noun>" << endl;  // print
  switch (next_token()) {               // grab next
  case WORD1:                           // check if word1
    match(WORD1);                       // match it
    cout << "Matched WORD1" << endl;    // print
    break;                              // break out
  case PRONOUN:                         // check pronoun
    match(PRONOUN);                     // match
    cout << "Matched PRONOUN" << endl;  // print
    break;                              // break out
  default:                              // on error
    syntaxerror2("noun", saved_lexeme); // call error
  }
}
//<after subject> ::=<verb><tense> PERIOD | <noun> <after noun>
void AfterSubject() {
  cout << "Processing <After-Subject>" << endl; // print
  switch (next_token()) {                       // check next
  case WORD2:                                   // on word2
    Verb();                                     // call verb
    getEword();
    gen("ACTION");
    Tense(); // call tense
    gen("TENSE");
    match(PERIOD);                    // match period
    cout << "Matched PERIOD" << endl; // print
    break;                            // break out
  case WORD1:                         // on word1 or pronoun call next functions
  case PRONOUN:
    Noun(); // call noun
    getEword();
    AfterNoun(); // call afterNoun
    break;       // break out

  default:                                      // on error
    syntaxerror2("aftersubject", saved_lexeme); // call error
  }
}
//<afterObject>::= <verb> <tense> PERIOD | <noun> DESTINATION <verb> <tense>
void AfterObject() {
  cout << "Processing <After-Object>" << endl; // print
  switch (next_token()) {                      // get next
  case WORD2:                                  // on word2
    Verb();                                    // call verb
    getEword();
    gen("ACTION");
    Tense(); // call tense
    gen("TENSE");
    match(PERIOD);                    // match period
    cout << "Matched PERIOD" << endl; // print
    break;                            // break out
  case WORD1:                         // on word1 or pronoun
  case PRONOUN:
    Noun(); // call noun
    getEword();
    match(DESTINATION);                    // match destination
    cout << "Matched DESTINATION" << endl; // print
    gen("TO");
    Verb(); // call verb
    getEword();
    gen("ACTION");
    Tense(); // call tense
    gen("TENSE");
    match(PERIOD);
    break;                                     // break out
  default:                                     // on error
    syntaxerror2("afterobject", saved_lexeme); // call function
  }
}
// <afterNoun> ::= <be>  PERIOD | DESTINATION  <verb> <tense> PERIOD | OBJECT
// <afterObject>
void AfterNoun() {
  cout << "Processing <After-Noun>" << endl; // print
  switch (next_token()) {                    // get next
  case IS:                                   // on is or was
  case WAS:
    Be(); // call be
    gen("DESCRIPTION");
    gen("TENSE");
    match(PERIOD);                         // match period
    cout << "Matched PERIOD" << endl;      // print
    break;                                 // break out
  case DESTINATION:                        // on destination
    match(DESTINATION);                    // match destination
    cout << "Matched DESTINATION" << endl; // print
    gen("TO");
    Verb(); // call verb
    getEword();
    gen("ACTION");
    Tense(); // call tense
    gen("TENSE");
    match(PERIOD);                    // match period
    cout << "Matched PERIOD" << endl; // print
    break;                            // break out
  case OBJECT:                        // on object
    match(OBJECT);                    // match object
    cout << "Matched OBJECT" << endl; // print
    gen("OBJECT");
    AfterObject();                           // call afterObject
    break;                                   // break out
  default:                                   // on error
    syntaxerror2("afternoun", saved_lexeme); // call error
  }
}
//<verb>::= WORD2
void Verb() {
  cout << "Processing <Verb>" << endl; // print
  match(WORD2);                        // match word2
  cout << "Matched WORD2" << endl;     // print
}
//<be>::=IS | WAS
void Be() {
  cout << "Processing <Be>" << endl;  // print
  switch (next_token()) {             // get next
  case IS:                            // on is
    match(IS);                        // match is
    cout << "Matched IS" << endl;     // print
    break;                            // break out
  case WAS:                           // on was
    match(WAS);                       // match was
    cout << "Matched WAS" << endl;    // print
    break;                            // break out
  default:                            // on error
    syntaxerror2("be", saved_lexeme); // call error
  }
}
//<tense>::=VERBPAST  | VERBPASTNEG | VERB | VERBNEG
void Tense() {
  cout << "Processing <Tense>" << endl;    // print
  switch (next_token()) {                  // next
  case VERBPAST:                           // on verbpast
    match(VERBPAST);                       // match verbpast
    cout << "Matched VERBPAST" << endl;    // print
    break;                                 // break out
  case VERBPASTNEG:                        // on verbpastneg
    match(VERBPASTNEG);                    // match verbpastneg
    cout << "Matched VERBPASTNEG" << endl; // print
    break;                                 // break out
  case VERB:                               // on verb
    match(VERB);                           // match verb
    cout << "Matched VERB" << endl;        // print
    break;                                 // break out
  case VERBNEG:                            // on verbneg
    match(VERBNEG);                        // match verbneg
    cout << "Matched VERBNEG" << endl;     // print
    break;                                 // break out
  default:                                 // on error
    syntaxerror2("tense", saved_lexeme);   // call error
  }
}
//_____________________________Scanners________

bool word(string s) {

  int state = 0;
  int charpos = 0;

  while (s[charpos] != '\0') {
    // each new state will have a different number
    // starting on q0
    if (state == 0) {
      switch (s[charpos]) {
      case 'a':
      case 'e':
      case 'i':
      case 'o':
      case 'u':
      case 'I':
      case 'E':
        state = 1; // q0q1
        break;
      case 'd':
      case 'w':
      case 'z':
      case 'y':
      case 'j':
        state = 2; // qsa
        break;
      case 'b':
      case 'g':
      case 'h':
      case 'k':
      case 'm':
      case 'n':
      case 'p':
      case 'r':
        state = 3; // qy
        break;
      case 'c':
        state = 4; // qc
        break;
      case 't':
        state = 5; // qt
        break;
      case 's':
        state = 6; // qs
        break;
      default:
        return (false);
        break;
      }
    }
    // q0q1
    else if (state == 1) {
      switch (s[charpos]) {
      case 'a':
      case 'e':
      case 'i':
      case 'o':
      case 'u':
      case 'I':
      case 'E':
        state = 1; // q0q1
        break;
      case 'b':
      case 'g':
      case 'h':
      case 'k':
      case 'm':
      case 'p':
      case 'r':
        state = 3; // qy this case is the one without the n
        break;
      case 'd':
      case 'w':
      case 'z':
      case 'y':
      case 'j':
        state = 2; // qsa
        break;
      case 't':
        state = 5; // qt
        break;
      case 's':
        state = 6; // qs
        break;
      case 'c':
        state = 4; // qc
        break;
      case 'n':
        state = 7; // q0qy
        break;
      default:
        return (false);
      }
    } else if (state == 2) { // qsa
      switch (s[charpos]) {
      case 'a':
      case 'e':
      case 'i':
      case 'o':
      case 'u':
      case 'I':
      case 'E':
        state = 1;
        break;
      default:
        return (false);
      }
    } else if (state == 3) { // qy
      switch (s[charpos]) {
      case 'a':
      case 'e':
      case 'i':
      case 'o':
      case 'u':
      case 'I':
      case 'E':
        state = 1; // q0q1
        break;
      case 'y':
        state = 2; // qsa
        break;
      default:
        return (false);
      }
    } else if (state == 4) { // qc
      switch (s[charpos]) {
      case 'h':
        state = 2; // qsa
        break;
      default:
        return (false);
      }
    } else if (state == 5) { // qt
      switch (s[charpos]) {
      case 'a':
      case 'e':
      case 'i':
      case 'o':
      case 'u':
      case 'I':
      case 'E':
        state = 1; // q0q1
        break;
      case 's':
        state = 2; // qsa
        break;
      default:
        return (false);
      }
    } else if (state == 6) { // qs
      switch (s[charpos]) {
      case 'a':
      case 'e':
      case 'i':
      case 'o':
      case 'u':
      case 'I':
      case 'E':
        state = 1; // q0q1
        break;
      case 'h':
        state = 2; // qsa
        break;
      default:
        return (false);
      }
    } else if (state == 7) { // q0qy
      switch (s[charpos]) {
      case 'a':
      case 'e':
      case 'i':
      case 'o':
      case 'u':
      case 'I':
      case 'E':
        state = 1; // q0q1
        break;
      case 'b':
      case 'g':
      case 'h':
      case 'k':
      case 'm':
      case 'n':
      case 'p':
      case 'r':
        state = 3; // qy
        break;
      case 'd':
      case 'w':
      case 'z':
      case 'y':
      case 'j':
        state = 2; // qsa
        break;
      case 't':
        state = 5; // qt
        break;
      case 's':
        state = 6; // qs
        break;
      case 'c':
        state = 4; // qc
        break;
      default:
        return (false);
      }
    } else {
      cout << "did not find .................." << endl;
    }
    charpos++; // move position
  }
  if (state == 0 || state == 1 || state == 7) { // final states
    return (true);
  } else {
    return (false);
  }
}
// PERIOD DFA
// Done by: Efrain Alvarez
bool period(string s) {
  if (s[0] == '.') {
    return (true);
  } else {
    return (false);
  }
}

ifstream finMain; // global for reading/opening file
int scanner(token_type &tt, string &w) {

  string tempWord;
  finMain >> tempWord;

  w = tempWord;

  if (tempWord == "EOFM" || tempWord == "eofm") {
    tt = EOFM;
    return 0;
  }
  // ** Grab the next word from the file via fin
  // 1. If it is eofm, return right now.

  /*  **
  2. Call the token functions (word and period)
     one after another (if-then-else).
     Generate a lexical error message if both DFAs failed.
     Let the tokentype be ERROR in that case.
*/
  if (word(tempWord)) {

    for (int i = 0; i < 20; i++) {
      if (tempWord == reservedWords[i]) {
        switch (i) {
        case 0:
          tt = VERB;
          return 0;
        case 1:
          tt = VERBNEG;
          return 0;
        case 2:
          tt = VERBPAST;
          return 0;
        case 3:
          tt = VERBPASTNEG;
          // cout << w << " is of type: " << tokenName[tt] << endl;;
          return 0;
        case 4:
          tt = IS;
          // cout << w << " is of type: " << tokenName[tt] << endl;;
          return 0;
        case 5:
          tt = WAS;
          // cout << w << " is of type: " << tokenName[tt] << endl;;
          return 0;
        case 6:
          tt = OBJECT;
          // cout << w << " is of type: " << tokenName[tt] << endl;;
          return 0;
        case 7:
          tt = SUBJECT;
          // cout << w << " is of type: " << tokenName[tt] << endl;;
          return 0;
        case 8:
          tt = DESTINATION;
          // cout << w << " is of type: " << tokenName[tt] << endl;;
          return 0;
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
          tt = PRONOUN;
          cout << w << " is of type: " << tokenName[tt] << endl;
          return 0;
        case 14:
        case 15:
        case 16:
        case 17:
          tt = CONNECTOR;
          // cout << w << " is of type: " << tokenName[tt] << endl;;
          return 0;
        case 18:
          tt = EOFM;
          // cout << w << " is of type: " << tokenName[tt] << endl;;
          return 0;
        default:
          // cout << "error, switch did not see it" << endl;
          return 0;
        }
      }
    }

    int length = tempWord.length();
    // cout << "LAST CHAR............. " << tempWord[length - 1] << endl;
    if (tempWord[length - 1] == 'i' | tempWord[length - 1] == 'u' |
        tempWord[length - 1] == 'a' | tempWord[length - 1] == 'n' |
        tempWord[length - 1] == 'e' | tempWord[length - 1] == 'o') {

      tt = WORD1;
      // cout << w << " is of type: " << tokenName[tt] << endl;;
      return 0;
    }

    else if (tempWord[length - 1] == 'E' | tempWord[length - 1] == 'I') {
      tt = WORD2;
      // cout << w << " is of type: " << tokenName[tt] << endl;
      return 0;
    }
  }

  else if (period(tempWord)) {
    tt = PERIOD;
    // cout << w << " is of type: " << tokenName[tt] << endl;;
    return 0;
  }

  tt = ERROR;
  // cout << "LEXICAL ERROR...TOKEN TYPE IS " << tokenName[tt] << endl;
  return 0;

  /*
      3. If it was a word,
         check against the reservedwords list.
         If not reserved, tokentype is WORD1 or WORD2
         decided based on the last character.

      4. Return the token type & string  (pass by reference)
      */

} // the end of scanner

string filename;
// fstream finMain;

//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by:  **
int main() {

  map<std::string, string> map; // map to hold dictionary
  ifstream dict;
  cout << "Enter the input dictionary name: ";
  cin >> filename;
  dict.open(filename.c_str());

  string japaneseWord;
  string englishWord;

  while (dict >> japaneseWord) { // fill map from dict.txt
    dict >> englishWord;
    map[japaneseWord] = englishWord;
  }

  // std::map<std::string, string>::iterator it = map.begin(); //iterator for
  // map

  // while (it != map.end()) { //iterator through map to display dictionary
  //   cout << "Japanese Word: " << it->first << " English Word: " << it->second
  //        << endl;
  //   it++;
  // }
  outfile.open("translated.txt");

  cout << "GROUP 15 PARSER" << endl;
  cout << "Eliseo Izazaga, Irvin Budwal, Efrain Alvarez" << endl;
  cout << "Enter the input file name: ";
  cin >> filename; // read in user input
  finMain.open(filename.c_str()); // finMain opens input file
  //** calls the <story> to start parsing
  story(); // call story
  //** closes the input file
  finMain.close(); // close file
  outfile.close();
} // end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output
// functions
