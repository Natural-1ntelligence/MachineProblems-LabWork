/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    string cur_line;
    ifstream infile(word_list_fname);


    if (infile.is_open()) {
        while (getline(infile, cur_line)) {
            if (cur_line.size() == 5) {
            	string cur_word1 = cur_line.substr(1, cur_line.size() - 1);

            	string cur_word2 = cur_line[0] + cur_line.substr(2, cur_line.size() - 1);

            	if (d.homophones(cur_line, cur_word1) && (d.homophones(cur_line, cur_word2)))
            		ret.push_back(tuple<string, string, string>(cur_line, cur_word1, cur_word2));
            }
        }
    }
    infile.close();
    return ret;
}
