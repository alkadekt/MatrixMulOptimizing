#pragma once
#include "pch.h"

/// <summary>
/// Templated Matrix class.
/// </summary>
template <typename T, std::size_t Rows, std::size_t Cols>
struct Matrix : public std::array<std::array<T, Rows>, Cols>
{
};

/// <summary>
/// Matrix template specialization.
/// </summary>
template <std::size_t Rows, std::size_t Cols>
struct Matrix<float, Rows, Cols> : public std::array<std::array<float, Rows>, Cols>
{
	/// <summary>
	/// Simple matrix multiplication against rhs.
	/// </summary>
	template <std::size_t rhsCols>
	gsl::owner<Matrix<float, Rows, rhsCols>*> NaiveMultiply(const Matrix<float, Cols, rhsCols>* rhs);

	/// <summary>
	/// Transposes lhs matrix, then simple multiplication.
	/// </summary>
	template <std::size_t rhsCols>
	gsl::owner<Matrix<float, Rows, rhsCols>*> TransposeMultiply(const Matrix<float, Cols, rhsCols>* rhs);	

	/// <summary>
	/// Splits multiplication across multiple threads.
	/// </summary>
	template <std::size_t rhsCols>
	gsl::owner<Matrix<float, Rows, rhsCols>*> MultiThreadMultiply(const Matrix<float, Cols, rhsCols>* rhs, std::size_t threadCount = 4);

	/// <summary>
	/// Fills this Matrix with random values within a range.
	/// </summary>
	void Fill(float min, float max);

private:
	template <std::size_t rhsCols>
	static void ThreadDotFill(Matrix<float, Rows, rhsCols>* result, const Matrix<float, Rows, Cols>* lhs, 
		const Matrix<float, Cols, rhsCols>* rhs, std::size_t threadIndex, std::size_t threadCount);
};

#include "Matrix.inl"