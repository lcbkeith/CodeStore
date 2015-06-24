#include <map>

template<class T>
class NamedObject
{
public:
	NamedObject(std::string& name, const T& value) :nameValue(name), objectValue(value)
	{

	}


	std::string& nameValue;
	const T objectValue;
};


void maintest()
{
	std::string newDog("Persephone");
	std::string oldDog("satch");
	NamedObject<int> p(newDog, 2);
	newDog = "aaaa";

	NamedObject<int> s(oldDog, 36);


	//p = s;
}