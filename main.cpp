/*
    Actividad Integradora 1 - TC2038
    Integrantes:
        Arturo Duran Castillo - A00833516
        Andrés Marcelo De Luna Pámanes - A00832239
    Fecha: 1 de octubre 2023
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


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
    cout << posMatch.size() << " veces" << endl;
    for(int i = 0; i < posMatch.size(); i++) {
        if(i == posMatch.size() - 1) {
            cout << posMatch[i];
            cout << endl;
        }
        else
            cout << posMatch[i] << ", ";
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

    cout << "Posición: " << start << endl;
    for(i=start; i<=end; i++)
        cout << s[i];

    cout << endl;
}


int main() {
    vector<string> mcodes, transmissions;

    // read the files and store the data
    readMCodes(mcodes);
    readTransmission(transmissions, "./in/transmission1.txt");
    readTransmission(transmissions, "./in/transmission2.txt");
    readTransmission(transmissions, "./in/transmission3.txt");


    // 1. Occurrences of malicious codes in each file.
    for(int i = 0; i < mcodes.size(); i++) { // for each malicious code
        cout << "Código: " << mcodes[i]    << endl;
        for(int j = 0; j < transmissions.size(); j++) { // for each tranmission
            cout << "Transmission" << j+1 << ".txt ==> ";
            printKMPOcurrences(kmp(transmissions[j], mcodes[i]));
        }
        cout << "--------------" << endl;
    }

    cout << "==============" << endl;

    // 2. largest palindrome
    cout << "Palíndromo más grande:" << endl;
    for(int i = 0; i < transmissions.size(); i++) { // for each transmission
        cout << "Transmission" << i+1 << ".txt ==> ";
        manacher(transmissions[i]);
        cout << "----" << endl;
    }

    return 0;
}