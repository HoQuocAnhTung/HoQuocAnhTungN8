#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

#include <glew.h>
#include <freeglut.h>

#include <vector_matrix.h>


using namespace std;

typedef struct
{
	float XYZW[4];
	float RGBA[4];
} Vertex;

//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3
Vertex Vertices[] =
{
	// v0-v1-v2 (front)
	{ { 0.5f,	 0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	 0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	// v2-v3-v0
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	-0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	 0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },

	// v0-v3-v4 (right)
	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	-0.5f,   0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	-0.5f,  -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	// v4-v5-v0
	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	 0.5f,	-0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	 0.5f,   0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },

	// v0-v5-v6 (top)
	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	0.5f,	-0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	// v6-v1-v0
	{ { -0.5f,	 0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	0.5f,	 0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },

	// v1-v6-v7 (left)
	{ { -0.5f,	 0.5f,	 0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	0.5f,	-0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	-0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	// v7-v2-v1
	{ { -0.5f,	 -0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	0.5f,	 0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },

	// v7-v4-v3 (bottom)
	{ { -0.5f,	 -0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	-0.5f,	 0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	// v3-v2-v7
	{ { 0.5f,	 -0.5f,	 0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	-0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },

	// v4-v7-v6 (back)
	{ { 0.5f,	 -0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	-0.5f,	-0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	// v6-v5-v4
	{ { -0.5f,	 0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	-0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } }
};


class MatrixStack {
	int    index;
	int    size;
	mat4* matrices;

public:
	MatrixStack(int numMatrices = 32) :index(0), size(numMatrices)
	{
		matrices = new mat4[numMatrices];
	}

	~MatrixStack()
	{
		delete[]matrices;
	}

	// phép toán đẩy vào
	mat4& push(const mat4& m) {
		assert(index + 1 < size);
		matrices[index++] = m;
		return matrices[index];
	}

	// phép toán lấy ra
	mat4& pop(void) {
		assert(index - 1 >= 0);
		index--;
		return matrices[index];
	}
};

MatrixStack  mvstack;

const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].XYZW);

int
CurrentWidth = 1080,
CurrentHeight = 1080;

GLuint
VaoId,
VboId,
VertexShaderId,
FragmentShaderId,
ProgramId;

mat4 model_mat_cpp;
int model_mat_location;

mat4 view_mat_cpp;
int view_mat_location;
float alphaQuat = 0.0f;
float otodichuyen2 = 0.4f;


// ---------------------------------------------------------------------------	
string ReadShaderSourceFile(string fileName) {
	fstream reader(fileName.c_str());
	string line;
	string code = "";
	while (getline(reader, line)) {
		code += line + "\n";
	}
	reader.close();
	return code;
}

// ---------------------------------------------------------------------------	
void CreatVaoVbo()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}
// ---------------------------------------------------------------------------	
void CreatShaders()
{
	string vertexSrc = ReadShaderSourceFile("./vs.shader");
	string fragmentSrc = ReadShaderSourceFile("./fs.shader");

	const GLchar* VertexShader = vertexSrc.c_str();
	const GLchar* FragmentShader = fragmentSrc.c_str();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);

}
// ---------------------------------------------------------------------------	
void CloseFunc()
{
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}

// ---------------------------------------------------------------------------	
void flat()
{
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * scale(vec3(1.4, 0.001, 1.4));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.8f, 0.662f, 0.678f, 1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void drawGrass()
{
	// Kích thước bụi cỏ = 1/5 kích thước của mặt đất
	float grassSize = 1.5f / 4.0f; // Tỷ lệ kích thước của bụi cỏ

	// Vị trí góc trên cùng của mặt đất
	vec3 grassPosition = vec3(0.5f, 0.01f, 0.5f); // Lấy vị trí góc trên cùng (y = 0.001f + một nửa chiều cao của bụi cỏ)

	// Vẽ bụi cỏ tại vị trí này
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * translate(grassPosition) * scale(vec3(grassSize, 0.01, grassSize));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

	// Màu xanh cho bụi cỏ
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.1f, 0.6f, 0.1f, 1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void road1()
{
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * scale(vec3(0.30, 0.021, 1.4));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.5f, 0.5f, 0.5f, 1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void drawLaneMarkers()
{
	// Kích thước và khoảng cách giữa các vạch phân làn
	float laneWidth = 0.05f; // Độ rộng của vạch phân làn
	float laneSpacing = 0.2f; // Khoảng cách giữa các vạch phân làn
	float roadLength = 1.2f; // Chiều dài của con đường

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 1.0f, 1.0f, 1.0f, 1.0f); // Màu trắng cho vạch phân làn
	int count = 0;
	// Vẽ các vạch phân làn song song với con đường
	float currentPosition = -roadLength / 2; // Vị trí bắt đầu của vạch phân làn
	while (currentPosition < roadLength / 2) // Duyệt dọc theo chiều dài con đường
	{	
		if (count == 3) {
			currentPosition += laneSpacing;
			count++;
			continue;
		}
		mat4 laneInstance = identity_mat4();
		laneInstance = model_mat_cpp * translate(vec3(0.0f, 0.011f, currentPosition)) * scale(vec3(laneWidth, 0.002f, 0.1f));
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, laneInstance.m);

		glDrawArrays(GL_TRIANGLES, 0, 36); // Vẽ một vạch phân làn

		// Di chuyển đến vị trí vạch phân làn tiếp theo
		currentPosition += laneSpacing;
		count++;
	}
}
void road2()
{
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * scale(vec3(1.4, 0.021, 0.30));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.5f, 0.5f, 0.5f, 1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

float scale_factor = 15.0f;

void duiQUAT()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(1.2f / scale_factor, 0.5f / scale_factor, 1.2f / scale_factor)) * translate(vec3(0.0, 13.9 / scale_factor, 0.0));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.5f, 0.7f, 0.6f, 1.0f); // Màu xanh lam

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void trucQUAT()
{
	mvstack.push(model_mat_cpp);
	mat4 instance = identity_mat4();

	for (int i = 0; i < 360; i+=10) {
		instance = scale(vec3(0.5f / scale_factor, 7.0f / scale_factor, 0.2f / scale_factor)) * translate(vec3(0.0, -0.4f / scale_factor, 0.0))*rotate_y(i);

		mat4 model_MS = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
		GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
		glUniform4f(colorLocation, 0.9f, 0.9f, 0.8f, 1.0f); // Màu đỏ nhạt
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}


	model_mat_cpp = mvstack.pop();
}

void tamQUAT()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(0.9f / scale_factor, 0.2f / scale_factor, 0.9f / scale_factor)) * translate(vec3(0.0, 24.5 / scale_factor, 0.0));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.5f, 0.5f, 0.6f, 1.0f); // Màu xanh lam

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void canhQUATTRAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(4.0f / scale_factor, 0.15f / scale_factor, 0.7f / scale_factor)) * translate(vec3(0.6 / scale_factor, 32.5 / scale_factor, 0.0));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.5f, 0.5f, 0.6f, 1.0f); // Màu xanh lam


	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void canhQUATPHAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(4.0f / scale_factor, 0.15f / scale_factor, 0.7f / scale_factor)) * translate(vec3(-0.6 / scale_factor, 32.5 / scale_factor, 0.0));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.5f, 0.5f, 0.6f, 1.0f); // Màu xanh lam


	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void canhQUATTRUOC()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(0.7f / scale_factor, 0.15f / scale_factor, 4.0f / scale_factor)) * translate(vec3(0.0, 32.5 / scale_factor, 0.0)) * rotate_y(90);

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.5f, 0.5f, 0.6f, 1.0f); // Màu xanh lam



	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void canhQUATSAU()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(0.7f / scale_factor, 0.15f / scale_factor, 4.0f / scale_factor)) * translate(vec3(0.0, 32.5 / scale_factor, 0.0)) * rotate_y(-90);

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.5f, 0.5f, 0.6f, 1.0f); // Màu xanh lam

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
// ---------------------------------------------------------------------------


