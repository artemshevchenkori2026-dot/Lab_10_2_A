#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

//3
//Sydorenko 10555
//Petrenko 21545
//Kovalchuk 32555

using namespace std;

enum Spec { KN, INF, ME, FI, TN };
string specStr[] = { "Comp. Science", "Informatics", "Math & Econ.", "Phys. & Inf.", "Labor Educ." };

struct Student
{
    string prizv;
    unsigned kurs;
    Spec spec;
    int fizyka;
    int matematyka;
    int informatyka;
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
double GetAverage(const Student& s);
void Sort(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int BinSearch(Student* p, const int N, const string prizv, const Spec spec, const double avg);

int main()
{
    int N;
    do {
        cout << "Enter the number of students N (> 0): ";
        cin >> N;
        if (cin.fail() || N <= 0) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Invalid input! Please enter a positive integer." << endl;
            N = 0;
        }
    } while (N <= 0);

    Student* p = new Student[N];
    int* idxArr = nullptr;

    int ispec, found, menuItem;
    Spec spec;
    string prizv;
    double avg;

    do {
        cout << endl << endl;
        cout << "Select an action:" << endl;
        cout << " [1] - enter student data from keyboard" << endl;
        cout << " [2] - print student table" << endl;
        cout << " [3] - physical sorting (by avg grade, specialty, surname)" << endl;
        cout << " [4] - index sorting and print sorted table" << endl;
        cout << " [5] - binary search (by surname, specialty, avg grade)" << endl;
        cout << " [0] - exit" << endl << endl;
        cout << "Enter choice: ";
        cin >> menuItem;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            menuItem = -1;
        }
        cout << endl;

        switch (menuItem)
        {
        case 1: Create(p, N); break;
        case 2: Print(p, N); break;
        case 3:
            Sort(p, N);
            cout << "Array has been physically sorted." << endl;
            break;
        case 4:
            delete[] idxArr;
            idxArr = IndexSort(p, N);
            PrintIndexSorted(p, idxArr, N);
            break;
        case 5:
            cout << "Enter search keys:" << endl;
            do {
                cout << " specialty (0 - CS, 1 - INF, 2 - ME, 3 - PI, 4 - LE): ";
                cin >> ispec;
                if (cin.fail() || ispec < 0 || ispec > 4) {
                    cin.clear();
                    cin.ignore(32767, '\n');
                    cout << "Invalid specialty! Enter 0..4." << endl;
                    ispec = -1;
                }
            } while (ispec < 0 || ispec > 4);
            spec = (Spec)ispec;

            cin.ignore(32767, '\n');
            cout << " surname: ";
            getline(cin, prizv);

            do {
                cout << " average grade: ";
                cin >> avg;
                if (cin.fail() || avg < 0.0 || avg > 5.0) {
                    cin.clear();
                    cin.ignore(32767, '\n');
                    cout << "Invalid grade! Enter value between 0 and 5." << endl;
                    avg = -1.0;
                }
            } while (avg < 0.0 || avg > 5.0);

            found = BinSearch(p, N, prizv, spec, avg);
            if (found != -1)
                cout << "Student found at position #" << found + 1 << endl;
            else
                cout << "Student not found (make sure array is physically sorted first)." << endl;
            break;
        case 0: break;
        default: cout << "Invalid choice! Enter a menu number (0-5)." << endl;
        }
    } while (menuItem != 0);

    delete[] idxArr;
    delete[] p;
    return 0;
}

int InputGrade(const string& prompt)
{
    int grade;
    do {
        cout << prompt;
        cin >> grade;
        if (cin.fail() || grade < 1 || grade > 5) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Invalid grade! Please enter an integer from 1 to 5." << endl;
            grade = 0;
        }
    } while (grade < 1 || grade > 5);
    return grade;
}

void Create(Student* p, const int N)
{
    int spec;
    for (int i = 0; i < N; i++)
    {
        cout << "Student # " << i + 1 << ":" << endl;
        cin.ignore(32767, '\n');

        cout << " surname: ";
        getline(cin, p[i].prizv);

        do {
            cout << " course (1-6): ";
            cin >> p[i].kurs;
            if (cin.fail() || p[i].kurs < 1 || p[i].kurs > 6) {
                cin.clear();
                cin.ignore(32767, '\n');
                cout << "Invalid course! Enter 1..6." << endl;
                p[i].kurs = 0;
            }
        } while (p[i].kurs < 1 || p[i].kurs > 6);

        do {
            cout << " specialty (0 - CS, 1 - INF, 2 - ME, 3 - PI, 4 - LE): ";
            cin >> spec;
            if (cin.fail() || spec < 0 || spec > 4) {
                cin.clear();
                cin.ignore(32767, '\n');
                cout << "Invalid specialty! Enter 0..4." << endl;
                spec = -1;
            }
        } while (spec < 0 || spec > 4);
        p[i].spec = (Spec)spec;

        p[i].fizyka = InputGrade(" Physics grade (1-5): ");
        p[i].matematyka = InputGrade(" Mathematics grade (1-5): ");
        p[i].informatyka = InputGrade(" Informatics grade (1-5): ");
        cout << endl;
    }
}

