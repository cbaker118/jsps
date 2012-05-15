// reading a complete binary file
#include <iostream>
#include <fstream>

using namespace std;

ifstream::pos_type size;
char * memblock;

unsigned short getValue(char c){
	return(unsigned short)((unsigned char)(c));
}

int main () {
	ifstream file ("logo.ppm", ios::in|ios::binary|ios::ate);
	if (file.is_open()){
		size = file.tellg();
		memblock = new char [size];
		file.seekg (0, ios::beg);
		file.read (memblock, size);
		file.close();

		//cout << "the complete file content is in memory";
		cout<<"colors = {"<<endl;
		bool firstPrint = true;
		int i,j,pixel_start,x_samples,y_samples,
			sample_size=10,
			x_pixels=899,
			y_pixels=574, 
			pixel_offset=54, 
			x_max_samples = x_pixels / sample_size, 
			y_max_samples = y_pixels / sample_size;
		
		for( i = 0 ;i<y_max_samples;i++){
			for(j=0;j<x_max_samples;j++){
				
				pixel_start = pixel_offset + i*sample_size*x_pixels*3 + j * sample_size * 3;
				if((getValue(memblock[pixel_start]) != 0 ||
					getValue(memblock[pixel_start+1]) != 0 ||
					getValue(memblock[pixel_start+2]) != 0)&&
					(getValue(memblock[pixel_start]) != 255 ||
					getValue(memblock[pixel_start+1]) != 255 ||
					getValue(memblock[pixel_start+2]) != 255)){

						if(!firstPrint){
							cout<<","<<endl;
						}
						firstPrint = false;
						cout<<"	'"<<j<<"x"<<i<<"': ["<<getValue(memblock[pixel_start])<<",";
						cout<<getValue(memblock[pixel_start+1])<<",";
						cout<<getValue(memblock[pixel_start+2])<<"]  /*at loc:"<<j * sample_size<<","<<i*sample_size<<"*/";
				}
			}
			
		}
		cout<<endl<<"};"<<endl;
		
		//for(i=20;i<70;i++){
		//	cout<<i<<": "<<getValue(memblock[i])<<", "<<memblock[i]<<endl;
		//}
		
		delete[] memblock;
	}
	else cout << "Unable to open file";
	return 0;
}