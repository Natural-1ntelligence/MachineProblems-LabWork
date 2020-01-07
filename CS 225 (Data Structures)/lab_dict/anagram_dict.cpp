/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{   
    string cur_line;
    ifstream infile(filename);
    if (infile.is_open()) {
        while (getline(infile, cur_line)) {
        	string word = cur_line;
        	std::sort(word.begin(), word.end());
        	dict[word].push_back(cur_line);
        }
    }

    /* Your code goes here! */
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for (auto x: words){
        string y = x;
        std::sort(y.begin(),y.end());
        dict[y].push_back(x);

    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string x = word;
    std::sort(x.begin(),x.end());
    if (dict.find(x) == dict.end() ) {
    	return vector<string>();
    }
    return dict.at(x);
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */

     vector<vector<string>> res;
    for (auto x: dict)
    	if (x.second.size() > 1) {
        res.push_back(x.second);
        }
    return res;
}
