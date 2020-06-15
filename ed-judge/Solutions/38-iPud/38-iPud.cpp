#include <iostream>
#include <unordered_map>
#include <list>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

typedef string Cancion;
typedef string Artista;

struct InfoCancion {

	int duracion;
	Artista artista;

	list<Cancion>::iterator itPlaylist;
	list<Cancion>::iterator itPlayed;

	InfoCancion(int duracion,
				const Artista &artista,
				const list<Cancion>::iterator &itPlaylist,
				const list<Cancion>::iterator &itPlayed)
		: duracion(duracion), artista(artista), itPlaylist(itPlaylist), itPlayed(itPlayed)
	{}

	InfoCancion()
	{}
};

class iPud {

private:

	unordered_map<Cancion, InfoCancion> db;
	list<Cancion> playlist;
	list<Cancion> played;

	int playlistTotalTime = 0;

public:

	void addSong(const Cancion& c, const Artista& a, int duration) {
		auto[it, succeed] = db.insert({c, {duration, a, playlist.end(), played.end()} });
		if(!succeed) {
			throw domain_error("");
		}
	}

	void addToPlaylist(const Cancion& c) {

		auto it = db.find(c);

		if(it == db.end()) {
			throw domain_error("");
		}

		auto& info = it->second;

		if(info.itPlaylist == playlist.end()) {
			info.itPlaylist = playlist.insert(playlist.end(), c);
			playlistTotalTime += info.duracion;
		}

	}

	Cancion current() const {
		if(playlist.empty()) {
			throw domain_error("");
		}

		return playlist.front();
	}

	void play() {
		if(playlist.empty()) {
			return;
		}

		auto cancion = playlist.front();
		auto& info = db[cancion];

		playlist.pop_front();
		info.itPlaylist = playlist.end();

		if(info.itPlayed != played.end()) {
			//Already played before
			played.erase(info.itPlayed);
		}

		info.itPlayed = played.insert(played.begin(), cancion);
		playlistTotalTime -= info.duracion;
	}

	int totalTime() const {
		return playlistTotalTime;
	}

	vector<Cancion> recent(size_t n) {
		vector<Cancion> v;

		int num = min(n, played.size());

		auto it = played.begin();
		for(int i = 0; i < num; ++i, ++it ) {
			v.push_back(*it);
		}

		return v;
	}

	void deleteSong(const Cancion& c) {
		auto it = db.find(c);

		if(it == db.end()) {
			return;
		}

		auto& info = it->second;

		if(info.itPlayed != played.end()) {
			played.erase(info.itPlayed);
		}

		if(info.itPlaylist != playlist.end()) {
			playlist.erase(info.itPlaylist);
			playlistTotalTime -= it->second.duracion;
		}

		db.erase(it);
	}

};

int main()
{
	string operation;
	iPud P;

	while(cin >> operation) {
		try {
			if(operation == "FIN") {
				P = {};
				cout << "---" << endl;
			} else if(operation == "addSong") {
				Cancion c;
				Artista a;
				int d;

				cin >> c >> a >> d;

				P.addSong(c, a, d);
			} else if(operation == "addToPlaylist") {
				Cancion c;
				cin >> c;

				P.addToPlaylist(c);
			} else if(operation == "current") {

				//Call this for the side effects
				volatile auto res = P.current();

			} else if(operation == "play") {

				try {
					auto cancion = P.current();
					P.play();

					cout << "Sonando " << cancion << endl;

				} catch (exception& e) {
					cout << "No hay canciones en la lista" << endl;
				}

			} else if(operation == "totalTime") {

				auto time = P.totalTime();
				cout << "Tiempo total " << time << endl;

			} else if (operation == "recent") {
				int n;
				cin >> n;

				auto v = P.recent(n);

				if(v.empty()) {
					cout << "No hay canciones recientes" << endl;
				} else {
					cout << "Las " << v.size() << " mas recientes" << endl;
					for(auto& el : v) {
						cout << "    " << el << endl;
					}
				}

			} else if (operation == "deleteSong") {
				Cancion c;
				cin >> c;

				P.deleteSong(c);
			}


		} catch(exception& e) {
			cout << "ERROR " << operation << endl;
		}
	}


	return 0;
}