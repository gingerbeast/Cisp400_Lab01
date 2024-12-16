#include "Particle-2.h"

Particle::Particle(RenderTarget& target, int numPoints, Vector2i mouseClickPosition)
    : m_numPoints(numPoints), m_ttl(TTL), m_vx(0), m_vy(0), m_radiansPerSec(M_PI / 2), m_centerCoordinate(mouseClickPosition)
{
    m_A = Matrix(2, m_numPoints);

    // Initialize the points in a circle
    float radius = 50.0f; // Initial particle radius
    for (int i = 0; i < m_numPoints; i++)
    {
        double angle = 2.0 * M_PI * i / m_numPoints;
        m_A(0, i) = radius * cos(angle) + m_centerCoordinate.x;
        m_A(1, i) = radius * sin(angle) + m_centerCoordinate.y;
    }

    m_color1 = Color::Red;
    m_color2 = Color::Yellow;
}

void Particle::draw(RenderTarget& target, RenderStates states) const
{
    VertexArray triangleFan(TriangleFan, m_numPoints + 2);

    triangleFan[0].position = m_centerCoordinate;
    triangleFan[0].color = m_color1;

    for (int i = 0; i < m_numPoints; i++)
    {
        triangleFan[i + 1].position = Vector2f(m_A(0, i), m_A(1, i));
        triangleFan[i + 1].color = m_color2;
    }

    triangleFan[m_numPoints + 1].position = Vector2f(m_A(0, 0), m_A(1, 0));
    triangleFan[m_numPoints + 1].color = m_color2;

    target.draw(triangleFan, states);
}

void Particle::update(float dt)
{
    rotate(m_radiansPerSec * dt);
    scale(SCALE);
    m_ttl -= dt;
}

void Particle::rotate(double theta)
{
    RotationMatrix R(theta);
    m_A = R * m_A;
}

void Particle::scale(double c)
{
    ScalingMatrix S(c);
    m_A = S * m_A;
}

void Particle::translate(double xShift, double yShift)
{
    TranslationMatrix T(xShift, yShift, m_A.getCols());
    m_A = T + m_A;
}
