#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>

class LCS { // LCS class 
public:

    /*-----------------------Print method for printing computed LCS string ------------------------------*/

    static std::string printLCS(const std::string& str1, const std::string sequences[], int size, int num) {

        int index = findLCS(str1, sequences, size, num);
        std::string lcs = constLCS(str1, sequences[index]);
        int length = lcs.length();

        std::string retval= std::to_string(index+1) + "\t" + std::to_string(length) + "\t" + lcs; // print each line with format of  "<the index of the most similar sequence> <tab> <the length of the LCS> <tab> <the LCS>"
        return retval;
    }

private:

    /*-----------------------Compute the maximum length & construct LCS itself--------------------*/
    static std::string constLCS(const std::string& str1, const std::string& str2) {
        
        int m = str1.length();
        int n = str2.length(); // get the length of 2 inputs

        int** tablec = new int* [m + 1]; // dynamically allocate table c to compute maximum LCS length
        for (int i = 0; i <= m; ++i) {
            tablec[i] = new int[n + 1];
        }
        
        for (int i = 0; i <= m; i++) { // fill the table c with tabulation method, which indicates the LCS length
            for (int j = 0; j <= n; j++) {
                if (i == 0 || j == 0) 
                    tablec[i][j] = 0; // first line of square
                else if (str1[i - 1] == str2[j - 1])
                    tablec[i][j] = tablec[i - 1][j - 1] + 1; // if the character in both string is same, get diagonal value +1. 
                else
                    tablec[i][j] = std::max(tablec[i - 1][j], tablec[i][j - 1]); // else, get the bigger one from either up or left.
            }
        }

        std::string lcs; // LCS itself
        int i = m;
        int j = n;
        
        while (i > 0 && j > 0) { // consturct LCS with reverselly follow the table c. (we don't need to indicate with arrows here so table b is omitted)
            if (str1[i - 1] == str2[j - 1]) {
                lcs = str1[i - 1] + lcs;
                i--;
                j--;
            }
            else if (tablec[i - 1][j] > tablec[i][j - 1]) {
                i--;
            }
            else {
                j--;
            }
        }
        return lcs;
    }

    /*-----------------------Find most similar sequence with the given sequence index ------------------------------*/

    static int findLCS(const std::string& input_str, const std::string sequences[], int size, int num) { // get the total number of given inputs, and compare each one of them with all the others to find the most similar one
        
        int max_length = 0;
        std::string most_similar_lcs;
        int most_similar_index = -1;

        for (int i = 0; i < size; i++) { //iterate through the all the given sequences
            if (i == num) continue; // don't count itself

            std::string lcs = constLCS(input_str, sequences[i]);
            int length = lcs.length();

            if (length > max_length) { //find the maximum length of LCS, which is the most similar sequence with the given one.
                max_length = length;
                most_similar_lcs = lcs;
                most_similar_index = i;
            }
        }
        return most_similar_index;
    }

};

int main(int argc, char* argv[]) { // execute in CLI with "compiledname", "inputfile", "outputfile"

    /*----------check number of arguments -------------------------------------------------*/

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    /*------------------------check input file opened--------------------------------------*/

    std::ifstream input_file(argv[1]);

    if (!input_file.is_open()) {
        std::cerr << "Error opening input file: " << argv[1] << std::endl;
        return 1;
    }

    /*------------------------------get data from input.txt---------------------------*/

    int input_size; 
    input_file >> input_size; // get the length of each line (number in first line)

    int linecount = 0; 
    std::string line;
    while (std::getline(input_file, line)) {
        linecount++; // count total number of sequence lines in input file
    }
    linecount--;  

    input_file.close();
    std::ifstream input_file2(argv[1]); //  close and re-open the file to reset the pointer
    std::getline(input_file2, line); //start to read from second line
    
    std::string* input_str = new std::string[linecount]; // make array to store input lines

    for (int i = 0; i < linecount; i++) {
        std::getline(input_file2, input_str[i]); // store each line of string into the array
    }
    
    input_file2.close();

    /*---------------make the output.txt and check ------------------*/

    std::ofstream output_file(argv[2]);

    if (!output_file.is_open()) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    /*--------------------print each line of result into the output--------------------------------*/

    for (int i = 0; i < linecount-1; i++) {
        output_file << LCS::printLCS(input_str[i], input_str, linecount, i) << "\n"; // print each line

    }
    output_file << LCS::printLCS(input_str[linecount-1], input_str, linecount, linecount-1); // no space at the last line of output

    /*------------------- free allocated memory & close output file ---------------------*/

    delete[] input_str;

    output_file.close();

    return 0;
}
