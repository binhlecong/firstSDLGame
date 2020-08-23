#include "Vector2D.h"
#include <iostream>

Vector2D::Vector2D()
{
	this->setZero();
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2D& Vector2D::add(const Vector2D& vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector2D& Vector2D::subtract(const Vector2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector2D& Vector2D::multiply(const Vector2D& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

Vector2D& Vector2D::divide(const Vector2D& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}

Vector2D operator+(const Vector2D& v1, const Vector2D& v2)
{
	return Vector2D(v1.x + v2.x, v1.y + v2.y);
}

Vector2D operator-(const Vector2D& v1, const Vector2D& v2)
{
	return Vector2D(v1.x - v2.x, v1.y - v2.y);
}

Vector2D operator*(const Vector2D& v1, const Vector2D& v2)
{
	return Vector2D(v1.x * v2.x, v1.y * v2.y);
}

Vector2D operator/(const Vector2D& v1, const Vector2D& v2)
{
	return Vector2D(v1.x / v2.x, v1.y / v2.y);
}

Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	return (*this).add(vec);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	return (*this).add(vec);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	return (*this).add(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	return (*this).add(vec);
}

Vector2D& Vector2D::operator*(const int& i)
{
	this->x *= i;
	this->y *= i;
	return *this;
}

void Vector2D::setZero()
{
	this->x = 0.0f;
	this->y = 0.0f;
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
{
	stream << '<' << vec.x << ", " << vec.y << '>';
	return stream;
}