// Eric Lowe and Rodolfo Hernandez
// scrabble.cpp
// Usage Statement: scrabble.out [input file]
//
// Explanations:
// Program reads in a file of potential Scrabble words
// in the form of scrambled letters (representing tiles).
// Program then attempts to find the highest scoring word for 
// particular set of tiles by checking in a database of words.
// Scoring scheme is built in.

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <map>
#include <iterator>

using namespace std;
typedef map < char, int > Scores; // have to typedef map to work properly
typedef map < string, int > Scored; // for scored valid words
typedef multimap< string, string > Match; // a for a list of all best matching words
typedef set< string > DB; // set for Database list of words

class Word {
    int count; // number of words that match
    int wordScore; // score for individual word
    int highScore; // highest score seen for set of tiles
    DB words; // set of valid words
    Match matching; // set of highest scoring words matching tiles
    Scores myScores; // map of scores
    Scored myScored; // map of scored valid words
  public:
    // Word class constructor that initializes count to 0 and 
    // fills myScores map
    Word() : count(0), wordScore(0), highScore(0) 
    { 
      // calls fillMap method to fill map myScores with score  
      //pairings for letter keys                
      fillScores(); 
      // before opening user supplied file, open database file and store words
      fillDB();
    } // Word() : count(0), word(NULL)
    
    // Word class destructor
    ~Word() 
    {
      
    } // ~Word()
    
