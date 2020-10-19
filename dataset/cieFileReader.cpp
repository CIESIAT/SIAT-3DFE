#include<iostream>
#include<fstream>
#include<vector>
#include<array>
using namespace std;
struct  VertItem {
	union {
		struct {
			std::array<float, 3> vert; 
			int : 8;
			std::array<float, 3> norm;
			int : 8;
			std::array<std::array<float, 2>, 4> vts;//Texture coordinate of the vertices 
		};
	};
};
//face_ex is the blendshape factors
// fmi is the index of the landmarks.
void loadDtStream(std::string fileName, std::vector<VertItem> &verts, std::vector<std::array<float, 4> >& faces,
	std::vector<std::array<int, 4> > &faces_ex, std::vector<int>& fmi) {
	std::ifstream file;
	file.open(fileName, std::ifstream::binary);
	if (!file.is_open()) return;
	unsigned int v_size[4] = {};
	file.read((char *)v_size, 4 * sizeof(unsigned int));
	verts.resize(v_size[0]);
	faces.resize(v_size[1]);
	faces_ex.resize(v_size[2]);
	fmi.resize(v_size[3]);
	file.read((char *)verts.data(), verts.size() * sizeof(verts[0]));
	file.read((char *)faces.data(), faces.size() * sizeof(faces[0]));
	file.read((char *)faces_ex.data(), faces_ex.size() * sizeof(faces_ex[0]));
	file.read((char *)fmi.data(), fmi.size() * sizeof(fmi[0]));
	file.close();
}

int main()
{
	std::vector<VertItem> verts;
	std::vector<std::array<float, 4> > faces;
	std::vector<std::array<int, 4> > faces_ex;
	std::vector<int> fmi;
	loadDtStream("model.cie", verts, faces, faces_ex, fmi);
	return 0;
}