double GetAverage(const Student& s)
{
    return (s.fizyka + s.matematyka + s.informatyka) / 3.0;
}

void Print(Student* p, const int N)
{
    cout << "==================================================================================" << endl;
    cout << "| No |    Surname    |Course|   Specialty   |Physics |Mathematics |Informatics |" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(2) << right << i + 1 << " "
            << "| " << setw(13) << left << p[i].prizv
            << "| " << setw(4) << right << p[i].kurs << " "
            << "| " << setw(13) << left << specStr[p[i].spec] << " "
            << "| " << setw(6) << right << p[i].fizyka << " "
            << "| " << setw(10) << right << p[i].matematyka << " "
            << "| " << setw(11) << right << p[i].informatyka << " |" << endl;
    }
    cout << "==================================================================================" << endl << endl;
}

void Sort(Student* p, const int N)
{
    Student tmp;
    const double EPS = 1e-5;
    for (int i0 = 0; i0 < N - 1; i0++)
    {
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
        {
            double avg1 = GetAverage(p[i1]);
            double avg2 = GetAverage(p[i1 + 1]);
            bool sameAvg = fabs(avg1 - avg2) < EPS;

            if ((avg1 > avg2 + EPS) ||
                (sameAvg && p[i1].spec > p[i1 + 1].spec) ||
                (sameAvg && p[i1].spec == p[i1 + 1].spec && p[i1].prizv > p[i1 + 1].prizv))
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
        }
    }
}

int* IndexSort(Student* p, const int N)
{
    int* I = new int[N];
    for (int i = 0; i < N; i++)
        I[i] = i;

    const double EPS = 1e-5;
    int i, j, value;
    for (i = 1; i < N; i++)
    {
        value = I[i];
        double avgVal = GetAverage(p[value]);

        for (j = i - 1; j >= 0; j--)
        {
            double avgJ = GetAverage(p[I[j]]);
            bool sameAvg = fabs(avgJ - avgVal) < EPS;

            if ((avgJ > avgVal + EPS) ||
                (sameAvg && p[I[j]].spec > p[value].spec) ||
                (sameAvg && p[I[j]].spec == p[value].spec && p[I[j]].prizv > p[value].prizv))
            {
                I[j + 1] = I[j];
            }
            else
                break;
        }
        I[j + 1] = value;
    }
    return I;
}

void PrintIndexSorted(Student* p, int* I, const int N)
{
    cout << "==================================================================================" << endl;
    cout << "| No |    Surname    |Course|   Specialty   |Physics |Mathematics |Informatics |" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(2) << right << i + 1 << " "
            << "| " << setw(13) << left << p[I[i]].prizv
            << "| " << setw(4) << right << p[I[i]].kurs << " "
            << "| " << setw(13) << left << specStr[p[I[i]].spec] << " "
            << "| " << setw(6) << right << p[I[i]].fizyka << " "
            << "| " << setw(10) << right << p[I[i]].matematyka << " "
            << "| " << setw(11) << right << p[I[i]].informatyka << " |" << endl;
    }
    cout << "==================================================================================" << endl << endl;
}

int BinSearch(Student* p, const int N, const string prizv, const Spec spec, const double avg)
{
    int L = 0, R = N - 1, m;
    const double EPS = 1e-2;

    do {
        m = (L + R) / 2;
        double mAvg = GetAverage(p[m]);
        bool sameAvg = fabs(mAvg - avg) < EPS;

        if (sameAvg && p[m].spec == spec && p[m].prizv == prizv)
            return m;

        if ((mAvg < avg - EPS) ||
            (sameAvg && p[m].spec < spec) ||
            (sameAvg && p[m].spec == spec && p[m].prizv < prizv))
            L = m + 1;
        else
            R = m - 1;
    } while (L <= R);

    return -1;
}