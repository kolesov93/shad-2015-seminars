#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::istream;
using std::ostream;

class Solver {
public:
	typedef int size_type;

public:
	void Processing(istream& inputStream, ostream& outputStream);

private:
	void inputData(istream& inputStream);
	void solve();
	void outputData(ostream& outputStream) const;

private:
	std::vector<std::vector<int> > color;
	std::vector<std::vector<int> > graph;
	std::vector<int> l, r, d, u;
	int n;
	std::vector<bool> used;
	std::vector<int> answer;

private:
	void find_borders();
	void create_graph();
	int upper(int ll, int rr, int uu, int dd, int col1, int col2);
	void dfs(int v);
	void topological_sort();
};

Solver solver;

void Solver::Processing(istream& inputStream, ostream& outputStream) {
	inputData(inputStream);
	solve();
	outputData(outputStream);
}


void Solver::inputData(istream& inputStream) {
	inputStream >> n;
	color.resize(n);
	for (size_type i = 0; i < n; ++i) {
		color[i].resize(n);
		for (size_type j = 0; j < n; ++j) {
			inputStream >> color[i][j];
		}
	}
}

void Solver::outputData(ostream& outputStream) const {
	for (size_type i = 1; i < answer.size(); ++i) {
		outputStream << answer[i] << " " << u[answer[i]]+1 << " ";
		outputStream << l[answer[i]]+1 << " " << d[answer[i]]+1 << " ";
		outputStream << r[answer[i]]+1 << "\n";
	}
}

void Solver::find_borders() {
	l.resize(n + 1);
	r.resize(n + 1);
	d.resize(n + 1);
	u.resize(n + 1);
	l[0] = u[0] = 0;
	r[0] = d[0] = n - 1;

	for (size_type i = 1; i <= n; ++i) {
		l[i] = u[i] = n - 1;
	}

	int x = 0;
	int y = 0;
	for (size_type i = 0; i < n; ++i) {
		for (size_type j = 0; j < n; ++j) {
			if (j < l[color[i][j]]) l[color[i][j]] = j;
			if (j > r[color[i][j]]) r[color[i][j]] = j;
			if (i < u[color[i][j]]) u[color[i][j]] = i;
			if (i > d[color[i][j]]) d[color[i][j]] = i;
			if (color[i][j]) { x = i; y = j; }
		}
	}

	for (size_type i = 1; i <= n; ++i) {
		if (l[i] > r[i]) {
			l[i] = r[i] = y;
			u[i] = d[i] = x;
		}
	}
}

int iters = 0;
int Solver::upper(int ll, int rr, int uu, int dd, int col1, int col2) {
	int col = 0;
	for (size_type i = uu; i <= dd; ++i) {
		for (size_type j = ll; j <= rr; ++j) {
            ++iters;
			if (color[i][j] == col1) return col1;
			if (color[i][j] == col2) return col2;
		}
	}
	return col;
}

void Solver::create_graph() {
	graph.resize(n + 1);
	for (size_type i = 1; i <= n; ++i) {
		graph[0].push_back(i);
	}

	for (size_type i = 1; i < n; ++i) {
		for (size_type j = i + 1; j <= n; ++j) {
			int col = upper(std::max(l[i], l[j]), std::min(r[i], r[j]),
				std::max(u[i], u[j]), std::min(d[i], d[j]), i, j);
			if (col == i) graph[j].push_back(i);
			if (col == j) graph[i].push_back(j);
		}
	}
}

void Solver::dfs(int v) {
	used[v] = true;
	for (size_type i = 0; i < graph[v].size(); ++i) {
		if (!used[graph[v][i]])
			dfs(graph[v][i]);
	}
	answer.push_back(v);
}

void Solver::topological_sort() {
	for (size_type i = 0; i <= n; ++i)
		used[i] = false;
	answer.clear();
	for (size_type i = 0; i <= n; ++i) {
		if (!used[i])
			dfs(i);
	}
	reverse(answer.begin(), answer.end());
}

void Solver::solve() {
	find_borders();
	create_graph();

	used.resize(n + 1);
	topological_sort();
}

int main() {
	solver.Processing(std::cin, std::cout);
    std::cerr << iters << std::endl;

	return 0;
}

