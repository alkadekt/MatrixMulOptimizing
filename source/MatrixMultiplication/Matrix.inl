#include "Matrix.h"

template <std::size_t Rows, std::size_t Cols>
template <std::size_t rhsCols>
gsl::owner<Matrix<float, Rows, rhsCols>*> Matrix<float, Rows, Cols>::NaiveMultiply(const Matrix<float, Cols, rhsCols>* rhs)
{
	Matrix<float, Rows, rhsCols>* result = new Matrix<float, Rows, rhsCols>;
	for (std::size_t i = 0; i < rhsCols; ++i)
	{
		for (std::size_t j = 0; j < Rows; ++j)
		{
			(*result)[i][j] = 0;
			for (std::size_t k = 0; k < Cols; ++k)
			{
				(*result)[i][j] += (*this)[k][j] * (*rhs)[i][k];
			}
		}
	}
	return result;
}

template <std::size_t Rows, std::size_t Cols>
template <std::size_t rhsCols>
gsl::owner<Matrix<float, Rows, rhsCols>*> Matrix<float, Rows, Cols>::TransposeMultiply(const Matrix<float, Cols, rhsCols>* rhs)
{
	Matrix<float, Cols, Rows>* transposedLHS = new Matrix<float, Cols, Rows>;
	for (std::size_t i = 0; i < Cols; ++i)
	{
		for (std::size_t j = 0; j < Rows; ++j)
		{
			(*transposedLHS)[j][i] = (*this)[i][j];
		}
	}

	Matrix<float, Rows, rhsCols>* result = new Matrix<float, Rows, rhsCols>;
	for (std::size_t i = 0; i < rhsCols; ++i)
	{
		for (std::size_t j = 0; j < Rows; ++j)
		{
			(*result)[i][j] = 0;
			for (std::size_t k = 0; k < Cols; ++k)
			{
				(*result)[i][j] += (*transposedLHS)[j][k] * (*rhs)[i][k];
			}
		}
	}
	delete transposedLHS;
	return result;
}

template <std::size_t Rows, std::size_t Cols>
template <std::size_t rhsCols>
gsl::owner<Matrix<float, Rows, rhsCols>*> Matrix<float, Rows, Cols>::MultiThreadMultiply(const Matrix<float, Cols, rhsCols>* rhs, std::size_t threadCount)
{
	if (threadCount == 0)
	{
		throw std::runtime_error("threadCount must be greater than 0");
	}

	Matrix<float, Rows, rhsCols>* result = new Matrix<float, Rows, rhsCols>;
	std::vector<std::future<void>> futures;
	futures.reserve(threadCount);

	for (std::size_t b = 0; b < threadCount; ++b)
	{
		futures.emplace_back(std::async(std::launch::async, &Matrix::ThreadDotFill<rhsCols>, result, this, rhs, b, threadCount));
	}
	
	for (auto& fut : futures)
	{
		fut.wait();
	}
	return result;
}

template <std::size_t Rows, std::size_t Cols>
template <std::size_t rhsCols>
void Matrix<float, Rows, Cols>::ThreadDotFill(Matrix<float, Rows, rhsCols>* const result, const Matrix<float, Rows, Cols>* const lhs, 
	const Matrix<float, Cols, rhsCols>* const rhs, std::size_t threadIndex, std::size_t threadCount)
{
	for (std::size_t i = 0; i < rhsCols; ++i)
	{
		for (std::size_t j = threadIndex; j < Rows; j += threadCount)
		{
			(*result)[i][j] = 0;
			for (std::size_t k = 0; k < Cols; ++k)
			{
				(*result)[i][j] += (*lhs)[k][j] * (*rhs)[i][k];
			}
		}
	}
}

template <std::size_t Rows, std::size_t Cols>
void Matrix<float, Rows, Cols>::Fill(float min, float max)
{
	if (max == 0.0f)
	{
		throw std::runtime_error("max cannot be set to 0.");
	}

	for (std::size_t i = 0; i < Cols; ++i)
	{
		std::array<float, Rows>& column = this->at(i);
		for (std::size_t j = 0; j < Rows; ++j)
		{
			column[j] = fmodf(static_cast<float>(rand()), max - min) + min;
		}
	}
}
