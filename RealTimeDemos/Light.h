#include <glm\glm\glm.hpp>

class Light
{
private:
	glm::vec3 _position;
public:
	Light();
	glm::vec3& getPosition();
	void setPosition(glm::vec3& iPosition);
	~Light();
};

