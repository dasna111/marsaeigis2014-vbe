#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <locale>

using namespace std;

const char info[] = "info.txt";
const char res[] = "results.txt";
const int CMax = 124;      // max number of commands
const int SeqMax = 30;     // max number of sequence

struct Command {
    string stopRea;                                                      // reason why stopped
    bool arrived;                                                            // does it reach destination
    int AllSeq[SeqMax];                                                      // all sequence
    int k;                                                                      // length of sequence
    int executedCommands[SeqMax];                                             // sequence that has been used
    int amount;                                                                   // number of commands that were done
};

void Reading(Command A[], int& n, int& x0, int& y0);                          // reading from the file
void CommandsExecution(int kIndex, int& x1, int& y1);                            // execution of one command (movement)
void SequencesExecution(Command B, int & x0, int & y0, int x1, int y1);              // whole line execution
void Execution(Command A[], int x0, int y0, int & x1, int & y1, int n);          // main execution
void Writing(Command A[], int n);                                               // writing to the file

int main() {
    int x0, y0;             // basics cordination
    int x1, y1;             // destination cordination
    int n;                  // number of executed sequences
    Command A[CMax];

    Reading(A, n, x0, y0);
    Execution(A, x0, y0, x1, y1, n);
    Writing(A, n);
    return 0;
}


void Reading(Command A[], int& n, int& x0, int& y0)
{
    ifstream fd (info);
    fd>> x0 >> y0;          // basics cordination
    fd>>n;                  // number of executed sequences
    for (int i = 0; i < n; i++) {
            fd >> A[i].k;
            A[i].amount = 0;                                // number of executed commands
            A[i].arrived = false;                           // destination not achieved
            for (int j = 0; j < A[i].k; j++)
                fd >> A[i].AllSeq[j];
        }
    fd.close();
}
void Execution(Command A[], int x0, int y0, int & x1, int & y1, int n)
{
    x1 = x0;    y1 = y0;
    for (int i = 0; i < n; i++) {
        x1 = x0;    y1 = y0;        // coming back to begining
        SequencesExecution(A[i], x0, y0, x1, y1);
    }
}
void SequencesExecution(Command A, int & x0, int & y0, int x1, int y1)
{
    for (int i = 0; i < A.k; i++)
    {
        CommandsExecution(A.AllSeq[i], x0, y0);        // first execution
        
        A.CommandsExecution[A.amount] = A.AllSeq[i];    // execution writing in to executed commands array
        A.amount++;                                       // increasing number of commands
        
        if ((x0 == x1) && (y0 == y1)) {                 // checking if destination reached
            A.arrived = true;
            A.stopRea = "destination reached";     // stop reason "destination reached"
            break;
        }
    }
    if (!A.arrived)                                  // if havent reach destination
        A.stopRea= "sequence ended";             // prints in result file "sequence ended"
}
void CommandsExecution(int kIndex, int & x1, int & y1)
{
    if (kIndex == 1)        // moving up
    {
        y1++;
        x1++;
    }
    else if (kIndex == 2)   // moving to the right
    {
        x1++;
        y1--;
    }
    else if (kIndex == 3)   // moving down
    {
        x1--;
        y1--;
    }
    else if (kIndex == 4)   //moving to the left
    {
        y1++;
        x1--;
    }
}
void Writing(Command A[], int n) {
    ofstream fr(res);
        for (int i = 0; i < n; i++)
            {
            fr << left << setw(20) << A[i].stopRea
            for (int j = 0; j < A[i].amount; j++)
                fr << A[i].executedCommands[j] << " ";
            fr << A[i].amount << endl;
        }
    fr.close();
}
