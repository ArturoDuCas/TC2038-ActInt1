/*
    Actividad Integradora 1 - TC2038
    Integrantes:
        Arturo Duran Castillo - A00833516
        Andrés Marcelo De Luna Pámanes - A00832239
    Fecha: 1 de octubre 2023
 */

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
using namespace std;

ofstream outFile;


void printVectorOfStrings(vector<string> vec) {
    for(int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

void readMCodes(vector<string> &vec) {
    ifstream file("./in/mcode.txt");

    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    string line;
    while (getline(file, line))
        vec.push_back(line);


    file.close();
}

void readTransmission(vector<string> &vec, string f) {
    ifstream file(f);

    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo de transmision " << f << "\"" << endl;
        return;
    }

    string line;
    while (getline(file, line))
        vec.push_back(line);

    file.close();
}

/**
 * Function to compute the Longest Proper Prefix which is also a Suffix (LPS) for a given pattern.
 *
 * Description:
 * This algorithm preprocesses the pattern and constructs an LPS array which will be useful
 * for string searching using the KMP (Knuth Morris Pratt) algorithm.
 * The value at position `i` in the LPS array indicates the length of the longest proper suffix
 * which is also a prefix in the pattern up to `i`.
 *
 * Parameters:
 * - p: A string representing the pattern for which we want to compute the LPS array.
 *
 * Returns:
 * - A vector of integers representing the LPS array for the pattern.
 *
 * Complexity:
 * - Time: O(m), where m is the length of the pattern.
 */
vector<int> lps(string p){
    int n = p.size();
    vector<int> lpsv(n, 0);
    int j=0, i=1;
    while (i < n){
        if (p[i] == p[j]){
            lpsv[i++] = ++j;
        }
        else{
            if (j==0){
                lpsv[i] = 0;
                i++;
            }
            else{
                j = lpsv[j-1];
            }
        }
    }
    return lpsv;
}


/**
 * Implements the Knuth-Morris-Pratt (KMP) pattern searching algorithm.
 *
 * Description:
 * This function searches for occurrences of a given pattern in a text using the KMP algorithm.
 * The KMP algorithm preprocesses the pattern to construct an LPS (Longest Proper Prefix which is also Suffix) array
 * which helps in searching the pattern in the text in a linear time complexity.
 *
 * Parameters:
 * - texto: The main text in which we want to search for the pattern.
 * - patron: The pattern we want to search within the text.
 *
 * Returns:
 * - A vector of integers representing starting positions (0-indexed) of all occurrences of the pattern in the text.
 *
 * Complexity:
 * - Time: O(n + m), where n is the length of the text and m is the length of the pattern.
 */
vector<int> kmp(string texto, string patron){
    vector<int> posMatch;
    vector<int> lpsv = lps(patron);
    int j = 0, i = 0;
    int n = texto.length();
    int m = patron.length();
    while (i < n){
        if (texto[i] == patron[j]){
            i++;
            j++;
            if (j == m){
                posMatch.push_back(i-m);
                j = lpsv[j-1];
            }
        }
        else{
            if (j == 0){
                i++;
            }
            else{
                j = lpsv[j-1];
            }
        }
    }
    return posMatch;
}

void printKMPOcurrences(vector<int> posMatch) {
    outFile << posMatch.size() << " veces" << endl;
    for(int i = 0; i < posMatch.size(); i++) {
        if(i == posMatch.size() - 1) {
            outFile << posMatch[i];
            outFile << endl;
        }
        else
            outFile << posMatch[i] << ", ";
    }
}


/**
 * Implements Manacher's algorithm to find the longest palindromic substring.
 *
 * Description:
 * This function identifies and prints the longest palindromic substring in the given string using Manacher's algorithm.
 * The algorithm preprocesses the string to accommodate even length palindromes and to simplify boundary checks.
 * It maintains a "center" and a "right boundary" for the current palindrome and iteratively expands palindromes around
 * the center, leveraging previously computed lengths to avoid redundant calculations.
 *
 * Parameters:
 * - s: The input string for which we want to determine the longest palindromic substring.
 *
 * Returns:
 * - None. The function prints the starting position and the content of the longest palindromic substring.
 *
 * Complexity:
 * - Time: O(N), where N is the length of the string.
 */
void manacher(string s) {
    int N = s.length();
    if(N == 0)
        return;

    N = 2*N + 1;
    int L[N];
    L[0] = 0;
    L[1] = 1;
    int C = 1; //centerPosition
    int R = 2; //centerRightPosition
    int i = 0; //currentRightPosition
    int iMirror; //currentLeftPosition
    int maxLPSLength = 0;
    int maxLPSCenterPosition = 0;
    int start = -1;
    int end = -1;
    int diff = -1;


    for (i = 2; i < N; i++)
    {
        iMirror = 2*C-i;
        L[i] = 0;
        diff = R - i;
        if(diff > 0)
            L[i] = min(L[iMirror], diff);


        while ( ((i + L[i]) < N && (i - L[i]) > 0) &&
                ( ((i + L[i] + 1) % 2 == 0) ||
                  (s[(i + L[i] + 1)/2] == s[(i - L[i] - 1)/2] )))
        {
            L[i]++;
        }

        if(L[i] > maxLPSLength) // Track maxLPSLength
        {
            maxLPSLength = L[i];
            maxLPSCenterPosition = i;
        }

        //If palindrome centered at currentRightPosition i
        //expand beyond centerRightPosition R,
        //adjust centerPosition C based on expanded palindrome.
        if (i + L[i] > R)
        {
            C = i;
            R = i + L[i];
        }
    }


    start = (maxLPSCenterPosition - maxLPSLength)/2;
    end = start + maxLPSLength - 1;

    outFile << "Posición: " << start << endl;
    for(i=start; i<=end; i++)
        outFile << s[i];

    outFile << endl;
}


/**
 * Finds the Longest Common Substring (LCSubstr) between two strings.
 *
 * Description:
 * This function determines the longest substring that is common to both the given strings using a dynamic programming approach.
 * It constructs a 2D array (lcs) to store the length of the LCSubstr considering the strings up to the respective indices.
 * The function iterates through both strings and populates the 2D array based on character matches, tracking the longest substring found.
 *
 * Parameters:
 * - s1: The first string.
 * - s2: The second string.
 *
 * Returns:
 * - The longest common substring of s1 and s2. If there are multiple substrings of the same maximum length, it returns the first one encountered.
 *
 * Complexity:
 * - Time: O(m * n), where m is the length of the first string and n is the length of the second string.
 */
string longestSubstring(string s1, string s2) {
    int lenS1 = s1.length(), lenS2 = s2.length(), max = 0;
    string maxStr = "";

    vector<vector<int>> lcs(lenS1, vector<int>(lenS2, 0));

    // fill first col (s1)
    for(int i = 0; i < lenS1; i++) {
        if(s1[i] == s2[0]) {
            lcs[i][0] = 1;
            max = 1;
        }
    }

    // fill first row (s2)
    for(int j = 0; j < lenS2; j++) {
        if(s1[0] == s2[j]) {
            lcs[0][j] = 1;
            max = 1;
        }
    }

    int actual;
    for(int i = 1; i < lenS1; i++) {
        for(int j = 1; j < lenS2; j++) {
            if(s1[i] == s2[j]) {
                actual = lcs[i-1][j-1] + 1;
                lcs[i][j] = actual;
                if(actual > max) {
                    max = actual;
                    maxStr = s1.substr(i - actual + 1, actual);
                }
            }
        }
    }

    return maxStr;
}


/**
 * Finds the Most Frequent Subsequence in Transmission Files.
 *
 * Description:
 * This function searches for the subsequence of a given code within a collection of transmission files.
 * It generates all possible subsequences of the input code and counts their occurrences in each transmission file.
 * The function tracks the subsequence with the highest number of occurrences and returns it along with the count.
 *
 * Parameters:
 * - code: The input code for which subsequences are generated and searched.
 * - transmissions: A vector of transmission files where occurrences are counted.
 *
 * Returns:
 * - A pair containing the most frequent subsequence found and its corresponding occurrence count.
 *
 * Complexity:
 * - Time: O(n * m * k), where:
 *   - "n" is the length of the input code string.
 *   - "m" is the average length of transmission files.
 *   - "k" is the number of transmission files.
 */

pair<pair<string, int>, int> findMostFrequentSubsequence(string code, vector<string> transmissions) {
    map<string, int> subsequenceCounts;

    // Generate all possible subsequences and initialize their counts to 0.
    for (int i = 0; i < code.length(); i++) {
        string subsequence = code.substr(0, i) + code.substr(i + 1);
        subsequenceCounts[subsequence] = 0;
    }

    int maxOccurrences = 0;
    int maxOccurrencesFile = -1; // Initialize with an invalid value
    vector<string> mostFrequentSubsequences;

    // Iterate through each transmission file.
    for (int j = 0; j < transmissions.size(); j++) {
        for (const auto& entry : subsequenceCounts) {
            vector<int> positions = kmp(transmissions[j], entry.first);
            int occurrences = positions.size();
            subsequenceCounts[entry.first] += occurrences;

            // Update maxOccurrences and the list of most frequent subsequences.
            if (occurrences > maxOccurrences) {
                maxOccurrences = occurrences;
                maxOccurrencesFile = j; // Update the file number
                mostFrequentSubsequences = {entry.first};
            } else if (occurrences == maxOccurrences) {
                mostFrequentSubsequences.push_back(entry.first);
            }
        }
    }

    // Return the most frequent subsequence and its number of occurrences, along with the file number.
    return make_pair(make_pair(mostFrequentSubsequences[0], maxOccurrences), maxOccurrencesFile);
}

int main() {
    vector<string> mcodes, transmissions;

    // read the files and store the data
    readMCodes(mcodes);
    readTransmission(transmissions, "./in/transmission1.txt");
    readTransmission(transmissions, "./in/transmission2.txt");
    readTransmission(transmissions, "./in/transmission3.txt");

    // for writing into the output file
    outFile.open("checking.txt");
    if(outFile.is_open()) {
        // 1. Occurrences of malicious codes in each file.
        for(int i = 0; i < mcodes.size(); i++) { // for each malicious code
            outFile << "Código: " << mcodes[i]    << endl;
            for(int j = 0; j < transmissions.size(); j++) { // for each tranmission
                outFile << "Transmission" << j+1 << ".txt ==> ";
                printKMPOcurrences(kmp(transmissions[j], mcodes[i]));
            }

            // Call function to find subsequence with most occurrences
            pair<pair<string, int>, int> result = findMostFrequentSubsequence(mcodes[i], transmissions);
            string mostFrequentSubsequence = result.first.first;
            int maxOccurrences = result.first.second;
            int maxOccurrencesFile = result.second;

            outFile << "La subsecuencia más encontrada es: " << mostFrequentSubsequence << " con "
                    << maxOccurrences << " veces en el archivo Transmission" << maxOccurrencesFile + 1 << ".txt" << endl;

            if(i != mcodes.size() - 1)
                outFile << "--------------" << endl;
        }


        outFile << "==============" << endl;


        // 2. largest palindrome
        outFile << "Palíndromo más grande:" << endl;
        for(int i = 0; i < transmissions.size(); i++) { // for each transmission
            outFile << "Transmission" << i+1 << ".txt ==> ";
            manacher(transmissions[i]);
            outFile << "----" << endl;
        }

        outFile << "==============" << endl;

        // 3. largest substring between files
        outFile << "Los Substring más largos son:" << endl;

        outFile << "T1-T2 ==> " << longestSubstring(transmissions[0], transmissions[1]) << endl;
        outFile << "T1-T3 ==> " << longestSubstring(transmissions[0], transmissions[2]) << endl;
        outFile << "T2-T3 ==> " << longestSubstring(transmissions[1], transmissions[2]) << endl;

        outFile.close();
    } else {
        cerr << "Unable to open the output file" << endl;
    }
    return 0;
}