void CAYCOI(float x, float z)
{
	mvstack.push(model_mat_cpp);

	// Thân cây (hình trụ dọc)
	float trunk_height = 0.15f;   // Chiều cao thân cây
	float trunk_radius = 0.01f;   // Bán kính thân cây
	model_mat_cpp = model_mat_cpp * translate(vec3(x, trunk_height / 2, z)); // Đặt thân cây
	mat4 instance = model_mat_cpp * scale(vec3(trunk_radius, trunk_height, trunk_radius));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.4f, 0.25f, 0.1f, 1.0f); // Màu nâu cho thân cây
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Tán cây (hình cầu trên đỉnh)
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0f, trunk_height / 2, 0.0f)); // Đỉnh thân cây


	for (int i = 0; i <= 360; i += 10) {
		for (int j = 0; j <= 360; j += 10) {
			model_mat_cpp = model_mat_cpp * rotate_y(j) * rotate_z(i); // Đẩy bóng đèn lên một chút

			// Bóng đèn (hình cầu)
			instance = model_mat_cpp * scale(vec3(0.05f, 0.05f, 0.05f));  // Tán cây dạng cầu
			glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

			glUniform4f(colorLocation, 0.1f, 0.6f, 0.2f, 1.0f); // Màu xanh lá cho tán cây
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}

	// Chi tiết tán cây: chia tán thành nhiều phần nhỏ hơn (các hình cầu)
	model_mat_cpp = model_mat_cpp * translate(vec3(-0.03f, 0.02f, 0.0f)); // Đẩy lại một chút để tránh tán cây bị nâng cao


	for (int i = 0; i <= 360; i += 10) {
		for (int j = 0; j <= 360; j += 10) {
			// Bóng đèn (hình cầu)
			model_mat_cpp = model_mat_cpp * rotate_y(j) * rotate_z(i); // Đẩy bóng đèn lên một chút

			instance = model_mat_cpp * scale(vec3(0.03f, 0.03f, 0.03f));
			glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);
			glUniform4f(colorLocation, 0.1f, 0.7f, 0.3f, 1.0f); // Màu xanh lá sáng cho các phần nhỏ của tán cây
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
	// Thêm nhiều phần cho tán cây: Lặp lại với nhiều vị trí và kích thước khác nhau
	model_mat_cpp = model_mat_cpp * translate(vec3(0.06f, 0.0f, 0.0f)); // Dịch ra ngoài một chút (chỉnh lại trục y)


	for (int i = 0; i <= 360; i += 10) {
		for (int j = 0; j <= 360; j += 10) {
			// Bóng đèn (hình cầu)
			model_mat_cpp = model_mat_cpp * rotate_y(j) * rotate_z(i); // Đẩy bóng đèn lên một chút

			instance = model_mat_cpp * scale(vec3(0.04f, 0.04f, 0.04f)); // Tăng kích thước cho một phần khác
			glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);
			glUniform4f(colorLocation, 0.1f, 0.5f, 0.2f, 1.0f); // Màu xanh lá khác cho các phần của tán cây
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
	// Thêm một số phần nhỏ khác để tán cây trông tự nhiên hơn
	model_mat_cpp = model_mat_cpp * translate(vec3(-0.05f, 0.01f, 0.05f)); // Dịch ra ngoài một chút (tránh nâng cao quá mức)
	for (int i = 0; i <= 360; i += 10) {
		for (int j = 0; j <= 360; j += 10) {
			// Bóng đèn (hình cầu)
			model_mat_cpp = model_mat_cpp * rotate_y(j) * rotate_z(i); // Đẩy bóng đèn lên một chút
			instance = model_mat_cpp * scale(vec3(0.03f, 0.03f, 0.03f));
			glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);
			glUniform4f(colorLocation, 0.2f, 0.6f, 0.2f, 1.0f); // Một màu khác cho tán cây
			glDrawArrays(GL_TRIANGLES, 0, 36);

		}
	}

	model_mat_cpp = mvstack.pop();
}
void XEOTAI(float x, float z)
{
	mvstack.push(model_mat_cpp);

	// Kích thước chung
	float car_height = 0.05f;  // Chiều cao thân xe

	// Đầu xe (cabin)
	float cabin_length = 0.1f;  // Chiều dài cabin
	float cabin_width = 0.08f;  // Chiều rộng cabin
	model_mat_cpp = model_mat_cpp * translate(vec3(x, 0.01f + car_height / 2 + 0.02, z)) * rotate_y(90.0f);
	mat4 instance = scale(vec3(cabin_length, car_height, cabin_width));
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
	glUniform4f(colorLocation, 0.8f, 0.2f, 0.2f, 1.0f); // Màu đỏ cho cabin
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Đèn pha
	float headlight_radius = 0.01f; // Bán kính đèn pha
	float headlight_depth = 0.01f;  // Độ sâu đèn pha
	vec3 headlight_positions[2] = {
		vec3(cabin_length / 2 + headlight_depth / 2, 0.02f, cabin_width / 2 - headlight_radius),
		vec3(cabin_length / 2 + headlight_depth / 2, 0.02f, -cabin_width / 2 + headlight_radius)
	};
	for (int i = 0; i < 2; i++)
	{
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(headlight_positions[i]);
		instance = scale(vec3(headlight_radius, headlight_radius, headlight_depth));
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
		glUniform4f(colorLocation, 1.0f, 1.0f, 0.8f, 1.0f); // Màu vàng nhạt cho đèn pha
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model_mat_cpp = mvstack.pop();
	}

	// Lưới tản nhiệt
	float grill_width = 0.06f;  // Chiều rộng lưới tản nhiệt
	float grill_height = 0.02f; // Chiều cao lưới tản nhiệt
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(cabin_length / 2 + 0.005f, 0.01f, 0.0f));
	instance = scale(vec3(0.005f, grill_height, grill_width));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
	glUniform4f(colorLocation, 0.3f, 0.3f, 0.3f, 1.0f); // Màu xám đậm cho lưới tản nhiệt
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();

	// Logo
	float logo_size = 0.01f; // Kích thước logo
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(cabin_length / 2 + 0.006f, 0.03f, 0.0f));
	instance = scale(vec3(logo_size, logo_size, 0.002f));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
	glUniform4f(colorLocation, 1.0f, 1.0f, 1.0f, 1.0f); // Màu trắng cho logo
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();

	// Thùng xe
	float box_length = 0.2f;  // Chiều dài thùng xe
	float box_width = 0.09f;  // Chiều rộng thùng xe
	float box_height = 0.07f; // Chiều cao thùng xe
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-cabin_length / 2 - box_length / 2, car_height / 2, 0.0f));
	instance = scale(vec3(box_length, box_height, box_width));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
	glUniform4f(colorLocation, 0.6f, 0.6f, 0.6f, 1.0f); // Màu bạc cho thùng xe
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();

	// Bánh xe (6 bánh)
	float wheel_radius = 0.02f; // Bán kính bánh xe
	float wheel_width = 0.03f;  // Bề rộng bánh xe
	vec3 wheel_positions[6] = {
		vec3(-0.03f + cabin_length / 2, -car_height / 2, cabin_width / 2),   // Bánh trước phải
		vec3(-0.03f + cabin_length / 2, -car_height / 2, -cabin_width / 2),  // Bánh trước trái
		vec3(-0.03f, -car_height / 2, cabin_width / 2),               // Bánh giữa phải
		vec3(-0.03f, -car_height / 2, -cabin_width / 2),              // Bánh giữa trái
		vec3(-0.03f -cabin_length / 2 - box_length / 2, -car_height / 2, cabin_width / 2),   // Bánh sau phải
		vec3(-0.03f -cabin_length / 2 - box_length / 2, -car_height / 2, -cabin_width / 2)   // Bánh sau trái
	};

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 360; j += 20)
		{
			mvstack.push(model_mat_cpp);
			model_mat_cpp = model_mat_cpp * translate(wheel_positions[i]) * rotate_z(j);
			instance = scale(vec3(wheel_radius, wheel_width, wheel_radius));
			glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
			glUniform4f(colorLocation, 0.1f, 0.1f, 0.1f, 1.0f); // Màu đen cho bánh xe
			glDrawArrays(GL_TRIANGLES, 0, 36);
			model_mat_cpp = mvstack.pop();
		}
	}

	// Kính chắn gió
	float windshield_height = 0.03f; // Chiều cao kính chắn gió
	float windshield_width = 0.06f;  // Chiều rộng kính chắn gió
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.02f, car_height / 2 + windshield_height / 2, 0.0f));
	instance = scale(vec3(0.005f, windshield_height, windshield_width));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
	glUniform4f(colorLocation, 0.6f, 0.8f, 1.0f, 0.8f); // Màu kính trong suốt
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();

	for (float i = 0.02; i <= 0.1; i+= 0.02) {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(-i + 0.02f, car_height / 2 + windshield_height / 2, 0.0f));
		instance = scale(vec3(0.02f, windshield_height, windshield_width));
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
		glUniform4f(colorLocation, 0.6f, 0.2f, 0.2f, 1.0f); // Màu kính trong suốt
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model_mat_cpp = mvstack.pop();
	}


	// Gương chiếu hậu (2 bên)
	float mirror_width = 0.005f;  // Bề rộng gương
	float mirror_height = 0.015f; // Chiều cao gương
	float mirror_depth = 0.01f;  // Độ dày gương
	vec3 mirror_positions[2] = {
		vec3(-0.04 + cabin_length / 2 + mirror_depth / 2,0.02 + car_height / 2, cabin_width / 2 + mirror_width / 2),   // Gương phải
		vec3(-0.04 + cabin_length / 2 + mirror_depth / 2,0.02 + car_height / 2, -cabin_width / 2 - mirror_width / 2)  // Gương trái
	};

	for (int i = 0; i < 2; i++)
	{
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(mirror_positions[i]);
		instance = scale(vec3(mirror_width, mirror_height, mirror_depth));
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
		glUniform4f(colorLocation, 0.9f, 0.9f, 0.9f, 1.0f); // Màu xám cho gương
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model_mat_cpp = mvstack.pop();
	}

	model_mat_cpp = mvstack.pop();
}




