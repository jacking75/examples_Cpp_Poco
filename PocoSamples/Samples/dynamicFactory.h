#pragma once

#include <Poco/DynamicFactory.h>
#include <Poco/TypeList.h>
#include <Poco/SharedPtr.h>

#include <string>


enum EShapeType
{
	eTriangle = 0
	, eRectangle
	, eOval
	, eNumShapes
};

const std::string kShapeNames[] =
{
	"Triangle"
,	"Rectangle"
,	"Oval"
};

class Shape
{
public:
	Shape(){ }

	virtual ~Shape() {}
	
	virtual void draw(void) = 0;

protected:
	void draw(const std::string& str)
	{
		std::cout << "Shape" << std::endl;
	}
};

class TriangleShape : public Shape
{
public:
	void draw(void)
	{
		std::cout << "Triangle" << std::endl;
	}
};

class RectangleShape : public Shape
{
public:
	void draw(void)
	{
		std::cout << "Rectangle" << std::endl;
	}
};

class OvalShape : public Shape
{
public:
	void draw(void)
	{
		std::cout << "Oval" << std::endl;
	}
};

//typedef Poco::TypeListType<
//	TriangleShape
//	, RectangleShape
//	, OvalShape
//>::HeadType ShapeTypeList;
//
//template<EShapeType N>
//void RegisterClass(Poco::DynamicFactory<Shape>& shapeFactory)
//{
//	typedef typename Poco::TypeGetter<N, ShapeTypeList>::HeadType	ShapeType;
//	shapeFactory.registerClass<ShapeType>(kShapeNames[N]);
//	RegisterClass<static_cast<EShapeType>(N + 1)>(shapeFactory);	// recursive call
//}
//
//template<>
//void RegisterClass<eOval>(Poco::DynamicFactory<Shape>& shapeFactory)
//{
//	typedef Poco::TypeGetter<eOval, ShapeTypeList>::HeadType	ShapeType;
//	shapeFactory.registerClass<ShapeType>(kShapeNames[eOval]);
//}

void RegisterClass(Poco::DynamicFactory<Shape>& shapeFactory)
{
	//typedef Poco::TypeGetter<eOval, ShapeTypeList>::HeadType	ShapeType;
	shapeFactory.registerClass<TriangleShape>("TriangleShape");
	shapeFactory.registerClass<RectangleShape>("RectangleShape");
	shapeFactory.registerClass<OvalShape>("OvalShape");
}

void Sample_DynamicFactory()
{
	Poco::DynamicFactory<Shape> shapeFactory;

	RegisterClass(shapeFactory);


	auto shape1 = shapeFactory.createInstance("TriangleShape");
	shape1->draw();

	auto shape2 = shapeFactory.createInstance("RectangleShape");
	shape2->draw();

	auto shape3 = shapeFactory.createInstance("OvalShape");
	shape3->draw();
}