#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_10_2_A/Lab_10_2_A.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest102A
{
    TEST_CLASS(UnitTest102A)
    {
    public:
        TEST_METHOD(TestSortAndBinSearchA)
        {
            const int N = 3;
            Student s[N];

            s[0] = { "Sydorenko", 1, KN, 5, 5, 5 };   // avg = 5.0, spec = KN (0)
            s[1] = { "Petrenko", 1, ME, 3, 4, 5 };    // avg = 4.0, spec = ME (2)
            s[2] = { "Kovalchuk", 2, INF, 4, 4, 4 };  // avg = 4.0, spec = INF (1)

            int* idx = IndexSort(s, N);
            Assert::AreEqual(2, idx[0]);
            Assert::AreEqual(1, idx[1]);
            Assert::AreEqual(0, idx[2]);
            delete[] idx;

            Sort(s, N);
            Assert::AreEqual(string("Kovalchuk"), s[0].prizv);
            Assert::AreEqual(string("Petrenko"), s[1].prizv);
            Assert::AreEqual(string("Sydorenko"), s[2].prizv);

            Assert::AreEqual(1, BinSearch(s, N, "Petrenko", ME, 4.0));
            Assert::AreEqual(2, BinSearch(s, N, "Sydorenko", KN, 5.0));
            Assert::AreEqual(-1, BinSearch(s, N, "Unknown", KN, 5.0));
        }
    };
}