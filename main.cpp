/***************************************
	CONWAY'S GAME OF LIFE
	AUTHOR: Michael Abebe
	@nil_leo
	2011 E.C	2019 G.C	
****************************************/
#define OLC_PGE_APPLICATION

#include <array>
#include <ctime>
#include <iostream>

#include <stdlib.h>
#include <windows.h>

#include "olcPixelGameEngine.h"

constexpr int cols = 100;
constexpr int rows = 100;

using grid_t = std::array< std::array< bool, cols>, rows>;

void init_empty(grid_t& grd) {
	for(auto &i : grd)	std::memset(i.begin(), 0, cols * sizeof(bool));
}
void init_rand(grid_t& grd) {
	for(auto &i : grd)	for(auto &j : i)	j = rand() % 2;
}
void copy_grid(grid_t & src, grid_t & dst) {
	int x = 0;
	for(auto i : src)
		std::copy(i.begin(), i.end(), dst[x++].begin());
}
int get_surr_count(grid_t & grd, int h, int k) {
	int r_strt	= (h == 0 ? 0 : -1);
	int r_end	= (h == rows-1 ? 0 : 1);

	int c_strt	= (k == 0 ? 0 : -1);
	int c_end	= (k == cols-1 ? 0 : 1);

	int count = 0;

	for(int i = r_strt; i <= r_end; ++i)
		for(int j = c_strt; j <= c_end; ++j)
			count += (grd[h + i][k + j] ? 1 : 0);

	return count - int( grd[ h ][ k ] );
}
void evolve(grid_t & frnt, grid_t & back) {
	for(int i=0; i < rows; ++i) {
		for(int j=0; j < cols; ++j) {
			int x = get_surr_count(frnt, i, j);
			if(x == 2)
				back[ i ][ j ] = frnt[ i ][ j ];
			else if(x == 3)
				back[ i ][ j ] = true;
			else if(x > 3 || x < 2)
				back[ i ][ j ] = false;
		}
	}
}

class game_of_life: public olc::PixelGameEngine {
private:
	grid_t grd[ 2 ];
	grid_t * grd_f = nullptr;
	grid_t * grd_b = nullptr;

	bool front = false;
public:
	game_of_life() {
		sAppName = "Game of Life";
	}
	bool OnUserCreate() override {
		srand(time(nullptr));
		init_rand(grd[0] );
		copy_grid(grd[ 0 ], grd[ 1 ]);
		return true;
	}
	bool OnUserUpdate(float felapsed) override {
		grd_f = &grd[ front ];
		grd_b = &grd[ front ^ true ];

		// print_grid(grd_f);
		for( auto i=0; i < cols; ++i)
			for( auto j=0; j < rows; ++j)
				Draw(i, j,
					((*grd_f)[ j ][ i ] ? olc::WHITE : olc::BLACK));

		evolve(*grd_f, *grd_b);

		front ^= true;
		Sleep(100);

		if( GetKey(olc::Key::R).bPressed)
			init_rand( *grd_b);

		return true;
	}
};

int main() {
	game_of_life gm;
	if( gm.Construct( cols, rows, 5, 5))
		gm.Start();
	return 0;
}