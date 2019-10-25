#include "Scene.h"

#include "ShaderEyelight.h"
#include "ShaderPhong.h"
#include "PrimTriangle.h"


void CScene::ParseOBJ(const std::string& fileName)
{
	std::cout << "Parsing OBJFile : " << fileName << std::endl;

	std::shared_ptr<IShader> pShader = std::make_shared<CShaderEyelight>(RGB(1, 1, 1));
	// --- PUT YOUR CODE HERE ---

	std::vector<Vec3f> vertex ;
	vertex.push_back(0);
	Vec3f temp1,temp2;

	std::ifstream file(fileName);
	if(!file.is_open())
	{
		std::cerr << "Error opening file\n";
		exit(1);
	}
	std::string line; // will be used to read each line
	// Reading the OBJ file
	while(std::getline(file, line)){
			if(line[0]== 'v'){
				std::istringstream a(line.substr(2));
				// read the three values
				a >> temp1[0] >> temp1[1] >> temp1[2];
				vertex.push_back(temp1*100);
				break;
			}
			if(line[0] == 'f'){
				std::istringstream a(line.substr(2));
				// read the three values
				a >> temp2[0] >> temp2[1] >> temp2[2];
				this->Add(std::make_shared<CPrimTriangle>(vertex[temp2[0]], vertex[temp2[1]], vertex[temp2[2]], pShader));
				break;
			}
	}
	file.close();
	std::cout << "Finished Parsing" << std::endl;
    
}