#include "pch.h"
#include "CppUnitTest.h"
#include "../pds_6/pds_6.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(TestReadGraph)
        {
            std::ofstream testInput("testInput.txt");
            testInput << "3 3\n1 2\n2 3\n3 1\n";
            testInput.close();

            int n, m;
            int** edges = nullptr;

            readGraph("testInput.txt", n, m, edges);

            Assert::AreEqual(3, n);
            Assert::AreEqual(3, m);
            Assert::AreEqual(1, edges[0][0]);
            Assert::AreEqual(2, edges[0][1]);
            Assert::AreEqual(2, edges[1][0]);
            Assert::AreEqual(3, edges[1][1]);
            Assert::AreEqual(3, edges[2][0]);
            Assert::AreEqual(1, edges[2][1]);

            for (int i = 0; i < m; ++i) {
                delete[] edges[i];
            }
            delete[] edges;
        }

        TEST_METHOD(TestCreateAdjacencyMatrix)
        {
            int n = 3, m = 3;
            int** edges = new int* [m];
            edges[0] = new int[2] {1, 2};
            edges[1] = new int[2] {2, 3};
            edges[2] = new int[2] {3, 1};

            int** adjacencyMatrix = createAdjacencyMatrix(n, m, edges);

            Assert::AreEqual(1, adjacencyMatrix[0][1]); // 1->2
            Assert::AreEqual(0, adjacencyMatrix[0][2]); // 1->3
            Assert::AreEqual(1, adjacencyMatrix[1][2]); // 2->3
            Assert::AreEqual(1, adjacencyMatrix[2][0]); // 3->1

            deleteMatrix(adjacencyMatrix, n);
            for (int i = 0; i < m; ++i) {
                delete[] edges[i];
            }
            delete[] edges;
        }

        TEST_METHOD(TestCreateIncidenceMatrix)
        {
            int n = 3, m = 3;
            int** edges = new int* [m];
            edges[0] = new int[2] {1, 2};
            edges[1] = new int[2] {2, 3};
            edges[2] = new int[2] {3, 1};

            int** incidenceMatrix = createIncidenceMatrix(n, m, edges);

            Assert::AreEqual(1, incidenceMatrix[0][0]);  
            Assert::AreEqual(-1, incidenceMatrix[1][0]); 
            Assert::AreEqual(0, incidenceMatrix[2][0]);  
            Assert::AreEqual(1, incidenceMatrix[1][1]);  
            Assert::AreEqual(-1, incidenceMatrix[2][1]); 
            Assert::AreEqual(1, incidenceMatrix[2][2]); 
            Assert::AreEqual(-1, incidenceMatrix[0][2]); 

            deleteMatrix(incidenceMatrix, n);
            for (int i = 0; i < m; ++i) {
                delete[] edges[i];
            }
            delete[] edges;
        }
	};
}