//
// Created by Denis Wagner on 1/16/19.
//

#ifndef PONG_SFMLMATH_HPP
#define PONG_SFMLMATH_HPP

#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace sf
{
    static const auto PI = acos( -1 );

    /*
     * Vector addition
     */
    template <typename T>
    T operator+( const T& vec1, const T& vec2 )
    {
        const auto newX = vec1.x + vec2.x;
        const auto newY = vec1.y + vec2.y;

        return T( newX, newY );
    }

    /*
     * Vector subtraction
     */
    template <typename T>
    T operator-( const T& vec1, const T& vec2 )
    {
        const auto newX = vec1.x - vec2.x;
        const auto newY = vec1.y - vec2.y;

        return T( newX, newY );
    }

    /*
     * Scalar multiplication
     */
    template <typename T, typename U>
    T operator*( const T& vec, U scalar )
    {
        const auto newX = vec.x * scalar;
        const auto newY = vec.y * scalar;

        return T( newX, newY );
    }

    /*
     * Scalar multiplication
     */
    template <typename U, typename T>
    T operator*( U scalar, const T& vec )
    {
        const auto newX = vec.x * scalar;
        const auto newY = vec.y * scalar;

        return T( newX, newY );
    }

    /*
     * Returns the dot product of two given vectors
     */
    template <typename T>
    double operator*( const T& vec1, const T& vec2 )
    {
        return vec1.x * vec2.x + vec1.y * vec2.y;
    }

    /*
     * Returns the square of a given value
     */
    template <typename T>
    inline T sqr( T value )
    {
        return value * value;
    }

    /*
     * Converts radians to degrees
     */
    template <typename T>
    inline double radToDeg( T radians )
    {
        return radians * 180.0 / PI;
    }

    /*
     * Converts degrees to radian
     */
    template <typename T>
    inline double degToRad( T degree )
    {
        return degree / 180.0 * PI;
    }

    /*
     * Returns the length of a given vector
     */
    template <typename T>
    inline double getLength( const T& vec )
    {
        return sqrt( sqr( vec.x ) + sqr( vec.y ) );
    }

    /*
     * Returns an inverted vector
     */
    template <typename T>
    inline T getInverted( const T& vec )
    {
        return T( -vec.x, -vec.y );
    }

    /*
     * Inverts a given vector in-place
     */
    template <typename T>
    inline T& invert( T& vec )
    {
        vec.x = -vec.x;
        vec.y = -vec.y;

        return vec;
    }

    /*
     * Returns a normalized vector
     */
    template <typename T>
    inline T getNormalized( const T& vec )
    {
        const double length = getLength( vec );
        const double newX   = vec.x / length;
        const double newY   = vec.y / length;

        return T( newX, newY );
    }

    /*
     * Normalizes a given vector in-place
     */
    template <typename T>
    inline T& normalize( T& vec )
    {
        const double length = getLength( vec );
        vec.x /= length;
        vec.y /= length;

        return vec;
    }

    /*
     * Returns the angle of a given vector from 0 to 360° depending its direction on the unit circle
     */
    template <typename T>
    inline double getRotationAngle( const T& vec )
    {
        const T      normalizedVec = getNormalized( vec );
        const double angleXRad     = acos( normalizedVec.x );
        const double angleYRad     = asin( normalizedVec.y );
        double       angleRad;

        if ( angleYRad < 0 )
            angleRad = degToRad( 360 ) - angleXRad;
        else
            angleRad = angleXRad;

        return radToDeg( angleRad );
    }

    /*
     * Returns the angle in degrees between two given vectors
     */
    template <typename T>
    inline double getAngleBetween( const T& vec1, const T& vec2 )
    {
        const double angle = acos( ( vec1 * vec2 ) / ( getLength( vec1 ) * getLength( vec2 ) ) );

        return radToDeg( angle );
    }

    /*
     * Returns a vector rotated with a given angle in degrees
     */
    template <typename T>
    inline T getRotated( const T& vec, double angle )
    {
        const double angleRad = degToRad( -angle );
        const double newX     = vec.x * cos( angleRad ) - vec.y * sin( angleRad );
        const double newY     = vec.x * sin( angleRad ) + vec.y * cos( angleRad );

        return T( newX, newY );
    }

    /*
     * Rotates a vector in-place with a given angle in degrees
     */
    template <typename T>
    inline T& rotate( T& vec, double angle )
    {
        const double angleRad = degToRad( -angle );
        float x = vec.x;
        float y = vec.y;
        
        vec.x = x * cos( angleRad ) - y * sin( angleRad );
        vec.y = x * sin( angleRad ) + y * cos( angleRad );

        return vec;
    }

    // ADDED FUNCTION BY AHMED BINEURO
     //Gets normalized vector pointing at angle in degrees
    inline sf::Vector2f getAbsoluteRotated(float angle)
    {
        return sf::Vector2f(cos(degToRad(angle)), sin(degToRad(angle)));
    }

    inline void clamp(sf::Vector2f& v, float min, float max)
    {
        float mag = sf::getLength(v);
        if (mag > max)
        {
            sf::normalize(v);
            v *= max;
        }
        else if (min > mag) {
            sf::normalize(v);
            v *= min;
        }
    }

    template <typename T>
    void clamp(T & f, T min, T max)
    {
        if (f > max)
        {
            f = max;
        }
        else if (min > f) {
            f = min;
        }
    }

    template <typename T>
    T getClamped(T f, T min, T max)
    {
        if (f > max)
        {
            f = max;
        }
        else if (min > f) {
            f = min;
        }
        return f;
    }

    inline sf::Vector2f getClamped(sf::Vector2f v, float min, float max)
    {
        float mag = getLength(v);
        sf::Vector2f output = sf::getNormalized(v);
        if (mag > max)
        {
            output *= max;
        }
        else if (min > mag) {
            output *= min;
        }
        else output *= mag;
        return output;
    }

    inline float lerp(float min, float max, float t)
    {
        return min + (max - min) * t;
    }
    inline sf::Color mix(sf::Color c1, sf::Color c2, float t)
    {
        sf::Color output;
        output.r = floor(lerp(float(c1.r), float(c2.r), t));
        output.g = floor(lerp(float(c1.g), float(c2.g), t));
        output.b = floor(lerp(float(c1.b), float(c2.b), t));
        output.a = floor(lerp(float(c1.a), float(c2.a), t));
        return output;
    }

}
#endif //PONG_SFMLMATH_HPP
