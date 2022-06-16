#include "pch.h"
#include "CppUnitTest.h"
#include "Matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatrixMultiplicationTests
{
	TEST_CLASS(MatrixMultiplicationTests)
	{
	public:	
        TEST_METHOD_INITIALIZE(Initialize)
        {
#if defined(_DEBUG)
            _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
            _CrtMemCheckpoint(&_startMemState);
#endif
        }

        TEST_METHOD_CLEANUP(Cleanup)
        {
#if defined(_DEBUG)
            _CrtMemState endMemState, diffMemState;
            _CrtMemCheckpoint(&endMemState);
            if (_CrtMemDifference(&diffMemState, &_startMemState, &endMemState))
            {
                _CrtMemDumpStatistics(&diffMemState);
                //Assert::Fail(L"There was a memory leak.");
            }
#endif
        }

        TEST_METHOD(NaiveMatrixMultiplication)
        {
            {
                Matrix<float, 2, 3>* matrix1 = new Matrix<float, 2, 3>;
                Matrix<float, 3, 1>* matrix2 = new Matrix<float, 3, 1>;

                (*matrix1)[0][0] = 1;
                (*matrix1)[1][0] = 2;
                (*matrix1)[2][0] = 3;
                (*matrix1)[0][1] = 4;
                (*matrix1)[1][1] = 5;
                (*matrix1)[2][1] = 6;

                (*matrix2)[0][0] = 1;
                (*matrix2)[0][1] = 2;
                (*matrix2)[0][2] = 3;

                Matrix<float, 2, 1>* result = matrix1->NaiveMultiply(matrix2);

                Assert::AreEqual(14.0f, (*result)[0][0]);
                Assert::AreEqual(32.0f, (*result)[0][1]);

                delete matrix1;
                delete matrix2;
                delete result;
            }

            {
                Matrix<float, 2, 3>* matrix1 = new Matrix<float, 2, 3>;
                Matrix<float, 3, 4>* matrix2 = new Matrix<float, 3, 4>;

                (*matrix1)[0][0] = 1;
                (*matrix1)[1][0] = 2;
                (*matrix1)[2][0] = 3;
                (*matrix1)[0][1] = 4;
                (*matrix1)[1][1] = 5;
                (*matrix1)[2][1] = 6;

                (*matrix2)[0][0] = 1;
                (*matrix2)[0][1] = 2;
                (*matrix2)[0][2] = 3;
                (*matrix2)[1][0] = 4;
                (*matrix2)[1][1] = 5;
                (*matrix2)[1][2] = 6;
                (*matrix2)[2][0] = 7;
                (*matrix2)[2][1] = 8;
                (*matrix2)[2][2] = 9;
                (*matrix2)[3][0] = 10;
                (*matrix2)[3][1] = 11;
                (*matrix2)[3][2] = 12;

                Matrix<float, 2, 4>* result = matrix1->NaiveMultiply(matrix2);

                Assert::AreEqual(14.0f, (*result)[0][0]);
                Assert::AreEqual(32.0f, (*result)[0][1]);
                Assert::AreEqual(32.0f, (*result)[1][0]);
                Assert::AreEqual(77.0f, (*result)[1][1]);
                Assert::AreEqual(50.0f, (*result)[2][0]);
                Assert::AreEqual(122.0f, (*result)[2][1]);
                Assert::AreEqual(68.0f, (*result)[3][0]);
                Assert::AreEqual(167.0f, (*result)[3][1]);

                delete matrix1;
                delete matrix2;
                delete result;
            }
        }

        TEST_METHOD(TransposeMatrixMultiplication)
        {
            {
                Matrix<float, 2, 3>* matrix1 = new Matrix<float, 2, 3>;
                Matrix<float, 3, 1>* matrix2 = new Matrix<float, 3, 1>;

                (*matrix1)[0][0] = 1;
                (*matrix1)[1][0] = 2;
                (*matrix1)[2][0] = 3;
                (*matrix1)[0][1] = 4;
                (*matrix1)[1][1] = 5;
                (*matrix1)[2][1] = 6;

                (*matrix2)[0][0] = 1;
                (*matrix2)[0][1] = 2;
                (*matrix2)[0][2] = 3;

                Matrix<float, 2, 1>* result = matrix1->TransposeMultiply(matrix2);

                Assert::AreEqual(14.0f, (*result)[0][0]);
                Assert::AreEqual(32.0f, (*result)[0][1]);

                delete matrix1;
                delete matrix2;
                delete result;
            }

            {
                Matrix<float, 2, 3>* matrix1 = new Matrix<float, 2, 3>;
                Matrix<float, 3, 4>* matrix2 = new Matrix<float, 3, 4>;

                (*matrix1)[0][0] = 1;
                (*matrix1)[1][0] = 2;
                (*matrix1)[2][0] = 3;
                (*matrix1)[0][1] = 4;
                (*matrix1)[1][1] = 5;
                (*matrix1)[2][1] = 6;

                (*matrix2)[0][0] = 1;
                (*matrix2)[0][1] = 2;
                (*matrix2)[0][2] = 3;
                (*matrix2)[1][0] = 4;
                (*matrix2)[1][1] = 5;
                (*matrix2)[1][2] = 6;
                (*matrix2)[2][0] = 7;
                (*matrix2)[2][1] = 8;
                (*matrix2)[2][2] = 9;
                (*matrix2)[3][0] = 10;
                (*matrix2)[3][1] = 11;
                (*matrix2)[3][2] = 12;

                Matrix<float, 2, 4>* result = matrix1->TransposeMultiply(matrix2);

                Assert::AreEqual(14.0f, (*result)[0][0]);
                Assert::AreEqual(32.0f, (*result)[0][1]);
                Assert::AreEqual(32.0f, (*result)[1][0]);
                Assert::AreEqual(77.0f, (*result)[1][1]);
                Assert::AreEqual(50.0f, (*result)[2][0]);
                Assert::AreEqual(122.0f, (*result)[2][1]);
                Assert::AreEqual(68.0f, (*result)[3][0]);
                Assert::AreEqual(167.0f, (*result)[3][1]);

                delete matrix1;
                delete matrix2;
                delete result;
            }
        }

        TEST_METHOD(MultiThreadMatrixMultiplication)
        {
            {
                Matrix<float, 2, 3>* matrix1 = new Matrix<float, 2, 3>;
                Matrix<float, 3, 1>* matrix2 = new Matrix<float, 3, 1>;

                (*matrix1)[0][0] = 1;
                (*matrix1)[1][0] = 2;
                (*matrix1)[2][0] = 3;
                (*matrix1)[0][1] = 4;
                (*matrix1)[1][1] = 5;
                (*matrix1)[2][1] = 6;

                (*matrix2)[0][0] = 1;
                (*matrix2)[0][1] = 2;
                (*matrix2)[0][2] = 3;

                Matrix<float, 2, 1>* result = matrix1->MultiThreadMultiply(matrix2);

                Assert::AreEqual(14.0f, (*result)[0][0]);
                Assert::AreEqual(32.0f, (*result)[0][1]);

                delete matrix1;
                delete matrix2;
                delete result;
            }

            {
                Matrix<float, 2, 3>* matrix1 = new Matrix<float, 2, 3>;
                Matrix<float, 3, 4>* matrix2 = new Matrix<float, 3, 4>;

                (*matrix1)[0][0] = 1;
                (*matrix1)[1][0] = 2;
                (*matrix1)[2][0] = 3;
                (*matrix1)[0][1] = 4;
                (*matrix1)[1][1] = 5;
                (*matrix1)[2][1] = 6;

                (*matrix2)[0][0] = 1;
                (*matrix2)[0][1] = 2;
                (*matrix2)[0][2] = 3;
                (*matrix2)[1][0] = 4;
                (*matrix2)[1][1] = 5;
                (*matrix2)[1][2] = 6;
                (*matrix2)[2][0] = 7;
                (*matrix2)[2][1] = 8;
                (*matrix2)[2][2] = 9;
                (*matrix2)[3][0] = 10;
                (*matrix2)[3][1] = 11;
                (*matrix2)[3][2] = 12;

                Matrix<float, 2, 4>* result = matrix1->MultiThreadMultiply(matrix2);

                Assert::AreEqual(14.0f, (*result)[0][0]);
                Assert::AreEqual(32.0f, (*result)[0][1]);
                Assert::AreEqual(32.0f, (*result)[1][0]);
                Assert::AreEqual(77.0f, (*result)[1][1]);
                Assert::AreEqual(50.0f, (*result)[2][0]);
                Assert::AreEqual(122.0f, (*result)[2][1]);
                Assert::AreEqual(68.0f, (*result)[3][0]);
                Assert::AreEqual(167.0f, (*result)[3][1]);

                delete matrix1;
                delete matrix2;
                delete result;
            }
        }

    private:
        static _CrtMemState _startMemState;
	};

    _CrtMemState MatrixMultiplicationTests::_startMemState;
}
