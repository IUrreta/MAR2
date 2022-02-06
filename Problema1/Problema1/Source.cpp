
// Ignacio Urretavizcaya Tato

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


#include "Matriz.h"
#include "EnterosInf.h"
using namespace std;



// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...

/*
Matriz<bool> resolver1(std::vector<std::pair<int, int>> v, int l) {
	Matriz<bool> m(v.size() + 1, l + 1, false);
	m[0][0] = true;
	for (int i = 1; i <= v.size(); i++) {
		m[i][0] = true;
		for (int j = 1; j <= l; j++) {
			if (v[i - 1].first > j) m[i][j] = m[i - 1][j];
			else m[i][j] = (m[i - 1][j] || m[i - 1][j - v[i - 1].first]);
		}
	}
	return m;
}
*/


vector<bool> resolver1(std::vector<std::pair<int, int>> v, int l) {
	vector<bool> sol(l + 1, false);
	sol[0] = true;
	for (int i = 1; i <= v.size(); i++) {
		for (int j = l; j >= 1; j--) {
			if (v[i - 1].first > j) sol[j] = sol[j];
			else sol[j] = (sol[j] || sol[j - v[i - 1].first]);

		}
	}
	return sol;
}


/*
Matriz<int> resolver2(std::vector<std::pair<int, int>> v, int l) {
	Matriz<int> m(v.size() + 1, l + 1, 0);
	for (int i = 1; i <= v.size(); i++) {
		for (int j = 1; j <= l; j++) {
			m[i][0] = 1;
			if (v[i - 1].first > j) m[i][j] = m[i - 1][j];
			else if (v[i - 1].first == j) m[i][j] = m[i - 1][j] + 1;
			else m[i][j] = m[i - 1][j] + m[i - 1][j - v[i - 1].first];
			
		}
	}
	return m;
}

*/

vector<int> resolver2(std::vector<std::pair<int, int>> v, int l) {
	vector<int> sol(l + 1, 0);
	sol[0] = 1;
	for (int i = 1; i <= v.size(); i++) {
		for (int j = l; j >= 1; j--) {
			if (v[i - 1].first > j) sol[j] = sol[j];
			else sol[j] = sol[j] + sol[j-v[i - 1].first];

		}
	}
	return sol;
}


/*
Matriz<EntInf> resolver3(std::vector<std::pair<int, int>> v, int l) {
	Matriz<EntInf> m(v.size() + 1, l + 1, Infinito);
	for (int i = 1; i <= v.size(); i++) {
		for (int j = 1; j <= l; j++) {
			m[i][0] = 0;
			if (v[i - 1].first > j) m[i][j] = m[i - 1][j];
			else m[i][j] = min(m[i - 1][j], m[i - 1][j - v[i - 1].first] + 1);

		}
	}
	return m;

}

*/

vector<EntInf> resolver3(std::vector<std::pair<int, int>> v, int l) {
	vector<EntInf> sol(l + 1, Infinito);
	sol[0] = 0;
	for (int i = 1; i <= v.size(); i++) {
		for (int j = l; j >= 1; j--) {
			if (v[i - 1].first > j) sol[j] = sol[j];
			else sol[j] = min(sol[j], sol[j - v[i - 1].first] + 1);

		}
	}
	return sol;

}

/*
Matriz<EntInf> resolver4(std::vector<std::pair<int, int>> v, int l) {
	Matriz<EntInf> m(v.size() + 1, l + 1, Infinito);
	for(int i = 1; i <= v.size(); i++) {
		for (int j = 1; j <= l; j++) {
			m[i][0] = 0;
			if (v[i - 1].first > j) m[i][j] = m[i - 1][j];
			else m[i][j] = min(m[i - 1][j], m[i - 1][j - v[i - 1].first] + v[i - 1].second);
		}
	} 
	return m;
}
*/

vector<EntInf> resolver4(std::vector<std::pair<int, int>> v, int l) {
	vector<EntInf> sol(l + 1, Infinito);
	sol[0] = 0;
	for (int i = 1; i <= v.size(); i++) {
		for (int j = l; j >= 1; j--) {
			if (v[i - 1].first > j) sol[j] = sol[j];
			else sol[j] = min(sol[j], sol[j - v[i - 1].first] + v[i - 1].second);
		}
	}
	return sol;
}


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	// leer los datos de la entrada
	int n;
	std::cin >> n;

	if (!std::cin)  // fin de la entrada
		return false;

	int longitud;
	std::cin >> longitud;
	std::vector<std::pair<int, int>> datos;
	int a, b;


	for (int i = 0; i < n; i++) {
		std::cin >> a;
		std::cin >> b;
		datos.push_back({ a,b });

	}

	if (longitud == 0) cout << "SI" << '\n';
	else if (datos.size() == 0) cout << "NO" << '\n';
	else {

		//Matriz<bool> sol = resolver1(datos, longitud);
		vector<bool> solv = resolver1(datos, longitud);
		



		if (solv[longitud]) {
			cout << "SI ";
			vector<int> sol2 = resolver2(datos, longitud);
			vector<EntInf> sol3 = resolver3(datos, longitud);
			vector<EntInf> sol4 = resolver4(datos, longitud);

			cout << sol2[longitud] << " " << sol3[longitud] << " " << sol4[longitud] <<'\n';
		}
		else cout << "NO" << '\n';
	}
	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
