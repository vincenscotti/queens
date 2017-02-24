#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

template <typename T, size_t Side>
using Matrix = array<array<T, Side>, Side>;

enum class Cell {
	Empty,
	Queen,
	Busted,
};

const map<Cell, char> cellNames = {
	{ Cell::Empty, '_', },
	{ Cell::Queen, 'Q', },
	{ Cell::Busted, 'x', },
};

template <size_t Sides, size_t NumQueens>
class Board;

template <size_t Sides, size_t NumQueens>
ostream &operator <<(ostream &o, const Board<Sides, NumQueens> &b);

template <size_t Sides, size_t NumQueens>
class Board
{
public:
	Board()
	{
		for_each(_mat.begin(), _mat.end(), [] (auto &row) {
			row.fill(Cell::Empty);
		});
	}

	vector<Board> nextMoves() const
	{
		vector<Board> ret;

		for (size_t i = 0; i < Sides; i++) {
			for (size_t j = 0; j < Sides; j++) {
				if (_mat[i][j] == Cell::Empty) {
					Board newb = *this;
					newb._mat[i][j] = Cell::Queen;

					// bust vertical

					for (size_t k = 0; k < i; k++) {
						if (newb._mat[k][j] != Cell::Queen) {
							newb._mat[k][j] = Cell::Busted;
						}
					}

					for (size_t k = i; k < Sides; k++) {
						if (newb._mat[k][j] != Cell::Queen) {
							newb._mat[k][j] = Cell::Busted;
						}
					}

					// bust horizontal

					for (size_t k = 0; k < j; k++) {
						if (newb._mat[i][k] != Cell::Queen) {
							newb._mat[i][k] = Cell::Busted;
						}
					}

					for (size_t k = j; k < Sides; k++) {
						if (newb._mat[i][k] != Cell::Queen) {
							newb._mat[i][k] = Cell::Busted;
						}
					}

					// bust first diagonal

					for (ssize_t r = i, c = j; r >= 0 && c >= 0; r--, c--) {
						if (newb._mat[r][c] != Cell::Queen) {
							newb._mat[r][c] = Cell::Busted;
						}
					}

					for (size_t r = i, c = j; r < Sides && c < Sides; r++, c++) {
						if (newb._mat[r][c] != Cell::Queen) {
							newb._mat[r][c] = Cell::Busted;
						}
					}

					// bust second diagonal

					for (ssize_t r = (ssize_t) i, c = (ssize_t) j; r >= 0 && c < Sides; r--, c++) {
						if (newb._mat[r][c] != Cell::Queen) {
							newb._mat[r][c] = Cell::Busted;
						}
					}

					for (ssize_t r = (ssize_t) i, c = (ssize_t) j; r < Sides && c >= 0; r++, c--) {
						if (newb._mat[r][c] != Cell::Queen) {
							newb._mat[r][c] = Cell::Busted;
						}
					}

					ret.push_back(newb);
				}
			}
		}

		return ret;
	}

	bool winner() const
	{
		int q = 0;

		for_each(_mat.begin(), _mat.end(), [&q] (const auto &row) {
			for_each(row.begin(), row.end(), [&q] (const auto &elem) {
				if (elem == Cell::Queen) {
					q++;
				}
			});
		});

		return q == NumQueens;
	}

	friend ostream &operator << <Sides, NumQueens>(ostream &o, const Board &b);

private:
	Matrix<Cell, Sides> _mat;
};

template <size_t Sides, size_t NumQueens>
ostream &operator <<(ostream &o, const Board<Sides, NumQueens> &b)
{
	for_each(b._mat.begin(), b._mat.end(), [&o] (const auto &col) {
		for_each(col.begin(), col.end(), [&o] (const auto &elem) {
			o << cellNames.at(elem) << ' ';
		});
		cout << endl;
	});

	return o;
}

template <size_t Sides, size_t NumQueens>
vector<Board<Sides, NumQueens>> run(const Board<Sides, NumQueens> &b, vector<Board<Sides, NumQueens>> &v = vector<Board<Sides, NumQueens>>())
{
	if (b.winner()) {
		v.push_back(b);
//		cout << b << endl;
	} else {
		for (const auto &nb : b.nextMoves()) {
			run(nb, v);
		}
	}

	return v;
}

constexpr size_t sides = 7;
constexpr size_t queens = 7;
using BoardT = Board<sides, queens>;

int main()
{
	BoardT b;
	vector<BoardT> winners;

	cout << boolalpha;
//	auto nms = b.nextMoves();
//	for (const auto &nm : nms) {
//		cout << nm << endl;
//	}
	run(b, winners);

	for (const auto &wb : winners) {
		cout << wb.winner() << endl;
	}

	return 0;
}