    // Method fillMap fills the map myScores with keys = single letters and
    // values = Scrabble score for that letter.  In other words, given any 
    // letter of the English alphabet this map will return the corresponding
    // value of the letter as given by Scrabble.
    void fillScores()
    {
      int score[] = {1,3,3,2,1,4,2,4,2,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
      char letter[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m',
          'n','o','p','q','r','s','t','u','v','w','x','y','z'};
      
      for(int i = 0; i < 26; i++)
        myScores.insert( Scores::value_type( letter[i], score[i] ) );
      
     return;
    } // void fillScores()
    
    
    // Method to fill myScored map, which is a map of keys = words with 
    // values = total word score.  In other words, myScored map returns
    // the score of a valid Scrabble word when given a word (if it exists
    // in the map).
    void fillScored(const string &s)
    {
      int score = 0;
      int a = s.length();
      for(int i = 0; i < a; i++)
        score += myScores[s[i]];
      
      myScored.insert( Scored::value_type( s, score ) );
      return;
    } // void fillScored()
    
    // Method to fill the Database set with valid Scrabble words. This method
    // also calls a method to fill the map myScored for use in scoring user
    // input tiles.
    void fillDB()
    {
      string line;
      ifstream db("words.txt");
      
      while(getline(db, line)) // while able to read from file
      {
        if(line.length() <= 8 && line.find_first_not_of("abcdefghijklmnopqrstu"
            "vwxyz")) // if current word is 7 letters or less
        {
          setWord(line); // call method to insert into word set
          fillScored(line);
        } // if(line.length <= 7 && line.find_first_not_of("a-z"))
      } // while(getline(db, line))
      
      db.close();
      return;
    } // void fillDB()
    
    // Method fills the map matching, which is a multimap of the highest
    // scoring words for a given line.  This is because one line may give
    // multiple same-scoring words that are all 'the best' word to play
    // for a move, such as how tiles 'abcdefg' give badge, cafe, and face,
    // which are each worth 9 points.  Method will continue to add new 
    // same-scoring words until a word of higher score is found, which resets
    // the map for the particular key.
    void fillMatching(const string &line, const string &s)
    {
      wordScore = myScored.find(s)->second; // set wordScore to score of word
      if(count == 0)
      {
        highScore = wordScore;// set highScore to score of word
        matching.insert(Match::value_type(line, s)); //insert into map
        setCount(); // increase count
      }//if(count == 0)
      else
      {
        for(Match::const_iterator itr = matching.begin(); itr != matching.end(); itr++)
          if(s == itr->second)
            return;
           
        if(wordScore > highScore)
        {
          matching.erase(line);
          count = 0;
          matching.insert(Match::value_type(line, s)); //insert into map
          highScore = wordScore;
          setCount();
        }// if(wordScore > highScore)
        else
        {
          if(wordScore == highScore)
          {
            matching.insert(Match::value_type(line, s)); //insert into map
            setCount(); //increment count
          } // if(wordScore == highScore)   
          else
            return; // wordScore < highScore, so ignore and leave
        }// else wordScore <= highScore
      }// else count > 0
      return;
    } // void fillMatching()
    
    // Method setCount sets count variable (if needed)
    void setCount()
    {
      count += 1;
      return;
    } // void setCount(int count)
    
    
    // Method setWord should set a word within the set of words
    void setWord(const string &s)
    {
      words.insert( s );
    } // void setWord(const string &s)
    
    // This method reads the user inputed file and will process each line 
    // sequentially.
    void readInFile(ifstream& inf)
    {
      string line;
      // while not EOF
      while(getline(inf, line)) 
      {
        if(mindTheGap(line))
        {
          permuteTiles(line);
          printResults(line);
        }//if(mindTheGap(line))
        else
        {
          darkStar(line);
          printResults(line);
        }//else
        
        // clear out variables for next line
        highScore = 0; 
        wordScore = 0;
        count = 0;
      } // while(getline(inf, line))
      
      return;
    } // void readInFile(ifstream& inf)
    
    // Method prints out the results for each set of input user tiles
    void printResults(const string l)
    {
      cout << setw(2) << highScore;
      cout << " " << l << ": ";
      for(Match::const_iterator itr = matching.begin(); itr != matching.end(); itr++)
        if(l == itr->first)
          cout << itr->second << " ";
        
      if(count == 0)
        cout << "No words found." << endl;
      else
        cout << endl;
      
      return;
    } // void printResults(const string l)
    
    // Method that permutes the user-input line and calls 
    // the method findMatch as needed.  
    void permuteTiles(const string &s)
    {
      int i = s.length();
      string permute, temp;
      permute = s;
      
      for(int n = 0; n <= i; n++)
      {
        rotate(permute.begin(), permute.begin()+n, permute.end());
        do 
        {
          temp = permute.substr(0, i);
          if(myScored.find(temp) == myScored.end())
          {
            findMatch(s, permute, temp);
          } // if(words.find(temp) == words.end())
          else
          {
            fillMatching(s, temp);
            findMatch(s, permute, temp);
          } // else
        } while(next_permutation(permute.begin(), permute.end()));
      } // for(int n = 0; n <= i; n++)
      return;
    } // void permuteTiles(const string &s)
    
    // Method that finds the best match for a given permutation and calls
    // the method fillMatching as needed. Only added to make more compact
    // function implementation for method permuteTiles and to reduce 
    // redundant code.
    void findMatch(const string &line, const string &permute, const string &t)
    {
      string temp = t;
      for(int i = 7; i >= 1 && myScored.find(temp) == myScored.end(); i--)
        temp = permute.substr(0, i);
                    
      if(myScored.find(temp) != myScored.end())
        fillMatching(line, temp);
      return;
    } // void findMatch(const string &s)
    
    
    // Method to check a users tiles to see if a space tile exists.  If one
    // exists, mindTheGap calls appropriate methods to deal with spaces. 
    bool mindTheGap(const string &s)
    {
      size_t gap = s.find(" ");
      if(gap != string::npos)
        return(false);
      else
        return(true); 
    }// bool mindTheGap(const string &s)
    
    // Method to deal with space tiles, which are essentially wildcards. 
    // Called by method mindTheGap.
    void darkStar(const string &s)
    {
      size_t pos = s.find(" ");
      string wildcard;
      for(Scores::const_iterator itr = myScores.begin(); itr != myScores.end(); itr++)
      {
        wildcard = s.substr(0, pos);
        wildcard += itr->first;
        wildcard += s.substr(pos + 1, s.length());
        if(wildcard.length() <= 8 && wildcard.find_first_not_of("abcdefghijklm"
            "nopqrstuvwxyz"))
        {
          //cout << wildcard << endl;
          gapToothed(s, wildcard);
        }
      } // for(Scores::const_iterator itr = myScores.begin(); itr != myScores.end(); itr++)
      return;
    }// void darkStar(const string &s)
    
    void gapToothed(const string &s, const string &t)
    {
      int i = s.length();
      string permute, temp;
      permute = t;
            
      for(int n = 0; n <= i; n++)
      {
        rotate(permute.begin(), permute.begin()+n, permute.end());
        do 
        {
          temp = permute.substr(0, i);
          if(myScored.find(temp) == myScored.end())
          {
            findMatch(s, permute, temp);
          } // if(words.find(temp) == words.end())
          else
          {
            fillMatching(s, temp);
            findMatch(s, permute, temp);
          } // else
        } while(next_permutation(permute.begin(), permute.end()));
      } // for(int n = 0; n <= i; n++)
            
      return;
    } // void gapToothed(const string &s, const string &t)
};

// to take command line arguments, argc for number of args and argv[] to hold args
int main(int argc, const char * argv[]) 
{
  // tests if more or less than one argument given at command line
  if(argc != 2) 
  {
    cout << "Invalid number of arguments given" << endl;
    exit(1); // if incorrect number of args, print message and exit
  } // if(argc != 1)
  
  Word words; // declare Word object here, stores words and fills score map
  
  ifstream inf(argv[1]);
  
  words.readInFile(inf);
  
  inf.close();
  return(0);
} // int main(int argc, const char * argv[])