void DisplayFunc(void)
{
	vec3	eye(0.1f, -0.1f, 0.1f), //****************************************
			at(0.0f, 0.0f, 0.0f),
			up(0.0f, 1.0f, 0.0f);

	view_mat_cpp = lookat(eye, at, up);
	view_mat_location = glGetUniformLocation(ProgramId, "view_mat_shader");
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat_cpp.m);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.266, 0.537, 0.894, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");

	model_mat_cpp = identity_mat4();


	flat();
	road1();
	drawGrass();
	road2();
	drawLaneMarkers();

	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * rotate_y(90);
	drawLaneMarkers();
	model_mat_cpp = mvstack.pop();

	//chong chong
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.4f, 0.2f, 0.4f));
	trucQUAT();
	model_mat_cpp = model_mat_cpp * translate(vec3(0.01f, 0.18f, 0.0f))*rotate_x(-90) * rotate_y(alphaQuat);
	duiQUAT();
	tamQUAT();
	canhQUATTRAI();
	canhQUATPHAI();
	canhQUATTRUOC();
	canhQUATSAU();
	model_mat_cpp = mvstack.pop();

	CAYCOI(0.2, 0.2);
	CAYCOI(0.35, 0.2);
	CAYCOI(0.5, 0.2);
	CAYCOI(0.65, 0.2);
	CAYCOI(0.2, 0.35);
	CAYCOI(0.2, 0.5);
	CAYCOI(0.2, 0.65);

	XEOTAI(0.1f, otodichuyen2);




	glutSwapBuffers();
}
// ---------------------------------------------------------------------------	

void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;

	glViewport(0, 0, CurrentWidth, CurrentHeight);
}
// ---------------------------------------------------------------------------	
void IdleFunc(void)
{
	alphaQuat += 1.0f;
	if (alphaQuat > 360.0f) {
		alphaQuat -= 360.0f;
	}
	glutPostRedisplay();
}
// ---------------------------------------------------------------------------
void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'k':

		glutPostRedisplay();
		break;
	case 'K':

		glutPostRedisplay();
		break;
	case 't':

		glutPostRedisplay();
		break;
	case 'p':

		glutPostRedisplay();
		break;
	case 'v':
		otodichuyen2 += 0.01;
		if (otodichuyen2 > 0.4) otodichuyen2 = 0.4;  // Giới hạn trên
		break;
	case 'V':
		otodichuyen2 -= 0.01;
		if (otodichuyen2 < 0.0) otodichuyen2 = 0.0;   // Giới hạn dưới
		break;
	case 27:
		exit(EXIT_SUCCESS); break;
	}
}
// ---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Cube");

	glewExperimental = GL_TRUE;
	glewInit();

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutCloseFunc(CloseFunc);

	glutMainLoop();

	return 0;
}
// -------------------------------------