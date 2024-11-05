#include <iostream>
#include <cmath>
#include <utility>

// Length of Mathematical axises
#define WIDTH_M 40
#define HEIGHT_M 40

// Length of Graphical axises
#define WIDTH_G 200
#define HEIGHT_G 100

using namespace std;


pair<float,float> translate(float x, float y){
	
    float percent_x = (x+WIDTH_M/2)/WIDTH_M;
    float percent_y = (-y+HEIGHT_M/2)/HEIGHT_M;

	percent_x*=WIDTH_G;
	percent_y*=HEIGHT_G;
	
	pair<float,float> result;
	result.first=percent_x;
	result.second=percent_y;
	
    return result;
}

int main(){
	
	float x, y;
	
	cout << "Points in [-20,20]: " << endl;
	cout << "\tx: ";
	cin >> x;
	cout << "\ty: ";
	cin >> y;
	cout << endl << "You have introduced the point: (" << x << "," << y << ")" << endl;
	
	pair<float,float> new_coord = translate(x,y);
	
	cout << "New coordinates are: (" << new_coord.first << "," << new_coord.second << ")" << endl;

	return 0;
}
